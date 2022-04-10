#include "Font.h"

#include <sstream>
#include <string>

#include "../Common/BinaryReader.h"
#include "../Common/BinaryWriter.h"
#include "../Common/Profiler.h"
#include "../IO/File.h"
#include "../Logger/Log.h"
#include "../Platform/FileSystem.h"
#include "Graphics.h"
#include "ImageFont.h"

#ifdef _WIN32
#undef CreateDirectory
#endif

namespace Altseed2 {

Glyph::Glyph()
    : textureSize_(Vector2I(0, 0)), textureIndex_(0), position_(Vector2I(0, 0)), size_(Vector2I(0, 0)), offset_(Vector2F(0, 0)), advance_(0.0f) {}
Glyph::Glyph(Vector2I textureSize, int32_t textureIndex, Vector2I position, Vector2I size, Vector2F offset, float advance)
    : textureSize_(textureSize), textureIndex_(textureIndex), position_(position), size_(size), offset_(offset), advance_(advance) {}

std::mutex Font::mtx;
std::shared_ptr<msdfgen::FreetypeHandle> Font::freetypeHandle_;

Font::Font(std::u16string path)
    : resources_(nullptr),
      fontHandle_(nullptr),
      ascent_(0),
      descent_(0),
      lineGap_(0),
      samplingSize_(0),
      file_(nullptr),
      textureSize_(Vector2I(Font::TextureSize, Font::TextureSize)),
      sourcePath_(path),
      isStaticFont_(true) {}

Font::Font(
        std::shared_ptr<Resources>& resources,
        std::shared_ptr<StaticFile>& file,
        std::shared_ptr<msdfgen::FontHandle> fontHandle,
        int32_t samplingSize,
        std::u16string path)
    : resources_(resources),
      fontHandle_(fontHandle),
      samplingSize_(samplingSize),
      file_(file),
      textureSize_(Vector2I(Font::TextureSize, Font::TextureSize)),
      sourcePath_(path),
      isStaticFont_(false) {
    msdfgen::FontMetrics metrics;
    msdfgen::getFontMetrics(metrics, fontHandle.get());
    ascent_ = static_cast<float>(metrics.ascenderY);
    descent_ = static_cast<float>(metrics.descenderY);
    emSize_ = static_cast<float>(metrics.emSize);
    lineGap_ = static_cast<float>(metrics.lineHeight);

    Log::GetInstance()->Info(LogCategory::Core, u"Font::Font: enSize={0}, ascent={1}, descent={2}, lineGap={3}", emSize_, ascent_, descent_, lineGap_);

    AddFontTexture();

    SetInstanceName(__FILE__);
}

Font::~Font() {
    std::lock_guard<std::mutex> lock(mtx);
    if (resources_ != nullptr && sourcePath_ != u"") {
        resources_->GetResourceContainer(ResourceType::Font)
                ->Unregister(isStaticFont_ ? sourcePath_ : Font::GetKeyName(sourcePath_.c_str(), samplingSize_));
        resources_ = nullptr;
    }
}

bool Font::Initialize() {
    std::shared_ptr<msdfgen::FreetypeHandle> freetypeHandle(msdfgen::initializeFreetype(), msdfgen::deinitializeFreetype);

    freetypeHandle_ = freetypeHandle;

    if (freetypeHandle_ == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::Initialize: failed to initialize freetype");
        return false;
    }

    return true;
}

void Font::Terminate() {
}

std::shared_ptr<Glyph> Font::GetGlyph(const int32_t character) {
    if (glyphs_.count(character)) {
        return glyphs_[character];
    } else if (GetIsStaticFont()) {
        std::string tmp;
        tmp += (char32_t)character;
        Log::GetInstance()->Warn(LogCategory::Core, u"Glyph for '{0}' character not found", tmp.c_str());

        return glyphs_[u'\0'];
    }

    AddGlyph(character);
    return glyphs_[character];
}

int32_t Font::GetKerning(const int32_t c1, const int32_t c2) {
    if (GetIsStaticFont()) {
        if (kernings_.count(std::make_pair(c1, c2)) != 0)
            return kernings_[std::make_pair(c1, c2)];
        else
            return 0;
    }

    double kern;
    if (!msdfgen::getKerning(kern, fontHandle_.get(), c1, c2)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::GetKerning: failed to get kerning");
        return 0;
    }

    return (float)kern;
}

const char16_t* Font::GetPath() const { return sourcePath_.c_str(); }

std::shared_ptr<Font> Font::LoadDynamicFont(const char16_t* path, int32_t samplingSize) {
    EASY_BLOCK("Altseed2(C++).Font.LoadDynamicFont");

    RETURN_IF_NULL(path, nullptr);

    const auto normalizedPath = FileSystem::NormalizePath(path);

    auto resources = Resources::GetInstance();
    if (resources == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"File is not initialized.");
        return nullptr;
    }

    const auto resourceKeyName = Font::GetKeyName(normalizedPath.c_str(), samplingSize);

    std::shared_ptr<Font> result = nullptr;

    {
        std::lock_guard<std::mutex> lock(mtx);

        result = std::dynamic_pointer_cast<Font>(
                resources->GetResourceContainer(ResourceType::Font)->Get(resourceKeyName));
        if (result != nullptr && result->GetRef() > 0 && !result->GetIsStaticFont()) {
            return result;
        }

        auto file = StaticFile::Create(normalizedPath.c_str());
        if (file == nullptr) {
            Log::GetInstance()->Error(
                    LogCategory::Core, u"Font::LoadDynamicFont: Failed to create file from '{0}'", utf16_to_utf8(normalizedPath).c_str());
            return nullptr;
        }

        std::shared_ptr<msdfgen::FontHandle> fontHandle(msdfgen::loadFontMemory(Font::freetypeHandle_.get(), (unsigned char*)file->GetData(), file->GetSize()), msdfgen::destroyFont);

        if (fontHandle == nullptr) {
            Log::GetInstance()->Error(LogCategory::Core, u"Font::LoadDynamicFont: Failed to initialize font '{0}'", utf16_to_utf8(normalizedPath).c_str());
            return nullptr;
        }

        result = MakeAsdShared<Font>(resources, file, fontHandle, samplingSize, normalizedPath);
        resources->GetResourceContainer(ResourceType::Font)
                ->Register(resourceKeyName, std::make_shared<ResourceContainer::ResourceInfomation>(result, normalizedPath));
    }

    result->AddGlyph('\0');

    return result;
}

std::shared_ptr<Font> Font::LoadStaticFont(const char16_t* path) {
    EASY_BLOCK("Altseed2(C++).Font.LoadStaticFont");

    RETURN_IF_NULL(path, nullptr);

    const auto normalizedPath = FileSystem::NormalizePath(path);
    const auto rawFilename = FileSystem::GetFileName(normalizedPath, false);

    auto resources = Resources::GetInstance();
    if (resources == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"File is not initialized.");
        return nullptr;
    }

    std::lock_guard<std::mutex> lock(mtx);

    auto cache = std::dynamic_pointer_cast<Font>(resources->GetResourceContainer(ResourceType::Font)->Get(normalizedPath));
    if (cache != nullptr && cache->GetRef() > 0 && cache->GetIsStaticFont()) {
        return cache;
    }

    auto file = StaticFile::Create(normalizedPath.c_str());
    if (file == nullptr) return nullptr;

    BinaryReader reader(file);

    auto font = MakeAsdShared<Font>(normalizedPath);
    font->resources_ = resources;
    font->file_ = file;
    reader.Get(&font->samplingSize_);
    reader.Get(&font->ascent_);
    reader.Get(&font->descent_);
    reader.Get(&font->lineGap_);
    reader.Get(&font->emSize_);
    reader.Get(&font->textureSize_);

    const auto textureCount = reader.Get<int32_t>();
    for (size_t i = 0; i < textureCount; i++) {
        auto texturePath = FileSystem::GetParentPath(normalizedPath) + u"/" + rawFilename + u"/Texture" + utf8_to_utf16(std::to_string(i)) + u".png";
        auto texture = Texture2D::Load(texturePath.c_str());
        if (texture == nullptr) return nullptr;
        font->textures_.push_back(texture);
    }

    const auto glyphCount = reader.Get<int32_t>();
    for (size_t i = 0; i < glyphCount; i++) {
        const auto character = reader.Get<int32_t>();
        if (reader.Get<bool>()) continue;
        const auto glyph = reader.GetAsShared<Glyph>();
        font->glyphs_[character] = glyph;

        for (size_t l = 0; l < glyphCount; l++) {
            font->kernings_[std::make_pair(reader.Get<int32_t>(), reader.Get<int32_t>())] = reader.Get<int32_t>();
        }
    }

    return font;
}

std::shared_ptr<Font> Font::CreateImageFont(std::shared_ptr<Font> baseFont) {
    RETURN_IF_NULL(baseFont, nullptr);
    return std::static_pointer_cast<Font>(MakeAsdShared<ImageFont>(baseFont));
}

bool Font::GenerateFontFile(const char16_t* dynamicFontPath, const char16_t* staticFontPath, int32_t samplingSize, const char16_t* characters) {
    EASY_BLOCK("Altseed2(C++).Font.GenerateFontFile");

    RETURN_IF_NULL(dynamicFontPath, false);
    RETURN_IF_NULL(staticFontPath, false);
    RETURN_IF_NULL(characters, false);

    const auto nDynamicFontPath = FileSystem::NormalizePath(dynamicFontPath);
    const auto nStaticFontPath = FileSystem::NormalizePath(staticFontPath);
    const auto staticFontRawFilename = FileSystem::GetFileName(nStaticFontPath, false);

    auto parentDir = FileSystem::GetParentPath(FileSystem::GetAbusolutePath(nStaticFontPath));
    if (!FileSystem::GetIsDirectory(parentDir)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::GenerateFontFile: The output directory cannot be accessed.");
        return false;
    }
    BinaryWriter writer;

    auto font = Font::LoadDynamicFont(nDynamicFontPath.c_str(), samplingSize);
    if (font == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::GenerateFontFile: Failed to create font");
        return false;
    }

    writer.Push(font->samplingSize_);
    writer.Push(font->ascent_);
    writer.Push(font->descent_);
    writer.Push(font->lineGap_);
    writer.Push(font->emSize_);
    writer.Push(font->textureSize_);

    // add characters
    std::u16string addCharacters(characters);
    addCharacters += u'\0';
    std::map<int32_t, std::shared_ptr<Glyph>> glyphs;
    for (size_t i = 0; i < addCharacters.size(); i++) {
        char32_t tmp = 0;
        ASD_ASSERT(i < addCharacters.size(), "buffer overrun");

        ConvChU16ToU32({addCharacters[i], i + 1 < addCharacters.size() ? addCharacters[i + 1] : u'\0'}, tmp);
        int32_t character = static_cast<int32_t>(tmp);

        // Surrogate pair
        if (addCharacters[i] >= 0xD800 && addCharacters[i] <= 0xDBFF) {
            i++;
        }

        glyphs[character] = font->GetGlyph(character);
    }

    // add glyph data
    writer.Push((int32_t)font->textures_.size());
    writer.Push((int32_t)glyphs.size());
    for (auto glyph : glyphs) {
        writer.Push(glyph.first);
        writer.Push(glyph.second == nullptr);
        if (glyph.second == nullptr) continue;
        writer.Push(glyph.second);
        for (auto glyph2 : glyphs) {
            writer.Push(glyph.first);
            writer.Push(glyph2.first);
            writer.Push(font->GetKerning(glyph.first, glyph2.first));
        }
    }

    // save font textures
    const auto parentPath = FileSystem::GetParentPath(nStaticFontPath);
    auto textureDir = parentPath + (parentPath.size() == 0 ? u"" : u"/") + staticFontRawFilename;
    if (!FileSystem::GetIsDirectory(textureDir.c_str())) {
        if (!FileSystem::CreateDirectory(textureDir.c_str())) {
            Log::GetInstance()->Error(LogCategory::Core, u"Font::GenerateFontFile: Failed to create directory: {0}", utf16_to_utf8(textureDir));
            return false;
        }
    }
    int i = 0;
    for (auto& texture : font->textures_) {
        texture->Save((textureDir + u"/Texture" + utf8_to_utf16(std::to_string(i++)) + u".png").c_str());
    }

    std::ofstream fs;
#ifdef _WIN32
    fs.open((wchar_t*)nStaticFontPath.c_str(), std::basic_ios<char>::out | std::basic_ios<char>::binary);
#else
    fs.open(utf16_to_utf8(nStaticFontPath).c_str(), std::basic_ios<char>::out | std::basic_ios<char>::binary);
#endif
    if (!fs.is_open()) return false;

    writer.WriteOut(fs);
    return true;
}

bool Font::Reload() { return false; }

void Font::AddFontTexture() {
    std::vector<uint8_t> temp;
    temp.resize(textureSize_.X * textureSize_.Y);
    for (int32_t i = 0; i < textureSize_.X * textureSize_.Y; i++) {
        temp[i] = 0;
    }

    auto llgiTexture = Graphics::GetInstance()->CreateTexture(temp.data(), textureSize_.X, textureSize_.Y, 1);
    auto texture = MakeAsdShared<Texture2D>(Resources::GetInstance(), llgiTexture, u"");
    textures_.push_back(texture);

    currentTexturePosition_ = Vector2I();
}

void Font::AddGlyph(const int32_t character) {
    if (GetIsStaticFont()) return;

    double advance = 0.0;

    // フォントデータ読み込み
    msdfgen::Shape shape;
    if (!msdfgen::loadGlyph(shape, fontHandle_.get(), character, &advance)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::AddGlyph: failed to load glyph of character '{0}'", static_cast<char>(character));
        glyphs_[character] = GetGlyph('\0');
        return;
    }

    // 空白等形状なしのフォント
    if (shape.edgeCount() < 1) {
        Log::GetInstance()->Info(LogCategory::Core, u"Font::AddGlyph: Edge Count of '{0}' is less than 1", static_cast<char>(character));
        auto glyph = MakeAsdShared<Glyph>(textureSize_, textures_.size() - 1, currentTexturePosition_, Vector2I(0, 0), Vector2F(), advance);
        glyphs_[character] = glyph;
        return;
    }

    const auto bounds = shape.getBounds();
    const Vector2F boundsSize(bounds.r - bounds.l, bounds.t - bounds.b);

    const float scale = samplingSize_ / (ascent_ - descent_);

    const auto w = advance * scale;
    const float h = samplingSize_;

    const int32_t width = std::ceil(w);
    const int32_t height = samplingSize_;

    const auto widthWithPadding = width + TextureSamplingPaddingPixel;
    const auto heightWithPadding = height + TextureSamplingPaddingPixel;

    // MDFGデータ生成
    msdfgen::Bitmap<float, 3> msdf(widthWithPadding, heightWithPadding);
    {
        shape.inverseYAxis = true;
        shape.normalize();
        shape.orientContours();
        msdfgen::edgeColoringSimple(shape, AngleThresholdDefault);

        const auto padding = static_cast<double>(TextureSamplingPaddingPixel / 2);

        const auto translate = msdfgen::Vector2(padding / width, padding / height - bounds.b - descent_);

        msdfgen::generateMSDF(msdf, shape, PxRangeDefault, msdfgen::Vector2(scale), translate);
    }

    // 横幅が収まらない場合は次の行へ
    if (textureSize_.X < currentTexturePosition_.X + widthWithPadding) {
        currentTexturePosition_.X = 0;
        currentTexturePosition_.Y += TextureAtlasMarginPixel + heightWithPadding;
    }

    // 縦幅が収まらない場合は新しいテクスチャを追加
    if (textureSize_.Y < currentTexturePosition_.Y + heightWithPadding) AddFontTexture();

    auto pos = currentTexturePosition_;

    {
        const auto llgiTexture = textures_.back()->GetNativeTexture();
        const auto buf = (LLGI::Color8*)llgiTexture->Lock();

        for (int32_t y = 0; y < heightWithPadding; y++) {
            const auto ty = pos.Y + y;
            for (int32_t x = 0; x < widthWithPadding; x++) {
                const auto tx = x + pos.X;
                buf[tx + ty * textureSize_.X].R = msdfgen::pixelFloatToByte(msdf(x, y)[0]);
                buf[tx + ty * textureSize_.X].G = msdfgen::pixelFloatToByte(msdf(x, y)[1]);
                buf[tx + ty * textureSize_.X].B = msdfgen::pixelFloatToByte(msdf(x, y)[2]);
                // buf[x + y * textureSize_.X].A = 0;
            }
        }

        llgiTexture->Unlock();
        currentTexturePosition_.X += widthWithPadding + Font::TextureAtlasMarginPixel;
    }

    const Vector2F offset(0.0f, -ascent_ - bounds.b);

    const auto glyphPos = pos + Vector2I(TextureSamplingPaddingPixel / 2, TextureSamplingPaddingPixel / 2);

    const auto glyph = MakeAsdShared<Glyph>(textureSize_, textures_.size() - 1, glyphPos, Vector2I(width, height), offset, advance);
    glyphs_[character] = glyph;
}

}  // namespace Altseed2
