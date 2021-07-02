
#pragma once

#include <memory>

#include "../Graphics/RenderTexture.h"
#include "../Math/Vector2I.h"

namespace Altseed2 {

class MediaPlayer_Impl;

class MediaPlayer
    : public BaseObject {
private:
    std::shared_ptr<MediaPlayer_Impl> impl_;

public:
    MediaPlayer();
    virtual ~MediaPlayer() = default;

    bool Play(bool isLoopingMode);

    bool WriteToRenderTexture(std::shared_ptr<RenderTexture> target);

    Vector2I GetSize() const;

    int32_t GetCurrentFrame() const;

    static std::shared_ptr<MediaPlayer> Load(const char16_t* path);
};

}  // namespace Altseed2