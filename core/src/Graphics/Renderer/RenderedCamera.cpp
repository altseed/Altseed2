#include "RenderedCamera.h"

#include "../../Common/Array.h"
#include "../../Window/Window.h"
#include "../Graphics.h"
#include "../RenderTexture.h"
#include "../../Logger/Log.h"

namespace Altseed2 {

RenderedCamera::RenderedCamera() {
    matView_.SetIdentity();
    SetTargetTexture(nullptr);
}

std::shared_ptr<RenderedCamera> RenderedCamera::Create() { return MakeAsdShared<RenderedCamera>(); }

std::shared_ptr<RenderTexture> RenderedCamera::GetTargetTexture() { return targetTexture_; }
void RenderedCamera::SetTargetTexture(const std::shared_ptr<RenderTexture>& targetTexture) {
    targetTexture_ = targetTexture;

    Vector2I windowSize;
    if (targetTexture_ != nullptr) {
        windowSize = targetTexture_->GetSize();
    } else {
        windowSize = Window::GetInstance()->GetSize();
    }

    matProjection_.SetIdentity();
    matProjection_.Values[0][0] = 2.0f / windowSize.X;
    matProjection_.Values[1][1] = -2.0f / windowSize.Y;
    matProjection_.Values[0][3] = 0.0f;
    matProjection_.Values[1][3] = 0.0f;
}

RenderPassParameter RenderedCamera::GetRenderPassParameter() const { return renderPassParameter_; }
void RenderedCamera::SetRenderPassParameter(const RenderPassParameter renderPassParameter) { renderPassParameter_ = renderPassParameter; }

Matrix44F RenderedCamera::GetProjectionMatrix() const {
    return matProjection_;
}

Matrix44F RenderedCamera::GetViewMatrix() const {
    return matView_;
}

void RenderedCamera::SetViewMatrix(Matrix44F matrix) {
    matView_ = matrix;
}

b2AABB RenderedCamera::GetAABB() {
    b2AABB res;
    Vector2I windowSize;

    if (targetTexture_ != nullptr) {
        windowSize = targetTexture_->GetSize();
    } else {
        windowSize = Window::GetInstance()->GetSize();
    }

    auto vertexes = std::array<Vector3F, 4>();
    vertexes[0] = Vector3F(0, 0, 0);
    vertexes[1] = Vector3F(windowSize.X, 0, 0);
    vertexes[2] = Vector3F(windowSize.X, windowSize.Y, 0);
    vertexes[3] = Vector3F(0, windowSize.Y, 0);

    res.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
    res.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
    for (auto&& _v : vertexes) {
        auto v = matView_.Transform3D(_v);
        res.lowerBound = b2Vec2(res.lowerBound.x > v.X ? v.X : res.lowerBound.x, res.lowerBound.y > v.Y ? v.Y : res.lowerBound.y);
        res.upperBound = b2Vec2(res.upperBound.x < v.X ? v.X : res.upperBound.x, res.upperBound.y < v.Y ? v.Y : res.upperBound.y);
    }

    Log::GetInstance()->Info(LogCategory::Core, u" '{0}, {1}, {2}, {3}'", res.upperBound.x, res.upperBound.y, res.lowerBound.x, res.lowerBound.y);
    return res;
}

}  // namespace Altseed2