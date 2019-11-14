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
class RenderTexture : public Texture2D {
private:
    std::shared_ptr<LLGI::RenderPass> renderPass_;

public:
    RenderTexture(Vector2DI size);
    virtual ~RenderTexture();

    LLGI::RenderPass* GetRenderPass() const { return renderPass_.get(); }
};

}  // namespace altseed