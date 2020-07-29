#pragma once

#include <stdio.h>

#include <memory>

#include "../../Math/RectF.h"
#include "../Color.h"
#include "../Material.h"
#include "../TextureBase.h"
#include "Rendered.h"

namespace Altseed2 {

class TextureBase;

class RenderedSprite : public Rendered {
private:
    AlphaBlend alphaBlend_;
    std::shared_ptr<TextureBase> texture_;
    std::shared_ptr<Material> material_;
    RectF src_;
    Color color_;

public:
    static std::shared_ptr<RenderedSprite> Create();

    AlphaBlend GetAlphaBlend() const { return alphaBlend_; }
    void SetAlphaBlend(AlphaBlend alphaBlend) { alphaBlend_ = alphaBlend; }

    RectF GetSrc() const;
    void SetSrc(const RectF& src);

    Color GetColor() const { return color_; }
    void SetColor(const Color color) { color_ = color; }

    std::shared_ptr<TextureBase> GetTexture() const;
    void SetTexture(const std::shared_ptr<TextureBase>& texture);

    std::shared_ptr<Material> GetMaterial() const;
    void SetMaterial(const std::shared_ptr<Material>& material);

    b2AABB GetAABB() override;
};

}  // namespace Altseed2