#include "Material.h"
#include <glslang/Public/ShaderLang.h>
#include <spirv_cross/spirv.hpp>
#include "../Common/StringHelper.h"
#include "../Logger/Log.h"
#include "BuiltinShader.h"

namespace Altseed {

Vector4F MaterialPropertyBlock::GetVector4F(const char16_t* key) const {
    auto it = vector4s_.find(key);

    if (it != vector4s_.end()) return it->second;

    Log::GetInstance()->Error(LogCategory::Core, u"MaterialPropertyBlock::GetVector4F: '{0}' is not found", utf16_to_utf8(key).c_str());
    return Vector4F();
}

void MaterialPropertyBlock::SetVector4F(const char16_t* key, const Vector4F& value) { vector4s_[key] = value; }

bool MaterialPropertyBlock::GetVector4F(const char16_t* key, Vector4F& value) {
    auto it = vector4s_.find(key);

    if (it != vector4s_.end()) {
        value = it->second;
        return true;
    }

    Log::GetInstance()->Error(LogCategory::Core, u"MaterialPropertyBlock::GetVector4F: '{0}' is not found", utf16_to_utf8(key).c_str());
    return false;
}

Matrix44F MaterialPropertyBlock::GetMatrix44F(const char16_t* key) const {
    auto it = matrix44s_.find(key);

    if (it != matrix44s_.end()) return it->second;
    return Matrix44F();
}

void MaterialPropertyBlock::SetMatrix44F(const char16_t* key, const Matrix44F& value) { matrix44s_[key] = value; }

bool MaterialPropertyBlock::GetMatrix44F(const char16_t* key, Matrix44F& value) {
    auto it = matrix44s_.find(key);

    if (it != matrix44s_.end()) {
        value = it->second;
        return true;
    }

    Log::GetInstance()->Error(LogCategory::Core, u"MaterialPropertyBlock::GetMatrix44F: '{0}' is not found", utf16_to_utf8(key).c_str());
    return false;
}

std::shared_ptr<TextureBase> MaterialPropertyBlock::GetTexture(const char16_t* key) const {
    auto it = textures_.find(key);

    if (it != textures_.end()) return it->second;

    Log::GetInstance()->Error(LogCategory::Core, u"MaterialPropertyBlock::GetTexture: '{0}' is not found", utf16_to_utf8(key).c_str());
    return nullptr;
}

void MaterialPropertyBlock::SetTexture(const char16_t* key, const std::shared_ptr<TextureBase>& value) { textures_[key] = value; }

bool MaterialPropertyBlock::GetTexture(const char16_t* key, std::shared_ptr<TextureBase>& value) {
    auto it = textures_.find(key);

    if (it != textures_.end()) {
        value = it->second;
        return true;
    }

    Log::GetInstance()->Error(LogCategory::Core, u"MaterialPropertyBlock::GetTexture: '{0}' is not found", utf16_to_utf8(key).c_str());
    return false;
}

void MaterialPropertyBlockCollection::Add(std::shared_ptr<MaterialPropertyBlock> block) { blocks_.emplace_back(block); }

void MaterialPropertyBlockCollection::Clear() { blocks_.clear(); }

Vector4F MaterialPropertyBlockCollection::GetVector4F(const char16_t* key) const {
    Vector4F ret;
    for (int32_t i = static_cast<int32_t>(blocks_.size()) - 1; i >= 0; i--) {
        if (blocks_[i]->GetVector4F(key, ret)) {
            return ret;
        }
    }

    Log::GetInstance()->Error(
            LogCategory::Core, u"MaterialPropertyBlockCollection::GetVector4F: '{0}' is not found", utf16_to_utf8(key).c_str());
    return ret;
}

Matrix44F MaterialPropertyBlockCollection::GetMatrix44F(const char16_t* key) const {
    Matrix44F ret;
    for (int32_t i = static_cast<int32_t>(blocks_.size()) - 1; i >= 0; i--) {
        if (blocks_[i]->GetMatrix44F(key, ret)) {
            return ret;
        }
    }

    Log::GetInstance()->Error(
            LogCategory::Core, u"MaterialPropertyBlockCollection::GetMatrix44F: '{0}' is not found", utf16_to_utf8(key).c_str());
    return ret;
}

std::shared_ptr<TextureBase> MaterialPropertyBlockCollection::GetTexture(const char16_t* key) const {
    std::shared_ptr<TextureBase> ret;
    for (int32_t i = static_cast<int32_t>(blocks_.size()) - 1; i >= 0; i--) {
        if (blocks_[i]->GetTexture(key, ret)) {
            return ret;
        }
    }

    Log::GetInstance()->Error(
            LogCategory::Core, u"MaterialPropertyBlockCollection::GetTexture: '{0}' is not found", utf16_to_utf8(key).c_str());
    return ret;
}

Material::Material() { propertyBlock_ = MakeAsdShared<MaterialPropertyBlock>(); }

Vector4F Material::GetVector4F(const char16_t* key) const { return propertyBlock_->GetVector4F(key); }

void Material::SetVector4F(const char16_t* key, const Vector4F& value) { propertyBlock_->SetVector4F(key, value); }

Matrix44F Material::GetMatrix44F(const char16_t* key) const { return propertyBlock_->GetMatrix44F(key); }

void Material::SetMatrix44F(const char16_t* key, const Matrix44F& value) { propertyBlock_->SetMatrix44F(key, value); }

std::shared_ptr<TextureBase> Material::GetTexture(const char16_t* key) const { return propertyBlock_->GetTexture(key); }

void Material::SetTexture(const char16_t* key, const std::shared_ptr<TextureBase>& value) { propertyBlock_->SetTexture(key, value); }

std::shared_ptr<Shader> Material::GetShader(ShaderStageType shaderStage) const {
    switch (shaderStage) {
        case ShaderStageType::Vertex:
            return vertexShader_;
        case ShaderStageType::Pixel:
            return pixelShader_;
        default:
            ASD_ASSERT(false, "Invalid ShaderStageType in Material::GetShader");
    }
}

void Material::SetShader(std::shared_ptr<Shader>& shader) {
    switch (shader->GetStageType()) {
        case ShaderStageType::Vertex:
            vertexShader_ = shader;
            return;
        case ShaderStageType::Pixel:
            pixelShader_ = shader;
            return;
        default:
            ASD_ASSERT(false, "Invalid ShaderStageType in Material::SetShader");
    }
}

std::shared_ptr<MaterialPropertyBlock> Material::GetPropertyBlock() const { return propertyBlock_; }

std::shared_ptr<LLGI::PipelineState> Material::GetPipelineState(LLGI::RenderPass* renderPass) {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();

    auto renderPassPipelineState = LLGI::CreateSharedPtr(g->CreateRenderPassPipelineState(renderPass));
    auto it = pipelineStates_.find(renderPassPipelineState);
    if (it != pipelineStates_.end()) {
        return it->second;
    }

    if (vertexShader_ == nullptr) {
        vertexShader_ = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitVS);
    }

    auto piplineState = LLGI::CreateSharedPtr(g->CreatePiplineState());
    piplineState->SetShader(LLGI::ShaderStageType::Vertex, vertexShader_->Get());
    piplineState->SetShader(LLGI::ShaderStageType::Pixel, pixelShader_->Get());
    piplineState->Culling = LLGI::CullingMode::DoubleSide;
    piplineState->SetRenderPassPipelineState(renderPassPipelineState.get());

    piplineState->VertexLayouts[0] = LLGI::VertexLayoutFormat::R32G32B32_FLOAT;
    piplineState->VertexLayouts[1] = LLGI::VertexLayoutFormat::R8G8B8A8_UNORM;
    piplineState->VertexLayouts[2] = LLGI::VertexLayoutFormat::R32G32_FLOAT;
    piplineState->VertexLayouts[3] = LLGI::VertexLayoutFormat::R32G32_FLOAT;
    piplineState->VertexLayoutNames[0] = "POSITION";
    piplineState->VertexLayoutNames[1] = "COLOR";
    piplineState->VertexLayoutNames[2] = "UV";
    piplineState->VertexLayoutNames[3] = "UV";
    piplineState->VertexLayoutSemantics[0] = 0;
    piplineState->VertexLayoutSemantics[1] = 0;
    piplineState->VertexLayoutSemantics[2] = 0;
    piplineState->VertexLayoutSemantics[3] = 1;
    piplineState->VertexLayoutCount = 4;

    piplineState->Compile();

    pipelineStates_[renderPassPipelineState] = piplineState;

    return piplineState;
}

}  // namespace Altseed