static const char16_t* gaussianblur_ps =
        uR"(
Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);

cbuffer Consts : register(b1)
{
    float4 weight;
};

uint2 GetTextureSize(Texture2D texture_){
    uint width, height;
    texture_.GetDimensions(width, height);
    return uint2(width, height);
}

struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};

float4 main(PS_INPUT input ) : SV_TARGET
{
    uint2 texSize = GetTextureSize(mainTex);

#ifdef BLUR_X
    float2 accum = float2(1.0 / texSize.x, 0.0);
    float2 half_ = float2(0.5 / texSize.x, 0.0);
    float2 adder = float2(2.0 / texSize.x, 0.0);
#endif

#ifdef BLUR_Y
    float2 accum = float2(0.0, 1.0 / texSize.y);
    float2 half_ = float2(0.0, 0.5 / texSize.y);
    float2 adder = float2(0.0, 2.0 / texSize.y);
#endif

    float4 output_ = (mainTex.Sample(mainSamp, input.UV1 + half_ + accum) +
                     mainTex.Sample(mainSamp, input.UV1 + half_ - accum)) *
                     weight.x;
    if(output_.a == 0.0f) discard;
    accum += adder;
    output_ += (mainTex.Sample(mainSamp, input.UV1 + half_ + accum) +
               mainTex.Sample(mainSamp, input.UV1 + half_ - accum)) *
               weight.y;
    accum += adder;
    output_ += (mainTex.Sample(mainSamp, input.UV1 + half_ + accum) +
               mainTex.Sample(mainSamp, input.UV1 + half_ - accum)) *
               weight.z;

    output_.a = 1.0;

    return output_;
}
)";