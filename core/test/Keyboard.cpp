#include <Core.h>
#include <Input/Keyboard.h>
#include <gtest/gtest.h>

#include <string>
#define STR(var) #var

using namespace std::string_literals;

/*
TEST(Keyboard, Initialize) {
    char16_t s16[] = u"test";

    EXPECT_TRUE(Altseed2::Core::Initialize(s16, 640, 480, Altseed2::Configuration::Create()));

    int i = 0;

    while (i < (int)Altseed2::Keys::MAX) {
        Altseed2::Keyboard::GetInstance()->RefleshKeyStates();

        Altseed2::ButtonState state = Altseed2::Keyboard::GetInstance()->GetKeyState(static_cast<Altseed2::Keys>(i));
        EXPECT_EQ(Altseed2::ButtonState::Free, state);

        i++;
    }

    Altseed2::Core::Terminate();
}
*/

TEST(Keyboard, GetKeyState) {
    char16_t s16[] = u"test";

    EXPECT_TRUE(Altseed2::Core::Initialize(s16, 640, 480, Altseed2::Configuration::Create()));

    for (int count = 0; Altseed2::Core::GetInstance()->DoEvent() && count < 60; count++) {
        for (int i = 0; i < static_cast<int>(Altseed2::Keys::MAX); i++) {
            auto bs = Altseed2::Keyboard::GetInstance()->GetKeyState((Altseed2::Keys)i);
            if (bs != Altseed2::ButtonState::Free) std::cout << i;
        }
        std::cout << std::endl;
    }

    Altseed2::Core::Terminate();
}
