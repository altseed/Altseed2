#include "Font.h"
#include <string>
#include "../IO/File.h"
#include "Graphics.h"

namespace altseed {

Glyph::Glyph(Vector2DI textureSize, int32_t textureIndex, Vector2DI position, Vector2DI size, Vector2DI offset, int32_t glyphWidth)
    : textureSize_(textureSize), textureIndex_(textureIndex), position_(position), size_(size), offset_(offset), glyphWidth_(glyphWidth) {}

Font::Font(std::shared_ptr<Resources>& resources, std::shared_ptr<StaticFile>& file, stbtt_fontinfo fontinfo, int32_t size, Color color)
    : resources_(resources), file_(file), fontinfo_(fontinfo), size_(size), color_(color), textureSize_(Vector2DI(2000, 2000)) {
    scale_ = stbtt_ScaleForPixelHeight(&fontinfo_, size_);

    stbtt_GetFontVMetrics(&fontinfo_, &ascent_, &descent_, &lineGap_);
    ascent_ *= scale_;
    descent_ *= scale_;

    AddFontTexture();
}

Font::~Font() {
    file_->Release();
    for (auto& i : textures_) {
        if (i != nullptr) i->Release();
    }
    for (auto& i : glyphs_) {
        delete i.second;
    }
}

Glyph* Font::GetGlyph(const char16_t character) {
    if (glyphs_.count(character)) return glyphs_[character];

    AddGlyph(character);
    return glyphs_[character];
}

int32_t Font::GetKerning(const char16_t c1, const char16_t c2) {
    int kern;
    kern = stbtt_GetCodepointKernAdvance(&fontinfo_, c1, c2);
    return kern * scale_;
}

Vector2DI Font::CalcTextureSize(const char16_t* text, WritingDirection direction, bool isEnableKerning) {
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
    return direction == WritingDirection::Horizontal ? Vector2DI(w, h) : Vector2DI(h, w);
}

std::shared_ptr<Font> Font::LoadDynamicFont(const char16_t* path, int32_t size, Color color) {
    auto resources = Resources::GetInstance();
    auto cache = std::dynamic_pointer_cast<Font>(resources->GetResourceContainer(ResourceType::Font)->Get(path));
    if (cache != nullptr) {
        cache->AddRef();
        return cache;
    }

    auto file = File::GetInstance()->CreateStaticFile(path);
    if (file == nullptr) {
        return nullptr;
    }

    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, (unsigned char*)file->GetData(), 0)) {
        file->Release();
        return nullptr;
    }

    auto res = std::make_shared<Font>(resources, file, info, size, color);
    resources->GetResourceContainer(ResourceType::Font)->Register(path, std::make_shared<ResourceContainer::ResourceInfomation>(res, path));

    return res;
}

std::shared_ptr<Font> Font::LoadStaticFont(const char16_t* path) { return nullptr; }

bool Font::Reload() { return false; }

void Font::AddFontTexture() {
    uint8_t* data = new uint8_t[textureSize_.X * textureSize_.Y];
    for (int32_t i = 0; i < textureSize_.X * textureSize_.Y; i++) {
        data[i] = 0;
    }

    auto llgiTexture = Graphics::GetInstance()->CreateTexture(data, textureSize_.X, textureSize_.Y, 1);
    auto texture = new Texture2D(Resources::GetInstance(), llgiTexture, data, textureSize_.X, textureSize_.Y);
    textures_.push_back(texture);

    currentTexturePosition_ = Vector2DI();
}

void Font::AddGlyph(const char16_t character) {
    Vector2DI offset;
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

    auto glyph = new Glyph(textureSize_, textures_.size() - 1, pos, Vector2DI(w, h), offset, glyphW);
    glyphs_[character] = glyph;
}

}  // namespace altseed