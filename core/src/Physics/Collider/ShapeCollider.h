#pragma once

#include "../../Common/Array.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "EdgeCollider.h"
#include "PolygonCollider.h"

namespace Altseed2 {

class ShapeCollider : public Collider {
    friend class CircleCollider;
    friend class EdgeCollider;
    friend class PolygonCollider;

private:
    b2PolygonShape shape_;
    std::shared_ptr<Vector2FArray> vertexes_;

    bool GetIsCollidedWith_(std::shared_ptr<Collider> collider) override;

public:
    ShapeCollider();

    static std::shared_ptr<ShapeCollider> Create();

    std::shared_ptr<Vector2FArray> GetVertexes() const;
    void SetVertexes(const std::shared_ptr<Vector2FArray>& vertexes);
};

}  // namespace Altseed2