#include "Shader.h"

namespace Altseed {

Shader::Shader(
        std::string code,
        const std::vector<ShaderReflectionTexture>& textures,
        const std::vector<ShaderReflectionUniform>& uniforms,
        std::shared_ptr<LLGI::Shader> shader)
    : textures_(textures), uniforms_(uniforms), shader_(shader) {
    for (const auto& u : uniforms_) {
        uniformSize_ = std::max(u.Offset + u.Size, uniformSize_);
    }
}
}  // namespace Altseed