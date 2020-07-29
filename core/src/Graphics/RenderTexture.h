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
#include "TextureBase.h"

namespace Altseed2 {
class RenderTexture : public TextureBase {
public:
    RenderTexture(const std::shared_ptr<LLGI::Texture>& texture);
    RenderTexture(Vector2I size, TextureFormatType format);
    virtual ~RenderTexture();

    static std::shared_ptr<RenderTexture> Create(Vector2I size, TextureFormatType format = TextureFormatType::R8G8B8A8_UNORM);

    bool Save(const char16_t* path) override;

    bool Reload() override {
        assert(false);
        return false;
    };
};

}  // namespace Altseed2