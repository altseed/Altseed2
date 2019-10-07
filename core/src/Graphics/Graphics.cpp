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

bool Graphics::Initialize(std::shared_ptr<Window>& window, LLGI::DeviceType deviceType) {
    instance = std::make_shared<Graphics>();

    instance->llgiWindow = std::make_shared<LLGIWindow>(window->GetNativeWindow());
    instance->platform_ = LLGI::CreatePlatform(deviceType, instance->llgiWindow.get());
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

    auto renderPass = instance->platform_->GetCurrentScreen(color, true);
    auto renderPassPipelineState = LLGI::CreateSharedPtr(instance->graphics_->CreateRenderPassPipelineState(renderPass));
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
    for (auto& g : Groups) {
        commandList_->SetVertexBuffer(vb, sizeof(SimpleVertex), g.second.vb_offset * sizeof(SimpleVertex));
        commandList_->SetIndexBuffer(ib);
        commandList_->SetPipelineState(pips[renderPassPipelineState].get());
        commandList_->SetTexture(
                g.first, LLGI::TextureWrapMode::Repeat, LLGI::TextureMinMagFilter::Nearest, 0, LLGI::ShaderStageType::Pixel);
        commandList_->Draw(g.second.sprites.size() * 2);
    }
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
            auto v = s->GetVertex();

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

    ib->Unlock();
    vb->Unlock();
}

LLGI::Texture* Graphics::CreateDameyTexture(uint8_t b) {
    auto texture = graphics_->CreateTexture(LLGI::Vec2I(256, 256), false, false);

    auto texture_buf = (LLGI::Color8*)texture->Lock();
    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 256; x++) {
            texture_buf[x + y * 256].R = x;
            texture_buf[x + y * 256].G = y;
            texture_buf[x + y * 256].B = b;
            texture_buf[x + y * 256].A = 255;
        }
    }
    texture->Unlock();
    return texture;
}

}  // namespace altseed