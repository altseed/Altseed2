#include "ShaderCompiler.h"

#include "../../IO/File.h"
#include "../../IO/StaticFile.h"
#include "../../Logger/Log.h"
#include "../Graphics.h"

namespace Altseed2 {

std::shared_ptr<ShaderCompiler> ShaderCompiler::instance_ = nullptr;

std::shared_ptr<ShaderCompiler>& ShaderCompiler::GetInstance() { return instance_; }

bool ShaderCompiler::Initialize(std::shared_ptr<Graphics>& graphics, std::shared_ptr<File>& file) {
    instance_ = CreateSharedPtr(new ShaderCompiler(graphics, file));
    return true;
}

void ShaderCompiler::Terminate() { instance_ = nullptr; }

ShaderCompiler::ShaderCompiler(std::shared_ptr<Graphics>& graphics, std::shared_ptr<File>& file) : graphics_(graphics), file_(file) {
    auto loadFunc = [file](std::string s) -> std::vector<uint8_t> {
        auto path = utf8_to_utf16(s.c_str());
        auto sf = StaticFile::Create(path.c_str());

        if (sf == nullptr) {
            return std::vector<uint8_t>();
        }

        std::vector<uint8_t> ret;
        ret.resize(sf->GetSize());

        auto p = static_cast<const uint8_t*>(sf->GetData());
        ret.assign(p, p + sf->GetSize());
        return ret;
    };

    spirvGenerator_ = std::make_shared<LLGI::SPIRVGenerator>(loadFunc);
    compiler_ = LLGI::CreateSharedPtr(LLGI::CreateCompiler(LLGI::DeviceType::Default));

#ifdef _WIN32
    spirvTranspiler_ = std::make_shared<LLGI::SPIRVToHLSLTranspiler>(50, true);
#elif __APPLE__
    spirvTranspiler_ = std::make_shared<LLGI::SPIRVToMSLTranspiler>();
#else
    spirvTranspiler_ = std::make_shared<LLGI::SPIRVToGLSLTranspiler>(true);
#endif

    spirvReflection_ = std::make_shared<LLGI::SPIRVReflection>();
}

ShaderCompiler::~ShaderCompiler() {}

std::shared_ptr<Shader> ShaderCompiler::Compile(const char* path, const char* name, const char* code, ShaderStageType shaderStage) {
    std::string availableCode;

    std::vector<LLGI::SPIRVGeneratorMacro> macros;

#if defined(_WIN32) || defined(__APPLE__)
    auto spirv = spirvGenerator_->Generate(path, code, macros, static_cast<LLGI::ShaderStageType>(shaderStage), false);
#else
    auto spirv = spirvGenerator_->Generate(path, code, macros, static_cast<LLGI::ShaderStageType>(shaderStage), true);
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

std::shared_ptr<Shader> ShaderCompiler::Compile(const char* path, const char* name, ShaderStageType shaderStage) {
    auto sf = StaticFile::Create(utf8_to_utf16(path).c_str());

    if (sf == nullptr) {
        return nullptr;
    }

    std::vector<char> strvec;
    strvec.resize(sf->GetSize());

    auto p = static_cast<const char*>(sf->GetData());
    strvec.assign(p, p + sf->GetSize());
    strvec.push_back(0);

    return Compile(path, name, strvec.data(), shaderStage);
}

}  // namespace Altseed2