static const char16_t* lightbloom_ps =
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
    float4 imageSize;
    float4 intensity;
    float4 threshold;
    float4 exposure;
};

Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);

static float weight[4];

float3 getLuminance(float3 color)
{
    return float3(1, 1, 1) * (color.x * 0.300000 + color.y * 0.590000 + color.z * 0.110000);
}

float gauss(float x, float sigma)
{
    return exp(- 0.5 * (x * x) / (sigma * sigma));
}

float3 getColor(float2 uv)
{
#ifdef BLUR_X
    float4 color = mainTex.Sample(mainSamp, uv) * exposure;
    color.xyz = saturate(color.xyz);

#ifdef LUM_MODE
    float3 lum = getLuminance(color.xyz);
    float3 bloomedLum = lum - threshold;
    float3 bloomedPower = min(max(bloomedLum / 2.0, 0.0), 1.0);
    return color.xyz * bloomedPower;
#else
    float3 bloomedLum = color.xyz - threshold.xyz;
    bloomedLum = saturate(bloomedLum);
    color.xyz = bloomedLum;
    return color;
#endif

#endif

#ifdef BLUR_Y
    return mainTex.Sample(mainSamp, uv);
#endif
}

float4 getGaussianBlur(float2 uv)
{
    float weightTotal = 0;
    for(int i = 0; i < 4; ++i)
    {
        weight[i] = gauss(i + 0.5, intensity.x);
        weightTotal += weight[i] * 2.0;
    }
    
    float3 outputColor = float3(0.0, 0.0, 0.0);

    for(int i = 0; i < 4; ++i)
    {
#ifdef BLUR_X
        float2 nShiftedUV = uv + float2(-(i + 0.5) / imageSize.x, 0.0);
        float2 pShiftedUV = uv + float2(+(i + 0.5) / imageSize.x, 0.0);
#endif
#ifdef BLUR_Y
        float2 nShiftedUV = uv + float2(0.0, -(i + 0.5) / imageSize.y);
        float2 pShiftedUV = uv + float2(0.0, +(i + 0.5) / imageSize.y);
#endif
        outputColor += getColor(nShiftedUV) * weight[i] / weightTotal;
        outputColor += getColor(pShiftedUV) * weight[i] / weightTotal;
    }

    return float4(outputColor, 1.0);
}

float4 main(PS_INPUT input) : SV_TARGET 
{
    return getGaussianBlur(input.UV1);
}

)";