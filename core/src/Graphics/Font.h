#pragma once

#include <stb_truetype.h>

#include <array>
#include <map>
#include <memory>

#include "../Common/Resource.h"
#include "../Common/ThreadSafeMap.h"
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
    float weight_;

    std::shared_ptr<StaticFile> file_;

    std::map<int32_t, std::shared_ptr<Glyph>> glyphs_;
    std::vector<std::shared_ptr<Texture2D>> textures_;
    Vector2I textureSize_;

    Vector2I currentTexturePosition_;

    static ThreadSafeMap<std::u16string, std::mutex> m_fontMtx;

protected:
    Font();

public:
    Font(std::shared_ptr<Resources>& resources, std::shared_ptr<StaticFile>& file, stbtt_fontinfo fontinfo, int32_t size);

    virtual int32_t GetSize() { return size_; }
    virtual int32_t GetAscent() { return ascent_; }
    virtual int32_t GetDescent() { return descent_; }
    virtual int32_t GetLineGap() { return lineGap_; }

    virtual std::shared_ptr<Glyph> GetGlyph(const int32_t character);
    virtual std::shared_ptr<Texture2D> GetFontTexture(int32_t index) {
        if (index >= textures_.size()) return nullptr;
        return textures_[index];
    }

    virtual int32_t GetKerning(const int32_t c1, const int32_t c2);
    virtual Vector2I CalcTextureSize(const char16_t* text, WritingDirection direction, bool isEnableKerning = true);

    static std::shared_ptr<Font> LoadDynamicFont(const char16_t* path, int32_t size);
    static std::shared_ptr<Font> LoadStaticFont(const char16_t* path);
    static std::shared_ptr<Font> CreateImageFont(std::shared_ptr<Font> baseFont);

    virtual void AddImageGlyph(const int32_t character, std::shared_ptr<Texture2D> texture) {}
    virtual std::shared_ptr<Texture2D> GetImageGlyph(const int32_t character) { return nullptr; }

    bool Reload() override;

    const char16_t* GetPath() const;

private:
    void AddFontTexture();
    void AddGlyph(const int32_t character);
};
}  // namespace Altseed