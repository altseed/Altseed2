#pragma once

#include <LLGI.PipelineState.h>

#include "../BaseObject.h"
#include "Shader.h"

namespace Altseed2 {

enum class VertexLayoutFormat {
    R32G32B32_FLOAT,
    R32G32B32A32_FLOAT,
    R8G8B8A8_UNORM,
    R8G8B8A8_UINT,
    R32G32_FLOAT,
    R32_FLOAT,
};

class ComputePipelineState : public BaseObject {
private:
    std::shared_ptr<Shader> computeShader_;
    std::shared_ptr<LLGI::PipelineState> pipelineState_ = nullptr;

    std::shared_ptr<MaterialPropertyBlock> propertyBlock_;

    std::array<std::string, LLGI::VertexLayoutMax> vertexLayoutNames_;
    std::array<VertexLayoutFormat, LLGI::VertexLayoutMax> vertexLayouts_;
    std::array<int32_t, LLGI::VertexLayoutMax> vertexLayoutSemantics_;
    int32_t vertexLayoutCount_ = 0;

    bool requireCompile = true;

public:
    ComputePipelineState();

    std::shared_ptr<ComputePipelineState> Create();

    Vector4F GetVector4F(const char16_t* key) const;
    void SetVector4F(const char16_t* key, const Vector4F& value);

    Matrix44F GetMatrix44F(const char16_t* key) const;
    void SetMatrix44F(const char16_t* key, const Matrix44F& value);

    void SetShader(std::shared_ptr<Shader> shader);
    std::shared_ptr<Shader> GetShader();

    std::shared_ptr<MaterialPropertyBlock> GetPropertyBlock() const;

#if !USE_CBG
    std::shared_ptr<LLGI::PipelineState> GetPipelineState();
#endif

};

}  // namespace Altseed2