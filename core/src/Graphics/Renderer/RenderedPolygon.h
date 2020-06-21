#pragma once

#include <box2d/box2d.h>
#include <stdio.h>

#include <memory>

#include "../../Common/Array.h"
#include "../../Math/RectF.h"
#include "../Color.h"
#include "Rendered.h"

namespace Altseed2 {

class Material;
class Texture2D;

class RenderedPolygon : public Rendered {
private:
    AlphaBlendMode blendMode_;
    std::shared_ptr<VertexArray> vertexes_;
    std::shared_ptr<TextureBase> texture_;
    std::shared_ptr<Material> material_;
    RectF src_;

public:
    static std::shared_ptr<RenderedPolygon> Create();

    AlphaBlendMode GetBlendMode() const;
    void SetBlendMode(AlphaBlendMode blendMode);

    std::shared_ptr<VertexArray> GetVertexes();
    void SetVertexes(std::shared_ptr<VertexArray> vertexes);

    void CreateVertexesByVector2F(std::shared_ptr<Vector2FArray> vectors);
    void OverwriteVertexesColor(Color color);

    RectF GetSrc() const;
    void SetSrc(const RectF& src);

    std::shared_ptr<TextureBase> GetTexture() const;
    void SetTexture(const std::shared_ptr<TextureBase>& texture);

    std::shared_ptr<Material> GetMaterial() const;
    void SetMaterial(const std::shared_ptr<Material>& material);

    b2AABB GetAABB() override;
};

}  // namespace Altseed2
