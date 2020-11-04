#pragma once
#include "../BaseObject.h"

namespace Altseed2 {

#if !USE_CBG

enum class EasingType : int32_t {
    Linear,
    InSine,
    OutSine,
    InOutSine,
    InQuad,
    OutQuad,
    InOutQuad,
    InCubic,
    OutCubic,
    InOutCubic,
    InQuart,
    OutQuart,
    InOutQuart,
    InQuint,
    OutQuint,
    InOutQuint,
    InExpo,
    OutExpo,
    InOutExpo,
    InCirc,
    OutCirc,
    InOutCirc,
    InBack,
    OutBack,
    InOutBack,
    InElastic,
    OutElastic,
    InOutElastic,
    InBounce,
    OutBounce,
    InOutBounce,
};

class Easing {
public:
    static float GetEasing(EasingType easing, float t);

    // pseudo method for binding
    int32_t Release();
};

#endif

}  // namespace Altseed2
