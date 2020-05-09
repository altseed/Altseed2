static const char16_t* downsample_ps =
        uR"(

Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);
cbuffer Consts : register(b1)
{
    float4 offset;
};

struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return mainTex.Sample(mainSamp, input.UV1 + offset.xy);
}

)";