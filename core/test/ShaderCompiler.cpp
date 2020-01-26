#include <BaseObject.h>
#include <Graphics/ShaderCompiler/ShaderTranspiler.h>
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

Texture2D txt : register(t8);
SamplerState smp : register(s8);
Texture2D txt2 : register(t9);
SamplerState smp2 : register(s9);

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
    altseed::SPIRVGenerator generator;
    generator.Initialize();

    {
        auto spirv = generator.Generate(constantVS, altseed::ShaderStageType::Vertex);
        auto reflection = altseed::SPIRVReflection();
        reflection.Transpile(spirv);

        for (auto& u : reflection.Uniforms) {
            if (u.Name == u"offset1") {
                ASSERT_EQ(u.Offset, 16);
            }

            if (u.Name == u"offset2") {
                ASSERT_EQ(u.Offset, 32);
            }
        }
    }

    {
        auto spirv = generator.Generate(constantPS, altseed::ShaderStageType::Pixel);
        auto reflection = altseed::SPIRVReflection();
        reflection.Transpile(spirv);

        for (auto& u : reflection.Uniforms) {
            if (u.Name == u"offset") {
                ASSERT_EQ(u.Offset, 0);
            }

            if (u.Name == u"offset1") {
                ASSERT_EQ(u.Offset, 16);
            }

            if (u.Name == u"offset2") {
                ASSERT_EQ(u.Offset, 32);
            }
        }
    }

    {
        auto spirv = generator.Generate(texturePS, altseed::ShaderStageType::Pixel);
        auto reflection = altseed::SPIRVReflection();
        reflection.Transpile(spirv);

        for (auto& u : reflection.Textures) {
            if (u.Name == u"txt") {
                ASSERT_EQ(u.Offset, 0);
            }

            if (u.Name == u"txt2") {
                ASSERT_EQ(u.Offset, 1);
            }
        }
    }

    generator.Terminate();
}