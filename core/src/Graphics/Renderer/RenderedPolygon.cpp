#include "RenderedPolygon.h"

#include "../Material.h"
#include "CullingSystem.h"

namespace Altseed2 {

std::shared_ptr<RenderedPolygon> RenderedPolygon::Create() {
    auto p = MakeAsdShared<RenderedPolygon>();
    p->SetAlphaBlend(AlphaBlend::Normal());
    p->SetBuffers(Int32Array::Create(0));
    p->SetVertexes(VertexArray::Create(0));
    p->SetTexture(nullptr);
    p->SetMaterial(nullptr);
    return p;
}

std::shared_ptr<VertexArray> RenderedPolygon::GetVertexes() { return vertexes_; }

void RenderedPolygon::SetVertexes(std::shared_ptr<VertexArray> vertexes) {
    vertexes_ = vertexes;
    cullingSystem_->RequestUpdateAABB(this);
}

void RenderedPolygon::CreateVertexesByVector2F(std::shared_ptr<Vector2FArray> vectors) {
    if (vertexes_ == nullptr) {
        vertexes_ = VertexArray::Create(vectors->GetCount());
    } else {
        vertexes_->Clear();
        vertexes_->Resize(vectors->GetCount());
    }

    float xMin, xMax, yMin, yMax;
    {
        auto& v = vectors->GetVector()[0];
        xMin = v.X;
        xMax = v.X;
        yMin = v.Y;
        yMax = v.Y;
    }

    auto count = vertexes_->GetCount();
    for (int32_t i = 0; i < count; i++) {
        auto& v = vectors->GetVector()[i];
        auto& vertex = vertexes_->GetVector()[i];

        vertex.Pos = Vector3F(v.X, v.Y, 0.5f);

        if (v.X < xMin) {
            xMin = v.X;
        }
        if (v.X > xMax) {
            xMax = v.X;
        }
        if (v.Y < yMin) {
            yMin = v.Y;
        }
        if (v.Y > yMax) {
            yMax = v.Y;
        }
    }

    // UVを設定
    for (auto&& v : vertexes_->GetVector()) {
        v.UV1.X = (v.Pos.X - xMin) / (xMax - xMin);
        v.UV1.Y = (v.Pos.Y - yMin) / (yMax - yMin);
        v.UV2 = Vector2F();
    }

    cullingSystem_->RequestUpdateAABB(this);
}

void RenderedPolygon::OverwriteVertexesColor(Color color) {
    for (auto&& v : vertexes_->GetVector()) {
        v.Col = color;
    }
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

void RenderedPolygon::SetDefaultIndexBuffer() {
    auto vs = vertexes_->GetVector();
    if (vs.size() < 3) {
        buffers_->GetVector().resize(0);
        return;
    }
    auto length = vs.size() - 2;
    buffers_->GetVector().resize(length * 3);
    for (int i = 0; i < length; i++) {
        buffers_->GetVector()[i * 3] = 0;
        buffers_->GetVector()[i * 3 + 1] = i + 1;
        buffers_->GetVector()[i * 3 + 2] = i + 2;
    }
}

}  // namespace Altseed2
