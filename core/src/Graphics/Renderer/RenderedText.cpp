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

Vector2F RenderedText::IterateTexts(std::function<void(Vector2F pos, RectF src, float texScale, std::shared_ptr<TextureBase>& texture, bool isGlyph)> doEachText) {
    const auto font = GetFont();
    if (font == nullptr) return Vector2F(0.0f, 0.0f);

    auto& characters = GetTextAsStr();
    if (characters.size() == 0) Vector2F(0.0f, 0.0f);

    const auto fontSize = GetFontSize();
    if (fontSize == 0.0f) return Vector2F(0.0f, 0.0f);

    const auto samplingSize = (float)font->GetSamplingSize();
    const auto fontScale = fontSize / font->GetEmSize();
    const auto glyphScale = samplingSize / (font->GetAscent() - font->GetDescent());

    const auto writingDir = GetWritingDirection();

    const auto lineSpace = GetLineGap();

    // 各文字のオフセットを格納する
    Vector2F offset(0, 0);

    // 各ラインの最大長
    float lineMax = 0.0f;

    for (size_t i = 0; i < characters.size(); i++) {
        char32_t tmp = 0;
        ASD_ASSERT(i < characters.size(), "buffer overrun");

        ConvChU16ToU32({characters[i], i + 1 < characters.size() ? characters[i + 1] : u'\0'}, tmp);
        int32_t character = static_cast<int32_t>(tmp);

        // return
        if (character == '\n') {
            // 改行位置のリセット、次の行への移動
            if (writingDir == WritingDirection::Horizontal) {
                lineMax = std::fmax(lineMax, offset.X);
                offset = Vector2F(0, offset.Y + lineSpace);
            } else {
                lineMax = std::fmax(lineMax, offset.Y);
                offset = Vector2F(offset.X - lineSpace, 0);
            }
            continue;
        }

        // Surrogate pair
        if (characters[i] >= 0xD800 && characters[i] <= 0xDBFF) {
            i++;
        }

        RectF src;
        Vector2F pos;
        float texScale;
        std::shared_ptr<Glyph> glyph = nullptr;

        auto texture = font->GetImageGlyph(character);

        if (texture != nullptr) {
            auto texSize = texture->GetSize();

            src = RectF(0, 0, texSize.X, texSize.Y);

            pos = offset + Vector2F(0, font->GetAscent() * fontScale - fontSize);

            texScale = fontSize / texSize.Y;
        } else {
            glyph = font->GetGlyph(character);
            if (glyph == nullptr) continue;

            texture = font->GetFontTexture(glyph->GetTextureIndex());

            auto glyphPos = glyph->GetPosition();
            auto glyphSize = glyph->GetSize();
            src = RectF(glyphPos.X, glyphPos.Y, glyphSize.X, glyphSize.Y);

            pos = offset + Vector2F(0, font->GetAscent() * fontScale) + glyph->GetOffset() * fontScale;

            if (writingDir == WritingDirection::Vertical) {
                pos.X += -glyph->GetAdvance();
            }

            texScale = fontScale / glyphScale;
        }

        if (doEachText != nullptr) {
            doEachText(pos, src, texScale, texture, glyph != nullptr);
        }

        // advance
        if (writingDir == WritingDirection::Horizontal) {
            if (glyph != nullptr) {
                offset += Vector2F(glyph->GetAdvance() * fontScale, 0);
            } else {
                offset += Vector2F((float)texture->GetSize().X * fontSize / texture->GetSize().Y, 0);
            }
        } else {
            if (glyph != nullptr) {
                offset += Vector2F(0, (float)glyph->GetAdvance() * glyph->GetSize().Y / glyph->GetSize().X * fontScale);
            } else {
                offset += Vector2F(0, (float)texture->GetSize().Y * fontSize / texture->GetSize().X);
            }
        }

        // character spcae
        if (i != characters.size() - 1) {
            const auto space = GetCharacterSpace();
            if (writingDir == WritingDirection::Horizontal) {
                offset += Altseed2::Vector2F(space, 0);
            } else {
                offset += Altseed2::Vector2F(0, space);
            }
        }

        // kerning
        if (GetIsEnableKerning() && i != characters.size() - 1) {
            ConvChU16ToU32({characters[i + 1], i + 2 < characters.size() ? characters[i + 2] : u'\0'}, tmp);
            const int32_t next = static_cast<int32_t>(tmp);
            const auto kern = font->GetKerning(character, next) * fontScale;
            if (writingDir == WritingDirection::Horizontal) {
                offset += Altseed2::Vector2F(kern, 0);
            } else {
                offset += Altseed2::Vector2F(0, kern);
            }
        }
    }

    if (writingDir == WritingDirection::Horizontal) {
        return Vector2F(std::fmax(lineMax, offset.X), offset.Y + lineSpace);
    } else {
        return Vector2F(std::abs(offset.X - lineSpace), std::fmax(lineMax, offset.Y));
    }
}

Vector2F RenderedText::GetRenderingSize() {
    return IterateTexts(nullptr);
}

b2AABB RenderedText::GetAABB() {
    b2AABB res;
    auto size = GetRenderingSize();
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