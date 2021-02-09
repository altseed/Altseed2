#pragma once

#include "../../Math/Vector2F.h"
#include "Collider.h"
#include "EdgeCollider.h"
#include "PolygonCollider.h"
#include "ShapeCollider.h"

namespace Altseed2 {

class CircleCollider : public Collider {
private:
    b2CircleShape shape_;
    float radius_;

protected:
    const std::vector<const b2Shape*>& GetB2Shapes() override {
        return shapesBuffer_;
    }

public:
    CircleCollider();

    static std::shared_ptr<CircleCollider> Create();

    // 半径
    float GetRadius() const;
    void SetRadius(float radius);
};

}  // namespace Altseed2
