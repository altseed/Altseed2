#pragma once

#include "Collider.h"
#include "PolygonCollider.h"
#include "../../Math/Vector2F.h"

namespace Altseed {

class CircleCollider : public Collider {
    friend class PolygonCollider;

private:
    b2CircleShape shape_;

    Vector2F position_;
    double radius_;

public:
    CircleCollider();

    static std::shared_ptr<CircleCollider> Create();

    // 半径
    double GetRadius() const;
    void SetRadius(double radius);

    // 位置
    Vector2F GetPosition() const;
    void SetPosition(Vector2F position);

    bool GetIsCollidedWith(std::shared_ptr<Collider> shape) override;
};
    
} // namespace Altseed
