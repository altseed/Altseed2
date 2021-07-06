#pragma once

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <propvarutil.h>

#include <mutex>
#include <thread>
#include <vector>

#include "MediaPlayer_Impl.h"

namespace Altseed2 {

class MediaPlayer_WMF : public MediaPlayer_Impl {
    std::mutex mtx;
    std::thread thread_;
    Vector2I size_;
    float fps = 0;
    bool isLoopingMode_ = false;
    std::vector<uint8_t> internalBufferYUY;
    std::vector<uint8_t> internalBuffer;
    std::vector<uint8_t> internalBufferEditing;

    bool isPlaying = false;
    bool isThreadRequiredToJoin = false;

    int32_t currentFrame = 0;
    std::chrono::system_clock::time_point startTime;

    IMFSourceReader* reader = nullptr;

    void ThreadLoop();

public:
    MediaPlayer_WMF();
    ~MediaPlayer_WMF();

    bool Play(bool isLoopingMode) override;

    bool SetSourceFromPath(const char16_t* path) override;

    Vector2I GetSize() const override;

    int32_t GetCurrentFrame() const override;

    bool WriteToTexture2D(std::shared_ptr<RenderTexture> target) override;
};

}  // namespace Altseed2