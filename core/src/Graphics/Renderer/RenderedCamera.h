#pragma once

#include "../../Math/Matrix44F.h"
#include "../../Math/Vector2F.h"
#include "../CommandList.h"
#include "Rendered.h"

namespace Altseed2 {

class RenderTexture;

class RenderedCamera : public BaseObject {
    std::shared_ptr<RenderTexture> targetTexture_;
    RenderPassParameter renderPassParameter_;

    Matrix44F matProjection_;
    Matrix44F matView_;

public:
    RenderedCamera();

    static std::shared_ptr<RenderedCamera> Create();

    std::shared_ptr<RenderTexture> GetTargetTexture();
    void SetTargetTexture(const std::shared_ptr<RenderTexture>& renderPassParameter);

    RenderPassParameter GetRenderPassParameter() const;
    void SetRenderPassParameter(const RenderPassParameter targetTexture);

    Matrix44F GetProjectionMatrix() const;

    Matrix44F GetViewMatrix() const;
    void SetViewMatrix(Matrix44F matrix);

    b2AABB GetAABB();
};

}  // namespace Altseed2