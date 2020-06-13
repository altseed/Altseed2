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
};

Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);

static float weight[4];

float gauss(float x, float sigma)
{
    return exp(- 0.5 * (x * x) / (sigma * sigma));
}

float4 getGaussianBlur(float2 uv)
{
    float weightTotal = 0;
    for(int i = 0; i < 4; ++i)
    {
        weight[i] = gauss(i + 0.5, intensity.x);
        weightTotal += weight[i] * 2.0;
    }
    
    float4 outputColor = float4(0.0, 0.0, 0.0, 0.0);

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
        outputColor += mainTex.Sample(mainSamp, nShiftedUV) * weight[i] / weightTotal;
        outputColor += mainTex.Sample(mainSamp, pShiftedUV) * weight[i] / weightTotal;
    }

    return outputColor;
}

float4 main(PS_INPUT input) : SV_TARGET 
{
    return getGaussianBlur(input.UV1);
}

)";