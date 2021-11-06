#pragma once

#include <memory>

#include "../BaseObject.h"
#include "../Common/StringHelper.h"
#include "Graphics.h"

namespace Altseed2 {

class ShaderCompileResult;

enum class ShaderStageType {
    Vertex,
    Pixel,
    Compute,
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
    std::u16string code_;
    std::u16string name_;
    std::vector<ShaderReflectionTexture> textures_;
    std::vector<ShaderReflectionUniform> uniforms_;
    Vector3I numThreads_;
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
    Shader(std::u16string code,
           std::u16string name,
           const std::vector<ShaderReflectionTexture>& textures,
           const std::vector<ShaderReflectionUniform>& uniforms,
           Vector3I numThreads,
           std::shared_ptr<LLGI::Shader> shader,
           ShaderStageType stage);

    int32_t GetUniformSize() const { return uniformSize_; }

#if !USE_CBG

    const std::vector<ShaderReflectionTexture>& GetReflectionTextures() const { return textures_; }
    const std::vector<ShaderReflectionUniform>& GetReflectionUniforms() const { return uniforms_; }
    LLGI::Shader* Get() const { return shader_.get(); }

#endif

    const Vector3I GetNumThreads() { return numThreads_; }

    static std::shared_ptr<ShaderCompileResult> Compile(const char16_t* name, const char16_t* code, ShaderStageType shaderStage);

    static std::shared_ptr<ShaderCompileResult> CompileFromFile(const char16_t* name, const char16_t* path, ShaderStageType shaderStage);

    const char16_t* GetCode() const { return code_.c_str(); }

    const char16_t* GetName() const { return name_.c_str(); }

    ShaderStageType GetStageType() const { return stage_; }
};

}  // namespace Altseed2
