#pragma once

#include "../../Common/Array.h"
#include "../../Math/Vector2F.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "ShapeCollider.h"

namespace Altseed2 {

class PolygonCollider : public Collider {
    friend class CircleCollider;
    friend class ShapeCollider;

private:
    std::shared_ptr<Int32Array> buffers_;

    std::vector<b2PolygonShape> triangles_;

    std::shared_ptr<Vector2FArray> vertexes_;

    bool GetIsCollidedWith_(std::shared_ptr<Collider> collider) override;

    void UpdateTriangles();

public:
    PolygonCollider();

    static std::shared_ptr<PolygonCollider> Create();

    // IB
    std::shared_ptr<Int32Array> GetBuffers() const;
    void SetBuffers(const std::shared_ptr<Int32Array> buffers);

    // 頂点
    std::shared_ptr<Vector2FArray> GetVertexes() const;
    void SetVertexes(std::shared_ptr<Vector2FArray> vertexes);

    void SetDefaultIndexBuffer();
};

}  // namespace Altseed2