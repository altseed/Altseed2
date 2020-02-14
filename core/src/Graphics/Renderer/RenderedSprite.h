#pragma once

#include "Rendered.h"

#include <stdio.h>
#include <memory>
#include "../../Math/RectF.h"

namespace Altseed {

class Material;
class Texture2D;

class RenderedSprite : public Rendered {
private:
    std::shared_ptr<Texture2D> texture_;
    std::shared_ptr<Material> material_;
    RectF src_;

public:
    RectF GetSrc() const;
    void SetSrc(const RectF& src);

    std::shared_ptr<Texture2D> GetTexture() const;
    void SetTexture(const std::shared_ptr<Texture2D>& texture);

    std::shared_ptr<Material> GetMaterial() const;
    void SetMaterial(const std::shared_ptr<Material>& material);
};

}  // namespace Altseed