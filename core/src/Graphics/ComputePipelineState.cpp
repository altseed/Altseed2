#include "ComputePipelineState.h"

#include "../Logger/Log.h"

namespace Altseed2 {

ComputePipelineState::ComputePipelineState() {
    propertyBlock_ = MakeAsdShared<MaterialPropertyBlock>();
    computeShader_ = nullptr;
    pipelineState_ = nullptr;
}

std::shared_ptr<ComputePipelineState> ComputePipelineState::Create() {
    return MakeAsdShared<ComputePipelineState>();
}

Vector4F ComputePipelineState::GetVector4F(const char16_t* key) const {
    return propertyBlock_->GetVector4F(key);
}

void ComputePipelineState::SetVector4F(const char16_t* key, const Vector4F& value) {
    propertyBlock_->SetVector4F(key, value);
}

Matrix44F ComputePipelineState::GetMatrix44F(const char16_t* key) const {
    return propertyBlock_->GetMatrix44F(key);
}

void ComputePipelineState::SetMatrix44F(const char16_t* key, const Matrix44F& value) {
    propertyBlock_->SetMatrix44F(key, value);
}

void ComputePipelineState::SetShader(std::shared_ptr<Shader> shader) {
    computeShader_ = shader;
    requireCompile = true;
}

std::shared_ptr<Shader> ComputePipelineState::GetShader() {
    return computeShader_;
}

std::shared_ptr<MaterialPropertyBlock> ComputePipelineState::GetPropertyBlock() const {
    return propertyBlock_;
}

std::shared_ptr<LLGI::PipelineState> ComputePipelineState::GetPipelineState() {
    if (pipelineState_ != nullptr && !requireCompile) {
        return pipelineState_;
    }

    auto g = Graphics::GetInstance()->GetGraphicsLLGI();

    pipelineState_ = LLGI::CreateSharedPtr(g->CreatePiplineState());

    pipelineState_->SetShader(LLGI::ShaderStageType::Compute, computeShader_->Get());

    pipelineState_->Compile();
    requireCompile = false;

    return pipelineState_;
}

}  // namespace Altseed2