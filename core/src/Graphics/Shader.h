#pragma once

#include <memory>

#include "../BaseObject.h"
#include "Graphics.h"

namespace altseed {

class Shader : public BaseObject {
private:
    bool isValid_ = false;
    std::string code_;
    std::string errorMessage_;

    LLGI::Shader* shader_ = nullptr;

public:
    Shader() = default;

    ~Shader() { LLGI::SafeRelease(shader_); }

    Shader(std::string code, std::string errorMessage) : code_(code), errorMessage_(errorMessage), isValid_(false) {}

    Shader(std::string code, LLGI::Shader* shader) : isValid_(true) { LLGI::SafeAssign(shader_, shader); }

    LLGI::Shader* Get() const { return shader_; }

    void SetShaderBinary(LLGI::Shader* shader) { LLGI::SafeAssign(shader_, shader); }
};

}  // namespace altseed
