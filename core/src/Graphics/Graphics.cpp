#include "Graphics.h"

#include "../Logger/Log.h"
#include "BuiltinShader.h"
#include "Camera.h"
#include "CommandList.h"
#include "FrameDebugger.h"

#ifdef _WIN32
#pragma comment(lib, "d3dcompiler.lib")

#ifdef ENABLE_VULKAN
#pragma comment(lib, "vulkan-1.lib")
#endif

#endif

namespace Altseed {

GraphicsInitializationParameter::operator LLGI::PlatformParameter() const {
    LLGI::PlatformParameter pp;

    switch (this->Device) {
        case GraphicsDeviceType::Default:
            pp.Device = LLGI::DeviceType::Default;
            break;
        case GraphicsDeviceType::DirectX12:
            pp.Device = LLGI::DeviceType::DirectX12;
            break;
        case GraphicsDeviceType::Metal:
            pp.Device = LLGI::DeviceType::Metal;
            break;
        case GraphicsDeviceType::Vulkan:
            pp.Device = LLGI::DeviceType::Vulkan;
            break;
    }
    pp.WaitVSync = this->WaitVSync;

    return pp;
}

std::shared_ptr<Graphics> Graphics::instance = nullptr;

std::shared_ptr<Graphics>& Graphics::GetInstance() { return instance; }

bool Graphics::Initialize(std::shared_ptr<Window>& window, GraphicsInitializationParameter& parameter) {
    instance = CreateSharedPtr(new Graphics());

    LLGI::PlatformParameter pp = parameter;

    instance->window_ = window;
    instance->llgiWindow_ = std::make_shared<LLGIWindow>(window->GetNativeWindow());
    instance->platform_ = LLGI::CreatePlatform(pp, instance->llgiWindow_.get());
    if (instance->platform_ == nullptr) {
        LOG_CRITICAL(u"Graphics::Initialize: Failed to CreatePlatform");
        return false;
    }

    instance->graphics_ = instance->platform_->CreateGraphics();
    // ? instance->graphics_->SetDisposed([]() -> void { instance->platform_->Release(); });
    if (instance->graphics_ == nullptr) {
        LOG_CRITICAL(u"Graphics::Initialize: Failed to CreateGraphics");
        return false;
    }

    instance->compiler_ = LLGI::CreateCompiler(pp.Device);

    instance->BuiltinShader_ = MakeAsdShared<BuiltinShader>();
    instance->commandList_ = CommandList::Create();

    instance->clearColor_ = Color(50, 50, 50, 255);

    return true;
}

bool Graphics::BeginFrame() {
    if (!platform_->NewFrame()) return false;

    commandList_->StartFrame();
    RectI viewport(Vector2I(0, 0), commandList_->GetScreenTexture()->GetSize());
    commandList_->SetRenderTarget(commandList_->GetScreenTexture(), viewport);
    return true;
}

bool Graphics::EndFrame() {
    commandList_->PresentInternal();
    commandList_->EndFrame();
    graphics_->Execute(commandList_->GetLL());

    platform_->Present();

    FrameDebugger::GetInstance()->EndFrame();
    return true;
}

bool Graphics::DoEvents() const { return window_->DoEvent(); }

void Graphics::Terminate() {
    ASD_VERIFY(instance != nullptr, "instance must be not null.")
    instance->graphics_->WaitFinish();
    LLGI::SafeRelease(instance->graphics_);
    LLGI::SafeRelease(instance->platform_);
    instance = nullptr;
}

LLGI::RenderPass* Graphics::GetCurrentScreen(const LLGI::Color8& clearColor, bool isColorCleared, bool isDepthCleared) {
    return instance->platform_->GetCurrentScreen(clearColor, isColorCleared, isDepthCleared);
}

LLGI::RenderPassPipelineState* Graphics::CreateRenderPassPipelineState(LLGI::RenderPass* renderpass) {
    return instance->graphics_->CreateRenderPassPipelineState(renderpass);
}

LLGI::PipelineState* Graphics::CreatePipelineState() { return instance->graphics_->CreatePiplineState(); }

std::shared_ptr<LLGI::IndexBuffer> Graphics::CreateIndexBuffer(int32_t stride, int32_t count) {
    return LLGI::CreateSharedPtr(instance->graphics_->CreateIndexBuffer(stride, count));
}

std::shared_ptr<LLGI::VertexBuffer> Graphics::CreateVertexBuffer(int32_t size) {
    return LLGI::CreateSharedPtr(instance->graphics_->CreateVertexBuffer(size));
}

std::shared_ptr<LLGI::Texture> Graphics::CreateTexture(uint8_t* data, int32_t width, int32_t height, int32_t channel) {
    LLGI::TextureInitializationParameter params;
    params.Format = LLGI::TextureFormatType::R8G8B8A8_UNORM;
    params.Size = LLGI::Vec2I(width, height);

    std::shared_ptr<LLGI::Texture> texture = LLGI::CreateSharedPtr(graphics_->CreateTexture(params));
    if (texture == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Graphics::CreateTexture: failed");
        return nullptr;
    }

    auto texture_buf = (LLGI::Color8*)texture->Lock();
    if (channel == 4) {
        for (int32_t y = 0; y < height; y++) {
            for (int32_t x = 0; x < width; x++) {
                texture_buf[x + y * width].R = data[4 * (x + y * width)];
                texture_buf[x + y * width].G = data[4 * (x + y * width) + 1];
                texture_buf[x + y * width].B = data[4 * (x + y * width) + 2];
                texture_buf[x + y * width].A = data[4 * (x + y * width) + 3];
            }
        }
    } else if (channel == 3) {
        for (int32_t y = 0; y < height; y++) {
            for (int32_t x = 0; x < width; x++) {
                texture_buf[x + y * width].R = data[3 * (x + y * width)];
                texture_buf[x + y * width].G = data[3 * (x + y * width) + 1];
                texture_buf[x + y * width].B = data[3 * (x + y * width) + 2];
                texture_buf[x + y * width].A = 255;
            }
        }
    } else if (channel == 1) {
        for (int32_t y = 0; y < height; y++) {
            for (int32_t x = 0; x < width; x++) {
                texture_buf[x + y * width].R = data[x + y * width];
                texture_buf[x + y * width].G = data[x + y * width];
                texture_buf[x + y * width].B = data[x + y * width];
                texture_buf[x + y * width].A = 255;
            }
        }
    }

    texture->Unlock();
    return texture;
}

std::shared_ptr<LLGI::Texture> Graphics::CreateRenderTexture(int32_t width, int32_t height) {
    LLGI::RenderTextureInitializationParameter params;
    params.Format = LLGI::TextureFormatType::R8G8B8A8_UNORM;
    params.Size = LLGI::Vec2I(width, height);
    std::shared_ptr<LLGI::Texture> texture = LLGI::CreateSharedPtr(graphics_->CreateRenderTexture(params));
    if (texture == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Graphics::CreateRenderTexture: failed");
        return nullptr;
    }
    return texture;
}

std::shared_ptr<LLGI::RenderPass> Graphics::CreateRenderPass(LLGI::Texture* renderTexture) {
    return LLGI::CreateSharedPtr(graphics_->CreateRenderPass((const LLGI::Texture**)&renderTexture, 1, nullptr));
}

}  // namespace Altseed
