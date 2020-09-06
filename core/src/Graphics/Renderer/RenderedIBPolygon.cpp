#include "RenderedIBPolygon.h"

#include "../Material.h"
#include "CullingSystem.h"

namespace Altseed2 {

std::shared_ptr<RenderedIBPolygon> RenderedIBPolygon::Create() {
    auto result = MakeAsdShared<RenderedIBPolygon>();
    result->SetAlphaBlend(AlphaBlend::Normal());
    result->SetBuffers(Int32Array::Create(0));
    result->SetMaterial(nullptr);
    result->SetTexture(nullptr);
    result->SetVertexes(VertexArray::Create(0));
    return result;
}

AlphaBlend RenderedIBPolygon::GetAlphaBlend() const { return alphaBlend_; }
void RenderedIBPolygon::SetAlphaBlend(const AlphaBlend& value) { alphaBlend_ = value; }

std::shared_ptr<Int32Array> RenderedIBPolygon::GetBuffers() const { return buffers_; }
void RenderedIBPolygon::SetBuffers(const std::shared_ptr<Int32Array> value) { buffers_ = value == nullptr ? Int32Array::Create(0) : value; }

void RenderedIBPolygon::CreateVertexesByVector2F(const std::shared_ptr<Vector2FArray> vectors) {
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

std::shared_ptr<Material> RenderedIBPolygon::GetMaterial() const { return material_; }
void RenderedIBPolygon::SetMaterial(const std::shared_ptr<Material>& value) { material_ = value; }

void RenderedIBPolygon::OverwriteVertexesColor(const Color& color) {
    for (auto&& vertex : vertexes_->GetVector()) {
        vertex.Col = color;
    }
}

RectF RenderedIBPolygon::GetSrc() const { return src_; }
void RenderedIBPolygon::SetSrc(const RectF& value) { src_ = value; }

std::shared_ptr<TextureBase> RenderedIBPolygon::GetTexture() const { return texture_; }
void RenderedIBPolygon::SetTexture(const std::shared_ptr<TextureBase>& value) { texture_ = value; }

std::shared_ptr<VertexArray> RenderedIBPolygon::GetVertexes() const { return vertexes_; }
void RenderedIBPolygon::SetVertexes(const std::shared_ptr<VertexArray> value) {
    vertexes_ = value == nullptr ? VertexArray::Create(0) : value;
    cullingSystem_->RequestUpdateAABB(this);
}

b2AABB RenderedIBPolygon::GetAABB() {
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

void RenderedIBPolygon::SetDefaultIndexBuffer() {
    auto vs = vertexes_->GetVector();
    auto bs = buffers_->GetVector();
    if (vs.size() < 3) {
        bs.resize(0);
        return;
    }
    auto length = vs.size() - 2;
    bs.resize(length * 3);
    for (int i = 0; i < length; i++) {
        bs[i * 3] = 0;
        bs[i * 3 + 1] = i + 1;
        bs[i * 3 + 2] = i + 2;
    }
}

}  // namespace Altseed2
