#include "EdgeCollider.h"

#include "Box2DHelper.h"

namespace Altseed2 {

EdgeCollider::EdgeCollider() {
    point1_ = Vector2F();
    point2_ = Vector2F();
    shape_.m_vertex1 = b2Vec2_zero;
    shape_.m_vertex2 = b2Vec2_zero;
    shapesBuffer_.emplace_back(&shape_);
}

std::shared_ptr<EdgeCollider> EdgeCollider::Create() { return MakeAsdShared<EdgeCollider>(); }

Vector2F EdgeCollider::GetPoint1() const { return point1_; }
void EdgeCollider::SetPoint1(const Vector2F& point) {
    point1_ = point;
    shape_.m_vertex1 = Box2DHelper::ToBox2D_Vec(point);
}

Vector2F EdgeCollider::GetPoint2() const { return point2_; }
void EdgeCollider::SetPoint2(const Vector2F& point) {
    point2_ = point;
    shape_.m_vertex2 = Box2DHelper::ToBox2D_Vec(point);
}

}  // namespace Altseed2