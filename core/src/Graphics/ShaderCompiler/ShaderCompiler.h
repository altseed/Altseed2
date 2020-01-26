#pragma once

#include "../../BaseObject.h"
#include "ShaderTranspiler.h"
#include <LLGI.Compiler.h>

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

public:
    static std::shared_ptr<ShaderCompiler>& GetInstance();

    static bool Initialize(std::shared_ptr<Graphics>& graphics);

    static void Terminate();

	ShaderCompiler(std::shared_ptr<Graphics>& graphics);
    ~ShaderCompiler();

	std::shared_ptr<Shader> Compile(const char* code, ShaderStageType shaderStage);
};

}  // namespace Altseed