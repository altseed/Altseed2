#include "CircleCollider.h"

namespace Altseed {

Vector2F CircleCollider::GetPosition() const { return position_; }
void CircleCollider::SetPositoin(Vector2F position) {
    position_ = position;
    shape_.m_p = b2Vec2(position.X, position.Y);
}

double CircleCollider::GetRadius() const { return radius_; }
void CircleCollider::SetRadius(double radius) {
    radius_ = radius;
    shape_.m_radius = radius;
}

bool CircleCollider::GetIsCollidedWith(std::shared_ptr<Collider> collider) {
    
    auto circle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if(circle != nullptr) {
        return b2TestOverlap(&shape_, 0, &circle->shape_, 0, b2Transform_, circle->b2Transform_);
    }

    auto polygon = std::dynamic_pointer_cast<PolygonCollider>(collider);
    if(polygon != nullptr) {
        for(auto triangle : polygon->triangles_) {
            if(b2TestOverlap(&shape_, 0, &triangle, 0, b2Transform_, polygon->b2Transform_)) return true;
        }
        return false;
    }

    return false;
}

} // namespace Altseed