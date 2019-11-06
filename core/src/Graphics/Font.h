#pragma once

#include <stb_truetype.h>
#include <map>
#include <memory>
#define STB_TRUETYPE_IMPLEMENTATION
#include "../Common/Resource.h"
#include "../IO/StaticFile.h"
#include "../Math/Vector2DI.h"
#include "Color.h"
#include "Texture2D.h"

namespace altseed {
class Font : public Resource {
private:
    std::shared_ptr<Resources> resources_;

    stbtt_fontinfo fontinfo_;
    int32_t size_;
    Color color_;
    StaticFile* file_;

    std::map<char32_t, Texture2D*> glyphTextures_;

public:
    Font(std::shared_ptr<Resources>& resources, StaticFile* file, stbtt_fontinfo fontinfo, int32_t size, Color color);
    virtual ~Font();

    Color GetColor() { return color_; }
    int32_t GetSize() { return size_; }

    Texture2D* GetGlyphTexture(const char16_t character);
    Vector2DI* CalcTextureSize(const char16_t* text);

    static Font* LoadDynamicFont(const char16_t path, int32_t size, Color color);
    static Font* LoadStaticFont(const char16_t path);

private:
    void* AddGlyphTexture(const char16_t character);
};
}  // namespace altseed