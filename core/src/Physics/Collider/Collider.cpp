#include "Collider.h"

namespace Altseed {

Collider::Collider() {
    transform_.SetIdentity();
    transformMatrix_.SetIdentity();
}

bool Collider::GetIsCollided(std::shared_ptr<Collider> shape) { throw "Not Implemented"; }

Vector2F Collider::GetPosition() const { return position_; }
void Collider::SetPosition(Vector2F position) {
    position_ = position;
    transform_.p = b2Vec2(position.X, position.Y);
    transformMatrix_ = transformMatrix_.SetTranslation(position.X, position.Y, 0);
}

double Collider::GetRotation() const { return rotation_; }
void Collider::SetRotation(double rotation) {
    rotation_ = rotation;
    transform_.q = b2Rot(rotation);
    transformMatrix_ = transformMatrix_.SetRotationZ(rotation);
}

Matrix44F Collider::GetTransform() { return transformMatrix_; }

} // namespace Altseed
