#include "RenderedSprite.h"

namespace Altseed {

RectF RenderedSprite::GetSrc() const { return src_; }

void RenderedSprite::SetSrc(const RectF& src) { src_ = src; }

std::shared_ptr<Texture2D> RenderedSprite::GetTexture() const { return texture_; }

void RenderedSprite::SetTexture(const std::shared_ptr<Texture2D>& texture) { texture_ = texture; }

std::shared_ptr<Material> RenderedSprite::GetMaterial() const { return material_; }

void RenderedSprite::SetMaterial(const std::shared_ptr<Material>& material) { material_ = material; }

}  // namespace Altseed