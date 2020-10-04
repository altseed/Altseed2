#include <Common/StringHelper.h>
#include <Core.h>
#include <Input/Joystick.h>
#include <gtest/gtest.h>
#include <hidapi.h>

#include <chrono>
#include <cmath>

#include "TestHelper.h"

bool IsPushedOrHolded(int joystickIndex, Altseed2::JoystickButton btn, int count) {
    if (Altseed2::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, btn) == Altseed2::ButtonState::Free ||
        Altseed2::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, btn) == Altseed2::ButtonState::Release) {
        return false;
    } else if (Altseed2::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, btn) == Altseed2::ButtonState::Push) {
        return true;
    } else {
        return (count % 80000 == 0);
    }
}

// TODO
TEST(Joystick, Vibrate) {

    auto config = Altseed2TestConfig(Altseed2::CoreModules::Joystick);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Joystick ButtonState", 640, 480, config));

    float time = 0.0f;

    while (Altseed2::Core::GetInstance()->DoEvent()) {
        int joystickIndex = 0;
        float frequency = 150.0f;
        float amplitude = 0.8f;

        if (time < 5.0f) {
            frequency = 150.0f;
            amplitude = 0.5f * (0.5f * std::sin(time)) * 0.8f;
        } else {
            frequency = 0.5f * (0.5f * std::sin(time)) * 150.0f;
            amplitude = 0.8f;
        }

        Altseed2::Joystick::GetInstance()->Vibrate(joystickIndex, frequency, amplitude);
        
        time += Altseed2::Core::GetInstance()->GetDeltaSecond();

        if (time > 10.0f) {
            break;
        }
    }

    // while (Altseed2::Core::GetInstance()->DoEvent()) {
    //     if (!vibrated && Altseed2::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, Altseed2::JoystickButton::RightDown) == Altseed2::ButtonState::Push) {
    //         Altseed2::Joystick::GetInstance()->Vibrate(joystickIndex, frequency, amplitude);
    //         start = std::chrono::system_clock::now();
    //         vibrated = true;
    //     }

    //     if (IsPushedOrHolded(joystickIndex, Altseed2::JoystickButton::RightRight, count)) {
    //         frequency += 10.0f;
    //         std::cout << "freq: " << frequency << std::endl;
    //     }
        
    //     if (IsPushedOrHolded(joystickIndex, Altseed2::JoystickButton::RightDown, count)) {
    //         frequency -= 10.0f;
    //         std::cout << "freq: " << frequency << std::endl;
    //     }

    //     if (IsPushedOrHolded(joystickIndex, Altseed2::JoystickButton::RightUp, count)) {
    //         amplitude += 0.05f;
    //         std::cout << "amp : " << amplitude << std::endl;
    //     }

    //     if (IsPushedOrHolded(joystickIndex, Altseed2::JoystickButton::RightLeft, count)) {
    //         amplitude -= 0.05f;
    //         std::cout << "amp : " << amplitude << std::endl;
    //     }

    //     if (IsPushedOrHolded(joystickIndex, Altseed2::JoystickButton::RightBumper, count)) {
    //         vibrate_time += 10.0f;
    //         std::cout << "time: " << vibrate_time << std::endl;
    //     }

    //     if (IsPushedOrHolded(joystickIndex, Altseed2::JoystickButton::LeftBumper, count)) {
    //         vibrate_time -= 10.0f;
    //         std::cout << "time: " << vibrate_time << std::endl;
    //     }

    //     if (vibrated && std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= vibrate_time) {
    //         Altseed2::Joystick::GetInstance()->Vibrate(joystickIndex, 100.0f, 0);
    //         vibrated = false;
    //     }

    //     end = std::chrono::system_clock::now();
    //     count++;

    //     time += Altseed2::Core::GetInstance()->GetDeltaSecond();
    //     if (time > 10.0f) {
    //         break;
    //     }
    // }

    Altseed2::Core::Terminate();
}

void printJoystickInformation() {
    for (int i = 0; i < 16; i++) {
        auto info = Altseed2::Joystick::GetInstance()->GetJoystickInfo(i);
        if (info == nullptr) {
            continue;
        }
        std::cout
                << "--- Index: " << i << " ---" << std::endl
                << "Name: " << Altseed2::utf16_to_utf8(std::u16string(info->GetName())) << std::endl
                << "ButtonCount: " << info->GetButtonCount() << std::endl
                << "AxisCount: " << info->GetAxisCount() << std::endl
                << "GUID: " << Altseed2::utf16_to_utf8(std::u16string(info->GetGUID())) << std::endl
                << "Bustype: " << info->GetBustype() << std::endl
                << "Vendor: " << info->GetVendor() << std::endl
                << "Product: " << info->GetProduct() << std::endl
                << "Version: " << info->GetVersion() << std::endl;

        if (info->GetIsGamepad()) {
            std::cout
                    << "--- Gamepad ---" << std::endl
                    << "GamepadName: " << Altseed2::utf16_to_utf8(std::u16string(info->GetGamepadName())) << std::endl;
        }

        std::cout << std::endl;
    }
}

TEST(Joystick, Initialize) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Joystick);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Joystick Initialize", 640, 480, config));

    auto joystickCount = Altseed2::Joystick::GetInstance()->GetConnectedJoystickCount();

    if (joystickCount > 0) {
        printJoystickInformation();
    } else {
        std::cout << "No joystick is connected" << std::endl;
    }

    Altseed2::Core::Terminate();
}

TEST(Joystick, ButtonState) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Joystick);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Joystick ButtonState", 640, 480, config));

    auto joystickCount = Altseed2::Joystick::GetInstance()->GetConnectedJoystickCount();

    if (joystickCount > 0) {
        printJoystickInformation();

        float time = 0.0f;
        while (Altseed2::Core::GetInstance()->DoEvent()) {
            for (int ji = 0; ji < 16; ji++) {
                auto info = Altseed2::Joystick::GetInstance()->GetJoystickInfo(ji);
                if (info == nullptr) continue;

                for (int bi = 0; bi < info->GetButtonCount(); bi++) {
                    auto bs = Altseed2::Joystick::GetInstance()->GetButtonStateByIndex(ji, bi);

                    if (bs == Altseed2::ButtonState::Push) {
                        printf("%d - %d : Push\n", ji, bi);
                    } else if (bs == Altseed2::ButtonState::Hold) {
                        printf("%d - %d : Hold\n", ji, bi);
                    } else if (bs == Altseed2::ButtonState::Release) {
                        printf("%d - %d : Release\n", ji, bi);
                    }
                }
            }

            time += Altseed2::Core::GetInstance()->GetDeltaSecond();
            if (time > 10.0f) {
                break;
            }
        }
    } else {
        std::cout << "No joystick is connected" << std::endl;
    }

    Altseed2::Core::Terminate();
}

TEST(Joystick, AxisState) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Joystick);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Joystick AxisState", 640, 480, config));

    auto joystickCount = Altseed2::Joystick::GetInstance()->GetConnectedJoystickCount();

    if (joystickCount > 0) {
        printJoystickInformation();

        float time = 0.0f;
        while (Altseed2::Core::GetInstance()->DoEvent()) {
            for (int ji = 0; ji < 16; ji++) {
                auto info = Altseed2::Joystick::GetInstance()->GetJoystickInfo(ji);
                if (info == nullptr) continue;

                for (int ai = 0; ai < info->GetAxisCount(); ai++) {
                    auto v = Altseed2::Joystick::GetInstance()->GetAxisStateByIndex(ji, ai);
                    if (std::abs(v) > 0.1) {
                        printf("%d - %d : %f\n", ji, ai, v);
                    }
                }
            }

            time += Altseed2::Core::GetInstance()->GetDeltaSecond();
            if (time > 10.0f) {
                break;
            }
        }
    } else {
        std::cout << "No joystick is connected" << std::endl;
    }

    Altseed2::Core::Terminate();
}

TEST(Joystick, ButtonStateByType) {
    const std::map<std::string, Altseed2::JoystickButton> buttonTypes{
            {std::string("RightDown"), Altseed2::JoystickButton::RightDown},
            {std::string("RightRight"), Altseed2::JoystickButton::RightRight},
            {std::string("RightLeft"), Altseed2::JoystickButton::RightLeft},
            {std::string("RightUp"), Altseed2::JoystickButton::RightUp},
            {std::string("LeftBumper"), Altseed2::JoystickButton::LeftBumper},
            {std::string("RightBumper"), Altseed2::JoystickButton::RightBumper},
            {std::string("Back"), Altseed2::JoystickButton::Back},
            {std::string("Start"), Altseed2::JoystickButton::Start},
            {std::string("Guide"), Altseed2::JoystickButton::Guide},
            {std::string("LeftThumb"), Altseed2::JoystickButton::LeftThumb},
            {std::string("RightThumb"), Altseed2::JoystickButton::RightThumb},
            {std::string("DPadUp"), Altseed2::JoystickButton::DPadUp},
            {std::string("DPadRight"), Altseed2::JoystickButton::DPadRight},
            {std::string("DPadDown"), Altseed2::JoystickButton::DPadDown},
            {std::string("DPadLeft"), Altseed2::JoystickButton::DPadLeft},
    };

    auto config = Altseed2TestConfig(Altseed2::CoreModules::Joystick);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Joystick ButtonStateByType", 640, 480, config));

    auto joystickCount = Altseed2::Joystick::GetInstance()->GetConnectedJoystickCount();

    if (joystickCount > 0) {
        printJoystickInformation();

        float time = 0.0f;
        while (Altseed2::Core::GetInstance()->DoEvent()) {
            for (int ji = 0; ji < 16; ji++) {
                auto info = Altseed2::Joystick::GetInstance()->GetJoystickInfo(ji);
                if (info == nullptr) continue;

                for (auto const& x : buttonTypes) {
                    auto bs = Altseed2::Joystick::GetInstance()->GetButtonStateByType(ji, x.second);
                    if (bs == Altseed2::ButtonState::Push) {
                        printf("%d - %s : Push\n", ji, x.first.c_str());
                    } else if (bs == Altseed2::ButtonState::Release) {
                        printf("%d - %s : Release\n", ji, x.first.c_str());
                    }
                }
            }

            time += Altseed2::Core::GetInstance()->GetDeltaSecond();
            if (time > 10.0f) {
                break;
            }
        }
    } else {
        std::cout << "No joystick is connected" << std::endl;
    }

    Altseed2::Core::Terminate();
}

TEST(Joystick, AxisStateByType) {
    const std::map<std::string, Altseed2::JoystickAxis> axisTypes{
            {std::string("LeftX"), Altseed2::JoystickAxis::LeftX},
            {std::string("LeftY"), Altseed2::JoystickAxis::LeftY},
            {std::string("RightX"), Altseed2::JoystickAxis::RightX},
            {std::string("RightY"), Altseed2::JoystickAxis::RightY},
    };

    auto config = Altseed2TestConfig(Altseed2::CoreModules::Joystick);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Joystick ButtonStateByType", 640, 480, config));

    auto joystickCount = Altseed2::Joystick::GetInstance()->GetConnectedJoystickCount();

    if (joystickCount > 0) {
        printJoystickInformation();

        float time = 0.0f;
        while (Altseed2::Core::GetInstance()->DoEvent()) {
            for (int ji = 0; ji < 16; ji++) {
                auto info = Altseed2::Joystick::GetInstance()->GetJoystickInfo(ji);
                if (info == nullptr) continue;

                for (auto const& x : axisTypes) {
                    auto as = Altseed2::Joystick::GetInstance()->GetAxisStateByType(ji, x.second);
                    if (std::abs(as) > 0.1) {
                        printf("%d - %s : %f\n", ji, x.first.c_str(), as);
                    }
                }
                {
                    auto as = Altseed2::Joystick::GetInstance()->GetAxisStateByType(ji, Altseed2::JoystickAxis::RightTrigger);
                    if (as > 0.1) {
                        printf("%d - RightTrigger : %f\n", ji, as);
                    }
                }
                {
                    auto as = Altseed2::Joystick::GetInstance()->GetAxisStateByType(ji, Altseed2::JoystickAxis::LeftTrigger);
                    if (as > 0.1) {
                        printf("%d - LeftTrigger : %f\n", ji, as);
                    }
                }
            }

            time += Altseed2::Core::GetInstance()->GetDeltaSecond();
            if (time > 10.0f) {
                break;
            }
        }
    } else {
        std::cout << "No joystick is connected" << std::endl;
    }

    Altseed2::Core::Terminate();
}
