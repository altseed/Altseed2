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
    bool isValid_ = false;
    std::string code_;
    std::string errorMessage_;

    std::vector<ShaderReflectionTexture> textures_;
    std::vector<ShaderReflectionUniform> uniforms_;
    int32_t uniformSize_ = 0;

    LLGI::Shader* shader_ = nullptr;

public:
    ~Shader() { LLGI::SafeRelease(shader_); }


	/**
		@brief constructor
		@note
		please use ShaderCompiler to generate a shader
	*/
    Shader(std::string code, std::string errorMessage) : code_(code), errorMessage_(errorMessage), isValid_(false) {}

	/**
        @brief constructor
        @note
        please use ShaderCompiler to generate a shader
    */
    Shader(std::string code,
           const std::vector<ShaderReflectionTexture>& textures,
           const std::vector<ShaderReflectionUniform>& uniforms,
           LLGI::Shader* shader);

	int32_t GetUniformSize() const { return uniformSize_; }
    const std::vector<ShaderReflectionTexture>& GetReflectionTextures() const { return textures_; }
    const std::vector<ShaderReflectionUniform>& GetReflectionUniforms() const { return uniforms_; }

    bool GetIsValid() const { return isValid_; }

    LLGI::Shader* Get() const { return shader_; }
};

}  // namespace Altseed
