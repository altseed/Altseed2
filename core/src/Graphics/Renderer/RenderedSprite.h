#pragma once

#include <stdio.h>

#include <memory>

#include "../../Math/RectF.h"
#include "../TextureBase.h"
#include "Rendered.h"

namespace Altseed {

class Material;
class TextureBase;

class RenderedSprite : public Rendered {
private:
    std::shared_ptr<TextureBase> texture_;
    std::shared_ptr<Material> material_;
    RectF src_;

public:
    static std::shared_ptr<RenderedSprite> Create();

    RectF GetSrc() const;
    void SetSrc(const RectF& src);

    std::shared_ptr<TextureBase> GetTexture() const;
    void SetTexture(const std::shared_ptr<TextureBase>& texture);

    std::shared_ptr<Material> GetMaterial() const;
    void SetMaterial(const std::shared_ptr<Material>& material);
};

}  // namespace Altseed