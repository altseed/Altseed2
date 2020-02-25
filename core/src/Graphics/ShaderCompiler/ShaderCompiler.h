#pragma once

#include <LLGI.Compiler.h>
#include "../../BaseObject.h"
#include "ShaderTranspiler.h"

namespace Altseed {

enum class GraphicsDeviceType : int32_t {
    DirectX12,
    Metal,
    Vulkan,
    Other,
};

class Graphics;
class Shader;

class ShaderCompiler : public BaseObject {
private:
    static std::shared_ptr<ShaderCompiler> instance_;
    std::shared_ptr<Graphics> graphics_;
    std::shared_ptr<LLGI::Compiler> compiler_;
    std::shared_ptr<SPIRVGenerator> spirvGenerator_;
    std::shared_ptr<SPIRVTranspiler> spirvTranspiler_;
    std::shared_ptr<SPIRVReflection> spirvReflection_;

public:
    static std::shared_ptr<ShaderCompiler>& GetInstance();

    static bool Initialize(std::shared_ptr<Graphics>& graphics);

    static void Terminate();

    ShaderCompiler(std::shared_ptr<Graphics>& graphics);
    ~ShaderCompiler();

    std::shared_ptr<Shader> Compile(const char* name, const char* code, ShaderStageType shaderStage);
};

}  // namespace Altseed