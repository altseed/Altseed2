#pragma once

#include <map>
#include <memory>
#include <vector>

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

namespace altseed {

class Sprite;

struct SimpleVertex {
    LLGI::Vec3F Pos;
    LLGI::Vec2F UV;
    LLGI::Color8 Color;
};

class Graphics {
    struct DrawGroup {
        int vb_offset;
        std::vector<std::shared_ptr<Sprite>> sprites;
    };

    static std::shared_ptr<Graphics> instance;
    int count;  // temp

    std::map<std::shared_ptr<LLGI::RenderPassPipelineState>, std::shared_ptr<LLGI::PipelineState>> pips;
    LLGI::Platform* platform_;
    LLGI::Graphics* graphics_;
    LLGI::SingleFrameMemoryPool* sfMemoryPool_;
    LLGI::CommandList* commandList_;

    LLGI::Shader* ps_;
    LLGI::Shader* vs_;

    LLGI::IndexBuffer* ib;
    LLGI::VertexBuffer* vb;

    std::unordered_map<LLGI::Texture*, DrawGroup> Groups;
    void UpdateBuffers();

public:
    static bool Intialize(LLGI::DeviceType deviceType = LLGI::DeviceType::Default /*std::shared_ptr<Window>& window*/);

    static std::shared_ptr<Graphics>& GetInstance();

    bool Update();

    static void Terminate();

    std::vector<std::shared_ptr<Sprite>> Sprites;
    LLGI::Texture* CreateDameyTexture(uint8_t b);

private:
    const char* HlslVSCode = R"(
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
        
    output.Position = float4(input.Position, 1.0f);
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
	c.a = 255;
	return c;
}
)";
};
}  // namespace altseed