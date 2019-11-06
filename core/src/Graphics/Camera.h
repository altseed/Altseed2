#pragma once

#include <LLGI.Base.h>
#include <LLGI.Graphics.h>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include "../Common/Resource.h"
#include "../Common/Resources.h"
#include "../Math/Vector2DI.h"
#include "Graphics.h"
#include "Texture2D.h"

namespace altseed {
class Camera : public Texture2D {
private:
    Vector2DI src_;
    std::shared_ptr<LLGI::RenderPass> renderPass_;
    std::array<float, 16> matView_;
    std::array<float, 16> matProjection_;

public:
    Camera(Vector2DI src, Vector2DI size);
    virtual ~Camera();

    LLGI::RenderPass* GetRenderPass() const { return renderPass_.get(); }
    Vector2DI GetSrc() const { return src_; }
    std::array<float, 16>& GetViewMatrix() { return matView_; }
    std::array<float, 16>& GetProjectionMatrix() { return matProjection_; }
};

}  // namespace altseed