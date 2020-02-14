#include "Renderer.h"
#include "../../Math/Vector2I.h"
#include "../../Window/Window.h"
#include "../CommandList.h"
#include "../Graphics.h"
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

void Renderer::Render(std::shared_ptr<CommandList> commandList) {
    int32_t w, h = 0;
    window_->GetSize(w, h);

    batchRenderer_->SetViewProjectionWithWindowsSize(Vector2I(w, h));
    renderedBatchRenderer_->SetViewProjectionWithWindowsSize(Vector2I(w, h));

    for (auto o : objects_) {
        // TOTO switch static
        auto s = dynamic_cast<RenderedSprite*>(o.get());

        if (s != nullptr) {
            std::array<BatchVertex, 4> vs;
            vs[0].Pos.X = 0;
            vs[0].Pos.Y = 0;
            vs[0].Pos.Z = 0.5f;

            vs[1].Pos.X = s->GetSrc().Width;
            vs[1].Pos.Y = 0;
            vs[1].Pos.Z = 0.5f;

            vs[2].Pos.X = s->GetSrc().Width;
            vs[2].Pos.Y = s->GetSrc().Height;
            vs[2].Pos.Z = 0.5f;

            vs[3].Pos.X = 0.0f;
            vs[3].Pos.Y = s->GetSrc().Height;
            vs[3].Pos.Z = 0.5f;

            vs[0].UV1.X = s->GetSrc().X;
            vs[0].UV1.Y = s->GetSrc().Y;
            vs[1].UV1.X = s->GetSrc().X + s->GetSrc().Width;
            vs[1].UV1.Y = s->GetSrc().Y;
            vs[2].UV1.X = s->GetSrc().X + s->GetSrc().Width;
            vs[2].UV1.Y = s->GetSrc().Y + s->GetSrc().Height;
            vs[3].UV1.X = s->GetSrc().X;
            vs[3].UV1.Y = s->GetSrc().Y + s->GetSrc().Height;

            for (size_t i = 0; i < 4; i++) {
                vs[i].UV1.X = vs[i].UV1.X / s->GetTexture()->GetSize().X;
                vs[i].UV1.Y = vs[i].UV1.Y / s->GetTexture()->GetSize().Y;
                vs[i].Col = Color(255, 255, 255, 255);
                vs[i].UV2 = vs[i].UV1;

                vs[i].Pos = s->GetTransform().Transform3D(vs[i].Pos);
            }

            int ib[6];
            ib[0] = 0;
            ib[1] = 1;
            ib[2] = 2;
            ib[3] = 2;
            ib[4] = 3;
            ib[5] = 0;

            renderedBatchRenderer_->Draw(vs.data(), ib, 4, 6, s->GetTexture(), s->GetMaterial(), nullptr);
        }
    }

    renderedBatchRenderer_->Render(commandList.get());
    renderedBatchRenderer_->ResetCache();
    batchRenderer_->Render(commandList.get());
}

void Renderer::Reset() { batchRenderer_->ResetCache(); }

std::shared_ptr<RenderedCamera> Renderer::CreateCamera() {
    auto ret = MakeAsdShared<RenderedCamera>();
    objects_.push_back(ret);
    return ret;
}

std::shared_ptr<RenderedSprite> Renderer::CreateSprite() {
    auto ret = MakeAsdShared<RenderedSprite>();
    objects_.push_back(ret);
    return ret;
}

}  // namespace Altseed