#include "Collider.h"

namespace Altseed {

Vector2F Collider::GetTranslation() const { return translation_; }
void Collider::SetTranslation(Vector2F translation) {
    translation_ = translation;
    b2Transform_.p = b2Vec2(translation.X, translation.Y);
}

double Collider::GetRotation() const { return rotation_; }
void Collider::SetRotation(double rotation) {
    rotation_ = rotation;
    b2Transform_.q = b2Rot(rotation);
}

} // namespace Altseed
