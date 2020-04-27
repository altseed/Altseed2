static const char16_t* lightbloom_ps =
        uR"(

cbuffer Consts : register(b1)
{
    float4 weight1;
    float4 weight2;
    float4 threshold_exposure;
};

#if BLUR_X
Texture2D blurredTex : register(t0);
SamplerState blurredSamp : register(s0);
#endif

#if BLUR_Y
Texture2D blurredTex : register(t0);
SamplerState blurredSamp : register(s0);
#endif

#if SUM
Texture2D blurred0Tex : register(t0);
SamplerState blurred0Samp : register(s0);

Texture2D blurred1Tex : register(t1);
SamplerState blurred1Samp : register(s1);

Texture2D blurred2Tex : register(t2);
SamplerState blurred2Samp : register(s2);

Texture2D blurred3Tex : register(t3);
SamplerState blurred3Samp : register(s3);
#endif

uint2 GetTextureSize(Texture2D texture_){
    uint width, height;
    texture_.GetDimensions(width, height);
    return uint2(width, height);
}

float GetLuminance(float3 color)
{
    return color.x * 0.300000 + color.y * 0.590000 + color.z * 0.110000;
}

float4 GetColor(float2 uv)
{
#if BLUR_X
    float4 color = blurredTex.Sample(blurredSamp, uv) * threshold_exposure.y;
    color.xyz = min(color.xyz, float3(255.000, 255.000, 255.000));
#if LUM
    float lum = GetLuminance(color.xyz);
    float bloomedLum = lum - threshold_exposure.x;
    float bloomedPower = min(max(bloomedLum / 2.00000, 0.000000), 1.00000);
    return color * bloomedPower;
#else
    float3 bloomedLum = color.xyz - float3(threshold_exposure.x, threshold_exposure.x, threshold_exposure.x);
    bloomedLum.xyz = max(bloomedLum.xyz, float3(0.000000, 0.000000, 0.000000));
    color.xyz = bloomedLum;
    return color;
#endif
#endif
#if BLUR_Y
    return blurredTex.Sample(blurredSamp, uv);
#endif
#if SUM
    return float4(0.000000, 0.000000, 0.000000, 0.000000);
#endif
}

float4 CalcBlurredColor(float2 uv)
{
#if SUM
    return float4(0.000000, 0.000000, 0.000000, 0.000000);
#endif
#if BLUR_X
    float2 size = GetTextureSize(blurredTex);
#endif
#if BLUR_Y
    float2 size = GetTextureSize(blurredTex);
#endif
#if SUM
    float2 size = float2(0.000000, 0.000000);
    float2 shift_p = float2(0.000000 / size.x, -0.500000 / size.y);
    float2 shift_m = float2(-1.50000 / size.x, -0.500000 / size.y);
    float2 adder = float2(2.00000f / size.x, 0.000000);
#endif
#if BLUR_X
    float2 shift_p = float2(0.500000 / size.x, -0.500000 / size.y);
    float2 shift_m = float2(-1.50000 / size.x, -0.500000 / size.y);
    float2 adder = float2(2.00000f / size.x, 0.000000);
#endif
#if BLUR_Y
    float2 shift_p = float2(-0.500000 / size.x, 0.500000 / size.y);
    float2 shift_m = float2(-0.500000 / size.x, -1.50000 / size.y);
    float2 adder = float2(0.000000, 2.00000 / size.y);
#endif
    float4 sum = float4(0.000000, 0.000000, 0.000000, 0.000000);
    sum += weight1.x * GetColor(uv + shift_p + adder * 0.000000);
    sum += weight1.x * GetColor(uv + shift_m - adder * 0.000000);
    sum += weight1.y * GetColor(uv + shift_p + adder * 1.00000);
    sum += weight1.y * GetColor(uv + shift_m - adder * 1.00000);
    sum += weight1.z * GetColor(uv + shift_p + adder * 2.00000);
    sum += weight1.z * GetColor(uv + shift_m - adder * 2.00000);
    sum += weight1.w * GetColor(uv + shift_p + adder * 3.00000);
    sum += weight1.w * GetColor(uv + shift_m - adder * 3.00000);
    sum += weight2.x * GetColor(uv + shift_p + adder * 4.000000);
    sum += weight2.x * GetColor(uv + shift_m - adder * 4.000000);
    sum += weight2.y * GetColor(uv + shift_p + adder * 5.00000);
    sum += weight2.y * GetColor(uv + shift_m - adder * 5.00000);
    sum += weight2.z * GetColor(uv + shift_p + adder * 6.00000);
    sum += weight2.z * GetColor(uv + shift_m - adder * 6.00000);
    sum += weight2.w * GetColor(uv + shift_p + adder * 7.00000);
    sum += weight2.w * GetColor(uv + shift_m - adder * 7.00000);
    sum.a = 1.00000;
    return sum;
}


float4 Main_(float2 uv)
{
#if BLUR_X
    return CalcBlurredColor(uv);
#endif
#if BLUR_Y
    return CalcBlurredColor(uv);
#endif
#if SUM
    return blurred0Tex.Sample(blurred0Samp, uv) * 1.00000;
    return blurred0Tex.Sample(blurred0Samp, uv) * 0.50000 + blurred1Tex.Sample(blurred1Samp, uv) * 0.300000 + blurred2Tex.Sample(blurred2Samp, uv) * 0.20000;
#endif
}

struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};

float4 main(PS_INPUT input) : SV_TARGET 
{
    float4 o = Main_(input.UV1);
    o.a = 1.0;
    return o;
}

)";