#pragma once

#undef INFINITE
#include <msdfgen/msdfgen-ext.h>
#include <msdfgen/msdfgen.h>

#include <array>
#include <map>
#include <memory>

#include "../Common/BinaryReader.h"
#include "../Common/BinaryWriter.h"
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

    Vector2F offset_;
    float advance_;

public:
    Glyph();
    Glyph(Vector2I textureSize, int32_t textureIndex, Vector2I position, Vector2I size, Vector2F offset, float advance);

    Vector2I GetTextureSize() { return textureSize_; }
    int32_t GetTextureIndex() { return textureIndex_; }
    Vector2I GetPosition() { return position_; }
    Vector2I GetSize() { return size_; }
    Vector2F GetOffset() { return offset_; }
    float GetAdvance() { return advance_; }

#if !USE_CBG
    inline void Write(BinaryWriter* writer) {
        writer->Push(textureSize_);
        writer->Push(textureIndex_);
        writer->Push(position_);
        writer->Push(size_);
        writer->Push(offset_);
        writer->Push(advance_);
    }

    static inline std::shared_ptr<Glyph> Read(BinaryReader* reader) {
        auto glyph = MakeAsdShared<Glyph>();
        reader->Get(&glyph->textureSize_);
        reader->Get(&glyph->textureIndex_);
        reader->Get(&glyph->position_);
        reader->Get(&glyph->size_);
        reader->Get(&glyph->offset_);
        reader->Get(&glyph->advance_);
        return glyph;
    }
#endif
};

class Font : public Resource {
private:
    std::shared_ptr<Resources> resources_;

    std::shared_ptr<msdfgen::FontHandle> fontHandle_;
    float ascent_, descent_, lineGap_, emSize_;
    int32_t samplingSize_;

    std::shared_ptr<StaticFile> file_;

    std::map<int32_t, std::shared_ptr<Glyph>> glyphs_;
    std::vector<std::shared_ptr<Texture2D>> textures_;
    Vector2I textureSize_;

    Vector2I currentTexturePosition_;

    std::u16string sourcePath_;

    bool isStaticFont_;
    std::map<std::pair<int32_t, int32_t>, int32_t> kernings_;

    static std::mutex mtx;

    static std::shared_ptr<msdfgen::FreetypeHandle> freetypeHandle_;

public:
    static constexpr float PxRangeDefault = 4.0;
    static constexpr float AngleThresholdDefault = 3.0;

    static constexpr int32_t TextureSize = 1024;
    static constexpr int32_t TextureAtlasMarginPixel = 4;
    static constexpr int32_t TextureSamplingPaddingPixel = 4;

    Font(std::u16string path);
    Font(std::shared_ptr<Resources>& resources,
         std::shared_ptr<StaticFile>& file,
         std::shared_ptr<msdfgen::FontHandle> fontHandle,
         int32_t samplingSize,
         std::u16string path);

    virtual ~Font();

#if !USE_CBG
    static bool Initialize();
    static void Terminate();
#endif

    virtual int32_t GetSamplingSize() { return samplingSize_; }
    virtual float GetAscent() { return ascent_; }
    virtual float GetDescent() { return descent_; }
    virtual float GetLineGap() { return lineGap_; }
    virtual float GetEmSize() { return emSize_; }
    virtual bool GetIsStaticFont() { return isStaticFont_; }

    virtual std::shared_ptr<Glyph> GetGlyph(const int32_t character);
    virtual std::shared_ptr<Texture2D> GetFontTexture(int32_t index) {
        if (index >= textures_.size()) return nullptr;
        return textures_[index];
    }

    virtual int32_t GetKerning(const int32_t c1, const int32_t c2);

    static std::shared_ptr<Font> LoadDynamicFont(const char16_t* path, int32_t samplingSize);
    static std::shared_ptr<Font> LoadStaticFont(const char16_t* path);
    static std::shared_ptr<Font> CreateImageFont(std::shared_ptr<Font> baseFont);

    static bool GenerateFontFile(const char16_t* dynamicFontPath, const char16_t* staticFontPath, int32_t samplingSize, const char16_t* characters);

    virtual void AddImageGlyph(const int32_t character, std::shared_ptr<TextureBase> texture) {}
    virtual std::shared_ptr<TextureBase> GetImageGlyph(const int32_t character) { return nullptr; }

    bool Reload() override;

    const char16_t* GetPath() const;

private:
#if !USE_CBG
    void AddFontTexture();
    void AddGlyph(const int32_t character);

    static std::u16string GetKeyName(const char16_t* path, float samplingSize) {
        return std::u16string(path) + utf8_to_utf16(std::to_string(samplingSize));
    }
#endif
};
}  // namespace Altseed2