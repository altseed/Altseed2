#include "Math/Easing.h"

#include <gtest/gtest.h>

#include <cmath>

namespace asd = Altseed;

enum class EasingTestType : uint32_t {
    Default = 0x00,
    From0to1 = 0x01,
    Monotonic = 0x10,
};

EasingTestType operator|(EasingTestType a, EasingTestType b) {
    return static_cast<EasingTestType>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

EasingTestType operator&(EasingTestType a, EasingTestType b) {
    return static_cast<EasingTestType>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

TEST(Easing, GetEasing) {
    const auto NumberOfTestsInEachCase = 100;

    std::map<asd::EasingType, EasingTestType> TestEasings = {
            {asd::EasingType::InBack, EasingTestType::Default},
            {asd::EasingType::OutBack, EasingTestType::Default},
            {asd::EasingType::InOutBack, EasingTestType::Default},
            {asd::EasingType::InElastic, EasingTestType::Default},
            {asd::EasingType::OutElastic, EasingTestType::Default},
            {asd::EasingType::InOutElastic, EasingTestType::Default},
            {asd::EasingType::InBounce, EasingTestType::From0to1},
            {asd::EasingType::OutBounce, EasingTestType::From0to1},
            {asd::EasingType::InOutBounce, EasingTestType::From0to1},
    };

    for (int i = static_cast<int32_t>(asd::EasingType::Linear); i <= static_cast<int32_t>(asd::EasingType::InOutCirc); i++) {
        TestEasings[static_cast<asd::EasingType>(i)] = EasingTestType::From0to1 | EasingTestType::Monotonic;
    }

    for (auto kvp : TestEasings) {
        auto easing = kvp.first;
        auto testType = kvp.second;

        //        std::cout << static_cast<int32_t>(easing) <<std::endl;

        float x0 = 0.0f, x = 0.0f;

        for (int i = 0; i <= NumberOfTestsInEachCase; i++) {
            x0 = x;
            x = asd::Easing::GetEasing(easing, (float)i / (float)NumberOfTestsInEachCase);

            EXPECT_FALSE(std::isinf(x));
            EXPECT_FALSE(std::isnan(x));

            if ((testType & EasingTestType::From0to1) == EasingTestType::From0to1) {
                EXPECT_TRUE(0.0f <= x && x <= 1.0f);
            }

            if ((testType & EasingTestType::Monotonic) == EasingTestType::Monotonic) {
                EXPECT_TRUE(x0 <= x);
            }
        }
    }
}
