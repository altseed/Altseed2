#include "RectangleCollider.h"

namespace Altseed {
    
RectangleCollider::RectangleCollider() {
    size_ = Vector2F(0, 0);
    position_ = Vector2F(0, 0);
    rotation_ = 0;

    shape_.m_count = 4;
    shape_.m_vertices[0] = b2Vec2_zero;
    shape_.m_vertices[1] = b2Vec2_zero;
    shape_.m_vertices[2] = b2Vec2_zero;
    shape_.m_vertices[3] = b2Vec2_zero;
}

Vector2F RectangleCollider::GetSize() const { return size_; }
void RectangleCollider::SetSize(Vector2F size) {
    size_ = size;
    shape_.m_vertices[0] = b2Vec2(0, 0);
    shape_.m_vertices[1] = b2Vec2(size.X, 0);
    shape_.m_vertices[2] = b2Vec2(size.X, size.Y);
    shape_.m_vertices[3] = b2Vec2(0, size.Y);
}

Vector2F RectangleCollider::GetPosition() const { return position_; }
void RectangleCollider::SetPosition(Vector2F position) {
    position_ = position;
    transform_.p = b2Vec2(position.X, position.Y);
    transformMatrix_ = transformMatrix_.SetTranslation(position.X, position.Y, 0);
}

double RectangleCollider::GetRotation() const { return rotation_; }
void RectangleCollider::SetRotation(double rotation) {
    rotation_ = rotation;
    transform_.q = b2Rot(rotation);
    transformMatrix_ = transformMatrix_.SetRotationZ(rotation);
}

bool RectangleCollider::GetIsCollidedWith(std::shared_ptr<Collider> collider) {
    
    auto circle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if(circle != nullptr) {
        return b2TestOverlap(&shape_, 0, &circle->shape_, 0, transform_, circle->transform_);
    }

    auto rectangle = std::dynamic_pointer_cast<RectangleCollider>(collider);
    if(rectangle != nullptr) {
        return b2TestOverlap(&shape_, 0, &rectangle->shape_, 0, transform_, rectangle->transform_);
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
