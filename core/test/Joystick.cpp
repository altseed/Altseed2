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

void CheckVibration(int joystickIndex) {
    int vibrate_time = 500;  // milliseconds
    float frequency = 150.0f;
    float amplitude = 0.8f;
    int32_t count = 0;
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();
    bool vibrated = false;

    while (true) {
        Altseed::Joystick::GetInstance()->RefreshInputState();

        if (!vibrated && Altseed::Joystick::GetInstance()->GetButtonStateByType(joystickIndex, Altseed::JoystickButtonType::RightDown) ==
                                 Altseed::ButtonState::Push) {
            Altseed::Joystick::GetInstance()->Vibrate(joystickIndex, frequency, amplitude);
            start = std::chrono::system_clock::now();
            vibrated = true;
        }

        if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::RightRight, count)) {
            frequency += 10.0f;
            std::cout << "freq: " << frequency << std::endl;
        }
        if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::RightLeft, count)) {
            frequency -= 10.0f;
            std::cout << "freq: " << frequency << std::endl;
        }
        if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::R3, count)) {
            amplitude += 0.05f;
            std::cout << "amp : " << amplitude << std::endl;
        }
        if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::L3, count)) {
            amplitude -= 0.05f;
            ;
            std::cout << "amp : " << amplitude << std::endl;
        }
        if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::R2, count)) {
            vibrate_time += 10.0f;
            std::cout << "time: " << vibrate_time << std::endl;
        }
        if (IsPushedOrHolded(joystickIndex, Altseed::JoystickButtonType::R1, count)) {
            vibrate_time -= 10.0f;
            std::cout << "time: " << vibrate_time << std::endl;
        }

        if (vibrated && std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= vibrate_time) {
            Altseed::Joystick::GetInstance()->Vibrate(joystickIndex, 100.0f, 0);
            vibrated = false;
        }

        end = std::chrono::system_clock::now();
        count++;
    }
}

TEST(Joystick, Initialize) {
    char16_t s16[] = u"Initialize";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    for (int i = 0; i < 16; i++) {
        if (Altseed::Joystick::GetInstance()->IsPresent(i)) {
            std::cout << "name : " << Altseed::utf16_to_utf8(std::u16string(Altseed::Joystick::GetInstance()->GetJoystickName(i)))
                      << std::endl;
            std::cout << "index : " << i << std::endl;
        }
    }

    if (Altseed::Joystick::GetInstance()->IsPresent(0)) {
        CheckVibration(0);
    }

    Altseed::Core::Terminate();
}
