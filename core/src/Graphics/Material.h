#pragma once

#include <memory>
#include <unordered_map>

#include "../BaseObject.h"
#include "../Math/Matrix44F.h"
#include "../Math/Vector4F.h"
#include "Shader.h"
#include "TextureBase.h"

namespace Altseed2 {

enum class ShaderStageType;
class Shader;
class TextureBase;

enum class AlphaBlendMode : int32_t { Opacity,
                                      Normal,
                                      Add,
                                      Subtract,
                                      Multiply,
                                      Max };

struct PipelineStateKey {
    AlphaBlendMode alphaBlendMode_ = AlphaBlendMode::Normal;
    std::shared_ptr<LLGI::RenderPassPipelineState> renderPassPipelineState_ = nullptr;

    bool operator==(const PipelineStateKey& value) const {
        return alphaBlendMode_ == value.alphaBlendMode_ && renderPassPipelineState_ == value.renderPassPipelineState_;
    };

    struct Hash {
        typedef std::size_t result_type;

        std::size_t operator()(const PipelineStateKey& key) const {
            auto ret = std::hash<AlphaBlendMode>()(key.alphaBlendMode_);
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
    bool GetVector4F(const char16_t* key, Vector4F& value);

    Matrix44F GetMatrix44F(const char16_t* key) const;
    void SetMatrix44F(const char16_t* key, const Matrix44F& value);
    bool GetMatrix44F(const char16_t* key, Matrix44F& value);

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

    AlphaBlendMode alphaBlendMode_;

    void SetBlendFuncs(const std::shared_ptr<LLGI::PipelineState>& piplineState);

public:
    Material();

    Vector4F GetVector4F(const char16_t* key) const;
    void SetVector4F(const char16_t* key, const Vector4F& value);

    Matrix44F GetMatrix44F(const char16_t* key) const;
    void SetMatrix44F(const char16_t* key, const Matrix44F& value);

    std::shared_ptr<TextureBase> GetTexture(const char16_t* key) const;
    void SetTexture(const char16_t* key, const std::shared_ptr<TextureBase>& value);

    std::shared_ptr<Shader> GetShader(Altseed2::ShaderStageType shaderStage) const;
    void SetShader(const std::shared_ptr<Shader>& shader);

    AlphaBlendMode GetBlendMode() const;
    void SetBlendMode(const AlphaBlendMode value);

    std::shared_ptr<MaterialPropertyBlock> GetPropertyBlock() const;

    std::shared_ptr<LLGI::PipelineState> GetPipelineState(LLGI::RenderPass* renderPass);
};

}  // namespace Altseed2
