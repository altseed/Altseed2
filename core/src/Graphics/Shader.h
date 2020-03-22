#pragma once

#include <memory>

#include "../BaseObject.h"
#include "../Common/StringHelper.h"
#include "Graphics.h"

namespace Altseed {

enum class ShaderStageType {
    Vertex,
    Pixel,
};

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
    std::string code_;
    std::string name_;
    std::vector<ShaderReflectionTexture> textures_;
    std::vector<ShaderReflectionUniform> uniforms_;
    int32_t uniformSize_ = 0;

    std::shared_ptr<LLGI::Shader> shader_ = nullptr;
    ShaderStageType stage_;

public:
    virtual ~Shader() {}

    /**
    @brief constructor
    @note
    please use ShaderCompiler to generate a shader
*/
    Shader(std::string code,
           std::string name,
           const std::vector<ShaderReflectionTexture>& textures,
           const std::vector<ShaderReflectionUniform>& uniforms,
           std::shared_ptr<LLGI::Shader> shader,
           ShaderStageType stage);

    int32_t GetUniformSize() const { return uniformSize_; }
    const std::vector<ShaderReflectionTexture>& GetReflectionTextures() const { return textures_; }
    const std::vector<ShaderReflectionUniform>& GetReflectionUniforms() const { return uniforms_; }

    LLGI::Shader* Get() const { return shader_.get(); }

    static std::shared_ptr<Shader> Create(const char16_t* code, const char16_t* name, ShaderStageType shaderStage);

    const char16_t* GetCode() const { return utf8_to_utf16(code_).c_str(); }

    const char16_t* GetName() const { return utf8_to_utf16(name_).c_str(); }

    ShaderStageType GetStageType() const { return stage_; }
};

}  // namespace Altseed
