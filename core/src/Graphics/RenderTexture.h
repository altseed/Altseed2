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
#include "Texture2D.h"

namespace Altseed {
class RenderTexture : public Texture2D {
public:
    RenderTexture(const std::shared_ptr<LLGI::Texture>& texture);
    RenderTexture(Vector2I size);
    virtual ~RenderTexture();
};

}  // namespace Altseed