#pragma once

#include <memory>

#include "../BaseObject.h"
#include "Graphics.h"

namespace Altseed {

struct ShaderReflectionUniform {
    std::u16string Name;
    int32_t Offset = 0;
    int32_t Size = 0;
};

struct ShaderReflectionTexture {
    std::u16string Name;
    int32_t Offset = 0;
};

class Shader : public BaseObject {
private:
    std::vector<ShaderReflectionTexture> textures_;
    std::vector<ShaderReflectionUniform> uniforms_;
    int32_t uniformSize_ = 0;

    std::shared_ptr<LLGI::Shader> shader_ = nullptr;

public:
    virtual ~Shader() {}

    /**
    @brief constructor
    @note
    please use ShaderCompiler to generate a shader
*/
    Shader(std::string code,
           const std::vector<ShaderReflectionTexture>& textures,
           const std::vector<ShaderReflectionUniform>& uniforms,
           std::shared_ptr<LLGI::Shader> shader);

    int32_t GetUniformSize() const { return uniformSize_; }
    const std::vector<ShaderReflectionTexture>& GetReflectionTextures() const { return textures_; }
    const std::vector<ShaderReflectionUniform>& GetReflectionUniforms() const { return uniforms_; }

    LLGI::Shader* Get() const { return shader_.get(); }
};

}  // namespace Altseed
