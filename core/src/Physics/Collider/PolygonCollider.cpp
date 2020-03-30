#include "PolygonCollider.h"

namespace Altseed {

std::shared_ptr<Vector2FArray> PolygonCollider::GetVertexes() const { return vertexes_; }
void PolygonCollider::SetVertexes(std::shared_ptr<Vector2FArray> vertexes) {
    vertexes_ = vertexes;

    int triangleCount = vertexes->GetCount() - 2;
    triangles_.resize(triangleCount);
    for(int i = 0; i < triangleCount; ++i) {
        b2PolygonShape triangle;
        triangle.m_count = 3;
        triangle.m_vertices[0] = b2Vec2(vertexes->GetVector()[0].X, vertexes->GetVector()[0].Y);
        triangle.m_vertices[1] = b2Vec2(vertexes->GetVector()[i + 1].X, vertexes->GetVector()[i + 1].Y);
        triangle.m_vertices[2] = b2Vec2(vertexes->GetVector()[i + 2].X, vertexes->GetVector()[i + 2].Y);
        triangles_[i] = triangle;
    }
}

bool PolygonCollider::GetIsCollidedWith(std::shared_ptr<Collider> collider) {

    auto circle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if(circle != nullptr) {
        for(auto triangle : triangles_) {
            if(b2TestOverlap(&triangle, 0, &circle->shape_, 0, b2Transform_, circle->b2Transform_)) return true;
        }
        return false;
    }

    auto polygon = std::dynamic_pointer_cast<PolygonCollider>(collider);
    if(polygon != nullptr) {
        for(auto triangle1 : triangles_) {
            for(auto triangle2 : polygon->triangles_) {
                if(b2TestOverlap(&triangle1, 0, &triangle2, 0, b2Transform_, polygon->b2Transform_)) return true;
            }
        }
        return false;
    }

    return false;
}

} // namespace Altseed
