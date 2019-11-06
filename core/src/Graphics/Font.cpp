#include "Font.h"
#include <string>
#include "../IO/File.h"
#include "Graphics.h"

namespace altseed {

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

Texture2D* Font::GetGlyphTexture(const char16_t character) {
    if (glyphTextures_.count(character)) return glyphTextures_[character];

    AddGlyphTexture(character);
    return glyphTextures_[character];
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

        auto texture = GetGlyphTexture(text[i]);
        if (texture != nullptr) w += texture->GetSize().X;

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

void Font::AddGlyphTexture(const char16_t character) {
    int32_t c_x1, c_y1, c_x2, c_y2;
    stbtt_GetCodepointBitmapBox(&fontinfo_, character, scale_, scale_, &c_x1, &c_y1, &c_x2, &c_y2);

    int32_t w;
    stbtt_GetCodepointHMetrics(&fontinfo_, character, &w, 0);
    w *= scale_;
    int32_t h = ascent_ - descent_;

    uint8_t* raw = new uint8_t[w * h];
    stbtt_MakeCodepointBitmap(&fontinfo_, raw + (ascent_ + c_y1) * w, c_x2 - c_x1, c_y2 - c_y1, w, scale_, scale_, character);

    uint8_t* bitmap = new uint8_t[w * h * 4];
    for (int32_t y = 0; y < h; y++) {
        for (int32_t x = 0; x < w; x++) {
            bitmap[4 * (x + y * w)] = (uint8_t)(color_.R * raw[x + y * w] / 255.0);
            bitmap[4 * (x + y * w) + 1] = (uint8_t)(color_.G * raw[x + y * w] / 255.0);
            bitmap[4 * (x + y * w) + 2] = (uint8_t)(color_.B * raw[x + y * w] / 255.0);
            bitmap[4 * (x + y * w) + 3] = (uint8_t)(color_.A * raw[x + y * w] / 255.0);
        }
    }

    auto llgiTexture = Graphics::GetInstance()->CreateTexture(bitmap, w, h, 4);
    Texture2D* texture = new Texture2D(std::shared_ptr<Resources>(), llgiTexture, bitmap, w, h);

    glyphTextures_[character] = texture;
}
}  // namespace altseed