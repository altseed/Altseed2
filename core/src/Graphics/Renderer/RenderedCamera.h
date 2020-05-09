#pragma once

#include "../../Math/Vector2F.h"
#include "Rendered.h"

namespace Altseed {

class RenderTexture;

class RenderedCamera : public Rendered {
    Vector2F centerOffset_;
    std::shared_ptr<RenderTexture> targetTexture_;

public:
    static std::shared_ptr<RenderedCamera> Create();

    Vector2F GetCenterOffset() const;
    void SetCenterOffset(const Vector2F& centerOffset);

    std::shared_ptr<RenderTexture> GetTargetTexture();
    void SetTargetTexture(const std::shared_ptr<RenderTexture>& targetTexture);

    Matrix44F GetProjectionMatrix() const;
    Matrix44F GetCameraMatrix() const;

    b2AABB GetAABB() override;
};

}  // namespace Altseed