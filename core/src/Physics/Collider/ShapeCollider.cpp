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

bool ShapeCollider::GetIsCollidedWith_(std::shared_ptr<Collider> collider) {
    auto circle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if (circle != nullptr) {
        return b2TestOverlap(&shape_, 0, &circle->shape_, 0, transform_, circle->transform_);
    }

    auto shape = std::dynamic_pointer_cast<ShapeCollider>(collider);
    if (shape != nullptr) {
        return b2TestOverlap(&shape_, 0, &shape->shape_, 0, transform_, shape->transform_);
    }

    auto polygon = std::dynamic_pointer_cast<PolygonCollider>(collider);
    if (polygon != nullptr) {
        for (auto triangle : polygon->triangles_) {
            if (b2TestOverlap(&shape_, 0, &triangle, 0, transform_, polygon->transform_)) return true;
        }
        return false;
    }

    return false;
}

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
