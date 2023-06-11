﻿#include "Material.h"

#include <glslang/Public/ShaderLang.h>

#include <spirv_cross/spirv.hpp>

#include "../Common/StringHelper.h"
#include "../Logger/Log.h"
#include "BuiltinShader.h"

namespace Altseed2 {

AlphaBlend::operator Altseed2::AlphaBlend_C() const {
    auto m = AlphaBlend_C();
    m.IsBlendEnabled = IsBlendEnabled;
    m.BlendSrcFunc = BlendSrcFunc;
    m.BlendDstFunc = BlendDstFunc;
    m.BlendSrcFuncAlpha = BlendSrcFuncAlpha;
    m.BlendDstFuncAlpha = BlendDstFuncAlpha;
    m.BlendEquationRGB = BlendEquationRGB;
    m.BlendEquationAlpha = BlendEquationAlpha;
    return m;
}

AlphaBlend_C::operator Altseed2::AlphaBlend() const {
    auto m = AlphaBlend();
    m.IsBlendEnabled = IsBlendEnabled;
    m.BlendSrcFunc = BlendSrcFunc;
    m.BlendDstFunc = BlendDstFunc;
    m.BlendSrcFuncAlpha = BlendSrcFuncAlpha;
    m.BlendDstFuncAlpha = BlendDstFuncAlpha;
    m.BlendEquationRGB = BlendEquationRGB;
    m.BlendEquationAlpha = BlendEquationAlpha;
    return m;
}

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

Material::Material() {
    propertyBlock_ = MakeAsdShared<MaterialPropertyBlock>();
    vertexShader_ = nullptr;
    pixelShader_ = nullptr;
    alphaBlend_ = AlphaBlend::Normal();
}

std::shared_ptr<Material> Material::Create() { return MakeAsdShared<Material>(); }

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
            ASD_ASSERT_FORCE("Invalid ShaderStageType in Material::GetShader");
    }
}

void Material::SetShader(const std::shared_ptr<Shader>& shader) {
    pipelineStates_.clear();

    switch (shader->GetStageType()) {
        case ShaderStageType::Vertex:
            vertexShader_ = shader;
            return;
        case ShaderStageType::Pixel:
            pixelShader_ = shader;
            return;
        default:
            ASD_ASSERT_FORCE("Invalid ShaderStageType in Material::SetShader");
    }
}

AlphaBlend Material::GetAlphaBlend() const { return alphaBlend_; }

void Material::SetAlphaBlend(const AlphaBlend value) { alphaBlend_ = value; }

std::shared_ptr<MaterialPropertyBlock> Material::GetPropertyBlock() const { return propertyBlock_; }

std::shared_ptr<LLGI::PipelineState> Material::GetPipelineState(LLGI::RenderPass* renderPass) {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();

    auto key = PipelineStateKey();
    key.renderPassPipelineState_ = LLGI::CreateSharedPtr(g->CreateRenderPassPipelineState(renderPass));
    key.alphaBlend_ = alphaBlend_;

    auto it = pipelineStates_.find(key);
    if (it != pipelineStates_.end()) {
        return it->second;
    }

    if (vertexShader_ == nullptr) {
        vertexShader_ = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitVS);
    }

    if (pixelShader_ == nullptr) {
        pixelShader_ = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitPS);
    }

    auto piplineState = LLGI::CreateSharedPtr(g->CreatePiplineState());
    piplineState->SetShader(LLGI::ShaderStageType::Vertex, vertexShader_->Get());
    piplineState->SetShader(LLGI::ShaderStageType::Pixel, pixelShader_->Get());
    piplineState->Culling = LLGI::CullingMode::DoubleSide;
    piplineState->SetRenderPassPipelineState(key.renderPassPipelineState_.get());

    piplineState->VertexLayouts[0] = LLGI::VertexLayoutFormat::R32G32B32_FLOAT;
    piplineState->VertexLayouts[1] = LLGI::VertexLayoutFormat::R8G8B8A8_UNORM;
    piplineState->VertexLayouts[2] = LLGI::VertexLayoutFormat::R32G32_FLOAT;
    piplineState->VertexLayouts[3] = LLGI::VertexLayoutFormat::R32G32_FLOAT;

    piplineState->VertexLayoutNames[0] = "TEXCOORD";
    piplineState->VertexLayoutNames[1] = "TEXCOORD";
    piplineState->VertexLayoutNames[2] = "TEXCOORD";
    piplineState->VertexLayoutNames[3] = "TEXCOORD";
    piplineState->VertexLayoutSemantics[0] = 0;
    piplineState->VertexLayoutSemantics[1] = 1;
    piplineState->VertexLayoutSemantics[2] = 2;
    piplineState->VertexLayoutSemantics[3] = 3;

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
    piplineState->VertexLayoutCount = 4;

    piplineState->IsBlendEnabled = alphaBlend_.IsBlendEnabled;
    piplineState->BlendSrcFunc = static_cast<LLGI::BlendFuncType>(alphaBlend_.BlendSrcFunc);
    piplineState->BlendDstFunc = static_cast<LLGI::BlendFuncType>(alphaBlend_.BlendDstFunc);
    piplineState->BlendSrcFuncAlpha = static_cast<LLGI::BlendFuncType>(alphaBlend_.BlendSrcFuncAlpha);
    piplineState->BlendDstFuncAlpha = static_cast<LLGI::BlendFuncType>(alphaBlend_.BlendDstFuncAlpha);
    piplineState->BlendEquationRGB = static_cast<LLGI::BlendEquationType>(alphaBlend_.BlendEquationRGB);
    piplineState->BlendEquationAlpha = static_cast<LLGI::BlendEquationType>(alphaBlend_.BlendEquationAlpha);

    piplineState->Compile();

    pipelineStates_[key] = piplineState;

    return piplineState;
}

}  // namespace Altseed2