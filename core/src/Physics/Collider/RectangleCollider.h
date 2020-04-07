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
    Vector2F center_;

    bool GetIsCollidedWith_(std::shared_ptr<Collider> shape) override;
    
public:
    RectangleCollider();

    // 大きさ
    Vector2F GetSize() const;
    void SetSize(Vector2F size);

    // 中心座標
    Vector2F GetCenterPosition() const;
    void SetCenterPosition(Vector2F center);
};
    
} // namespace Altseed