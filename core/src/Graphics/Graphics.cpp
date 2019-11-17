#include "Graphics.h"

#include "Camera.h"
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

    instance->window_ = window;
    instance->llgiWindow_ = std::make_shared<LLGIWindow>(window->GetNativeWindow());
    instance->platform_ = LLGI::CreatePlatform(deviceType, instance->llgiWindow_.get());
    if (instance->platform_ == nullptr) return false;

    instance->graphics_ = instance->platform_->CreateGraphics();
    // ? instance->graphics_->SetDisposed([]() -> void { instance->platform_->Release(); });
    if (instance->graphics_ == nullptr) return false;

    instance->compiler_ = LLGI::CreateCompiler(deviceType);

    return true;
}

std::shared_ptr<Renderer> Graphics::CreateRenderer() {
    auto obj = std::make_shared<Renderer>();
    if (!obj->Initialize()) return nullptr;
    renderer_ = obj;
    return obj;
}

bool Graphics::Update() {
    if (!platform_->NewFrame()) return false;
    auto commandList = renderer_->Render();
    // if (commandList == nullptr) return false;
    graphics_->Execute(commandList);
    platform_->Present();
    return true;
}

void Graphics::Terminate() {
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

std::shared_ptr<LLGI::SingleFrameMemoryPool> Graphics::CreateSingleFrameMemoryPool(int32_t size, int32_t count) {
    return LLGI::CreateSharedPtr(instance->graphics_->CreateSingleFrameMemoryPool(1024 * 1024, 128));
}

std::shared_ptr<LLGI::CommandList> Graphics::CreateCommandList(std::shared_ptr<LLGI::SingleFrameMemoryPool> sfMemoryPool) {
    return LLGI::CreateSharedPtr(instance->graphics_->CreateCommandList(sfMemoryPool.get()));
}

std::shared_ptr<LLGI::IndexBuffer> Graphics::CreateIndexBuffer(int32_t stride, int32_t count) {
    return LLGI::CreateSharedPtr(instance->graphics_->CreateIndexBuffer(stride, count));
}

std::shared_ptr<LLGI::VertexBuffer> Graphics::CreateVertexBuffer(int32_t size) {
    return LLGI::CreateSharedPtr(instance->graphics_->CreateVertexBuffer(size));
}

std::shared_ptr<Shader> Graphics::CreateShader(const char* code, LLGI::ShaderStageType shaderStageType) {
    if (instance->compiler_ == nullptr) return nullptr;

    std::vector<LLGI::DataStructure> data;
    LLGI::CompilerResult result;

    if (instance->platform_->GetDeviceType() == LLGI::DeviceType::DirectX12) {
        instance->compiler_->Compile(result, code, shaderStageType);
        assert(result.Message == "");
    } else
        return nullptr;

    for (auto& b : result.Binary) {
        LLGI::DataStructure d;
        d.Data = b.data();
        d.Size = b.size();
        data.push_back(d);
    }

    auto obj = std::make_shared<Shader>();
    obj->SetShaderBinary(instance->graphics_->CreateShader(data.data(), data.size()));

    return obj;
}

std::shared_ptr<LLGI::Texture> Graphics::CreateDameyTexture(uint8_t b) {
    LLGI::TextureInitializationParameter texParam;
    texParam.Size = LLGI::Vec2I(256, 256);

    std::shared_ptr<LLGI::Texture> texture = LLGI::CreateSharedPtr(graphics_->CreateTexture(texParam));
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

std::shared_ptr<LLGI::Texture> Graphics::CreateTexture(uint8_t* data, int32_t width, int32_t height, int32_t channel) {
    LLGI::TextureInitializationParameter params;
    params.Format = LLGI::TextureFormatType::R8G8B8A8_UNORM;
    params.Size = LLGI::Vec2I(width, height);

    std::shared_ptr<LLGI::Texture> texture = LLGI::CreateSharedPtr(graphics_->CreateTexture(params));
    if (texture == nullptr) return nullptr;

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
    if (texture == nullptr) return nullptr;
    return texture;
}

std::shared_ptr<LLGI::RenderPass> Graphics::CreateRenderPass(LLGI::Texture* renderTexture) {
    return LLGI::CreateSharedPtr(graphics_->CreateRenderPass((const LLGI::Texture**)&renderTexture, 1, nullptr));
}

}  // namespace altseed
