#include "ShaderCompiler.h"
#include "../Graphics.h"
#include "../Shader.h"

namespace altseed {

std::shared_ptr<ShaderCompiler> ShaderCompiler::instance_ = nullptr;

std::shared_ptr<ShaderCompiler>& ShaderCompiler::GetInstance() { return instance_; }

bool ShaderCompiler::Initialize(std::shared_ptr<Graphics>& graphics) {
    instance_ = CreateSharedPtr(new ShaderCompiler(graphics));
    return true;
}

void ShaderCompiler::Terminate() { instance_ = nullptr; }

ShaderCompiler::ShaderCompiler(std::shared_ptr<Graphics>& graphics) : graphics_(graphics) {
    spirvGenerator_ = std::make_shared<SPIRVGenerator>();

// TODO : change with graphics
    compiler_ = LLGI::CreateSharedPtr(LLGI::CreateCompiler(LLGI::DeviceType::Default));
#ifdef _WIN32
    // spirvTranspiler_ = std::make_shared<SPIRVToHLSLTranspiler>();
#elif __APPLE__
    spirvTranspiler_ = std::make_shared<SPIRVToMSLTranspiler>();
#else
    spirvTranspiler_ = std::make_shared<SPIRVToGLSLTranspiler>(true);
#endif
}

std::shared_ptr<Shader> ShaderCompiler::Compile(const char* code, ShaderStageType shaderStage) {
    std::string availableCode;

	// convert a code or use raw code
    if (spirvTranspiler_ != nullptr) {
        auto spirv = spirvGenerator_->Generate(code, shaderStage);

        if (!spirvTranspiler_->Transpile(spirv)) {
            return CreateSharedPtr(new Shader(availableCode, spirvTranspiler_->GetErrorCode()));
        }

        availableCode = spirvTranspiler_->GetCode();
    } else {
        availableCode = code;
	}

    LLGI::ShaderStageType shaderStageLLGI = LLGI::ShaderStageType::Vertex;
    if (shaderStage == ShaderStageType::Vertex) {
        shaderStageLLGI = LLGI::ShaderStageType::Vertex;
    } else if (shaderStage == ShaderStageType::Pixel) {
        shaderStageLLGI = LLGI::ShaderStageType::Pixel;
    }

	// compile actually
    LLGI::CompilerResult result;
    compiler_->Compile(result, availableCode.c_str(), shaderStageLLGI);

    LLGI::DataStructure data;
    data.Data = result.Binary.data();
    data.Size = result.Binary.size();
    auto shaderLLGI = graphics_->GetGraphicsLLGI()->CreateShader(&data, 1);
    
	return CreateSharedPtr(new Shader(availableCode, shaderLLGI));
}

}  // namespace altseed