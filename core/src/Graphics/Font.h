#pragma once

#include <msdfgen/msdfgen.h>
#include <msdfgen/msdfgen-ext.h>

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

namespace Altseed2 {
enum class WritingDirection : int32_t { Vertical,
                                        Horizontal };

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

    msdfgen::FontHandle* fontHandle_;
    int32_t ascent_, descent_, lineGap_;
    int32_t size_;

    std::shared_ptr<StaticFile> file_;

    std::map<int32_t, std::shared_ptr<Glyph>> glyphs_;
    std::vector<std::shared_ptr<Texture2D>> textures_;
    Vector2I textureSize_;

    Vector2I currentTexturePosition_;

    std::u16string sourcePath_;

    bool isStaticFont_;
    std::map<std::pair<int32_t, int32_t>, int32_t> kernings_;

    static std::mutex mtx;

    static msdfgen::FreetypeHandle *freetypeHandle_;

public:
    Font(std::u16string path);
    Font(std::shared_ptr<Resources>& resources,
         std::shared_ptr<StaticFile>& file,
         msdfgen::FontHandle* fontHandle,
         int32_t size,
         std::u16string path);

    virtual ~Font();

#if !USE_CBG
    static bool Initialize();
    static void Terminate();
#endif

    virtual int32_t GetSize() { return size_; }
    virtual int32_t GetAscent() { return ascent_; }
    virtual int32_t GetDescent() { return descent_; }
    virtual int32_t GetLineGap() { return lineGap_; }
    virtual bool GetIsStaticFont() { return isStaticFont_; }

    virtual std::shared_ptr<Glyph> GetGlyph(const int32_t character);
    virtual std::shared_ptr<Texture2D> GetFontTexture(int32_t index) {
        if (index >= textures_.size()) return nullptr;
        return textures_[index];
    }

    virtual int32_t GetKerning(const int32_t c1, const int32_t c2);

    static std::shared_ptr<Font> LoadDynamicFont(const char16_t* path, int32_t size);
    static std::shared_ptr<Font> LoadStaticFont(const char16_t* path);
    static std::shared_ptr<Font> CreateImageFont(std::shared_ptr<Font> baseFont);

    static bool GenerateFontFile(const char16_t* dynamicFontPath, const char16_t* staticFontPath, int32_t size, const char16_t* characters);

    virtual void AddImageGlyph(const int32_t character, std::shared_ptr<Texture2D> texture) {}
    virtual std::shared_ptr<Texture2D> GetImageGlyph(const int32_t character) { return nullptr; }

    bool Reload() override;

    const char16_t* GetPath() const;

private:
#if !USE_CBG
    void AddFontTexture();
    void AddGlyph(const int32_t character);
#endif
};
}  // namespace Altseed2