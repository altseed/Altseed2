#include "RenderTexture.h"
#include "Graphics.h"
#include "Texture2D.h"

namespace altseed {

RenderTexture::RenderTexture(Vector2DI size) {
    size_ = size;

    m_texture = Graphics::GetInstance()->CreateRenderTexture(size_.X, size_.Y);
    renderPass_ = Graphics::GetInstance()->CreateRenderPass(m_texture.get());

}

RenderTexture::~RenderTexture() { m_texture = nullptr; }

}  // namespace altseed