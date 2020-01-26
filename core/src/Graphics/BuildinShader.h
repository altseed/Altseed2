#pragma once
#include <unordered_map>
#include "../BaseObject.h"

namespace Altseed {

class Shader;

enum class BuildinShaderType {
    SpriteUnlitVS,
    SpriteUnlitPS,
};

class BuildinShader : public BaseObject {
private:
    std::unordered_map<BuildinShaderType, std::shared_ptr<Shader>> shaders_;

public:
    std::shared_ptr<Shader> Create(BuildinShaderType type);
};

}  // namespace altseed