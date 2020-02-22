#include <Core.h>
#include <Input/Joystick.h>
#include <gtest/gtest.h>
#include <hidapi.h>
#include <chrono>
#include <cmath>

uint8_t global_count = 0x00;

TEST(Joystick, Initialize) {
    char16_t s16[] = u"test";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

//    std::shared_ptr<Altseed::Joystick> joystick = std::make_shared<Altseed::Joystick>(Altseed::Joystick());
    auto joystick = new Altseed::Joystick();

    joystick->Initialize(Altseed::JoystickType::JoyconL);
    for (int i = 0; i < 10; i++) {
        if (joystick->IsPresent(i))
            printf("name: %s", joystick->GetJoystickName(i).c_str());
        
    }

    Altseed::Core::Terminate();
}
