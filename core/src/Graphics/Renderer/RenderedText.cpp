#include "RenderedText.h"

#include "../../Math/RectF.h"
#include "../../Math/Vector4F.h"
#include "../BuiltinShader.h"
#include "../Graphics.h"
#include "../Material.h"

namespace Altseed2 {

std::shared_ptr<RenderedText> RenderedText::Create() {
    auto t = MakeAsdShared<RenderedText>();
    t->SetAlphaBlend(AlphaBlend::Normal());
    t->SetIsEnableKerning(true);
    t->SetWritingDirection(WritingDirection::Horizontal);
    t->SetText(u"");
    t->SetCharacterSpace(0);
    t->SetLineGap(0);
    t->SetColor(Color(TextureDefaultColor, TextureDefaultColor, TextureDefaultColor, TextureDefaultColor));
    t->SetMaterialGlyph(nullptr);
    t->SetMaterialImage(nullptr);
    t->SetFontSize(32);

    return t;
}

void RenderedText::SetText(const char16_t* text) {
    text_ = text == nullptr ? u"" : std::u16string(text);
    cullingSystem_->RequestUpdateAABB(this);
}

Vector2F RenderedText::GetTextureSize() {
    if (GetFont() == nullptr) {
        return Vector2F(0, 0);
    }

    auto fontSize = (float)GetFontSize();
    auto samplingSize = (float)font_->GetSamplingSize();
    auto fontScale = fontSize / samplingSize;

    const auto& characters = GetTextAsStr();

    Vector2F offset(0, 0);
    float lineOffset = 0;
    for (size_t i = 0; i < characters.size(); i++) {
        char32_t tmp = 0;
        ASD_ASSERT(i < characters.size(), "buffer overrun");

        ConvChU16ToU32({characters[i], i + 1 < characters.size() ? characters[i + 1] : u'\0'}, tmp);
        int32_t character = static_cast<int32_t>(tmp);

        // return
        if (character == '\n') {
            if (writingDirection_ == WritingDirection::Horizontal)
                offset = Vector2F(fmax(offset.X, lineOffset), offset.Y + GetLineSpace());
            else
                offset = Vector2F(offset.X - GetLineSpace(), fmax(offset.Y, lineOffset));
            lineOffset = 0;
            continue;
        }

        // Surrogate pair
        if (characters[i] >= 0xD800 && characters[i] <= 0xDBFF) {
            i++;
        }

        RectF src;
        Vector2F pos;
        std::shared_ptr<Glyph> glyph = nullptr;

        auto texture = GetFont()->GetImageGlyph(character);
        if (texture != nullptr) {
            auto texSize = texture->GetSize();
            src = RectF(RectF(0, 0, texSize.X, texSize.Y));

            pos = offset + Vector2F(0, GetFont()->GetAscent() * fontScale - fontSize);
        } else {
            glyph = GetFont()->GetGlyph(character);
            if (glyph == nullptr) continue;

            texture = GetFont()->GetFontTexture(glyph->GetTextureIndex());
            
            auto glyphPos = glyph->GetPosition();
            auto glyphSize = glyph->GetSize();
            src = RectF(glyphPos.X, glyphPos.Y, glyphSize.X, glyphSize.Y);

            pos = offset + glyph->GetOffset() * fontScale + Vector2F(0, GetFont()->GetAscent() * fontScale);

            if (GetWritingDirection() == WritingDirection::Vertical) {
                pos.X += -glyph->GetAdvance();
            }
        }

        // advance
        if (writingDirection_ == WritingDirection::Horizontal) {
            if (glyph != nullptr) {
                lineOffset += glyph->GetAdvance() * fontScale;
            } else {
                lineOffset += (float)texture->GetSize().X * fontSize / texture->GetSize().Y;
            }
        } else {
            if (glyph != nullptr) {
                lineOffset += (float)glyph->GetAdvance() * glyph->GetSize().Y / glyph->GetSize().X * fontScale;
            } else {
                lineOffset += (float)texture->GetSize().Y * fontSize / texture->GetSize().X;
            }
        }

        // character spcae
        if (i != characters.size() - 1) lineOffset += GetCharacterSpace();

        // kerning
        if (isEnableKerning_ && i != characters.size() - 1) {
            ConvChU16ToU32({characters[i + 1], i + 2 < characters.size() ? characters[i + 2] : u'\0'}, tmp);
            int32_t next = static_cast<int32_t>(tmp);
            lineOffset += GetFont()->GetKerning(character, next) * fontScale;
        }
    }

    // update ofset
    if (writingDirection_ == WritingDirection::Horizontal)
        offset.X = fmax(offset.X, lineOffset);
    else
        offset.Y = fmax(offset.Y, lineOffset);
    offset.Y += GetFont()->GetAscent() - GetFont()->GetDescent();

    return offset;
}

b2AABB RenderedText::GetAABB() {
    b2AABB res;
    auto size = GetTextureSize();
    auto vertexes = std::array<Vector3F, 4>();
    vertexes[0] = Vector3F();
    vertexes[1] = Vector3F(size.X, 0, 0);
    vertexes[2] = Vector3F(size.X, size.Y, 0);
    vertexes[3] = Vector3F(0, size.Y, 0);
    res.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
    res.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
    for (auto&& _v : vertexes) {
        auto v = transform_.Transform3D(_v);
        res.lowerBound = b2Vec2(res.lowerBound.x > v.X ? v.X : res.lowerBound.x, res.lowerBound.y > v.Y ? v.Y : res.lowerBound.y);
        res.upperBound = b2Vec2(res.upperBound.x < v.X ? v.X : res.upperBound.x, res.upperBound.y < v.Y ? v.Y : res.upperBound.y);
    }
    return res;
}

}  // namespace Altseed2