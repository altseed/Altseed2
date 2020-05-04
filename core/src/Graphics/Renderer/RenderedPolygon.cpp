#include "RenderedPolygon.h"

#include "CullingSystem.h"

namespace Altseed {

std::shared_ptr<RenderedPolygon> RenderedPolygon::Create() { return MakeAsdShared<RenderedPolygon>(); }

std::shared_ptr<VertexArray> RenderedPolygon::GetVertexes() { return vertexes_; }

void RenderedPolygon::SetVertexes(std::shared_ptr<VertexArray> vertexes) {
    vertexes_ = vertexes;
    cullingSystem_->RequestUpdateAABB(this);
}

void RenderedPolygon::SetVertexesByVector2F(std::shared_ptr<Vector2FArray> vertexes) {
    vertexes_ = MakeAsdShared<VertexArray>();
    vertexes_->Resize(vertexes->GetCount());

    float xMin, xMax, yMin, yMax;
    {
        auto& v = vertexes->GetVector()[0];
        xMin = v.X;
        xMax = v.X;
        yMin = v.Y;
        yMax = v.Y;
    }

    for (int i = 0; i < vertexes->GetCount(); ++i) {
        auto& dst = vertexes_->GetVector()[i].Pos;
        auto& src = vertexes->GetVector()[i];

        dst.X = src.X;
        dst.Y = src.Y;
        dst.Z = 0.5f;

        if (src.X < xMin) {
            xMin = src.X;
        }
        if (src.X > xMax) {
            xMax = src.X;
        }
        if (src.Y < yMin) {
            yMin = src.Y;
        }
        if (src.Y > yMax) {
            yMax = src.Y;
        }
    }

    // UV, 色を設定
    for (int i = 0; i < vertexes->GetCount(); ++i) {
        auto& dst = vertexes_->GetVector()[i];
        dst.UV1.X = (dst.Pos.X - xMin) / (xMax - xMin);
        dst.UV1.Y = (dst.Pos.Y - yMin) / (yMax - yMin);
        dst.UV2 = dst.UV1;
        dst.Col = Color(255, 255, 255, 255);
    }

    cullingSystem_->RequestUpdateAABB(this);
}

RectF RenderedPolygon::GetSrc() const { return src_; }

void RenderedPolygon::SetSrc(const RectF& src) { src_ = src; }

std::shared_ptr<TextureBase> RenderedPolygon::GetTexture() const { return texture_; }

void RenderedPolygon::SetTexture(const std::shared_ptr<TextureBase>& texture) { texture_ = texture; }

std::shared_ptr<Material> RenderedPolygon::GetMaterial() const { return material_; }

void RenderedPolygon::SetMaterial(const std::shared_ptr<Material>& material) { material_ = material; }

b2AABB RenderedPolygon::GetAABB() {
    if (GetVertexes() == nullptr || GetVertexes()->GetCount() == 0) return b2AABB();

    b2AABB res;
    res.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
    res.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
    for (auto&& _v : GetVertexes()->GetVector()) {
        auto v = transform_.Transform3D(_v.Pos);
        res.lowerBound = b2Vec2(res.lowerBound.x > v.X ? v.X : res.lowerBound.x, res.lowerBound.y > v.Y ? v.Y : res.lowerBound.y);
        res.upperBound = b2Vec2(res.upperBound.x < v.X ? v.X : res.upperBound.x, res.upperBound.y < v.Y ? v.Y : res.upperBound.y);
    }
    return res;
}

}  // namespace Altseed
