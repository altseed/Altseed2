#include <Common/StringHelper.h>
#include <Core.h>
#include <Input/Joystick.h>
#include <gtest/gtest.h>
#include <hidapi.h>

#include <chrono>
#include <cmath>

bool IsPushedOrHolded(int joystickIndex, Altseed::JoystickButtonType btn, int count) {
    if (Altseed::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, btn) == Altseed::ButtonState::Free ||
        Altseed::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, btn) == Altseed::ButtonState::Release) {
        return false;
    } else if (Altseed::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, btn) == Altseed::ButtonState::Push) {
        return true;
    } else {
        return (count % 80000 == 0);
    }
}

// TODO
// void CheckVibration(int joystickIndex) {
//     int vibrate_time = 500;  // milliseconds
//     float frequency = 150.0f;
//     float amplitude = 0.8f;
//     int32_t count = 0;
//     std::chrono::system_clock::time_point start, end;
//     start = std::chrono::system_clock::now();
//     end = std::chrono::system_clock::now();
//     bool vibrated = false;

//     while (true) {
//         Altseed::Joystick::GetInstance()->RefreshInputState();

//         if (!vibrated && Altseed::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, Altseed::JoystickButtonType::RightDown) ==
//                                  Altseed::ButtonState::Push) {
//             Altseed::Joystick::GetInstance()->Vibrate(joystickIndex, frequency, amplitude);
//             start = std::chrono::system_clock::now();
//             vibrated = true;
//         }

//         if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::RightRight, count)) {
//             frequency += 10.0f;
//             std::cout << "freq: " << frequency << std::endl;
//         }
//         if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::RightLeft, count)) {
//             frequency -= 10.0f;
//             std::cout << "freq: " << frequency << std::endl;
//         }
//         if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::R3, count)) {
//             amplitude += 0.05f;
//             std::cout << "amp : " << amplitude << std::endl;
//         }
//         if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::L3, count)) {
//             amplitude -= 0.05f;
//             ;
//             std::cout << "amp : " << amplitude << std::endl;
//         }
//         if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::R2, count)) {
//             vibrate_time += 10.0f;
//             std::cout << "time: " << vibrate_time << std::endl;
//         }
//         if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::R1, count)) {
//             vibrate_time -= 10.0f;
//             std::cout << "time: " << vibrate_time << std::endl;
//         }

//         if (vibrated && std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= vibrate_time) {
//             Altseed::Joystick::GetInstance()->Vibrate(joystickIndex, 100.0f, 0);
//             vibrated = false;
//         }

//         end = std::chrono::system_clock::now();
//         count++;
//     }
// }

TEST(Joystick, Initialize) {
    char16_t s16[] = u"Initialize";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    for (int i = 0; i < 16; i++) {
        auto info = Altseed::Joystick::GetInstance()->GetJoystickInfo(i);
        if (info == nullptr) {
            continue;
        }
        std::cout
                << "Index: " << i << std::endl
                << "Name: " << info->GetName() << std::endl
                << "ButtonCount: " << info->GetButtonCount() << std::endl
                << "AxisCount: " << info->GetAxisCount() << std::endl
                << "GUID: " << info->GetGUID() << std::endl
                << "Bustype: " << info->GetBustype() << std::endl
                << "Vendor: " << info->GetVendor() << std::endl
                << "Product: " << info->GetProduct() << std::endl
                << "Version: " << info->GetVersion() << std::endl;
    }

    // if (Altseed::Joystick::GetInstance()->IsPresent(0)) {
    //     CheckVibration(0);
    // }

    Altseed::Core::Terminate();
}

TEST(Joystick, ButtonState) {
    char16_t s16[] = u"Initialize";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    float time = 0.0f;
    while (Altseed::Core::GetInstance()->DoEvent()) {
        for (int ji = 0; ji < 16; ji++) {
            auto info = Altseed::Joystick::GetInstance()->GetJoystickInfo(ji);
            if (info == nullptr) continue;

            for(int bi = 0; bi < info->GetButtonCount(); bi++) {
                auto bs = Altseed::Joystick::GetInstance()->GetButtonStateByIndex(ji, bi);

                if (bs == Altseed::ButtonState::Push) {
                    printf("%d - %d : Push\n", ji, bi);
                } else if (bs == Altseed::ButtonState::Hold) {
                    printf("%d - %d : Hold\n", ji, bi);
                } else if (bs == Altseed::ButtonState::Release) {
                    printf("%d - %d : Release\n", ji, bi);
                }
            }

        }

        time += Altseed::Core::GetInstance()->GetDeltaSecond();
        if (time > 10.0f) {
            break;
        }
    }

    Altseed::Core::Terminate();
}

TEST(Joystick, AxisState) {
    char16_t s16[] = u"Initialize";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    float time = 0.0f;
    while (Altseed::Core::GetInstance()->DoEvent()) {
        for (int ji = 0; ji < 16; ji++) {
            auto info = Altseed::Joystick::GetInstance()->GetJoystickInfo(ji);
            if (info == nullptr) continue;

            for (int ai = 0; ai < info->GetAxisCount(); ai++) {
                auto v = Altseed::Joystick::GetInstance()->GetAxisStateByIndex(ji, ai);
                if(std::abs(v) > 0.1) {
                    printf("%d - %d : %f\n", ji, ai, v);
                }
            }
        }

        time += Altseed::Core::GetInstance()->GetDeltaSecond();
        if (time > 10.0f) {
            break;
        }
    }

    Altseed::Core::Terminate();
}
