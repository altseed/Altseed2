#define STB_TRUETYPE_IMPLEMENTATION

#include "Font.h"

#include <sstream>
#include <string>

#include "../Common/BinaryReader.h"
#include "../Common/BinaryWriter.h"
#include "../IO/File.h"
#include "../Logger/Log.h"
#include "../Platform/FileSystem.h"
#include "Graphics.h"
#include "ImageFont.h"

#ifdef _WIN32
#undef CreateDirectory
#endif

namespace Altseed {

Glyph::Glyph(Vector2I textureSize, int32_t textureIndex, Vector2I position, Vector2I size, Vector2I offset, int32_t glyphWidth)
    : textureSize_(textureSize), textureIndex_(textureIndex), position_(position), size_(size), offset_(offset), glyphWidth_(glyphWidth) {}

std::mutex Font::mtx;

Font::Font(std::u16string path)
    : resources_(nullptr),
      file_(nullptr),
      size_(0),
      actualSize_(0),
      ascent_(0),
      descent_(0),
      lineGap_(0),
      scale_(0),
      actualScale_(0),
      fontinfo_(stbtt_fontinfo()),
      textureSize_(Vector2I(2000, 2000)),
      isStaticFont_(true),
      sourcePath_(path) {}

Font::Font(
        std::shared_ptr<Resources>& resources,
        std::shared_ptr<StaticFile>& file,
        stbtt_fontinfo fontinfo,
        int32_t size,
        std::u16string path)
    : resources_(resources),
      file_(file),
      fontinfo_(fontinfo),
      size_(size),
      actualSize_(size),
      actualScale_(1),
      textureSize_(Vector2I(2000, 2000)),
      isStaticFont_(false),
      sourcePath_(path) {
    size_ = size_ > 80 ? size_ : 80;
    actualScale_ = size_ > 80 ? 1 : (actualSize_ / 80.0f);

    scale_ = stbtt_ScaleForPixelHeight(&fontinfo_, size_);

    stbtt_GetFontVMetrics(&fontinfo_, &ascent_, &descent_, &lineGap_);
    ascent_ *= scale_;
    descent_ *= scale_;

    AddFontTexture();

    SetInstanceName(__FILE__);
}

Font::~Font() {
    std::lock_guard<std::mutex> lock(mtx);
    if (resources_ != nullptr && sourcePath_ != u"") {
        resources_->GetResourceContainer(ResourceType::Font)
                ->Unregister(sourcePath_ + (isStaticFont_ ? u"" : utf8_to_utf16(std::to_string(GetSize()))));
        resources_ = nullptr;
    }
}

std::shared_ptr<Glyph> Font::GetGlyph(const int32_t character) {
    if (glyphs_.count(character))
        return glyphs_[character];
    else if (GetIsStaticFont()) {
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

    int kern;
    kern = stbtt_GetCodepointKernAdvance(&fontinfo_, c1, c2);
    return kern * scale_ * actualScale_;
}

const char16_t* Font::GetPath() const { return sourcePath_.c_str(); }

std::shared_ptr<Font> Font::LoadDynamicFont(const char16_t* path, int32_t size) {
    std::lock_guard<std::mutex> lock(mtx);

    auto resources = Resources::GetInstance();
    auto cache = std::dynamic_pointer_cast<Font>(
            resources->GetResourceContainer(ResourceType::Font)->Get(path + utf8_to_utf16(std::to_string(size))));
    if (cache != nullptr && cache->GetRef() > 0 && !cache->GetIsStaticFont()) {
        return cache;
    }

    auto file = StaticFile::Create(path);
    if (file == nullptr) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"Font::LoadDynamicFont: Failed to create file from '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, (unsigned char*)file->GetData(), 0)) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"Font::LoadDynamicFont: Failed to initialize font '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    auto res = MakeAsdShared<Font>(resources, file, info, size, path);
    resources->GetResourceContainer(ResourceType::Font)
            ->Register(path + utf8_to_utf16(std::to_string(size)), std::make_shared<ResourceContainer::ResourceInfomation>(res, path));

    return res;
}

std::shared_ptr<Font> Font::LoadStaticFont(const char16_t* path) {
    std::lock_guard<std::mutex> lock(mtx);

    auto resources = Resources::GetInstance();
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
    font->size_ = reader.Get<int32_t>();
    font->actualSize_ = reader.Get<int32_t>();
    font->ascent_ = reader.Get<int32_t>();
    font->descent_ = reader.Get<int32_t>();
    font->lineGap_ = reader.Get<int32_t>();
    font->scale_ = reader.Get<float>();
    font->actualScale_ = reader.Get<float>();
    font->textureSize_ = reader.Get<Vector2I>();

    int textureCount = reader.Get<int32_t>();
    for (size_t i = 0; i < textureCount; i++) {
        auto texturePath = FileSystem::GetParentPath(path) + u"/Textures/font" + utf8_to_utf16(std::to_string(i++)) + u".png";
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
    if (baseFont == nullptr) return nullptr;
    return std::static_pointer_cast<Font>(MakeAsdShared<ImageFont>(baseFont));
}

bool Font::GenerateFontFile(const char16_t* dynamicFontPath, const char16_t* staticFontPath, int32_t size, const char16_t* characters) {
    BinaryWriter writer;

    auto font = Font::LoadDynamicFont(dynamicFontPath, size);
    writer.Push(font->size_);
    writer.Push(font->actualSize_);
    writer.Push(font->ascent_);
    writer.Push(font->descent_);
    writer.Push(font->lineGap_);
    writer.Push(font->scale_);
    writer.Push(font->actualScale_);
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
    int32_t w = 0;
    int32_t h = 0;
    int32_t glyphW = 0;

    uint8_t* data = stbtt_GetCodepointSDF(&fontinfo_, scale_, character, padding, 128, GetPixelDistScale(), &w, &h, &offset.X, &offset.Y);
    stbtt_GetCodepointHMetrics(&fontinfo_, character, &glyphW, 0);
    glyphW *= scale_ * actualScale_;
    offset = (offset.To2F() * actualScale_).To2I();

    if (data == nullptr) {
        auto glyph = MakeAsdShared<Glyph>(textureSize_, textures_.size() - 1, currentTexturePosition_, Vector2I(w, h), offset, glyphW);
        glyphs_[character] = glyph;
        return;
    }

    if (textureSize_.X < currentTexturePosition_.X + w) {
        currentTexturePosition_.X = 0;
        currentTexturePosition_.Y += padding * 2 + GetActualSize();
    }
    if (textureSize_.Y < currentTexturePosition_.Y + h) AddFontTexture();

    auto pos = currentTexturePosition_;
    {
        auto llgiTexture = textures_.back()->GetNativeTexture();
        auto buf = (LLGI::Color8*)llgiTexture->Lock();
        int i = 0;
        for (int32_t y = currentTexturePosition_.Y; y < currentTexturePosition_.Y + h; y++) {
            for (int32_t x = currentTexturePosition_.X; x < currentTexturePosition_.X + w; x++) {
                buf[x + y * textureSize_.X].R = data[i];
                buf[x + y * textureSize_.X].G = data[i];
                buf[x + y * textureSize_.X].B = data[i];
                buf[x + y * textureSize_.X].A = data[i++];
            }
        }
        llgiTexture->Unlock();
        currentTexturePosition_.X += w;
    }

    auto glyph = MakeAsdShared<Glyph>(textureSize_, textures_.size() - 1, pos, Vector2I(w, h), offset, glyphW);
    glyphs_[character] = glyph;
}

}  // namespace Altseed
