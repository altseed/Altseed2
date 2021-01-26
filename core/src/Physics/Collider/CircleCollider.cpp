#include "CircleCollider.h"

namespace Altseed2 {

CircleCollider::CircleCollider() {
    position_ = Vector2F(0, 0);
    radius_ = 0;

    shape_.m_p = b2Vec2_zero;
    shape_.m_radius = 0;
}

std::shared_ptr<CircleCollider> CircleCollider::Create() { return MakeAsdShared<CircleCollider>(); }

float CircleCollider::GetRadius() const { return radius_; }
void CircleCollider::SetRadius(float radius) {
    radius_ = radius;
    shape_.m_radius = radius;
}

}  // namespace Altseed2