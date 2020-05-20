static const char16_t* texturemix_ps =
        uR"(

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR0;
    float2 UV1 : UV0;
    float2 UV2 : UV1;
};

cbuffer Consts : register(b1)
{
    float4 weight;
};

Texture2D mainTex1 : register(t0);
SamplerState mainSamp1 : register(s0);

Texture2D mainTex2 : register(t1);
SamplerState mainSamp2 : register(s1);

float4 main(PS_INPUT input) : SV_TARGET 
{
    float4 color1 = mainTex1.Sample(mainSamp1, input.UV1);
    float4 color2 = mainTex2.Sample(mainSamp2, input.UV1);
    return color1 + color2 * weight;
}

)";