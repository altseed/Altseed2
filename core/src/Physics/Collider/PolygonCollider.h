#pragma once

#include "../../Common/Array.h"
#include "../../Math/Vector2F.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "RectangleCollider.h"

namespace Altseed2 {

class PolygonCollider : public Collider {
    friend class CircleCollider;
    friend class RectangleCollider;

private:
    std::vector<b2PolygonShape> triangles_;

    std::shared_ptr<Vector2FArray> vertexes_;

    bool GetIsCollidedWith_(std::shared_ptr<Collider> collider) override;

public:
    PolygonCollider();

    static std::shared_ptr<PolygonCollider> Create();

    // 頂点
    std::shared_ptr<Vector2FArray> GetVertexes() const;
    void SetVertexes(std::shared_ptr<Vector2FArray> vertexes);
};

}  // namespace Altseed2