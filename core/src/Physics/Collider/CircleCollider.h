#pragma once

#include "../../Math/Vector2F.h"
#include "Collider.h"
#include "PolygonCollider.h"
#include "RectangleCollider.h"

namespace Altseed {

class CircleCollider : public Collider {
    friend class RectangleCollider;
    friend class PolygonCollider;

private:
    b2CircleShape shape_;

    double radius_;

    bool GetIsCollidedWith_(std::shared_ptr<Collider> shape) override;

public:
    CircleCollider();

    // 半径
    double GetRadius() const;
    void SetRadius(double radius);
};

}  // namespace Altseed
