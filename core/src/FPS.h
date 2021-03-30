#pragma once
#include <chrono>

#include "BaseObject.h"

namespace Altseed2 {

enum class FramerateMode : int32_t {
    Variable,
    Constant,
};

#if !USE_CBG
class FPS {
private:
    float currentFPS_ = 0.0f;
    int32_t targetFPS_;
    float deltaSecond_ = 0.0f;
    FramerateMode framerateMode_ = FramerateMode::Variable;

    std::chrono::system_clock::time_point previousTime_;
    std::chrono::nanoseconds framens_;

    static const int64_t nano = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)).count();

public:
    FPS();
    ~FPS();
    void Update();

    float GetDeltaSecond() const;
    float GetCurrentFPS() const;

    int32_t GetTargetFPS() const;
    void SetTarget(int32_t fps);

    FramerateMode GetFramerateMode() const;
    void SetFramerateMode(FramerateMode framerateMode);
};

#endif

}  // namespace Altseed2