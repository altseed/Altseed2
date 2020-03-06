#include "RenderedPolygon.h"

namespace Altseed {

static std::shared_ptr<RenderedPolygon> Create() { return MakeAsdShared<RenderedPolygon>(); }

std::shared_ptr<VertexArray>& RenderedPolygon::GetVertexes() { return vertexes_; }

void RenderedPolygon::SetVertexes(std::shared_ptr<VertexArray> vertexes) { vertexes_ = vertexes; }

void RenderedPolygon::SetVertexesByVector2F(std::shared_ptr<Vector2FArray> vertexes) {
    vertexes_->Resize(vertexes->GetCount());

    float xMin = vertexes->GetVector()[0].X;
    float xMax = vertexes->GetVector()[0].X;
    float yMin = vertexes->GetVector()[0].Y;
    float yMax = vertexes->GetVector()[0].Y;

    for(int i = 0; i < vertexes->GetCount(); ++i) {
        vertexes_->GetVector()[i].Pos.X = vertexes->GetVector()[i].X;
        vertexes_->GetVector()[i].Pos.Y = vertexes->GetVector()[i].Y;
        vertexes_->GetVector()[i].Pos.Z = 0.5f;

        if(vertexes->GetVector()[i].X < xMin) { xMin = vertexes->GetVector()[i].X; }
        if(vertexes->GetVector()[i].X > xMax) { xMax = vertexes->GetVector()[i].X; }
        if(vertexes->GetVector()[i].Y < yMin) { yMin = vertexes->GetVector()[i].X; }
        if(vertexes->GetVector()[i].Y > yMax) { yMax = vertexes->GetVector()[i].X; }
    }

    for(int i = 0; i < vertexes->GetCount(); ++i) {
        vertexes_->GetVector()[i].UV1.X = (vertexes_->GetVector()[i].Pos.X - xMin) / (xMax - xMin);
        vertexes_->GetVector()[i].UV1.Y = (vertexes_->GetVector()[i].Pos.Y - yMin) / (yMax - yMin);
        vertexes_->GetVector()[i].UV1 = vertexes_->GetAt(i).UV2;
        vertexes_->GetVector()[i].Col = Color(255, 255, 255, 255);
        vertexes_->GetVector()[i].Pos = GetTransform().Transform3D(vertexes_->GetAt(i).Pos);
    }
}

RectF RenderedPolygon::GetSrc() const { return src_; }

void RenderedPolygon::SetSrc(const RectF& src) { src_ = src; }

std::shared_ptr<Texture2D> RenderedPolygon::GetTexture() const { return texture_; }

void RenderedPolygon::SetTexture(const std::shared_ptr<Texture2D>& texture) { texture_ = texture; }

std::shared_ptr<Material> RenderedPolygon::GetMaterial() const { return material_; }

void RenderedPolygon::SetMaterial(const std::shared_ptr<Material>& material) { material_ = material; }

} // namespace Altseed
