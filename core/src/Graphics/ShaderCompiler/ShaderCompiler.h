#pragma once

#include <LLGI.Compiler.h>
#include <ShaderTranspilerCore.h>

#include "../../BaseObject.h"
#include "../Graphics.h"

namespace Altseed2 {

class Graphics;
class Shader;
class File;

class ShaderCompileResult : public BaseObject {
private:
    std::shared_ptr<Shader> value_;
    std::u16string message_;

public:
    ShaderCompileResult(const std::shared_ptr<Shader> value, const std::u16string message);

    std::shared_ptr<Shader> GetValue() const { return value_; }
    const char16_t* GetMessage() const { return message_.c_str(); }
};

class ShaderCompiler : public BaseObject {
private:
    static std::shared_ptr<ShaderCompiler> instance_;
    std::shared_ptr<Graphics> graphics_;
    std::shared_ptr<File> file_;

    std::shared_ptr<LLGI::Compiler> compiler_;
    std::shared_ptr<LLGI::SPIRVGenerator> spirvGenerator_;
    std::shared_ptr<LLGI::SPIRVTranspiler> spirvTranspiler_;
    std::shared_ptr<LLGI::SPIRVReflection> spirvReflection_;

public:
    static std::shared_ptr<ShaderCompiler>& GetInstance();

    static bool Initialize(std::shared_ptr<Graphics>& graphics, std::shared_ptr<File>& file);

    static void Terminate();

    ShaderCompiler(std::shared_ptr<Graphics>& graphics, std::shared_ptr<File>& file);
    ~ShaderCompiler();

    std::shared_ptr<ShaderCompileResult> Compile(const char* path, const char* name, const char* code, ShaderStageType shaderStage);

#if !USE_CBG
    std::shared_ptr<ShaderCompileResult> Compile(const char* path, const char* name, ShaderStageType shaderStage);
#endif
};

}  // namespace Altseed2