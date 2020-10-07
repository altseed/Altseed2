#include "EdgeCollider.h"

#include "Box2DHelper.h"

namespace Altseed2 {

EdgeCollider::EdgeCollider() {
    point1_ = Vector2F();
    point2_ = Vector2F();
    shape_.m_vertex1 = b2Vec2_zero;
    shape_.m_vertex2 = b2Vec2_zero;
}

std::shared_ptr<EdgeCollider> EdgeCollider::Create() { return MakeAsdShared<EdgeCollider>(); }

Vector2F EdgeCollider::GetPoint1() const { return point1_; }
void EdgeCollider::SetPoint1(const Vector2F& point) {
    point1_ = point;
    shape_.m_vertex1 = Box2DHelper::ToBox2D_Vec(point);
}

Vector2F EdgeCollider::GetPoint2() const { return point2_; }
void EdgeCollider::SetPoint2(const Vector2F& point) {
    point2_ = point;
    shape_.m_vertex2 = Box2DHelper::ToBox2D_Vec(point);
}

bool EdgeCollider::GetIsCollidedWith_(std::shared_ptr<Collider> collider) {
    auto circle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if (circle != nullptr) {
        return b2TestOverlap(&shape_, 0, &circle->shape_, 0, transform_, circle->transform_);
    }

    auto edge = std::dynamic_pointer_cast<EdgeCollider>(collider);
    if (edge != nullptr) {
        return b2TestOverlap(&shape_, 0, &edge->shape_, 0, transform_, edge->transform_);
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

}  // namespace Altseed2