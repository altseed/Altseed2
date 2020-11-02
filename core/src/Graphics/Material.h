#pragma once

#include <memory>
#include <unordered_map>

#include "../BaseObject.h"
#include "../Common/HashHelper.h"
#include "../Math/Matrix44F.h"
#include "../Math/Vector4F.h"
#include "Shader.h"
#include "TextureBase.h"

namespace Altseed2 {
enum class ShaderStageType;
class Shader;
class TextureBase;

enum class BlendEquationType {
    Add,
    Sub,
    ReverseSub,
    Min,
    Max,
};

enum class BlendFuncType {
    Zero,
    One,
    SrcColor,
    OneMinusSrcColor,
    SrcAlpha,
    OneMinusSrcAlpha,
    DstAlpha,
    OneMinusDstAlpha,
    DstColor,
    OneMinusDstColor,
};

struct AlphaBlend_C;

struct AlphaBlend {
    bool IsBlendEnabled = true;

    BlendFuncType BlendSrcFunc = BlendFuncType::SrcAlpha;
    BlendFuncType BlendDstFunc = BlendFuncType::OneMinusSrcAlpha;
    BlendFuncType BlendSrcFuncAlpha = BlendFuncType::SrcAlpha;
    BlendFuncType BlendDstFuncAlpha = BlendFuncType::OneMinusSrcAlpha;

    BlendEquationType BlendEquationRGB = BlendEquationType::Add;
    BlendEquationType BlendEquationAlpha = BlendEquationType::Add;

    operator AlphaBlend_C() const;

    bool operator==(const AlphaBlend& value) const {
        return IsBlendEnabled == value.IsBlendEnabled &&
               BlendSrcFunc == value.BlendSrcFunc &&
               BlendDstFunc == value.BlendDstFunc &&
               BlendSrcFuncAlpha == value.BlendSrcFuncAlpha &&
               BlendDstFuncAlpha == value.BlendDstFuncAlpha &&
               BlendEquationRGB == value.BlendEquationRGB &&
               BlendEquationAlpha == value.BlendEquationAlpha;
    };

    struct Hash {
        typedef std::size_t result_type;

        std::size_t operator()(const AlphaBlend& alphaBlend) const {
            std::size_t ret = 0;
            hash_combine(
                    ret,
                    alphaBlend.IsBlendEnabled,
                    alphaBlend.BlendSrcFunc,
                    alphaBlend.BlendDstFunc,
                    alphaBlend.BlendSrcFuncAlpha,
                    alphaBlend.BlendDstFuncAlpha,
                    alphaBlend.BlendEquationRGB,
                    alphaBlend.BlendEquationAlpha);
            return ret;
        }
    };

    static AlphaBlend Normal() {
        auto alphaBlend = AlphaBlend();
        alphaBlend.IsBlendEnabled = true;
        alphaBlend.BlendSrcFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendDstFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendEquationAlpha = BlendEquationType::Max;

        alphaBlend.BlendEquationRGB = BlendEquationType::Add;
        alphaBlend.BlendDstFunc = BlendFuncType::OneMinusSrcAlpha;
        alphaBlend.BlendSrcFunc = BlendFuncType::SrcAlpha;

        return alphaBlend;
    }

    static AlphaBlend Add() {
        auto alphaBlend = AlphaBlend();
        alphaBlend.IsBlendEnabled = true;
        alphaBlend.BlendSrcFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendDstFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendEquationAlpha = BlendEquationType::Max;

        alphaBlend.BlendEquationRGB = BlendEquationType::Add;
        alphaBlend.BlendDstFunc = BlendFuncType::One;
        alphaBlend.BlendSrcFunc = BlendFuncType::SrcAlpha;

        return alphaBlend;
    }

    static AlphaBlend Opacity() {
        auto alphaBlend = AlphaBlend();
        alphaBlend.IsBlendEnabled = false;
        alphaBlend.BlendSrcFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendDstFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendEquationAlpha = BlendEquationType::Max;

        alphaBlend.BlendEquationRGB = BlendEquationType::Add;
        alphaBlend.BlendDstFunc = BlendFuncType::Zero;
        alphaBlend.BlendSrcFunc = BlendFuncType::One;

        return alphaBlend;
    }

    static AlphaBlend Substract() {
        auto alphaBlend = AlphaBlend();
        alphaBlend.IsBlendEnabled = true;
        alphaBlend.BlendSrcFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendDstFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendEquationAlpha = BlendEquationType::Max;

        alphaBlend.BlendEquationRGB = BlendEquationType::ReverseSub;
        alphaBlend.BlendDstFunc = BlendFuncType::One;
        alphaBlend.BlendSrcFunc = BlendFuncType::SrcAlpha;

        return alphaBlend;
    }

    static AlphaBlend Multiply() {
        auto alphaBlend = AlphaBlend();
        alphaBlend.IsBlendEnabled = true;
        alphaBlend.BlendSrcFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendDstFuncAlpha = BlendFuncType::One;
        alphaBlend.BlendEquationAlpha = BlendEquationType::Max;

        alphaBlend.BlendEquationRGB = BlendEquationType::Add;
        alphaBlend.BlendDstFunc = BlendFuncType::SrcColor;
        alphaBlend.BlendSrcFunc = BlendFuncType::Zero;

        return alphaBlend;
    }
};

struct AlphaBlend_C {
    bool IsBlendEnabled;

    BlendFuncType BlendSrcFunc;
    BlendFuncType BlendDstFunc;
    BlendFuncType BlendSrcFuncAlpha;
    BlendFuncType BlendDstFuncAlpha;

    BlendEquationType BlendEquationRGB;
    BlendEquationType BlendEquationAlpha;

    operator AlphaBlend() const;
};

struct PipelineStateKey {
    AlphaBlend alphaBlend_;
    std::shared_ptr<LLGI::RenderPassPipelineState> renderPassPipelineState_ = nullptr;

    bool operator==(const PipelineStateKey& value) const {
        return alphaBlend_ == value.alphaBlend_ && renderPassPipelineState_ == value.renderPassPipelineState_;
    };

    struct Hash {
        typedef std::size_t result_type;

        std::size_t operator()(const PipelineStateKey& key) const {
            auto ret = AlphaBlend::Hash()(key.alphaBlend_);
            ret += std::hash<std::shared_ptr<LLGI::RenderPassPipelineState>>()(key.renderPassPipelineState_);
            return ret;
        }
    };
};

class MaterialPropertyBlock : public BaseObject {
    std::unordered_map<std::u16string, Vector4F> vector4s_;
    std::unordered_map<std::u16string, Matrix44F> matrix44s_;
    std::unordered_map<std::u16string, std::shared_ptr<TextureBase>> textures_;

public:
    Vector4F GetVector4F(const char16_t* key) const;
    void SetVector4F(const char16_t* key, const Vector4F& value);

    Matrix44F GetMatrix44F(const char16_t* key) const;
    void SetMatrix44F(const char16_t* key, const Matrix44F& value);

#if !USE_CBG
    bool GetVector4F(const char16_t* key, Vector4F& value);
    bool GetMatrix44F(const char16_t* key, Matrix44F& value);
#endif

    std::shared_ptr<TextureBase> GetTexture(const char16_t* key) const;
    void SetTexture(const char16_t* key, const std::shared_ptr<TextureBase>& value);
    bool GetTexture(const char16_t* key, std::shared_ptr<TextureBase>& value);
};

class MaterialPropertyBlockCollection : public BaseObject {
    std::vector<std::shared_ptr<MaterialPropertyBlock>> blocks_;

public:
    void Add(std::shared_ptr<MaterialPropertyBlock> block);
    void Clear();
    Vector4F GetVector4F(const char16_t* key) const;
    Matrix44F GetMatrix44F(const char16_t* key) const;
    std::shared_ptr<TextureBase> GetTexture(const char16_t* key) const;
};

class Material : public BaseObject {
private:
    std::shared_ptr<Shader> vertexShader_;
    std::shared_ptr<Shader> pixelShader_;
    std::shared_ptr<MaterialPropertyBlock> propertyBlock_;

    std::unordered_map<PipelineStateKey, std::shared_ptr<LLGI::PipelineState>, PipelineStateKey::Hash> pipelineStates_;

    AlphaBlend alphaBlend_;

    void SetBlendFuncs(const std::shared_ptr<LLGI::PipelineState>& piplineState);

public:
    Material();

    static std::shared_ptr<Material> Create();

    Vector4F GetVector4F(const char16_t* key) const;
    void SetVector4F(const char16_t* key, const Vector4F& value);

    Matrix44F GetMatrix44F(const char16_t* key) const;
    void SetMatrix44F(const char16_t* key, const Matrix44F& value);

    std::shared_ptr<TextureBase> GetTexture(const char16_t* key) const;
    void SetTexture(const char16_t* key, const std::shared_ptr<TextureBase>& value);

    std::shared_ptr<Shader> GetShader(Altseed2::ShaderStageType shaderStage) const;
    void SetShader(const std::shared_ptr<Shader>& shader);

    AlphaBlend GetAlphaBlend() const;
    void SetAlphaBlend(const AlphaBlend value);

    std::shared_ptr<MaterialPropertyBlock> GetPropertyBlock() const;

#if !USE_CBG
    std::shared_ptr<LLGI::PipelineState> GetPipelineState(LLGI::RenderPass* renderPass);
#endif
};

}  // namespace Altseed2
