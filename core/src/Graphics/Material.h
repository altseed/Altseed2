#pragma once

#include <memory>

#include <map>
#include <unordered_map>
#include "../BaseObject.h"
#include "../Math/Matrix44F.h"
#include "../Math/Vector4DF.h"
#include "Shader.h"

namespace Altseed {

class Shader;
class Texture2D;

class MaterialPropertyBlock : public BaseObject {
    std::unordered_map<std::u16string, Vector4DF> vector4s_;
    std::unordered_map<std::u16string, Matrix44F> matrix44s_;
    std::unordered_map<std::u16string, std::shared_ptr<Texture2D>> textures_;

public:
    Vector4DF GetVector4F(const char16_t* key) const;
    void SetVector4F(const char16_t* key, const Vector4DF& value);
    bool GetVector4F(const char16_t* key, Vector4DF& value);

    Matrix44F GetMatrix44F(const char16_t* key) const;
    void SetMatrix44F(const char16_t* key, const Matrix44F& value);
    bool GetMatrix44F(const char16_t* key, Matrix44F& value);

    std::shared_ptr<Texture2D> GetTexture(const char16_t* key) const;
    void SetTexture(const char16_t* key, const std::shared_ptr<Texture2D>& value);
    bool GetTexture(const char16_t* key, std::shared_ptr<Texture2D>& value);
};

class MaterialPropertyBlockCollection : public BaseObject {
    std::vector<std::shared_ptr<MaterialPropertyBlock>> blocks_;

public:
    void Add(std::shared_ptr<MaterialPropertyBlock> block);
    void Clear();
    Vector4DF GetVector4F(const char16_t* key) const;
    Matrix44F GetMatrix44F(const char16_t* key) const;
    std::shared_ptr<Texture2D> GetTexture(const char16_t* key) const;
};

class Material : public BaseObject {
private:
    std::shared_ptr<Shader> vertexShader_;
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<MaterialPropertyBlock> propertyBlock_;

    std::map<std::shared_ptr<LLGI::RenderPassPipelineState>, std::shared_ptr<LLGI::PipelineState>> pipelineStates_;

public:
    Material();

    Vector4DF GetVector4F(const char16_t* key) const;
    void SetVector4F(const char16_t* key, const Vector4DF& value);

    Matrix44F GetMatrix44F(const char16_t* key) const;
    void SetMatrix44F(const char16_t* key, const Matrix44F& value);

    std::shared_ptr<Texture2D> GetTexture(const char16_t* key) const;
    void SetTexture(const char16_t* key, const std::shared_ptr<Texture2D>& value);

    std::shared_ptr<Shader> GetVertexShader() const { return vertexShader_; }
    std::shared_ptr<Shader> GetShader() const { return shader_; }
    void SetShader(std::shared_ptr<Shader>& shader) { shader_ = shader; }

    std::shared_ptr<MaterialPropertyBlock> GetPropertyBlock() const;

    std::shared_ptr<LLGI::PipelineState> GetPipelineState(LLGI::RenderPass* renderPass);
};

}  // namespace Altseed
