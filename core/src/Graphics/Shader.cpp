#include "Shader.h"

#include "../Logger/Log.h"
#include "ShaderCompiler/ShaderCompiler.h"
namespace Altseed2 {

Shader::Shader(
        std::u16string code,
        std::u16string name,
        const std::vector<ShaderReflectionTexture>& textures,
        const std::vector<ShaderReflectionUniform>& uniforms,
        Vector3I numThreads,
        std::shared_ptr<LLGI::Shader> shader,
        ShaderStageType stage)
    : code_(code), name_(name), textures_(textures), uniforms_(uniforms), shader_(shader), numThreads_(numThreads), stage_(stage) {
    for (const auto& u : uniforms_) {
        uniformSize_ = std::max(u.Offset + u.Size, uniformSize_);
    }
}

std::shared_ptr<ShaderCompileResult> Shader::Compile(const char16_t* name, const char16_t* code, ShaderStageType shaderStage) {
    RETURN_IF_NULL(name, MakeAsdShared<ShaderCompileResult>(nullptr, u"name is null"));
    RETURN_IF_NULL(code, MakeAsdShared<ShaderCompileResult>(nullptr, u"code is null"));

    auto shaderCompiler = ShaderCompiler::GetInstance();
    if (shaderCompiler == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Graphics is not initialized.");
        return nullptr;
    }

    return shaderCompiler->Compile("", utf16_to_utf8(name).c_str(), utf16_to_utf8(code).c_str(), shaderStage);
}

std::shared_ptr<ShaderCompileResult> Shader::CompileFromFile(const char16_t* name, const char16_t* path, ShaderStageType shaderStage) {
    RETURN_IF_NULL(name, MakeAsdShared<ShaderCompileResult>(nullptr, u"name is null"));
    RETURN_IF_NULL(path, MakeAsdShared<ShaderCompileResult>(nullptr, u"path is null"));

    auto shaderCompiler = ShaderCompiler::GetInstance();
    if (shaderCompiler == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Graphics is not initialized.");
        return nullptr;
    }

    return shaderCompiler->Compile(utf16_to_utf8(path).c_str(), utf16_to_utf8(name).c_str(), shaderStage);
}

}  // namespace Altseed2