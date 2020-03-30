#pragma once

#include "Collider.h"
#include "CircleCollider.h"
#include "../../Common/Array.h"
#include "../../Math/Vector2F.h"

namespace Altseed {

class PolygonCollider : public Collider {
    friend class CircleCollider;

private:
    std::vector<b2PolygonShape> triangles_;
    
    std::shared_ptr<Vector2FArray> vertexes_;

public:
    std::shared_ptr<Vector2FArray> GetVertexes() const;
    void SetVertexes(std::shared_ptr<Vector2FArray> vertexes);

    bool GetIsCollidedWith(std::shared_ptr<Collider> collider) override;
};
    
} // namespace Altseed