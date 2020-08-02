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

    return t;
}

Vector2F RenderedText::GetTextureSize() {
    if (GetFont() == nullptr) {
        return Vector2F(0, 0);
    }

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
            if (writingDirection_ == WritingDirection::Horizontal) {
                offset = Vector2F(fmax(offset.X, lineOffset), offset.Y + GetLineGap());
                lineOffset = 0;
            } else {
                offset = Vector2F(offset.X - GetLineGap(), fmax(offset.Y, lineOffset));
                lineOffset = 0;
            }
            continue;
        }

        // Surrogate pair
        if (characters[i] >= 0xD800 && characters[i] <= 0xDBFF) {
            i++;
        }

        RectF src;
        Vector2F pos;
        Vector2F scale;
        std::shared_ptr<Glyph> glyph = nullptr;

        auto texture = GetFont()->GetImageGlyph(character);
        if (texture != nullptr) {
            src = RectF(RectF(0, 0, texture->GetSize().X, texture->GetSize().Y));

            pos = offset;

            scale = Vector2F((float)GetFont()->GetSize() / texture->GetSize().Y, (float)GetFont()->GetSize() / texture->GetSize().Y);
        } else {
            glyph = GetFont()->GetGlyph(character);
            if (glyph == nullptr) continue;

            texture = GetFont()->GetFontTexture(glyph->GetTextureIndex());

            src = RectF(glyph->GetPosition().X, glyph->GetPosition().Y, glyph->GetSize().X, glyph->GetSize().Y);

            pos = offset + glyph->GetOffset().To2F() + Vector2F(0, GetFont()->GetAscent());

            scale = Vector2F(1, 1) * GetFont()->GetActualScale();
        }

        if (writingDirection_ == WritingDirection::Horizontal) {
            if (glyph != nullptr)
                lineOffset += glyph->GetGlyphWidth();
            else
                lineOffset += (float)texture->GetSize().X * GetFont()->GetSize() / texture->GetSize().Y;
        } else {
            if (glyph != nullptr)
                lineOffset += (float)glyph->GetGlyphWidth() * glyph->GetSize().Y / glyph->GetSize().X;
            else
                lineOffset += (float)texture->GetSize().Y * GetFont()->GetSize() / texture->GetSize().X;
        }

        // character spcae
        if (i != characters.size() - 1) lineOffset += GetCharacterSpace();

        // kerning
        if (isEnableKerning_ && i != characters.size() - 1) {
            ConvChU16ToU32({characters[i + 1], i + 2 < characters.size() ? characters[i + 2] : u'\0'}, tmp);
            int32_t next = static_cast<int32_t>(tmp);
            lineOffset += GetFont()->GetKerning(character, next);
        }
    }
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