#pragma once

#include "Rendered.h"

#include <stdio.h>
#include <memory>
#include "../../Common/Array.h"
#include "../../Math/RectF.h"
#include "../Color.h"

namespace Altseed {

class Material;
class Texture2D;

class RenderedPolygon : public Rendered {
private:
    std::shared_ptr<VertexArray> vertexes_;
    std::shared_ptr<TextureBase> texture_;
    std::shared_ptr<Material> material_;
    RectF src_;

public:
    static std::shared_ptr<RenderedPolygon> Create();

    std::shared_ptr<VertexArray> GetVertexes();
    void SetVertexes(std::shared_ptr<VertexArray> vertexes);
    void SetVertexesByVector2F(std::shared_ptr<Vector2FArray> vertexes);

    RectF GetSrc() const;
    void SetSrc(const RectF& src);

    std::shared_ptr<TextureBase> GetTexture() const;
    void SetTexture(const std::shared_ptr<TextureBase>& texture);

    std::shared_ptr<Material> GetMaterial() const;
    void SetMaterial(const std::shared_ptr<Material>& material);
};

}  // namespace Altseed
