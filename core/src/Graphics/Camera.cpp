#include "Camera.h"
#include "Graphics.h"
#include "Texture2D.h"

namespace altseed {

Camera::Camera(Vector2DI src, Vector2DI size) {
    src_ = src;
    size_ = size;

    m_texture = Graphics::GetInstance()->CreateRenderTexture(size_.X, size_.Y);
    renderPass_ = Graphics::GetInstance()->CreateRenderPass(m_texture.get());

    matView_.fill(0);
    matProjection_.fill(0);
    for (int64_t i = 0; i < 4; i++) {
        matView_[i * 4 + i] = 1.0f;
        matProjection_[i * 4 + i] = 1.0f;
    }
    matView_[3 * 4 + 0] = -src_.X;
    matView_[3 * 4 + 1] = -src_.Y;

    matProjection_[0 * 4 + 0] = 2.0f / size_.X;
    matProjection_[1 * 4 + 1] = -2.0f / size_.Y;
    matProjection_[3 * 4 + 0] = -1.0f;
    matProjection_[3 * 4 + 1] = +1.0f;
}

Camera::~Camera() { m_texture = nullptr; }

}  // namespace altseed