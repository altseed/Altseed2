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

#include <memory>
#include <unordered_map>
#include <vector>

#include "../BaseObject.h"
#include "../Math/Vector2DF.h"
#include "../Window/Window.h"
#include "Camera.h"
#include "Material.h"
#include "RenderTexture.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture2D.h"

namespace altseed {

class Camera;
class Shader;
class Sprite;
class RenderTexture;

class Renderer : public BaseObject {
    struct DrawGroup {
        int vb_offset;
        std::vector<std::shared_ptr<Sprite>> sprites;
    };

    std::shared_ptr<Shader> vs_;

    std::map<std::shared_ptr<LLGI::RenderPassPipelineState>, std::shared_ptr<LLGI::PipelineState>> pips;
    std::shared_ptr<LLGI::SingleFrameMemoryPool> sfMemoryPool_;
    std::array<std::shared_ptr<LLGI::CommandList>, 3> commandLists_;
    std::shared_ptr<LLGI::IndexBuffer> indexBuffer_;
    std::shared_ptr<LLGI::VertexBuffer> vertexBuffer_;

    int count;  // temp

private:
    std::unordered_map<std::shared_ptr<LLGI::Texture>, DrawGroup> Groups;

    void UpdateGroups();
    void Render(std::shared_ptr<Camera> camera, std::shared_ptr<LLGI::CommandList> commandList);
    LLGI::ConstantBuffer* SendConstantBuffer(Camera* camera);

public:
    std::vector<std::shared_ptr<Sprite>> Sprites;
    std::vector<std::shared_ptr<Camera>> Cameras;

    bool Initialize();
    LLGI::CommandList* Render();
    // void Terminate();

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
