#define STB_TRUETYPE_IMPLEMENTATION

#include "Font.h"
#include <string>
#include "../IO/File.h"
#include "../Logger/Log.h"
#include "Graphics.h"
#include "ImageFont.h"

namespace Altseed {

Glyph::Glyph(Vector2I textureSize, int32_t textureIndex, Vector2I position, Vector2I size, Vector2I offset, int32_t glyphWidth)
    : textureSize_(textureSize), textureIndex_(textureIndex), position_(position), size_(size), offset_(offset), glyphWidth_(glyphWidth) {}

Font::Font()
    : resources_(nullptr),
      file_(nullptr),
      size_(0),
      ascent_(0),
      descent_(0),
      lineGap_(0),
      scale_(0),
      fontinfo_(stbtt_fontinfo()),
      textureSize_(Vector2I(2000, 2000)) {}

Font::Font(std::shared_ptr<Resources>& resources, std::shared_ptr<StaticFile>& file, stbtt_fontinfo fontinfo, int32_t size)
    : resources_(resources),
      file_(file),
      fontinfo_(fontinfo),
      size_(size),
      textureSize_(Vector2I(2000, 2000)) {
    scale_ = stbtt_ScaleForPixelHeight(&fontinfo_, size_);

    stbtt_GetFontVMetrics(&fontinfo_, &ascent_, &descent_, &lineGap_);
    ascent_ *= scale_;
    descent_ *= scale_;

    AddFontTexture();

    SetInstanceName(__FILE__);
}

Font::~Font() {
    for (auto& i : textures_) {
        if (i != nullptr) i->Release();
    }
}

std::shared_ptr<Glyph> Font::GetGlyph(const int32_t character) {
    if (glyphs_.count(character)) return glyphs_[character];

    AddGlyph(character);
    return glyphs_[character];
}

int32_t Font::GetKerning(const int32_t c1, const int32_t c2) {
    int kern;
    kern = stbtt_GetCodepointKernAdvance(&fontinfo_, (char16_t)c1, (char16_t)c2);
    return kern * scale_;
}

Vector2I Font::CalcTextureSize(const char16_t* text, WritingDirection direction, bool isEnableKerning) {
    int32_t w = 0;
    int32_t l = 1;
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        if (text[i] == '\n') {
            l++;
            continue;
        }

        auto glyph = GetGlyph(text[i]);
        if (glyph != nullptr) w += glyph->GetGlyphWidth();

        if (isEnableKerning && i != std::char_traits<char16_t>::length(text) - 1) w += GetKerning(text[i], text[i + 1]);
    }

    int32_t h = (ascent_ - descent_) * l;
    return direction == WritingDirection::Horizontal ? Vector2I(w, h) : Vector2I(h, w);
}

std::shared_ptr<Font> Font::LoadDynamicFont(const char16_t* path, int32_t size) {
    auto resources = Resources::GetInstance();
    auto cache = std::dynamic_pointer_cast<Font>(resources->GetResourceContainer(ResourceType::Font)->Get(path));
    if (cache != nullptr) {
        cache->AddRef();
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
        file->Release();
        Log::GetInstance()->Error(
                LogCategory::Core, u"Font::LoadDynamicFont: Failed to initialize font '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    auto res = MakeAsdShared<Font>(resources, file, info, size);
    resources->GetResourceContainer(ResourceType::Font)->Register(path, std::make_shared<ResourceContainer::ResourceInfomation>(res, path));

    return res;
}

std::shared_ptr<Font> Font::LoadStaticFont(const char16_t* path) { return nullptr; }

std::shared_ptr<Font> Font::CreateImageFont(std::shared_ptr<Font> baseFont) {
    if (baseFont == nullptr) return nullptr;
    return std::static_pointer_cast<Font>(MakeAsdShared<ImageFont>(baseFont));
}

bool Font::Reload() { return false; }

void Font::AddFontTexture() {
    uint8_t* data = new uint8_t[textureSize_.X * textureSize_.Y];
    for (int32_t i = 0; i < textureSize_.X * textureSize_.Y; i++) {
        data[i] = 0;
    }

    auto llgiTexture = Graphics::GetInstance()->CreateTexture(data, textureSize_.X, textureSize_.Y, 1);
    auto texture = MakeAsdShared<Texture2D>(Resources::GetInstance(), llgiTexture, u"");
    textures_.push_back(texture);

    currentTexturePosition_ = Vector2I();
}

void Font::AddGlyph(const int32_t character) {
    Vector2I offset;
    int32_t w, h, glyphW;

    uint8_t* data = stbtt_GetCodepointSDF(&fontinfo_, scale_, character, GetSize() / 2, 128, 1, &w, &h, &offset.X, &offset.Y);
    if (data == nullptr) {
        glyphs_[character] = nullptr;
        return;
    }

    stbtt_GetCodepointHMetrics(&fontinfo_, character, &glyphW, 0);
    glyphW *= scale_;

    if (textureSize_.X < currentTexturePosition_.X + w) {
        currentTexturePosition_.X = 0;
        currentTexturePosition_.Y += h;
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
                buf[x + y * textureSize_.X].B = data[i++];
            }
        }
        llgiTexture->Unlock();
        currentTexturePosition_.X += w;
    }

    auto glyph = MakeAsdShared<Glyph>(textureSize_, textures_.size() - 1, pos, Vector2I(w, h), offset, glyphW);
    glyphs_[character] = glyph;
}

}  // namespace Altseed