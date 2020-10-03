#include "PolygonCollider.h"

#include "Box2DHelper.h"

namespace Altseed2 {

PolygonCollider::PolygonCollider() {
    buffers_ = Int32Array::Create(0);
    vertexes_ = Vector2FArray::Create(0);
    position_ = Vector2F(0, 0);
    rotation_ = 0;
}

std::shared_ptr<PolygonCollider> PolygonCollider::Create() { return MakeAsdShared<PolygonCollider>(); }

std::shared_ptr<Int32Array> PolygonCollider::GetBuffers() const { return buffers_; }
void PolygonCollider::SetBuffers(const std::shared_ptr<Int32Array> buffers) {
    buffers_ = buffers;
    UpdateTriangles();
}

std::shared_ptr<Vector2FArray> PolygonCollider::GetVertexes() const { return vertexes_; }
void PolygonCollider::SetVertexes(std::shared_ptr<Vector2FArray> vertexes) {
    vertexes_ = vertexes;
    UpdateTriangles();
}

bool PolygonCollider::GetIsCollidedWith_(std::shared_ptr<Collider> collider) {
    auto circle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if (circle != nullptr) {
        for (auto triangle : triangles_) {
            if (b2TestOverlap(&triangle, 0, &circle->shape_, 0, transform_, circle->transform_)) return true;
        }
        return false;
    }

    auto rectangle = std::dynamic_pointer_cast<CircleCollider>(collider);
    if (rectangle != nullptr) {
        for (auto triangle : triangles_) {
            if (b2TestOverlap(&triangle, 0, &rectangle->shape_, 0, transform_, rectangle->transform_)) return true;
        }
        return false;
    }

    auto polygon = std::dynamic_pointer_cast<PolygonCollider>(collider);
    if (polygon != nullptr) {
        for (auto triangle1 : triangles_) {
            for (auto triangle2 : polygon->triangles_) {
                if (b2TestOverlap(&triangle1, 0, &triangle2, 0, transform_, polygon->transform_)) return true;
            }
        }
        return false;
    }

    return false;
}

void PolygonCollider::SetDefaultIndexBuffer() {
    auto vs = vertexes_->GetVector();
    if (vs.size() < 3) {
        buffers_->GetVector().resize(0);
        return;
    }
    auto length = vs.size() - 2;
    buffers_->GetVector().resize(length * 3);
    triangles_.resize(length);

    for (int i = 0; i < length; i++) {
        buffers_->GetVector()[i * 3] = 0;
        buffers_->GetVector()[i * 3 + 1] = i + 1;
        buffers_->GetVector()[i * 3 + 2] = i + 2;

        b2PolygonShape triangle;
        triangle.m_count = 3;
        triangle.m_vertices[0] = Box2DHelper::ToBox2D_Vec(vertexes_->GetVector()[0]);
        triangle.m_vertices[1] = Box2DHelper::ToBox2D_Vec(vertexes_->GetVector()[i + 1]);
        triangle.m_vertices[2] = Box2DHelper::ToBox2D_Vec(vertexes_->GetVector()[i + 2]);
        triangles_[i] = triangle;
    }
}

void PolygonCollider::UpdateTriangles() {
    auto buffers = buffers_->GetVector();
    auto count = buffers.size() / 3;
    auto vertexesSize = vertexes_->GetVector().size();

    triangles_.resize(count);
    auto skipCount = 0;
    for (int i = 0; i < count; i++) {
        auto ib1 = buffers[i * 3];
        auto ib2 = buffers[i * 3 + 1];
        auto ib3 = buffers[i * 3 + 2];
        if (ib1 >= vertexesSize || ib2 >= vertexesSize || ib3 >= vertexesSize) continue;
        b2PolygonShape triangle;
        triangle.m_count = 3;
        triangle.m_vertices[0] = Box2DHelper::ToBox2D_Vec(vertexes_->GetVector()[ib1]);
        triangle.m_vertices[1] = Box2DHelper::ToBox2D_Vec(vertexes_->GetVector()[ib2]);
        triangle.m_vertices[2] = Box2DHelper::ToBox2D_Vec(vertexes_->GetVector()[ib3]);
        triangles_[i] = triangle;
    }
}

}  // namespace Altseed2
