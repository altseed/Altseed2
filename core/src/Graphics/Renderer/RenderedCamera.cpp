#include "RenderedCamera.h"

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

}  // namespace Altseed