#pragma once

#include <array>
#include <map>
#include <memory>
#include "../Common/Resource.h"
#include "../IO/StaticFile.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector2I.h"
#include "Color.h"
#include "Font.h"
#include "Texture2D.h"

namespace Altseed {

class ImageFont : public Font {
private:
    std::map<int32_t, std::shared_ptr<Texture2D>> imageGlyphs_;
    std::shared_ptr<Font> baseFont_;

public:
    ImageFont(std::shared_ptr<Font> baseFont);
    virtual ~ImageFont();

    void SetColor(Color color) override { baseFont_->SetColor(color); }
    Color GetColor() override { return baseFont_->GetColor(); }

    virtual void SetWeight(float weight) override { baseFont_->SetWeight(weight); }
    virtual float GetWeight() override { return baseFont_->GetWeight(); }

    virtual int32_t GetSize() override { return baseFont_->GetSize(); }
    virtual int32_t GetAscent() override { return baseFont_->GetAscent(); }
    virtual int32_t GetDescent() override { return baseFont_->GetDescent(); }
    virtual int32_t GetLineGap() override { return baseFont_->GetLineGap(); }

    virtual std::shared_ptr<Glyph> GetGlyph(const int32_t character) { return baseFont_->GetGlyph(character); }
    virtual std::shared_ptr<Texture2D> GetFontTexture(int32_t index) { return baseFont_->GetFontTexture(index); }

    virtual int32_t GetKerning(const int32_t c1, const int32_t c2) { return baseFont_->GetKerning(c1, c2); }
    virtual Vector2I CalcTextureSize(const char16_t* text, WritingDirection direction, bool isEnableKerning = true) override;

    void AddImageGlyph(const int32_t character, std::shared_ptr<Texture2D> texture);
    std::shared_ptr<Texture2D> GetImageGlyph(const int32_t character);

    static std::shared_ptr<ImageFont> CreateImageFont(std::shared_ptr<Font> baseFont);
};
}  // namespace Altseed