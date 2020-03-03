#pragma once
#include <map>
#include "../BaseObject.h"

namespace Altseed {

class Shader;

enum class BuiltinShaderType : int32_t {
    SpriteUnlitVS,
    SpriteUnlitPS,
    FontUnlitPS,
};

class BuiltinShader : public BaseObject {
private:
    std::map<BuiltinShaderType, std::shared_ptr<Shader>> shaders_;

public:
    std::shared_ptr<Shader> Create(BuiltinShaderType type);
};

}  // namespace Altseed