#pragma once

#include <LLGI.Compiler.h>
#include <ShaderTranspilerCore.h>

#include "../../BaseObject.h"
#include "../Graphics.h"

namespace Altseed2 {

class Graphics;
class Shader;
class File;

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

    std::shared_ptr<Shader> Compile(const char* path, const char* name, const char* code, ShaderStageType shaderStage);

    std::shared_ptr<Shader> Compile(const char* path, const char* name, ShaderStageType shaderStage);
};

}  // namespace Altseed2