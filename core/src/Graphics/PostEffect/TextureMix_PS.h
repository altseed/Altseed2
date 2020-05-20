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
    float4 _Weight;
};

Texture2D _Texture1 : register(t0);
SamplerState _Sampler1 : register(s0);

Texture2D _Texture2 : register(t1);
SamplerState _Sampler2 : register(s1);

float4 main(PS_INPUT input) : SV_TARGET 
{
    float4 color1 = _Texture1.Sample(_Sampler1, input.UV1);
    float4 color2 = _Texture2.Sample(_Sampler2, input.UV1);
    return color1 + color2 * _Weight;
}

)";