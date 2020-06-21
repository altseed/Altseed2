#include "RectangleCollider.h"

namespace Altseed2 {

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
    shape_.m_vertices[0] = b2Vec2(0 - center_.X, 0 - center_.Y);
    shape_.m_vertices[1] = b2Vec2(size_.X - center_.X, 0 - center_.Y);
    shape_.m_vertices[2] = b2Vec2(size_.X - center_.X, size_.Y - center_.Y);
    shape_.m_vertices[3] = b2Vec2(0 - center_.X, size_.Y - center_.Y);
}

Vector2F RectangleCollider::GetCenterPosition() const { return center_; }
void RectangleCollider::SetCenterPosition(Vector2F center) {
    center_ = center;
    shape_.m_vertices[0] = b2Vec2(0 - center_.X, 0 - center_.Y);
    shape_.m_vertices[1] = b2Vec2(size_.X - center_.X, 0 - center_.Y);
    shape_.m_vertices[2] = b2Vec2(size_.X - center_.X, size_.Y - center_.Y);
    shape_.m_vertices[3] = b2Vec2(0 - center_.X, size_.Y - center_.Y);
}

bool RectangleCollider::GetIsCollidedWith_(std::shared_ptr<Collider> collider) {
    auto circle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if (circle != nullptr) {
        return b2TestOverlap(&shape_, 0, &circle->shape_, 0, transform_, circle->transform_);
    }

    auto rectangle = std::dynamic_pointer_cast<RectangleCollider>(collider);
    if (rectangle != nullptr) {
        return b2TestOverlap(&shape_, 0, &rectangle->shape_, 0, transform_, rectangle->transform_);
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
