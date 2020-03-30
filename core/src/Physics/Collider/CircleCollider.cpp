#include "CircleCollider.h"

namespace Altseed {

CircleCollider::CircleCollider() {
    shape_.m_p = b2Vec2_zero;
    shape_.m_radius = 0;
}

std::shared_ptr<CircleCollider> CircleCollider::Create() { return MakeAsdShared<CircleCollider>(); }

Vector2F CircleCollider::GetPosition() const { return position_; }
void CircleCollider::SetPosition(Vector2F position) {
    position_ = position;
    transform_.p = b2Vec2(position.X, position.Y);
    transformMatrix_ = transformMatrix_.SetTranslation(position.X, position.Y, 0);
}

double CircleCollider::GetRadius() const { return radius_; }
void CircleCollider::SetRadius(double radius) {
    radius_ = radius;
    shape_.m_radius = radius;
}

bool CircleCollider::GetIsCollidedWith(std::shared_ptr<Collider> collider) {
    
    auto circle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if(circle != nullptr) {
        return b2TestOverlap(&shape_, 0, &circle->shape_, 0, transform_, circle->transform_);
    }

    auto polygon = std::dynamic_pointer_cast<PolygonCollider>(collider);
    if(polygon != nullptr) {
        for(auto triangle : polygon->triangles_) {
            if(b2TestOverlap(&shape_, 0, &triangle, 0, transform_, polygon->transform_)) return true;
        }
        return false;
    }

    return false;
}

} // namespace Altseed