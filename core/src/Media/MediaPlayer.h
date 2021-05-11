
#pragma once

#include <memory>

#include "../Graphics/Texture2D.h"
#include "../Math/Vector2I.h"

namespace Altseed2 {

class MediaPlayer_Impl;

class MediaPlayer
    : public BaseObject {
private:
    std::shared_ptr<MediaPlayer_Impl> impl_;

protected:
    MediaPlayer();
    virtual ~MediaPlayer() = default;
    bool isLoopingMode_ = false;

public:
    bool Play(bool isLoopingMode);

    bool Load(const char16_t* path);

    bool WriteToTexture2D(std::shared_ptr<Texture2D> target);

    Vector2I GetSize() const;

    int32_t GetCurrentFrame() const;
};

}  // namespace Altseed2