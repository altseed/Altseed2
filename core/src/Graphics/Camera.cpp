#include "Camera.h"
#include "Graphics.h"
#include "Texture2D.h"

namespace Altseed2 {

Camera::Camera() {
    matView_.fill(0);
    matProjection_.fill(0);
    for (int64_t i = 0; i < 4; i++) {
        matView_[i * 4 + i] = 1.0f;
        matProjection_[i * 4 + i] = 1.0f;
    }
}

void Camera::SetTarget(std::shared_ptr<RenderTexture> target) {
    target_ = target;

    auto size = target->GetSize();
    matProjection_[0 * 4 + 0] = 2.0f / size.X;
    matProjection_[1 * 4 + 1] = -2.0f / size.Y;
    matProjection_[3 * 4 + 0] = -1.0f;
    matProjection_[3 * 4 + 1] = +1.0f;
}

void Camera::SetSrc(Vector2I src) {
    src_ = src;
    matView_[3 * 4 + 0] = -src_.X;
    matView_[3 * 4 + 1] = -src_.Y;
}

Camera::~Camera() {}

}  // namespace Altseed