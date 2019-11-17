#pragma once

#include <memory>

#include "../BaseObject.h"
#include "Graphics.h"

namespace altseed {

class Shader : public BaseObject {
private:
    LLGI::Shader* shader_ = nullptr;

public:
    LLGI::Shader* Get() const { return shader_; }
    void SetShaderBinary(LLGI::Shader* shader) { shader_ = shader; }
};

}  // namespace altseed
