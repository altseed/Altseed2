#pragma once

#include "../../Math/Vector2F.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "PolygonCollider.h"
#include "ShapeCollider.h"

namespace Altseed2 {

class EdgeCollider : public Collider {
private:
    b2EdgeShape shape_;
    Vector2F point1_;
    Vector2F point2_;

protected:
    std::pair<b2Shape*, int32_t> GetB2Shapes() override { return {&shape_, 1}; }

public:
    EdgeCollider();

    Vector2F GetPoint1() const;
    void SetPoint1(const Vector2F& point);

    Vector2F GetPoint2() const;
    void SetPoint2(const Vector2F& point);

    static std::shared_ptr<EdgeCollider> Create();
};

}  // namespace Altseed2
