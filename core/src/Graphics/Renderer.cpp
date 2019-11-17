#include "Renderer.h"
#include "Graphics.h"

// hogehoge
#include <glslang/Public/ShaderLang.h>
#include <spirv_cross/spirv.hpp>

namespace altseed {

bool Renderer::Initialize() {
    sfMemoryPool_ = Graphics::GetInstance()->CreateSingleFrameMemoryPool(1024 * 1024, 128);

    for (int i = 0; i < commandLists_.size(); i++) {
        commandLists_[i] = Graphics::GetInstance()->CreateCommandList(sfMemoryPool_);
    }

    indexBuffer_ = Graphics::GetInstance()->CreateIndexBuffer(2, 1024);
    vertexBuffer_ = Graphics::GetInstance()->CreateVertexBuffer(sizeof(SimpleVertex) * 1024);

    vs_ = Graphics::GetInstance()->CreateShader(HlslVSCode, LLGI::ShaderStageType::Vertex);

    return true;  // todo error check
}

LLGI::CommandList* Renderer::Render() {
    count++;
    UpdateGroups();

    sfMemoryPool_->NewFrame();
    auto commandList = commandLists_[count % commandLists_.size()];

    commandList->Begin();
    for (auto c : Cameras) {
        if (c->GetTarget() != nullptr) Render(c, commandList);
    }
    Render(nullptr, commandList);
    commandList->End();

    return commandList.get();
}

void Renderer::Render(std::shared_ptr<Camera> camera, std::shared_ptr<LLGI::CommandList> commandList) {
    auto vsConsts = SendConstantBuffer(camera.get());

    LLGI::RenderPass* renderPass;
    if (camera == nullptr) {
        LLGI::Color8 color;
        color.R = count % 255;
        color.G = 0;
        color.B = 0;
        color.A = 255;
        renderPass = Graphics::GetInstance()->GetCurrentScreen(color, true);

    } else {
        renderPass = camera->GetTarget()->GetRenderPass();
    }

    commandList->BeginRenderPass(renderPass);
    auto renderPassPipelineState = LLGI::CreateSharedPtr(Graphics::GetInstance()->CreateRenderPassPipelineState(renderPass));
    if (pips.count(renderPassPipelineState) == 0) {
        auto pip = Graphics::GetInstance()->CreatePipelineState();
        pip->VertexLayouts[0] = LLGI::VertexLayoutFormat::R32G32B32_FLOAT;
        pip->VertexLayouts[1] = LLGI::VertexLayoutFormat::R32G32_FLOAT;
        pip->VertexLayouts[2] = LLGI::VertexLayoutFormat::R8G8B8A8_UNORM;
        pip->VertexLayoutNames[0] = "POSITION";
        pip->VertexLayoutNames[1] = "UV";
        pip->VertexLayoutNames[2] = "COLOR";
        pip->VertexLayoutCount = 3;

        pip->Culling = LLGI::CullingMode::DoubleSide;
        pip->SetShader(LLGI::ShaderStageType::Vertex, vs_->Get());
        pip->SetShader(LLGI::ShaderStageType::Pixel, Sprites[0]->GetMaterial()->GetShader()->Get());
        pip->SetRenderPassPipelineState(renderPassPipelineState.get());
        pip->Compile();

        pips[renderPassPipelineState] = LLGI::CreateSharedPtr(pip);
    }

    for (auto& g : Groups) {
        commandList->SetIndexBuffer(indexBuffer_.get());
        commandList->SetVertexBuffer(vertexBuffer_.get(), sizeof(SimpleVertex), g.second.vb_offset * sizeof(SimpleVertex));
        commandList->SetPipelineState(pips[renderPassPipelineState].get());
        commandList->SetTexture(
                g.first.get(), LLGI::TextureWrapMode::Repeat, LLGI::TextureMinMagFilter::Nearest, 0, LLGI::ShaderStageType::Pixel);
        commandList->SetConstantBuffer(vsConsts, LLGI::ShaderStageType::Vertex);
        commandList->Draw(g.second.sprites.size() * 2);
    }
    commandList->EndRenderPass();

    LLGI::SafeRelease(vsConsts);
}

LLGI::ConstantBuffer* Renderer::SendConstantBuffer(Camera* camera) {
    auto vsConsts = sfMemoryPool_->CreateConstantBuffer(sizeof(VSConstants));
    if (camera == nullptr) {
        auto vsConstsBuf = static_cast<VSConstants*>(vsConsts->Lock());

        vsConstsBuf->Projection.fill(0);
        vsConstsBuf->View.fill(0);

        for (int64_t i = 0; i < 4; i++) {
            vsConstsBuf->View[i * 4 + i] = 1.0f;
            vsConstsBuf->Projection[i * 4 + i] = 1.0f;
        }
        auto windowSize = Graphics::GetInstance()->GetLLGIWindow()->GetWindowSize();
        vsConstsBuf->Projection[0 * 4 + 0] = 2.0 / windowSize.X;
        vsConstsBuf->Projection[1 * 4 + 1] = -2.0 / windowSize.Y;
        vsConstsBuf->Projection[3 * 4 + 0] = -1.0f;
        vsConstsBuf->Projection[3 * 4 + 1] = +1.0f;
        vsConsts->Unlock();
    } else {
        auto vsConstsBuf = static_cast<VSConstants*>(vsConsts->Lock());
        vsConstsBuf->Projection = camera->GetProjectionMatrix();
        vsConstsBuf->View = camera->GetViewMatrix();
        vsConsts->Unlock();
    }
    return vsConsts;
}

void Renderer::UpdateGroups() {
    std::array<LLGI::Vec2F, 4> UVs = {LLGI::Vec2F(0.0f, 0.0f), LLGI::Vec2F(1.0f, 0.0f), LLGI::Vec2F(1.0f, 1.0f), LLGI::Vec2F(0.0f, 1.0f)};
    auto vb_buf = reinterpret_cast<SimpleVertex*>(vertexBuffer_->Lock());
    auto ib_buf = reinterpret_cast<uint16_t*>(indexBuffer_->Lock());

    int vb_idx = 0;
    int maxPrimitiveCount = 0;

    Groups.clear();
    for (int i = 0; i < Sprites.size(); i++) {
        Groups[Sprites[i]->GetTexture()].sprites.push_back(Sprites[i]);
    }

    for (auto& g : Groups) {
        g.second.vb_offset = vb_idx;

        // TODO: check size of buffers
        for (int i = 0; i < g.second.sprites.size(); i++) {
            auto s = g.second.sprites[i];
            auto w = Graphics::GetInstance()->GetLLGIWindow()->GetWindowSize();
            auto v = s->GetVertex(w);

            for (int j = 0; j < 4; j++) {
                vb_buf[vb_idx + j].Pos = {v[j].X, v[j].Y, 0.5f};
                vb_buf[vb_idx + j].UV = UVs[j];
                vb_buf[vb_idx + j].Color = LLGI::Color8();
            }

            vb_idx += 4;
        }
        maxPrimitiveCount = std::max<int>(maxPrimitiveCount, g.second.sprites.size());
    }

    for (int i = 0; i < maxPrimitiveCount; i++) {
        ib_buf[i * 6 + 0] = i * 4 + 0;
        ib_buf[i * 6 + 1] = i * 4 + 1;
        ib_buf[i * 6 + 2] = i * 4 + 2;
        ib_buf[i * 6 + 3] = i * 4 + 0;
        ib_buf[i * 6 + 4] = i * 4 + 2;
        ib_buf[i * 6 + 5] = i * 4 + 3;
    }

    indexBuffer_->Unlock();
    vertexBuffer_->Unlock();
};
}  // namespace altseed