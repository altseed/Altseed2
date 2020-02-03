#pragma once
#include <map>
#include "../BaseObject.h"

namespace Altseed {

class Shader;

enum class BuildinShaderType : int32_t {
    SpriteUnlitVS,
    SpriteUnlitPS,
    FontUnlitPS,
};

class BuildinShader : public BaseObject {
private:
    std::map<BuildinShaderType, std::shared_ptr<Shader>> shaders_;

public:
    std::shared_ptr<Shader> Create(BuildinShaderType type);
};

}  // namespace Altseed