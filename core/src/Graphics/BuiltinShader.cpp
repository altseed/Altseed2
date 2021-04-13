#include "BuiltinShader.h"

#include "../Logger/Log.h"
#include "ShaderCompiler/ShaderCompiler.h"

namespace Altseed2 {

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
    c = mainTex.Sample(mainSamp, input.UV1) * input.Color;
    return c;
}
)";

const char* FontUnlitPS = R"(
Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);

cbuffer Consts : register(b1)
{
    float4 pxRange;
}

struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};

float median (float3 col)
{
    return max(min(col.r, col.g), min(max(col.r, col.g), col.b));
}

uint2 GetTextureSize(Texture2D texture_){
    uint width, height;
    texture_.GetDimensions(width, height);
    return uint2(width, height);
}

float screenPxRange(float2 uv) {
    float2 unitRange = pxRange.xx / float2(GetTextureSize(mainTex));
    float2 screenTexSize = 1.0.xx/fwidth(uv);
    return max(0.5 * dot(unitRange, screenTexSize), 1.0);
}

float4 main(PS_INPUT input) : SV_TARGET 
{
    float3 msd = mainTex.Sample(mainSamp, input.UV1).rgb;

    float sd = median(msd);
    float screenPxDistance = screenPxRange(input.UV1) * (sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);

    if (opacity <= 0.0) discard;
    // if (opacity <= 0.0) { return float4(input.UV1, 1.0, 0.3); }

    return float4(input.Color.rgb, opacity);
}
)";

std::shared_ptr<Shader> BuiltinShader::Create(BuiltinShaderType type) {
    auto found = shaders_.find(type);
    if (found != shaders_.end()) return found->second;

    if (type == BuiltinShaderType::SpriteUnlitVS) {
        auto shader = ShaderCompiler::GetInstance()->Compile("", "SpriteUnlitVS", SpriteUnlitVS, ShaderStageType::Vertex)->GetValue();
        shaders_[type] = shader;
        return shader;
    } else if (type == BuiltinShaderType::SpriteUnlitPS) {
        auto shader = ShaderCompiler::GetInstance()->Compile("", "SpriteUnlitPS", SpriteUnlitPS, ShaderStageType::Pixel)->GetValue();
        shaders_[type] = shader;
        return shader;
    } else if (type == BuiltinShaderType::FontUnlitPS) {
        auto shader = ShaderCompiler::GetInstance()->Compile("", "FontUnlitPS", FontUnlitPS, ShaderStageType::Pixel)->GetValue();
        shaders_[type] = shader;
        return shader;
    } else {
        LOG_CRITICAL(u"type is not found");
        assert(0);
    }
    return nullptr;
}

}  // namespace Altseed2