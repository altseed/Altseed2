#pragma once

#include <mutex>
#include <process.hpp>
#include <thread>
#include <vector>

#include "MediaPlayer_Impl.h"

namespace Altseed2 {

class MediaPlayer_FFmpeg : public MediaPlayer_Impl {
    std::mutex mtx;
    std::thread thread_;
    Vector2I size_;
    float fps = 0;
    bool isLoopingMode_ = false;
    std::vector<uint8_t> internalBuffer;

    bool isPlaying = false;
    bool isThreadRequiredToJoin = false;

    int32_t currentFrame = 0;
    std::chrono::system_clock::time_point startTime;
    std::shared_ptr<TinyProcessLib::Process> process_;

    void ThreadLoop();

public:
    MediaPlayer_FFmpeg();
    ~MediaPlayer_FFmpeg();

    bool Play(bool isLoopingMode) override;

    bool SetSourceFromPath(const char16_t* path) override;

    Vector2I GetSize() const override;

    int32_t GetCurrentFrame() const override;

    bool WriteToTexture2D(std::shared_ptr<Texture2D> target) override;
};

}  // namespace Altseed2