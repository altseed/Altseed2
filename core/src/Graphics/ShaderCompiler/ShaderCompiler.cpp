#include "ShaderCompiler.h"

#include "../../Logger/Log.h"
#include "../Graphics.h"
#include "../Shader.h"
#ifdef _WIN32
#include <DX12/LLGI.CompilerDX12.h>
#endif

namespace Altseed {

std::shared_ptr<ShaderCompiler> ShaderCompiler::instance_ = nullptr;

std::shared_ptr<ShaderCompiler>& ShaderCompiler::GetInstance() { return instance_; }

bool ShaderCompiler::Initialize(std::shared_ptr<Graphics>& graphics) {
    instance_ = CreateSharedPtr(new ShaderCompiler(graphics));
    return true;
}

void ShaderCompiler::Terminate() { instance_ = nullptr; }

ShaderCompiler::ShaderCompiler(std::shared_ptr<Graphics>& graphics) : graphics_(graphics) {
    spirvGenerator_ = std::make_shared<SPIRVGenerator>();
    spirvGenerator_->Initialize();

    // TODO : change with graphics
#ifdef _WIN32
    auto compiler = new LLGI::CompilerDX12(LLGI::CompilerDX12Option::ColumnMajor);
    compiler->Initialize();
    compiler_ = LLGI::CreateSharedPtr(compiler);
#else
    compiler_ = LLGI::CreateSharedPtr(LLGI::CreateCompiler(LLGI::DeviceType::Default));
#endif
#ifdef _WIN32
    // spirvTranspiler_ = std::make_shared<SPIRVToHLSLTranspiler>();
#elif __APPLE__
    spirvTranspiler_ = std::make_shared<SPIRVToMSLTranspiler>();
#else
    spirvTranspiler_ = std::make_shared<SPIRVToGLSLTranspiler>(true);
#endif

    spirvReflection_ = std::make_shared<SPIRVReflection>();
}

ShaderCompiler::~ShaderCompiler() { spirvGenerator_->Terminate(); }

std::shared_ptr<Shader> ShaderCompiler::Compile(const char* name, const char* code, ShaderStageType shaderStage) {
    std::string availableCode;

    auto spirv = spirvGenerator_->Generate(code, shaderStage);

    // convert a code or use raw code
    if (spirvTranspiler_ != nullptr) {
        if (!spirvTranspiler_->Transpile(spirv)) {
            Log::GetInstance()->Write(LogCategory::Core, LogLevel::Error, u"Shader transpile error {} : {}", name, spirvTranspiler_->GetErrorCode());
            return nullptr;
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

    if (result.Binary.size() == 0) {
        Log::GetInstance()->Write(LogCategory::Core, LogLevel::Error, u"Shader compile error {} : {}", name, result.Message);
        Log::GetInstance()->Write(LogCategory::Core, LogLevel::Error, u"Code :\n{}", code);
        return nullptr;
    }

    if (!spirvReflection_->Transpile(spirv)) {
        Log::GetInstance()->Write(LogCategory::Core, LogLevel::Error, u"Shader error {} : Failed to refrect.", name);
        return nullptr;
    }

    std::vector<LLGI::DataStructure> data;

    for (auto& b : result.Binary) {
        LLGI::DataStructure d;
        d.Data = b.data();
        d.Size = static_cast<int32_t>(b.size());
        data.push_back(d);
    }

    auto shaderLLGI = graphics_->GetGraphicsLLGI()->CreateShader(data.data(), static_cast<int32_t>(data.size()));

    auto ret = CreateSharedPtr(new Shader(availableCode, spirvReflection_->Textures, spirvReflection_->Uniforms, shaderLLGI));
    LLGI::SafeRelease(shaderLLGI);
    return ret;
}

}  // namespace Altseed