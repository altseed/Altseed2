#pragma once

#include "../../Math/Vector2F.h"
#include "Collider.h"
#include "EdgeCollider.h"
#include "PolygonCollider.h"
#include "ShapeCollider.h"

namespace Altseed2 {

class CircleCollider : public Collider {
    friend class EdgeCollider;
    friend class PolygonCollider;
    friend class ShapeCollider;

private:
    b2CircleShape shape_;

    float radius_;

    bool GetIsCollidedWith_(std::shared_ptr<Collider> shape) override;

public:
    CircleCollider();

    static std::shared_ptr<CircleCollider> Create();

    // 半径
    float GetRadius() const;
    void SetRadius(float radius);
};

}  // namespace Altseed2
