#include "ShaderCompiler.h"

#include "../../Logger/Log.h"
#include "../Graphics.h"
#include "../Shader.h"
#ifdef _WIN32
#include <DX12/LLGI.CompilerDX12.h>
#endif

namespace Altseed2 {

std::shared_ptr<ShaderCompiler> ShaderCompiler::instance_ = nullptr;

std::shared_ptr<ShaderCompiler>& ShaderCompiler::GetInstance() { return instance_; }

bool ShaderCompiler::Initialize(std::shared_ptr<Graphics>& graphics) {
    instance_ = CreateSharedPtr(new ShaderCompiler(graphics));
    return true;
}

void ShaderCompiler::Terminate() { instance_ = nullptr; }

ShaderCompiler::ShaderCompiler(std::shared_ptr<Graphics>& graphics) : graphics_(graphics) {
    spirvGenerator_ = std::make_shared<LLGI::SPIRVGenerator>();
    compiler_ = LLGI::CreateSharedPtr(LLGI::CreateCompiler(LLGI::DeviceType::Default));

#ifdef _WIN32
    // spirvTranspiler_ = std::make_shared<LLGI::SPIRVToHLSLTranspiler>();
#elif __APPLE__
    spirvTranspiler_ = std::make_shared<LLGI::SPIRVToMSLTranspiler>();
#else
    spirvTranspiler_ = std::make_shared<LLGI::SPIRVToGLSLTranspiler>(true);
#endif

    spirvReflection_ = std::make_shared<LLGI::SPIRVReflection>();
}

ShaderCompiler::~ShaderCompiler() {}

std::shared_ptr<Shader> ShaderCompiler::Compile(const char* name, const char* code, ShaderStageType shaderStage) {
    std::string availableCode;

#if defined(_WIN32) || defined(__APPLE__)
    auto spirv = spirvGenerator_->Generate(code, static_cast<LLGI::ShaderStageType>(shaderStage), false);
#else
    auto spirv = spirvGenerator_->Generate(code, static_cast<LLGI::ShaderStageType>(shaderStage), true);
#endif

    // convert a code or use raw code
    if (spirvTranspiler_ != nullptr) {
        if (!spirvTranspiler_->Transpile(spirv)) {
            Log::GetInstance()->Error(LogCategory::Core, u"Shader transpile error {} : {}", name, spirvTranspiler_->GetErrorCode());
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
        Log::GetInstance()->Error(LogCategory::Core, u"Shader compile error {} : {}", name, result.Message);
        Log::GetInstance()->Error(LogCategory::Core, u"Code :\n{}", code);
        return nullptr;
    }

    if (!spirvReflection_->Transpile(spirv)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Shader error {} : Failed to refrect.", name);
        return nullptr;
    }

    std::vector<LLGI::DataStructure> data;

    for (auto& b : result.Binary) {
        LLGI::DataStructure d;
        d.Data = b.data();
        d.Size = static_cast<int32_t>(b.size());
        data.push_back(d);
    }

    auto shaderLLGI = LLGI::CreateSharedPtr(graphics_->GetGraphicsLLGI()->CreateShader(data.data(), static_cast<int32_t>(data.size())));

    std::vector<ShaderReflectionTexture> textures;
    std::vector<ShaderReflectionUniform> uniforms;

    for (auto& t : spirvReflection_->Textures) {
        auto _ = ShaderReflectionTexture{utf8_to_utf16(t.Name), t.Offset};
        textures.emplace_back(_);
    }

    for (auto& t : spirvReflection_->Uniforms) {
        auto _ = ShaderReflectionUniform{utf8_to_utf16(t.Name), t.Offset, t.Size};
        uniforms.emplace_back(_);
    }

    auto ret = MakeAsdShared<Shader>(
            utf8_to_utf16(availableCode),
            utf8_to_utf16(name),
            textures,
            uniforms,
            shaderLLGI,
            shaderStage);
    return ret;
}

}  // namespace Altseed2