#include "Graphics.h"
#include "Sprite.h"

#ifdef _WIN32
#pragma comment(lib, "d3dcompiler.lib")

#ifdef ENABLE_VULKAN
#pragma comment(lib, "vulkan-1.lib")
#endif

#endif

namespace altseed {

std::shared_ptr<Graphics> Graphics::instance = nullptr;

std::shared_ptr<Graphics>& Graphics::GetInstance() { return instance; }

bool Graphics::Intialize(LLGI::DeviceType deviceType) {
    instance = std::make_shared<Graphics>();

    instance->platform_ = LLGI::CreatePlatform(deviceType);
    LLGI::SafeAddRef(instance->platform_);
    if (instance->platform_ == nullptr) return false;

    instance->graphics_ = instance->platform_->CreateGraphics();
    // ? instance->graphics_->SetDisposed([]() -> void { instance->platform_->Release(); });
    if (instance->graphics_ == nullptr) return false;

    instance->sfMemoryPool_ = instance->graphics_->CreateSingleFrameMemoryPool(1024 * 1024, 128);
    instance->commandList_ = instance->graphics_->CreateCommandList(instance->sfMemoryPool_);

    instance->vb = instance->graphics_->CreateVertexBuffer(sizeof(SimpleVertex) * 1024);
    instance->ib = instance->graphics_->CreateIndexBuffer(2, 1024);

    auto compiler = LLGI::CreateCompiler(deviceType);

    std::vector<LLGI::DataStructure> data_vs;
    std::vector<LLGI::DataStructure> data_ps;

    if (compiler == nullptr) {
        return false;
    } else {
        LLGI::CompilerResult result_vs;
        LLGI::CompilerResult result_ps;

        if (instance->platform_->GetDeviceType() == LLGI::DeviceType::DirectX12) {
            compiler->Compile(result_vs, instance->HlslVSCode, LLGI::ShaderStageType::Vertex);
            assert(result_vs.Message == "");
            compiler->Compile(result_ps, instance->HlslPSCode, LLGI::ShaderStageType::Pixel);
            assert(result_ps.Message == "");
        } else
            return false;

        for (auto& b : result_vs.Binary) {
            LLGI::DataStructure d;
            d.Data = b.data();
            d.Size = b.size();
            data_vs.push_back(d);
        }

        for (auto& b : result_ps.Binary) {
            LLGI::DataStructure d;
            d.Data = b.data();
            d.Size = b.size();
            data_ps.push_back(d);
        }

        instance->vs_ = instance->graphics_->CreateShader(data_vs.data(), data_vs.size());
        instance->ps_ = instance->graphics_->CreateShader(data_ps.data(), data_ps.size());
    }

    return true;
}

bool Graphics::Update() {
    if (!platform_->NewFrame()) return false;

    instance->sfMemoryPool_->NewFrame();

    count++;

    LLGI::Color8 color;
    color.R = count % 255;
    color.G = 0;
    color.B = 0;
    color.A = 255;

    UpdateBuffers();

    auto renderPass = instance->graphics_->GetCurrentScreen(color, true);
    auto renderPassPipelineState = LLGI::CreateSharedPtr(renderPass->CreateRenderPassPipelineState());
    if (pips.count(renderPassPipelineState) == 0) {
        auto pip = graphics_->CreatePiplineState();
        pip->VertexLayouts[0] = LLGI::VertexLayoutFormat::R32G32B32_FLOAT;
        pip->VertexLayouts[1] = LLGI::VertexLayoutFormat::R32G32_FLOAT;
        pip->VertexLayouts[2] = LLGI::VertexLayoutFormat::R8G8B8A8_UNORM;
        pip->VertexLayoutNames[0] = "POSITION";
        pip->VertexLayoutNames[1] = "UV";
        pip->VertexLayoutNames[2] = "COLOR";
        pip->VertexLayoutCount = 3;

        pip->Culling = LLGI::CullingMode::DoubleSide;
        pip->SetShader(LLGI::ShaderStageType::Vertex, vs_);
        pip->SetShader(LLGI::ShaderStageType::Pixel, ps_);
        pip->SetRenderPassPipelineState(renderPassPipelineState.get());
        pip->Compile();

        pips[renderPassPipelineState] = LLGI::CreateSharedPtr(pip);
    }

    commandList_->Begin();
    commandList_->BeginRenderPass(renderPass);
    commandList_->SetVertexBuffer(vb, sizeof(SimpleVertex), 0);
    commandList_->SetIndexBuffer(ib);
    commandList_->SetPipelineState(pips[renderPassPipelineState].get());
    commandList_->Draw(PrimitiveCount);
    commandList_->EndRenderPass();
    commandList_->End();

    graphics_->Execute(commandList_);

    platform_->Present();

    count++;

    return true;
}

void Graphics::Terminate() {
    instance->graphics_->WaitFinish();
    LLGI::SafeRelease(instance->sfMemoryPool_);
    LLGI::SafeRelease(instance->commandList_);
    LLGI::SafeRelease(instance->vs_);
    LLGI::SafeRelease(instance->ps_);
    LLGI::SafeRelease(instance->ib);
    LLGI::SafeRelease(instance->vb);
    LLGI::SafeRelease(instance->graphics_);
    LLGI::SafeRelease(instance->platform_);
    instance = nullptr;
}

void Graphics::UpdateBuffers() {
    std::array<LLGI::Vec2F, 4> UVs = {LLGI::Vec2F(0.0f, 0.0f), LLGI::Vec2F(1.0f, 0.0f), LLGI::Vec2F(1.0f, 1.0f), LLGI::Vec2F(0.0f, 1.0f)};
    auto vb_buf = reinterpret_cast<SimpleVertex*>(vb->Lock());
    auto ib_buf = reinterpret_cast<uint16_t*>(ib->Lock());

    int vb_idx = 0;
    int ib_idx = 0;
    PrimitiveCount = 0;

    // TODO: check size of buffers
    for (int i = 0; i < Sprites.size(); i++) {
        auto s = Sprites[i];
        auto v = s->GetVertex();

        for (int j = 0; j < 4; j++) {
            vb_buf[vb_idx + j].Pos = {v[j].X, v[j].Y, 0.5f};
            vb_buf[vb_idx + j].UV = UVs[j];
            vb_buf[vb_idx + j].Color = LLGI::Color8();
        }

        ib_buf[ib_idx + 0] = vb_idx + 0;
        ib_buf[ib_idx + 1] = vb_idx + 1;
        ib_buf[ib_idx + 2] = vb_idx + 2;
        ib_buf[ib_idx + 3] = vb_idx + 0;
        ib_buf[ib_idx + 4] = vb_idx + 2;
        ib_buf[ib_idx + 5] = vb_idx + 3;
        vb_idx += 4;
        ib_idx += 6;
        PrimitiveCount += 2;
    }

    ib->Unlock();
    vb->Unlock();
}
}  // namespace altseed