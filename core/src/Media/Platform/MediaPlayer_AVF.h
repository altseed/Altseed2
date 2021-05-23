#pragma once

#include <mutex>
#include <thread>
#include <vector>

#include "MediaPlayer_Impl.h"

namespace Altseed2 {

class MediaPlayer_AVF : public MediaPlayer_Impl {
private:
    class Impl;
    std::shared_ptr<Impl> impl_;

public:
    MediaPlayer_AVF();
    ~MediaPlayer_AVF();

    bool Play(bool isLoopingMode) override;

    bool SetSourceFromPath(const char16_t* path) override;

    Vector2I GetSize() const override;

    int32_t GetCurrentFrame() const override;

    bool WriteToTexture2D(std::shared_ptr<Texture2D> target) override;
};

}  // namespace Altseed2
