#pragma once

#include <array>
#include <memory>

#include "Graphics.h"

namespace altseed {
class Sprite {
private:
    Vector2DF position_;
    Vector2DF size_;
    std::shared_ptr<LLGI::Texture> texture_;
    std::shared_ptr<Material> material_;

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
};
}  // namespace altseed
