#pragma once

#include "Collider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"
#include "../../Math/Vector2F.h"

namespace Altseed {

class RectangleCollider : public Collider {
    friend class CircleCollider;
    friend class PolygonCollider;

private:
    b2PolygonShape shape_;
    
    Vector2F size_;
    Vector2F position_;
    double rotation_;
    
public:
    RectangleCollider();

    // 大きさ
    Vector2F GetSize() const;
    void SetSize(Vector2F size);

    // 位置
    Vector2F GetPosition() const;
    void SetPosition(Vector2F position);

    // 回転
    double GetRotation() const;
    void SetRotation(double rotation);

    bool GetIsCollidedWith(std::shared_ptr<Collider> shape) override;
};
    
} // namespace Altseed