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
    Vector2F position_;
    double rotation_;

public:
    PolygonCollider();

    // 頂点
    std::shared_ptr<Vector2FArray> GetVertexes() const;
    void SetVertexes(std::shared_ptr<Vector2FArray> vertexes);

    // 位置
    Vector2F GetPosition() const;
    void SetPosition(Vector2F position);

    // 回転
    double GetRotation() const;
    void SetRotation(double rotation);

    bool GetIsCollidedWith(std::shared_ptr<Collider> collider) override;
};
    
} // namespace Altseed