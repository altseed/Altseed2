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

namespace Altseed2 {

class ImageFont : public Font {
private:
    std::map<int32_t, std::shared_ptr<Texture2D>> imageGlyphs_;
    std::shared_ptr<Font> baseFont_;

public:
    ImageFont(std::shared_ptr<Font> baseFont);

    int32_t GetSize() override { return baseFont_->GetSize(); }
    int32_t GetAscent() override { return baseFont_->GetAscent(); }
    int32_t GetDescent() override { return baseFont_->GetDescent(); }
    int32_t GetLineGap() override { return baseFont_->GetLineGap(); }

    bool GetIsStaticFont() override { return baseFont_->GetIsStaticFont(); }

    std::shared_ptr<Glyph> GetGlyph(const int32_t character) override { return baseFont_->GetGlyph(character); }
    std::shared_ptr<Texture2D> GetFontTexture(int32_t index) override { return baseFont_->GetFontTexture(index); }

    int32_t GetKerning(const int32_t c1, const int32_t c2) override { return baseFont_->GetKerning(c1, c2); }

    void AddImageGlyph(const int32_t character, std::shared_ptr<Texture2D> texture) override;
    std::shared_ptr<Texture2D> GetImageGlyph(const int32_t character) override;
};
}  // namespace Altseed2