#pragma once

#include "../../Graphics/Graphics.h"
#include "../../Graphics/RenderTexture.h"
#include "../../Math/Vector2I.h"

namespace Altseed2 {

class MediaPlayer_Impl {
public:
    virtual bool Play(bool isLoopingMode) = 0;

    virtual bool SetSourceFromPath(const char16_t* path) = 0;

    virtual Vector2I GetSize() const = 0;

    virtual int32_t GetCurrentFrame() const = 0;

    virtual bool WriteToTexture2D(std::shared_ptr<RenderTexture> target) = 0;
};

}  // namespace Altseed2