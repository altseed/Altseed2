#include <Common/StringHelper.h>
#include <Core.h>
#include <Input/Joystick.h>
#include <gtest/gtest.h>
#include <hidapi.h>

#include <chrono>
#include <cmath>

uint8_t global_count = 0x00;

TEST(Joystick, GetJoystickName) {
    char16_t s16[] = u"GetJoystickName";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));
    Altseed::Joystick::GetInstance()->RefreshConnectedState();

    for (int i = 0; i < 16; i++) {
        if (Altseed::Joystick::GetInstance()->IsPresent(i)) {
            std::cout << "name : " << Altseed::utf16_to_utf8(std::u16string(Altseed::Joystick::GetInstance()->GetJoystickName(i)))
                      << std::endl;
        }
    }

    Altseed::Core::Terminate();
}
