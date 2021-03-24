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

Glyph::Glyph(Vector2I textureSize, int32_t textureIndex, Vector2I position, Vector2I size, Vector2I offset, float glyphWidth)
    : textureSize_(textureSize), textureIndex_(textureIndex), position_(position), size_(size), offset_(offset), glyphWidth_(glyphWidth) {}

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
      textureSize_(Vector2I(2000, 2000)),
      sourcePath_(path),
      isStaticFont_(true) {}

Font::Font(
        std::shared_ptr<Resources>& resources,
        std::shared_ptr<StaticFile>& file,
        msdfgen::FontHandle* fontHandle,
        int32_t samplingSize,
        std::u16string path)
    : resources_(resources),
      fontHandle_(fontHandle),
      samplingSize_(samplingSize),
      file_(file),
      textureSize_(Vector2I(2000, 2000)),
      sourcePath_(path),
      isStaticFont_(false) {
    msdfgen::FontMetrics metrics;
    msdfgen::getFontMetrics(metrics, fontHandle);
    ascent_ = metrics.ascenderY;
    descent_ = metrics.descenderY;
    lineGap_ = metrics.lineHeight;

    AddFontTexture();

    SetInstanceName(__FILE__);
}

Font::~Font() {
    if (fontHandle_ != nullptr) {
        msdfgen::destroyFont(fontHandle_);
        fontHandle_ = nullptr;
    }

    std::lock_guard<std::mutex> lock(mtx);
    if (resources_ != nullptr && sourcePath_ != u"") {
        resources_->GetResourceContainer(ResourceType::Font)
                ->Unregister(sourcePath_ + (isStaticFont_ ? u"" : utf8_to_utf16(std::to_string(samplingSize_))));
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
    if (!msdfgen::getKerning(kern, fontHandle_, c1, c2)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::GetKerning: failed to get kerning");
        return 0;
    }

    return (float)kern;
}

const char16_t* Font::GetPath() const { return sourcePath_.c_str(); }

std::shared_ptr<Font> Font::LoadDynamicFont(const char16_t* path, int32_t samplingSize) {
    EASY_BLOCK("Altseed2(C++).Font.LoadDynamicFont");

    RETURN_IF_NULL(path, nullptr);

    auto resources = Resources::GetInstance();
    if (resources == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"File is not initialized.");
        return nullptr;
    }

    std::lock_guard<std::mutex> lock(mtx);

    auto cache = std::dynamic_pointer_cast<Font>(
            resources->GetResourceContainer(ResourceType::Font)->Get(path + utf8_to_utf16(std::to_string(samplingSize))));
    if (cache != nullptr && cache->GetRef() > 0 && !cache->GetIsStaticFont()) {
        return cache;
    }

    auto file = StaticFile::Create(path);
    if (file == nullptr) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"Font::LoadDynamicFont: Failed to create file from '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    msdfgen::FontHandle* fontHandle = msdfgen::loadFontMemory(Font::freetypeHandle_.get(), (unsigned char*)file->GetData(), file->GetSize());

    if (fontHandle == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::LoadDynamicFont: Failed to initialize font '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    auto res = MakeAsdShared<Font>(resources, file, fontHandle, samplingSize, path);
    resources->GetResourceContainer(ResourceType::Font)
            ->Register(path + utf8_to_utf16(std::to_string(samplingSize)), std::make_shared<ResourceContainer::ResourceInfomation>(res, path));

    return res;
}

std::shared_ptr<Font> Font::LoadStaticFont(const char16_t* path) {
    EASY_BLOCK("Altseed2(C++).Font.LoadStaticFont");

    RETURN_IF_NULL(path, nullptr);

    auto resources = Resources::GetInstance();
    if (resources == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"File is not initialized.");
        return nullptr;
    }

    std::lock_guard<std::mutex> lock(mtx);

    auto cache = std::dynamic_pointer_cast<Font>(resources->GetResourceContainer(ResourceType::Font)->Get(path));
    if (cache != nullptr && cache->GetRef() > 0 && cache->GetIsStaticFont()) {
        return cache;
    }

    auto file = StaticFile::Create(path);
    if (file == nullptr) return nullptr;

    BinaryReader reader(file);

    auto font = MakeAsdShared<Font>(path);
    font->resources_ = resources;
    font->file_ = file;
    font->samplingSize_ = reader.Get<int32_t>();
    font->ascent_ = reader.Get<int32_t>();
    font->descent_ = reader.Get<int32_t>();
    font->lineGap_ = reader.Get<int32_t>();
    font->textureSize_ = reader.Get<Vector2I>();

    int textureCount = reader.Get<int32_t>();
    for (size_t i = 0; i < textureCount; i++) {
        auto texturePath = FileSystem::GetParentPath(path) + u"/Textures/font" + utf8_to_utf16(std::to_string(i)) + u".png";
        auto texture = Texture2D::Load(texturePath.c_str());
        if (texture == nullptr) return nullptr;
        font->textures_.push_back(texture);
    }

    int glyphCount = reader.Get<int32_t>();
    for (size_t i = 0; i < glyphCount; i++) {
        int32_t character = reader.Get<int32_t>();
        if (reader.Get<bool>()) continue;
        Vector2I textureSize = reader.Get<Vector2I>();
        int32_t index = reader.Get<int32_t>();
        Vector2I position = reader.Get<Vector2I>();
        Vector2I size = reader.Get<Vector2I>();
        Vector2I offset = reader.Get<Vector2I>();
        int32_t width = reader.Get<int32_t>();

        auto glyph = MakeAsdShared<Glyph>(textureSize, index, position, size, offset, width);
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

    auto parentDir = FileSystem::GetParentPath(FileSystem::GetAbusolutePath(staticFontPath));
    if (!FileSystem::GetIsDirectory(parentDir)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::GenerateFontFile: The output directory cannot be accessed.");
        return false;
    }
    BinaryWriter writer;

    auto font = Font::LoadDynamicFont(dynamicFontPath, samplingSize);
    if (font == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::GenerateFontFile: Failed to create font");
        return false;
    }

    writer.Push(font->samplingSize_);
    writer.Push(font->ascent_);
    writer.Push(font->descent_);
    writer.Push(font->lineGap_);
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
        writer.Push(glyph.second->GetTextureSize());
        writer.Push(glyph.second->GetTextureIndex());
        writer.Push(glyph.second->GetPosition());
        writer.Push(glyph.second->GetSize());
        writer.Push(glyph.second->GetOffset());
        writer.Push(glyph.second->GetGlyphWidth());
        for (auto glyph2 : glyphs) {
            writer.Push(glyph.first);
            writer.Push(glyph2.first);
            writer.Push(font->GetKerning(glyph.first, glyph2.first));
        }
    }

    // save font textures
    auto textureDir = FileSystem::GetParentPath(staticFontPath) +
                      (FileSystem::GetParentPath(staticFontPath).size() == 0 ? u"Textures" : u"/Textures");
    if (!FileSystem::GetIsDirectory(textureDir.c_str()))
        if (!FileSystem::CreateDirectory(textureDir.c_str())) return false;
    int i = 0;
    for (auto& texture : font->textures_) {
        texture->Save((textureDir + u"/font" + utf8_to_utf16(std::to_string(i++)) + u".png").c_str());
    }

    std::ofstream fs;
#ifdef _WIN32
    fs.open((wchar_t*)staticFontPath, std::basic_ios<char>::out | std::basic_ios<char>::binary);
#else
    fs.open(utf16_to_utf8(staticFontPath).c_str(), std::basic_ios<char>::out | std::basic_ios<char>::binary);
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

const int padding = 64;

void Font::AddGlyph(const int32_t character) {
    if (GetIsStaticFont()) return;

    Vector2I offset;
    const int32_t w = samplingSize_;
    const int32_t h = samplingSize_;
    double glyphW = 0.0;

    msdfgen::Shape shape;
    // TODO
    if (!msdfgen::loadGlyph(shape, fontHandle_, character, &glyphW)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Font::AddGlyph: failed to load glyph");

        // TODO
        auto glyph = MakeAsdShared<Glyph>(textureSize_, textures_.size() - 1, currentTexturePosition_, Vector2I(w, h), offset, glyphW);
        glyphs_[character] = glyph;
        return;
    }

    shape.normalize();
    msdfgen::edgeColoringSimple(shape, 3.0);
    msdfgen::Bitmap<float, 3> msdf(w, h);
    msdfgen::generateMSDF(msdf, shape, Font::PxRange, 1.0, msdfgen::Vector2(4.0, 4.0));

    // TODO
    // stbtt_GetCodepointHMetrics(&fontinfo_, character, &glyphW, 0);
    // offset = (offset.To2F()).To2I();

    if (textureSize_.X < currentTexturePosition_.X + w) {
        currentTexturePosition_.X = 0;
        currentTexturePosition_.Y += padding * 2 + samplingSize_;
    }
    if (textureSize_.Y < currentTexturePosition_.Y + h) AddFontTexture();

    const auto pos = currentTexturePosition_;
    {
        const auto llgiTexture = textures_.back()->GetNativeTexture();
        const auto buf = (LLGI::Color8*)llgiTexture->Lock();

        for (int32_t y = pos.Y; y < pos.Y + h; y++) {
            for (int32_t x = pos.X; x < pos.X + w; x++) {
                const auto msdfY = h - (y - pos.Y);
                const auto msdfX = x - pos.X;
                buf[x + y * textureSize_.X].R = msdfgen::pixelFloatToByte(msdf(msdfX, msdfY)[0]);
                buf[x + y * textureSize_.X].G = msdfgen::pixelFloatToByte(msdf(msdfX, msdfY)[1]);
                buf[x + y * textureSize_.X].B = msdfgen::pixelFloatToByte(msdf(msdfX, msdfY)[2]);
                // buf[x + y * textureSize_.X].A = 0;
            }
        }
        llgiTexture->Unlock();
        currentTexturePosition_.X += w;
    }

    const auto glyph = MakeAsdShared<Glyph>(textureSize_, textures_.size() - 1, pos, Vector2I(w, h), offset, glyphW);
    glyphs_[character] = glyph;
}

}  // namespace Altseed2
