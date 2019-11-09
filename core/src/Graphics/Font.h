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

class Glyph : public Texture2D {
private:
    Vector2DI offset_;
    int32_t glyphWidth_;

public:
    Glyph(std::shared_ptr<Resources>& resources,
          std::shared_ptr<LLGI::Texture>& texture,
          uint8_t* data,
          int32_t width,
          int32_t height,
          Vector2DI offset,
          int32_t glyphWidth);

    Vector2DI GetOffset() { return offset_; }
    int32_t GetGlyphWidth() { return glyphWidth_; }
};

class Font : public Resource {
private:
    std::shared_ptr<Resources> resources_;

    stbtt_fontinfo fontinfo_;
    int32_t size_;
    float scale_;
    int32_t ascent_, descent_, lineGap_;

    Color color_;
    StaticFile* file_;

    std::map<char16_t, Glyph*> glyphs_;
    std::map<char16_t, Texture2D*> glyphTextures_;

public:
    Font(std::shared_ptr<Resources>& resources, StaticFile* file, stbtt_fontinfo fontinfo, int32_t size, Color color);
    virtual ~Font();

    Color GetColor() { return color_; }
    int32_t GetSize() { return size_; }

    Glyph* GetGlyph(const char16_t character);

    int32_t GetKerning(const char16_t c1, const char16_t c2);
    Vector2DI CalcTextureSize(const char16_t* text, WritingDirection direction, bool isEnableKerning = true);

    static Font* LoadDynamicFont(const char16_t* path, int32_t size, Color color);
    static Font* LoadStaticFont(const char16_t* path);

    static inline const char* HlslPSCode = R"(
Texture2D txt : register(t8);
SamplerState smp : register(s8);
struct PS_INPUT
{
    float4  Position : SV_POSITION;
	float2  UV : UV0;
    float4  Color    : COLOR0;
};
float4 main(PS_INPUT input) : SV_TARGET 
{ 
	float4 c;
	c = txt.Sample(smp, input.UV);
	c.a = 255;
	return c;
}
)";

    bool Reload() override;

private:
    void AddGlyph(const char16_t character);
};
}  // namespace altseed