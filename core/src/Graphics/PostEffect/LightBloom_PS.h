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
    float4 _Resolution;
    float4 _Intensity;
    float4 _Threshold;
    float4 _Exposure;
};

Texture2D _BaseTexture : register(t0);
SamplerState _BaseSampler : register(s0);

static float weight[4];

float3 getLuminance(float3 color)
{
    return float3(color.x * 0.300000 + color.y * 0.590000 + color.z * 0.110000);
}

float gauss(float x, float sigma)
{
    return exp(- 0.5 * (x * x) / (sigma * sigma));
}

float3 getColor(float2 uv)
{
#ifdef BLUR_X
    float4 color = _BaseTexture.Sample(_BaseSampler, uv) * _Exposure;
    color.xyz = min(color.xyz, float4(255.0));

#ifdef LUM_MODE
    float3 lum = getLuminance(color.xyz);
    float3 bloomedLum = lum - _Threshold;
    float3 bloomedPower = min(max(bloomedLum / 2.0, 0.0), 1.0);
    return color.xyz * bloomedPower;
#else
    float3 bloomedLum = color.xyz - _Threshold.xyz;
    bloomedLum = max(bloomedLum, float3(0.0, 0.0, 0.0));
    color.xyz = bloomedLum;
    return color;
#endif

#endif

#ifdef BLUR_Y
    return _BaseTexture.Sample(_BaseSampler, uv);
#endif
}

float4 getGaussianBlur(float2 uv)
{
    float weightTotal = 0;
    for(int i = 0; i < 4; ++i)
    {
        weight[i] = gauss(i + 0.5, _Intensity.x);
        weightTotal += weight[i] * 2.0;
    }
    
    float3 outputColor = float3(0.0);

    for(int i = 0; i < 4; ++i)
    {
#ifdef BLUR_X
        float2 nShiftedUV = uv + float2(-(i + 0.5) / _Resolution.x, 0.0);
        float2 pShiftedUV = uv + float2(+(i + 0.5) / _Resolution.x, 0.0);
#endif
#ifdef BLUR_Y
        float2 nShiftedUV = uv + float2(0.0, -(i + 0.5) / _Resolution.y);
        float2 pShiftedUV = uv + float2(0.0, +(i + 0.5) / _Resolution.y);
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