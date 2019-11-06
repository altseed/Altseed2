#pragma once

#include <stb_truetype.h>
#include <map>
#define STB_TRUETYPE_IMPLEMENTATION
#include "../Common/Resource.h"
#include "Color.h"
#include "Texture2D.h"

namespace altseed {
class Font : public Resource {
private:
    std::map<char32_t, Texture2D*> glyphTextures_;
    stbtt_fontinfo fontinfo_;
    int32_t size_;
    Color color_;

public:
    Font(stbtt_fontinfo fontinfo, int32_t size, Color color);
    virtual ~Font();

    Color GetColor() { return color_; }
    int32_t GetSize() { return size_; }

    Texture2D* GetGlyphTexture(const char16_t character);

    static Font* Load(const char16_t path);

private:
    void* AddGlyphTexture(const char16_t character);
};
}  // namespace altseed