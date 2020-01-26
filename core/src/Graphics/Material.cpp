#include "Material.h"
#include "BuildinShader.h"

#include <glslang/Public/ShaderLang.h>
#include <spirv_cross/spirv.hpp>

namespace Altseed {

Vector4DF MaterialPropertyBlock::GetVector4F(const char16_t* key) const {
    auto it = vector4s_.find(key);

    if (it != vector4s_.end()) return it->second;
    return Vector4DF();
}

void MaterialPropertyBlock::SetVector4F(const char16_t* key, const Vector4DF& value) { vector4s_[key] = value; }

bool MaterialPropertyBlock::GetVector4F(const char16_t* key, Vector4DF& value) {
    auto it = vector4s_.find(key);

    if (it != vector4s_.end()) {
        value = it->second;
        return true;
    }
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
    return false;
}

std::shared_ptr<Texture2D> MaterialPropertyBlock::GetTexture(const char16_t* key) const {
    auto it = textures_.find(key);

    if (it != textures_.end()) return it->second;
    return nullptr;
}

void MaterialPropertyBlock::SetTexture(const char16_t* key, const std::shared_ptr<Texture2D>& value) { textures_[key] = value; }

bool MaterialPropertyBlock::GetTexture(const char16_t* key, std::shared_ptr<Texture2D>& value) {
    auto it = textures_.find(key);

    if (it != textures_.end()) {
        value = it->second;
        return true;
    }
    return false;
}

void MaterialPropertyBlockCollection::Add(std::shared_ptr<MaterialPropertyBlock> block) { blocks_.emplace_back(block); }

void MaterialPropertyBlockCollection::Clear() { blocks_.clear(); }

Vector4DF MaterialPropertyBlockCollection::GetVector4F(const char16_t* key) const {
    Vector4DF ret;
    for (int32_t i = static_cast<int32_t>(blocks_.size()) - 1; i > 0; i--) {
        if (blocks_[i]->GetVector4F(key, ret)) {
            return ret;
        }
    }

    return ret;
}

Matrix44F MaterialPropertyBlockCollection::GetMatrix44F(const char16_t* key) const {
    Matrix44F ret;
    for (int32_t i = static_cast<int32_t>(blocks_.size()) - 1; i > 0; i--) {
        if (blocks_[i]->GetMatrix44F(key, ret)) {
            return ret;
        }
    }

    return ret;
}


std::shared_ptr<Texture2D> MaterialPropertyBlockCollection::GetTexture(const char16_t* key) const {
    std::shared_ptr<Texture2D> ret;
    for (int32_t i = static_cast<int32_t>(blocks_.size()) - 1; i > 0; i--) {
        if (blocks_[i]->GetTexture(key, ret)) {
            return ret;
        }
    }
    return ret;
}

Material::Material() { propertyBlock_ = MakeAsdShared<MaterialPropertyBlock>(); }

Vector4DF Material::GetVector4F(const char16_t* key) const { return propertyBlock_->GetVector4F(key); }

void Material::SetVector4F(const char16_t* key, const Vector4DF& value) { propertyBlock_->SetVector4F(key, value); }

Matrix44F Material::GetMatrix44F(const char16_t* key) const { return propertyBlock_->GetMatrix44F(key); }

void Material::SetMatrix44F(const char16_t* key, const Matrix44F& value) { propertyBlock_->SetMatrix44F(key, value); }

std::shared_ptr<Texture2D> Material::GetTexture(const char16_t* key) const { return propertyBlock_->GetTexture(key); }

void Material::SetTexture(const char16_t* key, const std::shared_ptr<Texture2D>& value) { propertyBlock_->SetTexture(key, value); }

std::shared_ptr<MaterialPropertyBlock> Material::GetPropertyBlock() const { return propertyBlock_; }

std::shared_ptr<LLGI::PipelineState> Material::GetPipelineState(LLGI::RenderPass* renderPass) {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();

    auto renderPassPipelineState = LLGI::CreateSharedPtr(g->CreateRenderPassPipelineState(renderPass));
    auto it = pipelineStates_.find(renderPassPipelineState);
    if (it != pipelineStates_.end()) {
        return it->second;
    }

    if (vertexShader_ == nullptr) {
        vertexShader_ = Graphics::GetInstance()->GetBuildinShader()->Create(BuildinShaderType::SpriteUnlitVS);
    }

    auto piplineState = LLGI::CreateSharedPtr(g->CreatePiplineState());
    piplineState->SetShader(LLGI::ShaderStageType::Vertex, vertexShader_->Get());
    piplineState->SetShader(LLGI::ShaderStageType::Pixel, shader_->Get());
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

}  // namespace altseed