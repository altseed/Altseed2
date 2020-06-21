// --Easing Functions(Equations)--

// MIT License

// Copyright Â© 2001 Robert Penner

// Permission is hereby granted,
// free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions :

// The above copyright notice and this permission notice shall be included in all copies
// or
// substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS",
// WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "Easing.h"

#include <cmath>

#include "../Common/Assertion.h"
#include "MathTemplate.h"

namespace Altseed2 {

// pseudo method for binding
int32_t Easing::Release() {
    ASD_ASSERT(false, "Easing class is static, cannot call Easing::Release.");
    return 0;
}

float Easing::GetEasing(EasingType easing, float t) {
    if (t <= 0.0f) return 0.0f;
    if (t >= 1.0f) return 1.0f;

    switch (easing) {
        case EasingType::Linear: {
            return t;
        }

        case EasingType::InSine: {
            return 1.0f - std::cos(t * PI * 0.5f);
        }

        case EasingType::OutSine: {
            return std::sin(t * PI * 0.5f);
        }

        case EasingType::InOutSine: {
            return -1.0f / 2.0f * (std::cos(t * PI) - 1.0f);
        }

        case EasingType::InQuad: {
            return t * t;
        }

        case EasingType::OutQuad: {
            return t * (2.0f - t);
        }

        case EasingType::InOutQuad: {
            if (t < 0.5f) return 2.0f * t * t;

            return t * (4.0f - 2.0f * t) - 1.0f;
        }

        case EasingType::InCubic: {
            return t * t * t;
        }

        case EasingType::OutCubic: {
            t = t - 1.0f;
            return t * t * t + 1.0f;
        }

        case EasingType::InOutCubic: {
            if (t < 0.5f) return 4.0f * t * t * t;

            t = t - 1.0f;
            return 1.0f + t * (2.0f * t) * (2.0f * t);
        }

        case EasingType::InQuart: {
            return t * t * t * t;
        }

        case EasingType::OutQuart: {
            t = t - 1.0f;
            return -(t * t * t * t - 1.0f);
        }

        case EasingType::InOutQuart: {
            if (t < 0.5f) {
                return 8.0f * t * t * t * t;
            }

            t = (t - 1.0f) * (t - 1.0f);
            return 1.0f - 8.0f * t * t;
        }

        case EasingType::InQuint: {
            return t * t * t * t * t;
        }

        case EasingType::OutQuint: {
            float t_ = (t - 1.0f) * (t - 1.0f);
            return (t - 1.0f) * t_ * t_ + 1.0f;
        }

        case EasingType::InOutQuint: {
            if (t < 0.5f) return 16.0f * t * t * t * t * t;

            float t_ = (t - 1.0f) * (t - 1.0f);
            return 1.0f + 16.0f * (t - 1.0f) * t_ * t_;
        }

        case EasingType::InExpo: {
            return std::pow(2.0f, 10.0f * (t - 1.0f));
        }

        case EasingType::OutExpo: {
            return -std::pow(2.0f, -10.0f * t) + 1.0f;
        }

        case EasingType::InOutExpo: {
            if (t < 0.5f) return (std::pow(2.0f, 16.0f * t) - 1.0f) / 510.0f;

            return 1.0f - 0.5f * std::pow(2.0f, -16.0f * (t - 0.5f));
        }

        case EasingType::InCirc: {
            return 1.0f - std::sqrt(1.0f - t);
        }

        case EasingType::OutCirc: {
            return std::sqrt(t);
        }

        case EasingType::InOutCirc: {
            if (t < 0.5f) return (1.0f - std::sqrt(1.0f - 2.0f * t)) * 0.5f;

            return (1.0f + std::sqrt(2.0f * t - 1.0f)) * 0.5f;
        }

        case EasingType::InBack: {
            return t * t * (2.70158f * t - 1.70158f);
        }

        case EasingType::OutBack: {
            t = t - 1.0f;
            return 1.0f + t * t * (2.70158f * t + 1.70158f);
        }

        case EasingType::InOutBack: {
            if (t < 0.5f) return (t * t * (7.0f * t - 2.5f) * 2.0f);

            t = t - 1.0f;
            return 1.0f + t * t * 2.0f * (7.0f * t + 2.5f);
        }

        case EasingType::InElastic: {
            return t * t * t * t * std::sin(t * PI * 4.5f);
        }

        case EasingType::OutElastic: {
            float t_ = (t - 1.0f) * (t - 1.0f);
            return 1.0f - t_ * t_ * std::cos(t * PI * 4.5f);
        }

        case EasingType::InOutElastic: {
            if (t < 0.45f) return 8.0f * t * t * t * t * std::sin(t * PI * 9.0f);
            if (t < 0.55f) return 0.5f + 0.75f * std::sin(t * PI * 4.0f);

            float t_ = (t - 1.0f) * (t - 1.0f);
            return 1.0f - 8.0f * t_ * t_ * std::sin(t * PI * 9.0f);
        }

        case EasingType::InBounce: {
            return std::pow(2.0f, 6.0f * (t - 1.0f)) * std::abs(std::sin(t * PI * 3.5f));
        }

        case EasingType::OutBounce: {
            return 1.0f - std::pow(2.0f, -6.0f * t) * std::abs(std::cos(t * PI * 3.5f));
        }

        case EasingType::InOutBounce: {
            if (t < 0.5f) return 8.0f * std::pow(2.0f, 8.0f * (t - 1.0f)) * std::abs(std::sin(t * PI * 7.0f));

            return 1.0f - 8.0f * std::pow(2.0f, -8.0f * t) * std::abs(std::sin(t * PI * 7.0f));
        }

        default:
            ASD_ASSERT(false, "Unexpected EasingType");
            return -1;
    }
}

}  // namespace Altseed2
