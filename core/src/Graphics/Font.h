#pragma once

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include <array>
#include <map>
#include <memory>
#include "../Common/Resource.h"
#include "../IO/StaticFile.h"
#include "../Math/Vector2DF.h"
#include "../Math/Vector2DI.h"
#include "Color.h"
#include "Texture2D.h"

namespace altseed {
enum class WritingDirection : int32_t { Vertical, Horizontal };

class Glyph {
private:
    Vector2DI textureSize_;
    int32_t textureIndex_;
    Vector2DI position_;
    Vector2DI size_;

    Vector2DI offset_;
    int32_t glyphWidth_;

public:
    Glyph(Vector2DI textureSize, int32_t textureIndex, Vector2DI position, Vector2DI size, Vector2DI offset, int32_t glyphWidth);
    Vector2DI GetTextureSize() { return textureSize_; }
    int32_t GetTextureIndex() { return textureIndex_; }
    Vector2DI GetPosition() { return position_; }
    Vector2DI GetSize() { return size_; }
    Vector2DI GetOffset() { return offset_; }
    int32_t GetGlyphWidth() { return glyphWidth_; }
    std::array<Vector2DF, 4> GetUVs() {
        return {Vector2DF((float)position_.X / textureSize_.X, (float)position_.Y / textureSize_.Y),
                Vector2DF((float)(position_.X + size_.X) / textureSize_.X, (float)position_.Y / textureSize_.Y),
                Vector2DF((float)(position_.X + size_.X) / textureSize_.X, (float)(position_.Y + size_.Y) / textureSize_.Y),
                Vector2DF((float)position_.X / textureSize_.X, (float)(position_.Y + size_.Y) / textureSize_.Y)};
    }
};

class Font : public Resource {
private:
    std::shared_ptr<Resources> resources_;

    stbtt_fontinfo fontinfo_;
    int32_t size_;
    float scale_;
    int32_t ascent_, descent_, lineGap_;

    Color color_;
    std::shared_ptr<StaticFile> file_;

    std::map<char16_t, Glyph*> glyphs_;
    std::vector<Texture2D*> textures_;
    Vector2DI textureSize_;

    Vector2DI currentTexturePosition_;

public:
    Font(std::shared_ptr<Resources>& resources, std::shared_ptr<StaticFile>& file, stbtt_fontinfo fontinfo, int32_t size, Color color);
    virtual ~Font();

    Color GetColor() { return color_; }
    int32_t GetSize() { return size_; }
    int32_t GetAscent() { return ascent_; }
    int32_t GetDescent() { return descent_; }
    int32_t GetLineGap() { return lineGap_; }

    Glyph* GetGlyph(const char16_t character);
    Texture2D* GetFontTexture(int32_t index) {
        if (index >= textures_.size()) return nullptr;
        return textures_[index];
    }

    int32_t GetKerning(const char16_t c1, const char16_t c2);
    Vector2DI CalcTextureSize(const char16_t* text, WritingDirection direction, bool isEnableKerning = true);

    static std::shared_ptr<Font> LoadDynamicFont(const char16_t* path, int32_t size, Color color);
    static std::shared_ptr<Font> LoadStaticFont(const char16_t* path);

    const char* HlslPSCode = R"(
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

	c = lerp(float4(0, 0, 0, 0), float4(1, 1, 1, 1), (c - 0.5) * 255);
	c = lerp(float4(0, 0, 0, 0), float4(1, 1, 1, 1), c + 0.5);
	if (c.r > 1)
	{
		return float4(1, 1, 1, 1);
	}
	if (c.r > 0) 
	{
		c += 0.5;
		c = input.Color + c * c.a;
		return c;
	} 
	return (float)0;
}
)";

    bool Reload() override;

private:
    void AddFontTexture();
    void AddGlyph(const char16_t character);
};
}  // namespace altseed