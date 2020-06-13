static const char16_t* highluminance_ps =
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
    float4 exposure;
    float4 threshold;
};

Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);

float3 getLuminance(float3 color)
{
    return float3(1, 1, 1) * (color.x * 0.300000 + color.y * 0.590000 + color.z * 0.110000);
}

float4 main(PS_INPUT input) : SV_TARGET 
{
    float4 color = mainTex.Sample(mainSamp, input.UV1) * exposure;
    color.xyz = saturate(color.xyz);

#ifdef LUM_MODE
    float3 lum = getLuminance(color.xyz);
    float3 bloomedLum = lum - threshold;
    float3 bloomedPower = min(max(bloomedLum / 2.0, 0.0), 1.0);
    color.xyz *= bloomedPower;
#else
    float3 bloomedLum = color.xyz - threshold.xyz;
    bloomedLum = saturate(bloomedLum);
    color.xyz = bloomedLum;
#endif

    return color;
}

)";