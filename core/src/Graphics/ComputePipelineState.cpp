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

std::shared_ptr<TextureBase> ComputePipelineState::GetTexture(const char16_t* key) const {
    return propertyBlock_->GetTexture(key);
}

void ComputePipelineState::SetTexture(const char16_t* key, const std::shared_ptr<TextureBase>& value) {
    propertyBlock_->SetTexture(key, value);
}

void ComputePipelineState::SetShader(std::shared_ptr<Shader> shader) {
    computeShader_ = shader;
    requireCompile = true;
}

std::shared_ptr<Shader> ComputePipelineState::GetShader() {
    return computeShader_;
}

const char16_t* ComputePipelineState::GetVertexLayoutName(int32_t index) {
    if (index >= LLGI::VertexLayoutMax) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"ComputePipelineState::GetVertexLayoutName: index out of range");
        return nullptr;
    }
    return utf8_to_utf16(vertexLayoutNames_[index]).c_str();
}

void ComputePipelineState::SetVertexLayoutName(int32_t index, const char16_t* name) {
    if (index >= LLGI::VertexLayoutMax) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"ComputePipelineState::SetVertexLayoutName: index out of range");
        return;
    }
    vertexLayoutNames_[index] = utf16_to_utf8(name);
    requireCompile = true;
}

VertexLayoutFormat ComputePipelineState::GetVertexLayoutFormat(int32_t index) {
    if (index >= LLGI::VertexLayoutMax) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"ComputePipelineState::GetVertexLayoutFormat: index out of range");
        return VertexLayoutFormat::R32G32B32A32_FLOAT;
    }
    return vertexLayouts_[index];
}

void ComputePipelineState::SetVertexLayoutFormat(int32_t index, VertexLayoutFormat format) {
    if (index >= LLGI::VertexLayoutMax) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"ComputePipelineState::SetVertexLayoutFormat: index out of range");
        return;
    }
    vertexLayouts_[index] = format;
    requireCompile = true;
}

int32_t ComputePipelineState::GetVertexLayoutSemasntics(int32_t index) {
    if (index >= LLGI::VertexLayoutMax) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"ComputePipelineState::GetVertexLayoutSemasntics: index out of range");
        return 0;
    }
    return vertexLayoutSemantics_[index];
}

void ComputePipelineState::SetVertexLayoutSemasntics(int32_t index, int32_t semantics) {
    if (index >= LLGI::VertexLayoutMax) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"ComputePipelineState::SetVertexLayoutSemasntics: index out of range");
        return;
    }
    vertexLayoutSemantics_[index] = semantics;
    requireCompile = true;
}

int32_t ComputePipelineState::GetVertexLayoutCount() {
    return vertexLayoutCount_;
}

void ComputePipelineState::SetVertexLayoutCount(int32_t count) {
    vertexLayoutCount_ = count;
    requireCompile = true;
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

    pipelineState_->VertexLayoutCount = GetVertexLayoutCount();
    for (int i = 0; i < GetVertexLayoutCount(); i++) {
        pipelineState_->VertexLayouts[i] = (LLGI::VertexLayoutFormat)vertexLayouts_[i];
        pipelineState_->VertexLayoutNames[i] = vertexLayoutNames_[i];
        pipelineState_->VertexLayoutSemantics[i] = vertexLayoutSemantics_[i];
    }
    // Transpiled
    /*
	piplineState->VertexLayoutNames[0] = "POSITION";
    piplineState->VertexLayoutNames[1] = "COLOR";
    piplineState->VertexLayoutNames[2] = "UV";
    piplineState->VertexLayoutNames[3] = "UV";
    piplineState->VertexLayoutSemantics[0] = 0;
    piplineState->VertexLayoutSemantics[1] = 0;
    piplineState->VertexLayoutSemantics[2] = 0;
    piplineState->VertexLayoutSemantics[3] = 1;
	*/

    pipelineState_->Compile();
    requireCompile = false;

    return pipelineState_;
}

}  // namespace Altseed2