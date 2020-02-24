#include "BuildinShader.h"
#include "ShaderCompiler/ShaderCompiler.h"

namespace Altseed {

const char* SpriteUnlitVS = R"(
cbuffer Consts : register(b0)
{
  float4x4 matView;
  float4x4 matProjection;
};

struct VS_INPUT{
    float3 Position : POSITION0;
    float4 Color : COLOR0;
	float2 UV1 : UV0;
	float2 UV2 : UV1;
};
struct VS_OUTPUT{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
	float2  UV1 : UV0;
	float2  UV2 : UV1;
};
    
VS_OUTPUT main(VS_INPUT input){
    VS_OUTPUT output;
    float4 pos = float4(input.Position, 1.0f);

    pos = mul(matView, pos);
    pos = mul(matProjection, pos);

    output.Position = pos;
	output.UV1 = input.UV1;
	output.UV2 = input.UV2;
    output.Color = input.Color;
        
    return output;
}
)";

const char* SpriteUnlitPS = R"(
Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);
struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
	float2  UV1 : UV0;
	float2  UV2 : UV1;
};
float4 main(PS_INPUT input) : SV_TARGET 
{ 
	float4 c;
	c = mainTex.Sample(mainSamp, input.UV1);
	return c;
}
)";

const char* FontUnlitPS = R"(
Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);
struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
	float2  UV1 : UV0;
	float2  UV2 : UV1;
};
float4 main(PS_INPUT input) : SV_TARGET 
{ 
	float4 c;
	c = mainTex.Sample(mainSamp, input.UV1);

	c = lerp(float4(0, 0, 0, 0), float4(1, 1, 1, 1), (c - 0.5) * 255);
	c = lerp(float4(0, 0, 0, 0), float4(1, 1, 1, 1), c + 0.5);
	if (c.r > 1)
	{
		return float4(1, 1, 1, 1);
	}
	if (c.r > 0) 
	{
		c += 0.5;
		c = input.Color + c * c.a;
		return c;
	} 
	return (float)0;
}
)";

std::shared_ptr<Shader> BuildinShader::Create(BuildinShaderType type) {
    auto found = shaders_.find(type);
    if (found != shaders_.end()) return found->second;

    if (type == BuildinShaderType::SpriteUnlitVS) {
        auto shader = ShaderCompiler::GetInstance()->Compile("SpriteUnlitVS", SpriteUnlitVS, ShaderStageType::Vertex);
        shaders_[type] = shader;
        return shader;
    } else if (type == BuildinShaderType::SpriteUnlitPS) {
        auto shader = ShaderCompiler::GetInstance()->Compile("SpriteUnlitPS", SpriteUnlitPS, ShaderStageType::Pixel);
        shaders_[type] = shader;
        return shader;
    } else if (type == BuildinShaderType::FontUnlitPS) {
        auto shader = ShaderCompiler::GetInstance()->Compile("FontUnlitPS", FontUnlitPS, ShaderStageType::Pixel);
        shaders_[type] = shader;
        return shader;
    } else {
        assert(0);
    }
    return nullptr;
}

}  // namespace Altseed