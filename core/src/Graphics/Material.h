#pragma once

#include <memory>

#include "../BaseObject.h"
#include "Shader.h"

namespace Altseed {

class Shader;

class Material : public BaseObject {
private:
    std::shared_ptr<Shader> shader_;

public:
    std::shared_ptr<Shader> GetShader() const { return shader_; }
    void SetShader(std::shared_ptr<Shader>& shader) { shader_ = shader; }
};

}  // namespace Altseed
