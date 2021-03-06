#include <BaseObject.h>
#include <ShaderTranspilerCore.h>
#include <gtest/gtest.h>

#include <thread>

TEST(ShaderCompiler, Basic) {
    const char* constantVS = R"(

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
   
cbuffer CB : register(b0)
{
  float4 offset;
  float4 offset1;
  float4 offset2;

};
VS_OUTPUT main(VS_INPUT input){
    VS_OUTPUT output;
        
    output.Position = float4(input.Position, 1.0f) + offset;
	output.UV = input.UV;
    output.Color = input.Color;
        
    return output;
}

)";

    const char* constantPS = R"(

cbuffer CB : register(b1)
{
  float4 offset;
  float4 offset1;
  float4 offset2;
};
struct PS_INPUT
{
    float4  Position : SV_POSITION;
	float2  UV : UV0;
    float4  Color    : COLOR0;
};
float4 main(PS_INPUT input) : SV_TARGET 
{ 
	float4 c;
	c = input.Color + offset;
	c.a = 1.0f;
	return c;
}

)";

    const char* texturePS = R"(

Texture2D txt : register(t0);
SamplerState smp : register(s0);
Texture2D txt2 : register(t1);
SamplerState smp2 : register(s1);

struct PS_INPUT
{
    float4  Position : SV_POSITION;
	float2  UV : UV0;
    float4  Color    : COLOR0;
};
float4 main(PS_INPUT input) : SV_TARGET 
{ 
	float4 c;
	c = input.Color * txt.Sample(smp, input.UV);
	return c;
}

)";
    LLGI::SPIRVGenerator generator([](std::string s) -> std::vector<uint8_t> { return std::vector<uint8_t>(); });
    std::vector<LLGI::SPIRVGeneratorMacro> macros;

    {
        auto spirv = generator.Generate("", constantVS, macros, LLGI::ShaderStageType::Vertex, false);
        auto reflection = LLGI::SPIRVReflection();
        reflection.Transpile(spirv);

        for (auto& u : reflection.Uniforms) {
            if (u.Name == "offset1") {
                ASSERT_EQ(u.Offset, 16);
            }

            if (u.Name == "offset2") {
                ASSERT_EQ(u.Offset, 32);
            }
        }
    }

    {
        auto spirv = generator.Generate("", constantPS, macros, LLGI::ShaderStageType::Pixel, false);
        auto reflection = LLGI::SPIRVReflection();
        reflection.Transpile(spirv);

        for (auto& u : reflection.Uniforms) {
            if (u.Name == "offset") {
                ASSERT_EQ(u.Offset, 0);
            }

            if (u.Name == "offset1") {
                ASSERT_EQ(u.Offset, 16);
            }

            if (u.Name == "offset2") {
                ASSERT_EQ(u.Offset, 32);
            }
        }
    }

    {
        auto spirv = generator.Generate("", texturePS, macros, LLGI::ShaderStageType::Pixel, false);
        auto reflection = LLGI::SPIRVReflection();
        reflection.Transpile(spirv);

        for (auto& u : reflection.Textures) {
            if (u.Name == "txt") {
                ASSERT_EQ(u.Offset, 0);
            }

            if (u.Name == "txt2") {
                ASSERT_EQ(u.Offset, 1);
            }
        }
    }
}