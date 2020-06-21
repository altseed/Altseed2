#pragma once

#include "../../Math/Vector2F.h"
#include "../CommandList.h"
#include "Rendered.h"

namespace Altseed2 {

class RenderTexture;

class RenderedCamera : public Rendered {
    Vector2F centerOffset_;
    std::shared_ptr<RenderTexture> targetTexture_;
    RenderPassParameter renderPassParameter_;

public:
    static std::shared_ptr<RenderedCamera> Create();

    Vector2F GetCenterOffset() const;
    void SetCenterOffset(const Vector2F& centerOffset);

    std::shared_ptr<RenderTexture> GetTargetTexture();
    void SetTargetTexture(const std::shared_ptr<RenderTexture>& renderPassParameter);

    RenderPassParameter GetRenderPassParameter() const;
    void SetRenderPassParameter(const RenderPassParameter targetTexture);

    Matrix44F GetProjectionMatrix() const;
    Matrix44F GetCameraMatrix() const;

    b2AABB GetAABB() override;
};

}  // namespace Altseed2