#pragma once

#include <box2d/box2d.h>
#include <stdio.h>

#include <memory>

#include "../../Common/Array.h"
#include "../../Math/RectF.h"
#include "../Color.h"
#include "../Material.h"
#include "../Texture2D.h"
#include "Rendered.h"

namespace Altseed2 {

class RenderedIBPolygon : public Rendered {
private:
    AlphaBlend alphaBlend_;
    std::shared_ptr<Int32Array> buffers_;
    std::shared_ptr<Material> material_;
    RectF src_;
    std::shared_ptr<TextureBase> texture_;
    std::shared_ptr<VertexArray> vertexes_;

public:
    static std::shared_ptr<RenderedIBPolygon> Create();

    AlphaBlend GetAlphaBlend() const;
    void SetAlphaBlend(const AlphaBlend& value);

    std::shared_ptr<Int32Array> GetBuffers() const;
    void SetBuffers(const std::shared_ptr<Int32Array> value);

    void CreateVertexesByVector2F(const std::shared_ptr<Vector2FArray> vectors);

    std::shared_ptr<Material> GetMaterial() const;
    void SetMaterial(const std::shared_ptr<Material>& value);

    void OverwriteVertexesColor(const Color& color);

    RectF GetSrc() const;
    void SetSrc(const RectF& value);

    std::shared_ptr<TextureBase> GetTexture() const;
    void SetTexture(const std::shared_ptr<TextureBase>& value);

    std::shared_ptr<VertexArray> GetVertexes() const;
    void SetVertexes(const std::shared_ptr<VertexArray> value);

    b2AABB GetAABB() override;

    void SetDefaultIndexBuffer();
};

}  // namespace Altseed2
