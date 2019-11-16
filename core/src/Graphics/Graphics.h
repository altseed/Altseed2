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
#include "Shader.h"
#include "Texture2D.h"

namespace altseed {

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
    struct DrawGroup {
        int vb_offset;
        std::vector<std::shared_ptr<Sprite>> sprites;
    };

    static std::shared_ptr<Graphics> instance;
    std::shared_ptr<Window> window_;
    std::shared_ptr<LLGIWindow> llgiWindow_;
    int count;  // temp

    std::map<std::shared_ptr<LLGI::RenderPassPipelineState>, std::shared_ptr<LLGI::PipelineState>> pips;
    LLGI::Platform* platform_;
    LLGI::Graphics* graphics_;
    LLGI::SingleFrameMemoryPool* sfMemoryPool_;
    std::array<LLGI::CommandList*, 3> commandLists_;

    LLGI::Compiler* compiler_;

    std::shared_ptr<Shader> vs_;

    LLGI::IndexBuffer* ib;
    LLGI::VertexBuffer* vb;

    std::unordered_map<std::shared_ptr<LLGI::Texture>, DrawGroup> Groups;

    LLGI::ConstantBuffer* SendConstantBuffer(Camera* camera);
    void UpdateGroups();
    void Render(Camera* camera, LLGI::CommandList* commandList);

public:
    static bool Initialize(std::shared_ptr<Window>& window, LLGI::DeviceType deviceType = LLGI::DeviceType::Default);

    static std::shared_ptr<Graphics>& GetInstance();

    bool DoEvents() const { return window_->DoEvent(); }
    bool Update();

    static void Terminate();

    std::vector<std::shared_ptr<Sprite>> Sprites;
    std::vector<std::shared_ptr<Camera>> Cameras;
    std::shared_ptr<LLGI::Texture> CreateDameyTexture(uint8_t b);
    std::shared_ptr<LLGI::Texture> CreateTexture(uint8_t* data, int32_t width, int32_t height, int32_t channel);
    std::shared_ptr<LLGI::Texture> CreateRenderTexture(int32_t width, int32_t height);
    std::shared_ptr<LLGI::RenderPass> CreateRenderPass(LLGI::Texture* renderTexture);

    std::shared_ptr<Shader> CreateShader(const char* code, LLGI::ShaderStageType shaderStageType = LLGI::ShaderStageType::Pixel);

    const char* HlslVSCode = R"(
cbuffer Consts : register(b0)
{
  float4x4 matView;
  float4x4 matProjection;
};

struct VS_INPUT{
    float3 Position : POSITION0;
	float2 UV : UV0;
    float4 Color : COLOR0;
};
struct VS_OUTPUT{
    float4 Position : SV_POSITION;
	float2 UV : UV0;
    float4 Color : COLOR0;
};
    
VS_OUTPUT main(VS_INPUT input){
    VS_OUTPUT output;
    float4 pos = float4(input.Position, 1.0f);

    pos = mul(pos, matView);
    pos = mul(pos, matProjection);

    output.Position = pos;
	output.UV = input.UV;
    output.Color = input.Color;
        
    return output;
}
)";

    const char* HlslPSCode = R"(
Texture2D txt : register(t8);
SamplerState smp : register(s8);
struct PS_INPUT
{
    float4  Position : SV_POSITION;
	float2  UV : UV0;
    float4  Color    : COLOR0;
};
float4 main(PS_INPUT input) : SV_TARGET 
{ 
	float4 c;
	c = txt.Sample(smp, input.UV);
	return c;
}
)";
};
}  // namespace altseed
