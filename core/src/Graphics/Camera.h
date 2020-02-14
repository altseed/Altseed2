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
#include "../Math/Vector2I.h"
#include "Graphics.h"
#include "RenderTexture.h"
#include "Texture2D.h"

namespace Altseed {

class RenderTexture;
class Sprites;

class Camera : public BaseObject {
private:
    Vector2I src_;
    std::shared_ptr<RenderTexture> target_;
    std::array<float, 16> matView_;
    std::array<float, 16> matProjection_;

public:
    Camera();
    virtual ~Camera();

    std::shared_ptr<RenderTexture> GetTarget() const { return target_; }
    void SetTarget(std::shared_ptr<RenderTexture> target);

    Vector2I GetSrc() const { return src_; }
    void SetSrc(Vector2I src);

    std::array<float, 16>& GetViewMatrix() { return matView_; }
    std::array<float, 16>& GetProjectionMatrix() { return matProjection_; }
};

}  // namespace Altseed