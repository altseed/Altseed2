#pragma once

#include <mutex>
#include <process.hpp>
#include <thread>
#include <vector>

#include "MediaPlayer_Impl.h"

namespace Altseed2 {

class MediaPlayer_FFmpeg : public MediaPlayer_Impl {
    std::mutex mtx_;
    std::thread thread_;
    Vector2I size_;
    float fps_ = 0;
    std::string filePath_;
    bool isLoopingMode_ = false;
    std::vector<uint8_t> internalBuffer_;

    bool isPlaying_ = false;
    bool isThreadRequiredToJoin_ = false;

    int32_t currentFrame_ = 0;
    std::chrono::system_clock::time_point startTime_;
    std::shared_ptr<TinyProcessLib::Process> process_;

    void ThreadLoop();

public:
    MediaPlayer_FFmpeg();
    ~MediaPlayer_FFmpeg();

    bool Play(bool isLoopingMode) override;

    bool SetSourceFromPath(const char16_t* path) override;

    Vector2I GetSize() const override;

    int32_t GetCurrentFrame() const override;

    bool WriteToTexture2D(std::shared_ptr<RenderTexture> target) override;
};

}  // namespace Altseed2