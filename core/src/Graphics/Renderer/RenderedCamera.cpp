#include "RenderedCamera.h"

#include "../../Common/Array.h"
#include "../../Window/Window.h"
#include "../Graphics.h"
#include "../RenderTexture.h"

namespace Altseed {

std::shared_ptr<RenderedCamera> RenderedCamera::Create() { return MakeAsdShared<RenderedCamera>(); }

Vector2F RenderedCamera::GetCenterOffset() const { return centerOffset_; }
void RenderedCamera::SetCenterOffset(const Vector2F& centerOffset) { centerOffset_ = centerOffset; }

std::shared_ptr<RenderTexture> RenderedCamera::GetTargetTexture() { return targetTexture_; }
void RenderedCamera::SetTargetTexture(const std::shared_ptr<RenderTexture>& targetTexture) { targetTexture_ = targetTexture; }

Matrix44F RenderedCamera::GetProjectionMatrix() const {
    Matrix44F matProjection;
    Vector2I windowSize;

    if (targetTexture_ != nullptr) {
        windowSize = targetTexture_->GetSize();
    } else {
        windowSize = Window::GetInstance()->GetSize();
    }

    matProjection.SetIdentity();
    matProjection.Values[0][0] = 2.0f / windowSize.X;
    matProjection.Values[1][1] = -2.0f / windowSize.Y;
    matProjection.Values[0][3] = 0.0f;
    matProjection.Values[1][3] = 0.0f;

    return matProjection;
}

Matrix44F RenderedCamera::GetCameraMatrix() const {
    Vector2I windowSize;

    if (targetTexture_ != nullptr) {
        windowSize = targetTexture_->GetSize();
    } else {
        windowSize = Window::GetInstance()->GetSize();
    }

    Matrix44F t;
    t.SetTranslation(windowSize.X / 2.0f + centerOffset_.X, windowSize.Y / 2.0f + centerOffset_.Y, 0.0f);
    return (t * transform_).GetInverted();
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
        auto v = transform_.Transform3D(_v);
        res.lowerBound = b2Vec2(res.lowerBound.x > v.X ? v.X : res.lowerBound.x, res.lowerBound.y > v.Y ? v.Y : res.lowerBound.y);
        res.upperBound = b2Vec2(res.upperBound.x < v.X ? v.X : res.upperBound.x, res.upperBound.y < v.Y ? v.Y : res.upperBound.y);
    }
    return res;
}

}  // namespace Altseed