#include "RenderedPolygon.h"

namespace Altseed {

std::shared_ptr<RenderedPolygon> RenderedPolygon::Create() { return MakeAsdShared<RenderedPolygon>(); }

std::shared_ptr<VertexArray> RenderedPolygon::GetVertexes() { return vertexes_; }

void RenderedPolygon::SetVertexes(std::shared_ptr<VertexArray> vertexes) { vertexes_ = vertexes; }

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

    // ���_���W���R�s�[
    for (int i = 0; i < vertexes->GetCount(); ++i) {
        auto& dst = vertexes_->GetVector()[i].Pos;
        auto& src = vertexes->GetVector()[i];

        dst.X = src.X;
        dst.Y = src.Y;
        dst.Z = 0.5f;

        // ���_�̑��ݔ͈�
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

    // UV, �F�𐶐�
    for (int i = 0; i < vertexes->GetCount(); ++i) {
        auto& dst = vertexes_->GetVector()[i];
        dst.UV1.X = (dst.Pos.X - xMin) / (xMax - xMin);
        dst.UV1.Y = (dst.Pos.Y - yMin) / (yMax - yMin);
        dst.UV2 = dst.UV1;
        dst.Col = Color(255, 255, 255, 255);
    }
}

RectF RenderedPolygon::GetSrc() const { return src_; }

void RenderedPolygon::SetSrc(const RectF& src) { src_ = src; }

std::shared_ptr<TextureBase> RenderedPolygon::GetTexture() const { return texture_; }

void RenderedPolygon::SetTexture(const std::shared_ptr<TextureBase>& texture) { texture_ = texture; }

std::shared_ptr<Material> RenderedPolygon::GetMaterial() const { return material_; }

void RenderedPolygon::SetMaterial(const std::shared_ptr<Material>& material) { material_ = material; }

}  // namespace Altseed
