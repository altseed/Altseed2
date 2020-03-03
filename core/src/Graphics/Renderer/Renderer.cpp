#include "Renderer.h"

#include "../../Math/Vector2I.h"
#include "../../Window/Window.h"
#include "../CommandList.h"
#include "../Graphics.h"
#include "../RenderTexture.h"
#include "RenderedCamera.h"
#include "RenderedSprite.h"

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

void Renderer::Render(std::shared_ptr<CommandList> commandList) {
    renderedBatchRenderer_->Render(commandList.get());
    renderedBatchRenderer_->ResetCache();
    batchRenderer_->Render(commandList.get());

    batchRenderer_->ResetCache();
}

void Renderer::DrawSprite(std::shared_ptr<RenderedSprite> sprite) {
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
        vs[i].UV1.X = vs[i].UV1.X / sprite->GetTexture()->GetSize().X;
        vs[i].UV1.Y = vs[i].UV1.Y / sprite->GetTexture()->GetSize().Y;
        vs[i].Col = Color(255, 255, 255, 255);
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

    renderedBatchRenderer_->Draw(vs.data(), ib, 4, 6, sprite->GetTexture(), sprite->GetMaterial(), nullptr);
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