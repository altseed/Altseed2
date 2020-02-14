#include "RenderTexture.h"
#include "Graphics.h"
#include "Texture2D.h"

namespace Altseed {

RenderTexture::RenderTexture(const std::shared_ptr<LLGI::Texture>& texture) { m_texture = texture; }

RenderTexture::RenderTexture(Vector2I size) {
    size_ = size;

    m_texture = Graphics::GetInstance()->CreateRenderTexture(size_.X, size_.Y);
    size_.X = m_texture->GetSizeAs2D().X;
    size_.Y = m_texture->GetSizeAs2D().Y;
}

RenderTexture::~RenderTexture() { m_texture = nullptr; }

}  // namespace Altseed