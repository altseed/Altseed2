#include "Renderer.h"

#include "../../Common/StringHelper.h"
#include "../../Logger/Log.h"
#include "../../Math/Vector2I.h"
#include "../../Window/Window.h"
#include "../CommandList.h"
#include "../Font.h"
#include "../RenderTexture.h"
#include "RenderedCamera.h"
#include "RenderedPolygon.h"
#include "RenderedSprite.h"
#include "RenderedText.h"
#include "../Graphics.h"
#include "../BuiltinShader.h"

namespace Altseed {

std::shared_ptr<Renderer> Renderer::instance_;

std::shared_ptr<Renderer>& Renderer::GetInstance() { return instance_; }

bool Renderer::Initialize(std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics) {
    instance_ = MakeAsdShared<Renderer>(window, graphics);

    return true;
}

void Renderer::Terminate() { instance_ = nullptr; }

Renderer::Renderer(std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics) : window_(window), graphics_(graphics) {
    renderedBatchRenderer_ = std::make_shared<BatchRenderer>(graphics_);
    batchRenderer_ = std::make_shared<BatchRenderer>(graphics_);
    ResetCamera();
}

Renderer::~Renderer() {}

void Renderer::DrawPolygon(
        const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Texture2D>& texture) {
    batchRenderer_->Draw(vb, ib, vbCount, ibCount, texture, nullptr, nullptr);
}

void Renderer::DrawPolygon(
        const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Material>& material) {
    batchRenderer_->Draw(vb, ib, vbCount, ibCount, nullptr, material, nullptr);
}

void Renderer::DrawPolygon(
        std::shared_ptr<VertexArray> vb,
        std::shared_ptr<Int32Array> ib,
        const std::shared_ptr<Texture2D>& texture,
        const std::shared_ptr<Material>& material) {
    batchRenderer_->Draw(
            static_cast<BatchVertex*>(vb->GetData()),
            static_cast<int32_t*>(ib->GetData()),
            vb->GetCount(),
            ib->GetCount(),
            texture,
            material,
            nullptr);
}

void Renderer::DrawPolygon(std::shared_ptr<RenderedPolygon> polygon) {
    std::shared_ptr<Texture2D> texture = polygon->GetTexture();

    RectF src = polygon->GetSrc();
    Vector2F size;
    if (texture == nullptr) {
        size = Vector2F(TextureMinimumSize, TextureMinimumSize);
    } else {
        size = texture->GetSize().To2F();
    }

    std::vector<BatchVertex> vs;
    vs.resize(polygon->GetVertexes()->GetCount());
    for (int i = 0; i < vs.size(); ++i) {
        vs[i] = polygon->GetVertexes()->GetVector()[i];
        vs[i].UV1.X = (src.X + vs[i].UV1.X * src.Width) / size.X;
        vs[i].UV1.Y = (src.Y + vs[i].UV1.Y * src.Width) / size.Y;
        vs[i].UV2 = vs[i].UV1;
        vs[i].Pos = polygon->GetTransform().Transform3D(vs[i].Pos);
    }

    std::vector<int> ib;
    ib.resize((vs.size() - 2) * 3);
    for (int i = 0; i < vs.size() - 2; ++i) {
        ib[i * 3 + 0] = 0;
        ib[i * 3 + 1] = i + 1;
        ib[i * 3 + 2] = i + 2;
    }

    auto material = polygon->GetMaterial();

    if (material == nullptr) {
        material = batchRenderer_->GetMaterialDefaultSprite();
    }

    batchRenderer_->Draw(vs.data(), ib.data(), vs.size(), ib.size(), texture, material, nullptr);
}

void Renderer::Render(std::shared_ptr<CommandList> commandList) {
    renderedBatchRenderer_->Render(commandList.get());
    renderedBatchRenderer_->ResetCache();
    batchRenderer_->Render(commandList.get());

    batchRenderer_->ResetCache();
}

void Renderer::DrawSprite(std::shared_ptr<RenderedSprite> sprite) {
    std::shared_ptr<Texture2D> texture = sprite->GetTexture();

    std::array<BatchVertex, 4> vs;
    vs[0].Pos.X = 0;
    vs[0].Pos.Y = 0;
    vs[0].Pos.Z = 0.5f;

    vs[1].Pos.X = sprite->GetSrc().Width;
    vs[1].Pos.Y = 0;
    vs[1].Pos.Z = 0.5f;

    vs[2].Pos.X = sprite->GetSrc().Width;
    vs[2].Pos.Y = sprite->GetSrc().Height;
    vs[2].Pos.Z = 0.5f;

    vs[3].Pos.X = 0.0f;
    vs[3].Pos.Y = sprite->GetSrc().Height;
    vs[3].Pos.Z = 0.5f;

    vs[0].UV1.X = sprite->GetSrc().X;
    vs[0].UV1.Y = sprite->GetSrc().Y;
    vs[1].UV1.X = sprite->GetSrc().X + sprite->GetSrc().Width;
    vs[1].UV1.Y = sprite->GetSrc().Y;
    vs[2].UV1.X = sprite->GetSrc().X + sprite->GetSrc().Width;
    vs[2].UV1.Y = sprite->GetSrc().Y + sprite->GetSrc().Height;
    vs[3].UV1.X = sprite->GetSrc().X;
    vs[3].UV1.Y = sprite->GetSrc().Y + sprite->GetSrc().Height;

    for (size_t i = 0; i < 4; i++) {
        if(texture == nullptr) {
            vs[i].UV1.X = vs[i].UV1.X / TextureMinimumSize;
            vs[i].UV1.Y = vs[i].UV1.Y / TextureMinimumSize;
        } else {
            vs[i].UV1.X = vs[i].UV1.X / texture->GetSize().X;
            vs[i].UV1.Y = vs[i].UV1.Y / texture->GetSize().Y;
        }

        vs[i].Col.R = TextureDefaultColor;
        vs[i].Col.G = TextureDefaultColor;
        vs[i].Col.B = TextureDefaultColor;
        vs[i].Col.A = TextureDefaultColor;

        vs[i].UV2 = vs[i].UV1;

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
        material = batchRenderer_->GetMaterialDefaultSprite();
    }

    renderedBatchRenderer_->Draw(vs.data(), ib, 4, 6, texture, material, nullptr);
}

#ifdef _WIN32
#undef DrawText
#endif
void Renderer::DrawText(std::shared_ptr<RenderedText> text) {
    const auto& characters = text->GetTextAsStr();

    auto material = text->GetMaterial();

    if (material == nullptr) {
        material = batchRenderer_->GetMaterialDefaultText();
    }

    material->SetVector4F(u"weight", Vector4F(0.5f - text->GetWeight() / 255.0f, 0.0f, 0.0f, 0.0f));

    // 改行を想定してVector2F
    Vector2F offset(0, 0);
    for (size_t i = 0; i < characters.size(); i++) {
        char32_t tmp = 0;
        ASD_ASSERT(i < characters.size(), "buffer overrun");

        ConvChU16ToU32({characters[i], i + 1 < characters.size() ? characters[i + 1] : u'\0'}, tmp);
        int32_t character = static_cast<int32_t>(tmp);

        // Surrogate pair
        if (characters[i] >= 0xD800 && characters[i] <= 0xDBFF) {
            i++;
        }

        RectF src;
        Vector2F pos;
        Vector2F scale;
        std::shared_ptr<Glyph> glyph = nullptr;

        auto texture = text->GetFont()->GetImageGlyph(character);
        if (texture != nullptr) {
            src = RectF(Altseed::RectF(0, 0, texture->GetSize().X, texture->GetSize().Y));

            pos = offset;

            scale = Vector2F(
                    (float)text->GetFont()->GetSize() / texture->GetSize().Y, (float)text->GetFont()->GetSize() / texture->GetSize().Y);
        } else {
            glyph = text->GetFont()->GetGlyph(character);
            if (glyph == nullptr) continue;

            texture = text->GetFont()->GetFontTexture(glyph->GetTextureIndex());

            src = RectF(glyph->GetPosition().X, glyph->GetPosition().Y, glyph->GetSize().X, glyph->GetSize().Y);

            pos = offset + glyph->GetOffset().To2F() + Vector2F(0, text->GetFont()->GetAscent());

            scale = Vector2F(1, 1);
        }

        int ib[] = {0, 1, 2, 2, 3, 0};
        std::array<BatchVertex, 4> vs;

        vs[0].Pos.Z = 0.5f;
        vs[1].Pos.Z = 0.5f;
        vs[2].Pos.Z = 0.5f;
        vs[3].Pos.Z = 0.5f;

        vs[0].Pos.X = pos.X;
        vs[0].Pos.Y = pos.Y;

        vs[1].Pos.X = pos.X + src.Width * scale.X;
        vs[1].Pos.Y = pos.Y;

        vs[2].Pos.X = pos.X + src.Width * scale.X;
        vs[2].Pos.Y = pos.Y + src.Height * scale.Y;

        vs[3].Pos.X = pos.X;
        vs[3].Pos.Y = pos.Y + src.Height * scale.Y;

        vs[0].UV1.X = src.X;
        vs[0].UV1.Y = src.Y;
        vs[1].UV1.X = src.X + src.Width;
        vs[1].UV1.Y = src.Y;
        vs[2].UV1.X = src.X + src.Width;
        vs[2].UV1.Y = src.Y + src.Height;
        vs[3].UV1.X = src.X;
        vs[3].UV1.Y = src.Y + src.Height;

        for (size_t i = 0; i < 4; i++) {
            vs[i].UV1.X = vs[i].UV1.X / texture->GetSize().X;
            vs[i].UV1.Y = vs[i].UV1.Y / texture->GetSize().Y;
            vs[i].UV2 = vs[i].UV1;

            vs[i].Col = text->GetColor();
            vs[i].Pos = text->GetTransform().Transform3D(vs[i].Pos);
        }

        renderedBatchRenderer_->Draw(vs.data(), ib, 4, 6, texture, glyph != nullptr ? material : nullptr, nullptr);

        if (glyph != nullptr)
            offset += Vector2F(glyph->GetGlyphWidth(), 0);
        else
            offset += Vector2F((float)texture->GetSize().X * text->GetFont()->GetSize() / texture->GetSize().Y, 0);

        if (i != characters.size() - 1) {
            ConvChU16ToU32({characters[i + 1], i + 2 < characters.size() ? characters[i + 2] : u'\0'}, tmp);
            int32_t next = static_cast<int32_t>(tmp);
            offset += Altseed::Vector2F(text->GetFont()->GetKerning(character, next), 0);
        }
    }
}

void Renderer::SetCamera(std::shared_ptr<RenderedCamera> camera) {
    if (camera->GetTargetTexture() != nullptr) {
        RectI viewport(Vector2I(0, 0), camera->GetTargetTexture()->GetSize());
        Graphics::GetInstance()->GetCommandList()->SetRenderTarget(camera->GetTargetTexture(), viewport);
    } else {
        Graphics::GetInstance()->GetCommandList()->SetRenderTargetWithScreen();
    }

    renderedBatchRenderer_->SetViewProjection(camera->GetCameraMatrix(), camera->GetProjectionMatrix());
    batchRenderer_->SetViewProjection(camera->GetCameraMatrix(), camera->GetProjectionMatrix());
}

void Renderer::ResetCamera() {
    int32_t w, h = 0;
    window_->GetSize(w, h);
    batchRenderer_->SetViewProjectionWithWindowsSize(Vector2I(w, h));
    renderedBatchRenderer_->SetViewProjectionWithWindowsSize(Vector2I(w, h));
}

}  // namespace Altseed