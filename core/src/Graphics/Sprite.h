#pragma once

#include <array>
#include <memory>

#include "Graphics.h"
#include "Material.h"

namespace Altseed {

class Material;

class Sprite : public BaseObject {
private:
    Vector2DF position_;
    Vector2DF size_;
    std::shared_ptr<LLGI::Texture> texture_;
    std::shared_ptr<Material> material_;
    std::array<Vector2DF, 4> uvs_;

public:
    Sprite();

    std::array<LLGI::Vec2F, 4> GetVertex(LLGI::Vec2I windowSize);

    void SetPosition(Vector2DF position) { position_ = position; }
    Vector2DF GetPosition() const { return position_; }

    void SetSize(Vector2DF size) { size_ = size; }
    Vector2DF GetSize() const { return size_; }

    void SetMaterial(std::shared_ptr<Material>& material) { material_ = material; }
    std::shared_ptr<Material> GetMaterial() const { return material_; }

    void SetTexture(std::shared_ptr<LLGI::Texture>& Texture) { texture_ = Texture; }
    std::shared_ptr<LLGI::Texture> GetTexture() const { return texture_; }

    void SetUV(Vector2DF uv, int32_t index) {
        if (index >= 0 && index <= 3) uvs_[index] = uv;
    }
    std::array<Vector2DF, 4> GetUVs() const { return uvs_; }
};
}  // namespace Altseed
