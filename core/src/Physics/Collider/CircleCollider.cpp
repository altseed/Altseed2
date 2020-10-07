#include "CircleCollider.h"

namespace Altseed2 {

CircleCollider::CircleCollider() {
    position_ = Vector2F(0, 0);
    radius_ = 0;

    shape_.m_p = b2Vec2_zero;
    shape_.m_radius = 0;
}

std::shared_ptr<CircleCollider> CircleCollider::Create() { return MakeAsdShared<CircleCollider>(); }

double CircleCollider::GetRadius() const { return radius_; }
void CircleCollider::SetRadius(double radius) {
    radius_ = radius;
    shape_.m_radius = radius;
}

bool CircleCollider::GetIsCollidedWith_(std::shared_ptr<Collider> collider) {
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

}  // namespace Altseed2