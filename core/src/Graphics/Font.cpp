#include "Font.h"
#include <string>
#include "../IO/File.h"
#include "Graphics.h"

namespace altseed {

Glyph::Glyph(
        std::shared_ptr<Resources>& resources,
        std::shared_ptr<LLGI::Texture>& texture,
        uint8_t* data,
        int32_t width,
        int32_t height,
        Vector2DI offset,
        int32_t glyphWidth)
    : Texture2D(resources, texture, data, width, height), offset_(offset), glyphWidth_(glyphWidth) {}

Font::Font(std::shared_ptr<Resources>& resources, StaticFile* file, stbtt_fontinfo fontinfo, int32_t size, Color color)
    : resources_(resources), file_(file), fontinfo_(fontinfo), size_(size), color_(color) {
    scale_ = stbtt_ScaleForPixelHeight(&fontinfo_, size_);

    stbtt_GetFontVMetrics(&fontinfo_, &ascent_, &descent_, &lineGap_);
    ascent_ *= scale_;
    descent_ *= scale_;
}

Font::~Font() {
    file_->Release();
    for (auto& i : glyphTextures_) {
        if (i.second != nullptr) i.second->Release();
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

Font* Font::LoadDynamicFont(const char16_t* path, int32_t size, Color color) {
    auto resources = Resources::GetInstance();
    Font* cache = (Font*)resources->GetResourceContainer(ResourceType::Font)->Get(path);
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

    Font* res = new Font(resources, file, info, size, color);
    resources->GetResourceContainer(ResourceType::Font)
            ->Register(path, std::make_shared<ResourceContainer::ResourceInfomation>((Resource*)res, path));

    return res;
}

Font* Font::LoadStaticFont(const char16_t* path) { return nullptr; }

bool Font::Reload() { return false; }

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

    auto llgiTexture = Graphics::GetInstance()->CreateTexture(data, w, h, 1);
    Glyph* glyph = new Glyph(Resources::GetInstance(), llgiTexture, data, w, h, offset, glyphW);

    glyphs_[character] = glyph;
}

}  // namespace altseed