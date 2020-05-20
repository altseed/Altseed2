#pragma once
#include <map>

#include "../BaseObject.h"
#include "../Common/StringHelper.h"
#include "PostEffect/Downsample_PS.h"
#include "PostEffect/GaussianBlur_PS.h"
#include "PostEffect/GrayScale_PS.h"
#include "PostEffect/LightBloom_PS.h"
#include "PostEffect/Sepia_PS.h"
#include "PostEffect/TextureMix_PS.h"

namespace Altseed {

class Shader;

enum class BuiltinShaderType : int32_t {
    SpriteUnlitVS,
    SpriteUnlitPS,
    FontUnlitPS,
};

class BuiltinShader : public BaseObject {
private:
    std::map<BuiltinShaderType, std::shared_ptr<Shader>> shaders_;

public:
    std::shared_ptr<Shader> Create(BuiltinShaderType type);

    const char16_t* GetDownsampleShader() const { return downsample_ps; }
    const char16_t* GetSepiaShader() const { return sepia_ps; }
    const char16_t* GetGrayScaleShader() const { return grayscale_ps; }
    const char16_t* GetGaussianBlurShader() const { return gaussianblur_ps; }
    const char16_t* GetLightBloomShader() const { return lightbloom_ps; }
    const char16_t* GetTextureMixShader() const { return texturemix_ps; }
};

}  // namespace Altseed