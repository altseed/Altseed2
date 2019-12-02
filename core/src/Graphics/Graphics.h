#pragma once

#include <LLGI.Base.h>
#include <LLGI.CommandList.h>
#include <LLGI.Compiler.h>
#include <LLGI.ConstantBuffer.h>
#include <LLGI.Graphics.h>
#include <LLGI.IndexBuffer.h>
#include <LLGI.PipelineState.h>
#include <LLGI.Platform.h>
#include <LLGI.Shader.h>
#include <LLGI.Texture.h>
#include <LLGI.VertexBuffer.h>

#include <array>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../Math/Vector2DF.h"
#include "../Window/Window.h"
#include "LLGIWindow.h"
#include "Material.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture2D.h"

namespace altseed {

class Renderer;
class Sprite;
class Shader;
class Material;
class Camera;

struct VSConstants {
    std::array<float, 16> View;
    std::array<float, 16> Projection;
};

struct SimpleVertex {
    LLGI::Vec3F Pos;
    LLGI::Vec2F UV;
    LLGI::Color8 Color;
};

class Graphics : public BaseObject {
    static std::shared_ptr<Graphics> instance;
    std::shared_ptr<Window> window_;
    std::shared_ptr<LLGIWindow> llgiWindow_;

    std::shared_ptr<Renderer> renderer_;

    LLGI::Platform* platform_;
    LLGI::Graphics* graphics_;

    LLGI::Compiler* compiler_;

public:
    static std::shared_ptr<Graphics>& GetInstance();

    static bool Initialize(std::shared_ptr<Window>& window, LLGI::DeviceType deviceType = LLGI::DeviceType::Default);

    std::shared_ptr<Renderer> CreateRenderer();

    bool DoEvents() const { return window_->DoEvent(); }
    bool Update();

    static void Terminate();

    std::shared_ptr<LLGIWindow> GetLLGIWindow() const { return llgiWindow_; }

    std::shared_ptr<LLGI::Texture> CreateDameyTexture(uint8_t b);

    LLGI::RenderPass* GetCurrentScreen(const LLGI::Color8& clearColor, bool isColorCleared = false, bool isDepthCleared = false);
    LLGI::RenderPassPipelineState* CreateRenderPassPipelineState(LLGI::RenderPass* renderpass);
    LLGI::PipelineState* CreatePipelineState();

    std::shared_ptr<LLGI::SingleFrameMemoryPool> CreateSingleFrameMemoryPool(int32_t size, int32_t count);
    std::shared_ptr<LLGI::CommandList> CreateCommandList(std::shared_ptr<LLGI::SingleFrameMemoryPool> sfMemoryPool);
    std::shared_ptr<LLGI::IndexBuffer> CreateIndexBuffer(int32_t stride, int32_t count);
    std::shared_ptr<LLGI::VertexBuffer> CreateVertexBuffer(int32_t size);
    std::shared_ptr<LLGI::Texture> CreateTexture(uint8_t* data, int32_t width, int32_t height, int32_t channel);
    std::shared_ptr<LLGI::Texture> CreateRenderTexture(int32_t width, int32_t height);
    std::shared_ptr<LLGI::RenderPass> CreateRenderPass(LLGI::Texture* renderTexture);
	LLGI::Graphics* GetGraphicsLLGI() const { return graphics_; }

};
}  // namespace altseed
