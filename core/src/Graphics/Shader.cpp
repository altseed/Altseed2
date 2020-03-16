#include "Shader.h"
#include "ShaderCompiler/ShaderCompiler.h"
namespace Altseed {

Shader::Shader(
        std::string code,
        const std::vector<ShaderReflectionTexture>& textures,
        const std::vector<ShaderReflectionUniform>& uniforms,
        std::shared_ptr<LLGI::Shader> shader,
        ShaderStageType stage)
    : code_(code), textures_(textures), uniforms_(uniforms), shader_(shader), stage_(stage) {
    for (const auto& u : uniforms_) {
        uniformSize_ = std::max(u.Offset + u.Size, uniformSize_);
    }
}

std::shared_ptr<Shader> Shader::Create(const char16_t* code, const char16_t* name, ShaderStageType shaderStage) {
    return ShaderCompiler::GetInstance()->Compile(utf16_to_utf8(code).c_str(), utf16_to_utf8(name).c_str(), shaderStage);
}

}  // namespace Altseed