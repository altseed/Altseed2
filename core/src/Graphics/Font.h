#pragma once

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include <map>
#include <memory>
#include "../Common/Resource.h"
#include "../IO/StaticFile.h"
#include "../Math/Vector2DI.h"
#include "Color.h"
#include "Texture2D.h"

namespace altseed {
enum class WritingDirection : int32_t { Vertical, Horizontal };

class Font : public Resource {
private:
    std::shared_ptr<Resources> resources_;

    stbtt_fontinfo fontinfo_;
    int32_t size_;
    float scale_;
    int32_t ascent_, descent_, lineGap_;

    Color color_;
    StaticFile* file_;

    std::map<char16_t, Texture2D*> glyphTextures_;

public:
    Font(std::shared_ptr<Resources>& resources, StaticFile* file, stbtt_fontinfo fontinfo, int32_t size, Color color);
    virtual ~Font();

    Color GetColor() { return color_; }
    int32_t GetSize() { return size_; }

    Texture2D* GetGlyphTexture(const char16_t character);

    int32_t GetKerning(const char16_t c1, const char16_t c2);
    Vector2DI CalcTextureSize(const char16_t* text, WritingDirection direction, bool isEnableKerning = true);

    static Font* LoadDynamicFont(const char16_t* path, int32_t size, Color color);
    static Font* LoadStaticFont(const char16_t* path);

    bool Reload() override;

private:
    void AddGlyphTexture(const char16_t character);
};
}  // namespace altseed