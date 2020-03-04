#pragma once

#include <stb_truetype.h>
#include <array>
#include <map>
#include <memory>
#include "../Common/Resource.h"
#include "../IO/StaticFile.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector2I.h"
#include "Color.h"
#include "Texture2D.h"

namespace Altseed {
enum class WritingDirection : int32_t { Vertical, Horizontal };

class Glyph : public BaseObject {
private:
    Vector2I textureSize_;
    int32_t textureIndex_;
    Vector2I position_;
    Vector2I size_;

    Vector2I offset_;
    int32_t glyphWidth_;

public:
    Glyph(Vector2I textureSize, int32_t textureIndex, Vector2I position, Vector2I size, Vector2I offset, int32_t glyphWidth);
    Vector2I GetTextureSize() { return textureSize_; }
    int32_t GetTextureIndex() { return textureIndex_; }
    Vector2I GetPosition() { return position_; }
    Vector2I GetSize() { return size_; }
    Vector2I GetOffset() { return offset_; }
    int32_t GetGlyphWidth() { return glyphWidth_; }
};

class Font : public Resource {
private:
    std::shared_ptr<Resources> resources_;

    stbtt_fontinfo fontinfo_;
    float scale_;
    int32_t ascent_, descent_, lineGap_;

    int32_t size_;
    Color color_;
    float weight_;

    std::shared_ptr<StaticFile> file_;

    std::map<char16_t, std::shared_ptr<Glyph>> glyphs_;
    std::vector<std::shared_ptr<Texture2D>> textures_;
    Vector2I textureSize_;

    Vector2I currentTexturePosition_;

public:
    Font(std::shared_ptr<Resources>& resources, std::shared_ptr<StaticFile>& file, stbtt_fontinfo fontinfo, int32_t size);
    virtual ~Font();

    void SetColor(Color color) { color_ = color; }
    Color GetColor() { return color_; }

	void SetWeight(float weight) { weight_ = weight; }
    float GetWeight() { return weight_; }

    int32_t GetSize() { return size_; }
    int32_t GetAscent() { return ascent_; }
    int32_t GetDescent() { return descent_; }
    int32_t GetLineGap() { return lineGap_; }

    std::shared_ptr<Glyph> GetGlyph(const int32_t character);
    std::shared_ptr<Texture2D> GetFontTexture(int32_t index) {
        if (index >= textures_.size()) return nullptr;
        return textures_[index];
    }

    int32_t GetKerning(const int32_t c1, const int32_t c2);
    Vector2I CalcTextureSize(const char16_t* text, WritingDirection direction, bool isEnableKerning = true);

    static std::shared_ptr<Font> LoadDynamicFont(const char16_t* path, int32_t size);
    static std::shared_ptr<Font> LoadStaticFont(const char16_t* path);

    bool Reload() override;

private:
    void AddFontTexture();
    void AddGlyph(const char16_t character);
};
}  // namespace Altseed