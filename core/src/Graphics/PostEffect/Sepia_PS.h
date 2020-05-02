static const char16_t* sepia_ps = uR"(
Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);

struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};

float4 main(PS_INPUT input) : SV_TARGET 
{
    float4 outputedColor = mainTex.Sample(mainSamp, input.UV1);
    if(outputedColor.a == 0.0f) discard;
    float y = outputedColor.r * 0.298912f + outputedColor.g * 0.586611f + outputedColor.b * 0.114478f;
    outputedColor.rgb = y;
    outputedColor.r *= 1.332249;
    outputedColor.r = outputedColor.r > 1.0f? 1.0f: outputedColor.r;
    outputedColor.g *= 0.921369f;
    outputedColor.b *= 0.535390f;
    return outputedColor;
}

)";