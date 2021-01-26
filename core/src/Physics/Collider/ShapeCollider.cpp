#include "ShapeCollider.h"

#include "../../Logger/Log.h"
#include "Box2DHelper.h"

namespace Altseed2 {

ShapeCollider::ShapeCollider() {
    position_ = Vector2F(0, 0);
    rotation_ = 0;
    vertexes_ = Vector2FArray::Create(0);

    shape_.m_count = 0;
}

std::shared_ptr<ShapeCollider> ShapeCollider::Create() { return MakeAsdShared<ShapeCollider>(); }

std::shared_ptr<Vector2FArray> ShapeCollider::GetVertexes() const { return vertexes_; }
void ShapeCollider::SetVertexes(const std::shared_ptr<Vector2FArray>& vertexes) {
    if (vertexes->GetVector().size() > b2_maxPolygonVertices) {
        Log::GetInstance()->Error(LogCategory::Core, u"頂点数は8つまでです");
        return;
    }
    vertexes_ = vertexes;
    shape_.m_count = vertexes->GetVector().size();
    for (int i = 0; i < vertexes->GetVector().size(); i++) shape_.m_vertices[i] = Box2DHelper::ToBox2D_Vec(vertexes_->GetVector()[i]);
}

}  // namespace Altseed2
