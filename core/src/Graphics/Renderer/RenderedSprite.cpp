#include "RenderedSprite.h"

#include "../../Common/Array.h"
#include "CullingSystem.h"

namespace Altseed {

std::shared_ptr<RenderedSprite> RenderedSprite::Create() { return MakeAsdShared<RenderedSprite>(); }

RectF RenderedSprite::GetSrc() const { return src_; }

void RenderedSprite::SetSrc(const RectF& src) {
    src_ = src;
    cullingSystem_->RequestUpdateAABB(this);
}

std::shared_ptr<TextureBase> RenderedSprite::GetTexture() const { return texture_; }

void RenderedSprite::SetTexture(const std::shared_ptr<TextureBase>& texture) { texture_ = texture; }

std::shared_ptr<Material> RenderedSprite::GetMaterial() const { return material_; }

void RenderedSprite::SetMaterial(const std::shared_ptr<Material>& material) { material_ = material; }

b2AABB RenderedSprite::GetAABB() {
    b2AABB res;
    auto vertexes = std::array<Vector3F, 4>();
    auto src = GetSrc();
    vertexes[0] = Vector3F(0, 0, 0);
    vertexes[1] = Vector3F(src.Width, 0, 0);
    vertexes[2] = Vector3F(src.Width, src.Height, 0);
    vertexes[3] = Vector3F(0, src.Height, 0);

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