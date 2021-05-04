#include "Collider.h"

#include "Box2DHelper.h"

#include "../../Logger/Log.h"

namespace Altseed2 {

Collider::Collider() {
    transform_.SetIdentity();
    transformMatrix_.SetIdentity();
}

Vector2F Collider::GetPosition() const { return position_; }
void Collider::SetPosition(Vector2F position) {
    position_ = position;
    transform_.p = b2Vec2(position.X, position.Y);
    Matrix44F t, r;
    t.SetTranslation(position.X, position.Y, 1);
    r.SetRotationZ(rotation_);
    transformMatrix_ = t * r;
}

float Collider::GetRotation() const { return rotation_; }
void Collider::SetRotation(float rotation) {
    rotation_ = rotation;
    transform_.q = b2Rot(rotation);
    Matrix44F t, r;
    t.SetTranslation(position_.X, position_.Y, 1);
    r.SetRotationZ(rotation);
    transformMatrix_ = t * r;
}

Matrix44F Collider::GetTransform() const { return transformMatrix_; }
void Collider::SetTransform(const Matrix44F& transform) {
    Box2DHelper::SetMat(transform_, transform);
    transformMatrix_ = transform;
    double r;
    Vector2F p, s;
    Matrix44F::CalcFromTransform2D(transform, r, p, s);
    position_ = p;
    rotation_ = r;
}

bool Collider::GetIsCollidedWith(const std::shared_ptr<Collider>& collider) {
    RETURN_IF_NULL(collider, false);
    auto selfShapes = GetB2Shapes();
    auto otherShapes = collider->GetB2Shapes();

    for (auto s1 : selfShapes) {
        for (auto s2 : otherShapes) {
            if (b2TestOverlap(s1, 0, s2, 0, transform_, collider->transform_)) {
                return true;
            }
        }
    }

    return false;
}

}  // namespace Altseed2
