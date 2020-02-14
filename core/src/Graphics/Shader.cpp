#include "Shader.h"

namespace Altseed {

Shader::Shader(
        std::string code,
        const std::vector<ShaderReflectionTexture>& textures,
        const std::vector<ShaderReflectionUniform>& uniforms,
        LLGI::Shader* shader)
    : isValid_(true), textures_(textures), uniforms_(uniforms) {
    LLGI::SafeAssign(shader_, shader);

    for (const auto& u : uniforms_) {
        uniformSize_ = std::max(u.Offset + u.Size, uniformSize_);
    }
}
}  // namespace Altseed