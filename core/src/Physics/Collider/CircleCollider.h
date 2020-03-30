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
    Vector2F GetPosition() const;
    void SetPositoin(Vector2F position);

    double GetRadius() const;
    void SetRadius(double radius);

    bool GetIsCollidedWith(std::shared_ptr<Collider> shape) override;
};
    
} // namespace Altseed
