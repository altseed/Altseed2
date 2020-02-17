#include <Core.h>
#include <Input/Keyboard.h>
#include <gtest/gtest.h>
#include <string>
#define STR(var) #var

using namespace std::string_literals;

TEST(Keyboard, Initialize) {
    char16_t s16[] = u"test";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    int i = 0;

    while (i < (int)Altseed::Keys::MAX) {
        Altseed::Keyboard::GetInstance()->RefleshKeyStates();

        Altseed::ButtonState state = Altseed::Keyboard::GetInstance()->GetKeyState(static_cast<Altseed::Keys>(i));
        EXPECT_EQ(Altseed::ButtonState::Free, state);

        i++;
    }

    Altseed::Core::Terminate();
}

TEST(Keyboard, GetKeyState) {
    char16_t s16[] = u"test";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    while (Altseed::Core::GetInstance()->DoEvent()) {
        for (int i = 0; i < static_cast<int>(Altseed::Keys::MAX); i++) {
            auto bs = Altseed::Keyboard::GetInstance()->GetKeyState((Altseed::Keys)i);
            if (bs != Altseed::ButtonState::Free) std::cout << i;
        }
    }

    Altseed::Core::Terminate();
}
