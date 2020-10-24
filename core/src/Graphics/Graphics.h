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

#include "../Math/Vector2F.h"
#include "../Window/Window.h"
#include "Color.h"
#include "LLGIWindow.h"
#include "Material.h"
#include "Shader.h"
#include "Texture2D.h"

namespace Altseed2 {

const uint8_t TextureMinimumSize = 16;
const uint8_t TextureDefaultColor = 255;

class Sprite;
class Shader;
class Material;
class Camera;
class BuiltinShader;
class CommandList;
struct RenderPassParameter;

enum class GraphicsDeviceType {
    Default,
    DirectX12,
    Metal,
    Vulkan,
};

struct GraphicsInitializationParameter {
    GraphicsDeviceType Device;
    bool WaitVSync;

    operator LLGI::PlatformParameter() const;
};

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

    std::shared_ptr<CommandList> commandList_;
    std::shared_ptr<BuiltinShader> BuiltinShader_;

    LLGI::Platform* platform_;
    LLGI::Graphics* graphics_;

    std::shared_ptr<LLGI::Compiler> compiler_;

public:
    static std::shared_ptr<Graphics>& GetInstance();

    static bool Initialize(std::shared_ptr<Window>& window, GraphicsInitializationParameter& parameter);

    bool BeginFrame(const RenderPassParameter& renderPassParameter);

    bool EndFrame();

    bool DoEvents() const;

    static void Terminate();

    std::shared_ptr<LLGIWindow> GetLLGIWindow() const { return llgiWindow_; }

#if !USE_CBG

    LLGI::RenderPass* GetCurrentScreen(const LLGI::Color8& clearColor, bool isColorCleared = false, bool isDepthCleared = false);
    LLGI::RenderPassPipelineState* CreateRenderPassPipelineState(LLGI::RenderPass* renderpass);
    LLGI::PipelineState* CreatePipelineState();

    std::shared_ptr<LLGI::IndexBuffer> CreateIndexBuffer(int32_t stride, int32_t count);
    std::shared_ptr<LLGI::VertexBuffer> CreateVertexBuffer(int32_t size);
    std::shared_ptr<LLGI::Texture> CreateTexture(uint8_t* data, int32_t width, int32_t height, int32_t channel);
    std::shared_ptr<LLGI::Texture> CreateRenderTexture(int32_t width, int32_t height, TextureFormatType format = TextureFormatType::R8G8B8A8_UNORM);
    std::shared_ptr<LLGI::RenderPass> CreateRenderPass(LLGI::Texture* renderTexture);
    LLGI::Graphics* GetGraphicsLLGI() const { return graphics_; }
    LLGI::Platform* GetLLGIPlatform() const { return platform_; }
#endif

    std::shared_ptr<CommandList> GetCommandList() const { return commandList_; }
    std::shared_ptr<BuiltinShader> GetBuiltinShader() const { return BuiltinShader_; }

    void SaveScreenshot(const char16_t* path);
};
}  // namespace Altseed2
