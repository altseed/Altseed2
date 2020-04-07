#pragma once

#include "Collider.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "../../Common/Array.h"
#include "../../Math/Vector2F.h"

namespace Altseed {

class PolygonCollider : public Collider {
    friend class CircleCollider;
    friend class RectangleCollider;

private:
    std::vector<b2PolygonShape> triangles_;
    
    std::shared_ptr<Vector2FArray> vertexes_;

    bool GetIsCollidedWith_(std::shared_ptr<Collider> collider) override;

public:
    PolygonCollider();

    // 頂点
    std::shared_ptr<Vector2FArray> GetVertexes() const;
    void SetVertexes(std::shared_ptr<Vector2FArray> vertexes);
};
    
} // namespace Altseed