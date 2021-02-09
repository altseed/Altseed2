#pragma once

#include "../../Common/Array.h"
#include "../../Math/Vector2F.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "EdgeCollider.h"
#include "ShapeCollider.h"

namespace Altseed2 {

class PolygonCollider : public Collider {
private:
    std::shared_ptr<Int32Array> buffers_;

    std::vector<b2PolygonShape> triangles_;

    std::shared_ptr<Vector2FArray> vertexes_;

    void UpdateTriangles();

    bool updatedTriangles_;

protected:
    const std::vector<const b2Shape*>& GetB2Shapes() override {
        if (updatedTriangles_)
        {
            shapesBuffer_.clear();
            for (int i = 0; i < triangles_.size(); i++) {
                shapesBuffer_.emplace_back(&triangles_[i]);
            }
            updatedTriangles_ = false;
        }
        return shapesBuffer_;
    }

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