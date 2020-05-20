static const char16_t* downsample_ps =
        uR"(

Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);

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
}

float4 main(PS_INPUT input) : SV_TARGET 
{
	float4 color1 = mainTex.Sample(mainSamp, input.UV1 + float2(-0.5, -0.5) / imageSize);
	float4 color2 = mainTex.Sample(mainSamp, input.UV1 + float2(+0.5, -0.5) / imageSize);
	float4 color3 = mainTex.Sample(mainSamp, input.UV1 + float2(-0.5, +0.5) / imageSize);
	float4 color4 = mainTex.Sample(mainSamp, input.UV1 + float2(+0.5, +0.5) / imageSize);
	return (color1 + color2 + color3 + color4) * 0.25;
}

)";