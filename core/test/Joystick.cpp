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
    auto config = Altseed::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed::Core::Initialize(u"Joystick Initialize", 640, 480, config));

    for (int i = 0; i < 16; i++) {
        auto info = Altseed::Joystick::GetInstance()->GetJoystickInfo(i);
        if (info == nullptr) {
            continue;
        }
        std::cout
                << "Index: " << i << std::endl
                << "Name: " << Altseed::utf16_to_utf8(std::u16string(info->GetName())) << std::endl
                << "ButtonCount: " << info->GetButtonCount() << std::endl
                << "AxisCount: " << info->GetAxisCount() << std::endl
                << "GUID: " << Altseed::utf16_to_utf8(std::u16string(info->GetGUID())) << std::endl
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
    auto config = Altseed::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed::Core::Initialize(u"Joystick ButtonState", 640, 480, config));

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
    auto config = Altseed::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed::Core::Initialize(u"Joystick AxisState", 640, 480, config));

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

TEST(Joystick, ButtonStateByType) {
    const std::map<std::string, Altseed::JoystickButtonType> buttonTypes {
            {std::string("Home"), Altseed::JoystickButtonType::Home},
            {std::string("Capture"), Altseed::JoystickButtonType::Capture},

            {std::string("LeftUp"), Altseed::JoystickButtonType::LeftUp},
            {std::string("LeftDown"), Altseed::JoystickButtonType::LeftDown},
            {std::string("LeftLeft"), Altseed::JoystickButtonType::LeftLeft},
            {std::string("LeftRight"), Altseed::JoystickButtonType::LeftRight},
            {std::string("LeftPush"), Altseed::JoystickButtonType::LeftPush},

            {std::string("RightUp"), Altseed::JoystickButtonType::RightUp},
            {std::string("RightRight"), Altseed::JoystickButtonType::RightRight},
            {std::string("RightLeft"), Altseed::JoystickButtonType::RightLeft},
            {std::string("RightDown"), Altseed::JoystickButtonType::RightDown},
            {std::string("RightPush"), Altseed::JoystickButtonType::RightPush},

            {std::string("L1"), Altseed::JoystickButtonType::L1},
            {std::string("R1"), Altseed::JoystickButtonType::R1},
            {std::string("L2"), Altseed::JoystickButtonType::L2},
            {std::string("R2"), Altseed::JoystickButtonType::R2},
            {std::string("L3"), Altseed::JoystickButtonType::L3},
            {std::string("R3"), Altseed::JoystickButtonType::R3},
    
            {std::string("LeftStart"), Altseed::JoystickButtonType::LeftStart},
            {std::string("RightStart"), Altseed::JoystickButtonType::RightStart},
    };

    auto config = Altseed::Configuration::Create();
    // config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed::Core::Initialize(u"Joystick ButtonStateByType", 640, 480, config));

    float time = 0.0f;
    while (Altseed::Core::GetInstance()->DoEvent()) {
        for (int ji = 0; ji < 16; ji++) {
            auto info = Altseed::Joystick::GetInstance()->GetJoystickInfo(ji);
            if (info == nullptr) continue;

            for(auto const& x : buttonTypes) {
                auto bs = Altseed::Joystick::GetInstance()->GetButtonStateByType(ji, x.second);
                    if (bs == Altseed::ButtonState::Push) {
                        printf("%d - %s : Push\n", ji, x.first.c_str());
                    } else if (bs == Altseed::ButtonState::Release) {
                        printf("%d - %s : Release\n", ji, x.first.c_str());
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

TEST(Joystick, AxisStateByType) {
    const std::map<std::string, Altseed::JoystickAxisType> axisTypes{
            {std::string("LeftH"), Altseed::JoystickAxisType::LeftH},
            {std::string("LeftV"), Altseed::JoystickAxisType::LeftV},
            {std::string("RightH"), Altseed::JoystickAxisType::RightH},
            {std::string("RightV"), Altseed::JoystickAxisType::RightV},
    };

    auto config = Altseed::Configuration::Create();

    EXPECT_TRUE(Altseed::Core::Initialize(u"Joystick ButtonStateByType", 640, 480, config));

    float time = 0.0f;
    while (Altseed::Core::GetInstance()->DoEvent()) {
        for (int ji = 0; ji < 16; ji++) {
            auto info = Altseed::Joystick::GetInstance()->GetJoystickInfo(ji);
            if (info == nullptr) continue;

            for (auto const& x : axisTypes) {
                auto as = Altseed::Joystick::GetInstance()->GetAxisStateByType(ji, x.second);
                if(std::abs(as) > 0.1) {
                    printf("%d - %s : %f\n", ji, x.first.c_str(), as);
                }
            }
            {
                auto as = Altseed::Joystick::GetInstance()->GetAxisStateByType(ji, Altseed::JoystickAxisType::R2);
                if (as > -0.5) {
                    printf("%d - R2 : %f\n", ji, as);
                }
            }
            {
                auto as = Altseed::Joystick::GetInstance()->GetAxisStateByType(ji, Altseed::JoystickAxisType::L2);
                if (as > -0.5) {
                    printf("%d - L2 : %f\n", ji, as);
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
