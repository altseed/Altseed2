#include "Collider.h"

#include "Box2DHelper.h"

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

bool Collider::GetIsCollidedWith(std::shared_ptr<Collider> collider) {
    auto selfShapes = GetB2Shapes();
    auto otherShapes = collider->GetB2Shapes();

    for (int i = 0; i < selfShapes.second; i++) {
        for (int j = 0; j < otherShapes.second; j++) {
            if (b2TestOverlap(selfShapes.first + i, 0, otherShapes.first + j, 0, transform_, collider->transform_)) {
                return true;
            }
        }
    }

    return false;
}

}  // namespace Altseed2
