#include "Renderer.h"

#include "../../Common/StringHelper.h"
#include "../../Logger/Log.h"
#include "../../Math/Vector2I.h"
#include "../../Window/Window.h"
#include "../BuiltinShader.h"
#include "../CommandList.h"
#include "../Font.h"
#include "../Graphics.h"
#include "../RenderTexture.h"
#include "RenderedCamera.h"
#include "RenderedPolygon.h"
#include "RenderedSprite.h"
#include "RenderedText.h"

#ifdef _WIN32
#undef DrawText
#endif

namespace Altseed2 {

std::shared_ptr<Renderer> Renderer::instance_;

std::shared_ptr<Renderer>& Renderer::GetInstance() { return instance_; }

bool Renderer::Initialize(
        std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics, std::shared_ptr<CullingSystem> cullingSystem) {
    instance_ = MakeAsdShared<Renderer>(window, graphics, cullingSystem);

    return true;
}

void Renderer::Terminate() { instance_ = nullptr; }

Renderer::Renderer(std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics, std::shared_ptr<CullingSystem> cullingSystem)
    : window_(window), graphics_(graphics), cullingSystem_(cullingSystem) {
    batchRenderer_ = std::make_shared<BatchRenderer>(graphics_);
    ResetCamera();
}

Renderer::~Renderer() {}

void Renderer::DrawPolygon(std::shared_ptr<RenderedPolygon> polygon) {
    if (polygon->GetVertexes() == nullptr) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Renderer::DrawPolygon: Vertexes is null");
        return;
    }

    std::shared_ptr<TextureBase> texture = polygon->GetTexture();

    RectF src = polygon->GetSrc();
    Vector2F size;
    if (texture == nullptr) {
        size = Vector2F(TextureMinimumSize, TextureMinimumSize);
    } else {
        size = texture->GetSize().To2F();
    }

    auto vs = std::vector<BatchVertex>(polygon->GetVertexes()->GetVector());
    for (auto&& v : vs) {
        // NOTE: Do NOT overwrite UV1, UV2 and Col so that original values which RenderedPolygon provides are applied.
        v.Pos = polygon->GetTransform().Transform3D(v.Pos);
    }

    auto material = polygon->GetMaterial();

    if (material == nullptr) {
        material = batchRenderer_->GetMaterialDefaultSprite(polygon->GetAlphaBlend());
    }

    auto ib = polygon->GetBuffers()->GetVector();

    batchRenderer_->Draw(vs.data(), ib.data(), vs.size(), ib.size(), texture, material, nullptr);
}

void Renderer::Render() {
    // Window doesn't have a callback to notify that a size is changed, so get an window size directly
    if (currentCamera_ == nullptr) {
        int32_t w, h = 0;
        window_->GetSize(w, h);
        batchRenderer_->SetViewProjectionWithWindowsSize(Vector2I(w, h));
    }

    batchRenderer_->Render();
    batchRenderer_->ResetCache();
}

void Renderer::DrawSprite(std::shared_ptr<RenderedSprite> sprite) {
    auto texture = sprite->GetTexture();
    auto src = sprite->GetSrc();

    std::array<BatchVertex, 4> vs;
    vs[0].Pos.X = 0;
    vs[0].Pos.Y = 0;
    vs[0].Pos.Z = 0.5f;

    vs[1].Pos.X = src.Width;
    vs[1].Pos.Y = 0;
    vs[1].Pos.Z = 0.5f;

    vs[2].Pos.X = src.Width;
    vs[2].Pos.Y = src.Height;
    vs[2].Pos.Z = 0.5f;

    vs[3].Pos.X = 0.0f;
    vs[3].Pos.Y = src.Height;
    vs[3].Pos.Z = 0.5f;

    vs[0].UV1.X = src.X;
    vs[0].UV1.Y = src.Y;
    vs[1].UV1.X = src.X + src.Width;
    vs[1].UV1.Y = src.Y;
    vs[2].UV1.X = src.X + src.Width;
    vs[2].UV1.Y = src.Y + src.Height;
    vs[3].UV1.X = src.X;
    vs[3].UV1.Y = src.Y + src.Height;

    auto textureSize = (texture == nullptr ? Vector2I(TextureMinimumSize, TextureMinimumSize) : texture->GetSize()).To2F();
    for (size_t i = 0; i < 4; i++) {
        vs[i].UV1 /= textureSize;
        vs[i].UV2 = Vector2F();  // There is no valid UV2 because BatchVertex is NOT provided by RenderedSprite.
        vs[i].Col = sprite->GetColor();
        vs[i].Pos = sprite->GetTransform().Transform3D(vs[i].Pos);
    }

    int ib[6];
    ib[0] = 0;
    ib[1] = 1;
    ib[2] = 2;
    ib[3] = 2;
    ib[4] = 3;
    ib[5] = 0;

    auto material = sprite->GetMaterial();

    if (material == nullptr) {
        material = batchRenderer_->GetMaterialDefaultSprite(sprite->GetAlphaBlend());
    }

    batchRenderer_->Draw(vs.data(), ib, 4, 6, texture, material, nullptr);
}

void Renderer::DrawText(std::shared_ptr<RenderedText> text) {
    const auto font = text->GetFont();
    if (font == nullptr) return;

    const auto& characters = text->GetTextAsStr();

    auto materialGlyph = text->GetMaterialGlyph();
    if (materialGlyph == nullptr) {
        materialGlyph = batchRenderer_->GetMaterialDefaultText(text->GetAlphaBlend());
    }

    materialGlyph->SetVector4F(u"pxRange", Vector4F(font->GetPxRange(), 0.0f, 0.0f, 0.0f));

    auto materialImage = text->GetMaterialImage();
    if (materialImage == nullptr) {
        materialImage = batchRenderer_->GetMaterialDefaultSprite(text->GetAlphaBlend());
    }

    const auto fontSize = (float)text->GetFontSize();
    const auto samplingSize = (float)font->GetSamplingSize();
    const auto fontScale = fontSize / font->GetEmSize();

    Vector2F offset(0, 0);
    for (size_t i = 0; i < characters.size(); i++) {
        char32_t tmp = 0;
        ASD_ASSERT(i < characters.size(), "buffer overrun");

        ConvChU16ToU32({characters[i], i + 1 < characters.size() ? characters[i + 1] : u'\0'}, tmp);
        int32_t character = static_cast<int32_t>(tmp);

        // return
        if (character == '\n') {
            if (text->GetWritingDirection() == WritingDirection::Horizontal)
                offset = Vector2F(0, offset.Y + text->GetLineSpace());
            else
                offset = Vector2F(offset.X - text->GetLineSpace(), 0);
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

            if (text->GetWritingDirection() == WritingDirection::Vertical) {
                pos.X += -glyph->GetAdvance();
            }

            texScale = fontScale / glyph->GetScale();
        }

        int ib[] = {0, 1, 2, 2, 3, 0};
        std::array<BatchVertex, 4> vs;

        vs[0].Pos.X = pos.X;
        vs[0].Pos.Y = pos.Y;
        vs[0].Pos.Z = 0.5f;

        vs[1].Pos.X = pos.X + src.Width * texScale;
        vs[1].Pos.Y = pos.Y;
        vs[1].Pos.Z = 0.5f;

        vs[2].Pos.X = pos.X + src.Width * texScale;
        vs[2].Pos.Y = pos.Y + src.Height * texScale;
        vs[2].Pos.Z = 0.5f;

        vs[3].Pos.X = pos.X;
        vs[3].Pos.Y = pos.Y + src.Height * texScale;
        vs[3].Pos.Z = 0.5f;

        vs[0].UV1.X = src.X;
        vs[0].UV1.Y = src.Y;
        vs[1].UV1.X = src.X + src.Width;
        vs[1].UV1.Y = src.Y;
        vs[2].UV1.X = src.X + src.Width;
        vs[2].UV1.Y = src.Y + src.Height;
        vs[3].UV1.X = src.X;
        vs[3].UV1.Y = src.Y + src.Height;

        auto textureSize = texture->GetSize().To2F();
        for (size_t i = 0; i < 4; i++) {
            vs[i].UV1 /= textureSize;
            vs[i].UV2 = Vector2F();  // There is no valid UV2 because BatchVertex is NOT provided by RenderedSprite.
            vs[i].Col = text->GetColor();

            vs[i].Pos = text->GetTransform().Transform3D(vs[i].Pos);
        }

        auto material = (glyph == nullptr) ? materialImage : materialGlyph;
        batchRenderer_->Draw(vs.data(), ib, 4, 6, texture, material, nullptr);

        // advance
        if (text->GetWritingDirection() == WritingDirection::Horizontal) {
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
            const auto space = text->GetCharacterSpace();
            if (text->GetWritingDirection() == WritingDirection::Horizontal) {
                offset += Altseed2::Vector2F(space, 0);
            } else {
                offset += Altseed2::Vector2F(0, space);
            }
        }

        // kerning
        if (text->GetIsEnableKerning() && i != characters.size() - 1) {
            ConvChU16ToU32({characters[i + 1], i + 2 < characters.size() ? characters[i + 2] : u'\0'}, tmp);
            const int32_t next = static_cast<int32_t>(tmp);
            const auto kern = font->GetKerning(character, next) * fontScale;
            if (text->GetWritingDirection() == WritingDirection::Horizontal)
                offset += Altseed2::Vector2F(kern, 0);
            else
                offset += Altseed2::Vector2F(0, kern);
        }
    }
}

void Renderer::SetCamera(std::shared_ptr<RenderedCamera> camera) {
    std::shared_ptr<RenderTexture> texture;
    if (camera->GetTargetTexture() != nullptr) {
        texture = camera->GetTargetTexture();
    } else {
        texture = Graphics::GetInstance()->GetCommandList()->GetScreenTexture();
    }

    currentCamera_ = camera;

    RectI viewport(Vector2I(0, 0), texture->GetSize());
    RenderPassParameter param = camera->GetRenderPassParameter();
    Graphics::GetInstance()->GetCommandList()->SetRenderTarget(texture, param);

    batchRenderer_->SetViewProjection(camera->GetViewMatrix(), camera->GetProjectionMatrix());
    auto aabb = camera->GetAABB();
    cullingSystem_->Cull(
            RectF(aabb.lowerBound.x, aabb.lowerBound.y, aabb.upperBound.x - aabb.lowerBound.x, aabb.upperBound.y - aabb.lowerBound.y));
}

void Renderer::ResetCamera() {
    currentCamera_ = nullptr;

    int32_t w, h = 0;
    window_->GetSize(w, h);
    batchRenderer_->SetViewProjectionWithWindowsSize(Vector2I(w, h));
}

}  // namespace Altseed2