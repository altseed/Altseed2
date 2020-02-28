#pragma once
#include <chrono>
#include "BaseObject.h"

namespace Altseed {

enum class FramerateMode : int32_t {
    Variable,
    Constant,
};

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
    void Update();

    const float GetDeltaSecond();
    const float GetCurrentFPS();

    const int32_t GetTargetFPS();
    void SetTarget(int32_t fps);

    const FramerateMode GetFramerateMode();
    void SetFramerateMode(FramerateMode framerateMode);

};

} // namespace Altseed