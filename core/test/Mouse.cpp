#include <Core.h>
#include <Input/Mouse.h>
#include <gtest/gtest.h>

#include <string>
#define STR(var) #var

using namespace std::string_literals;

TEST(Mouse, Initialize) {
    char16_t s16[] = u"Mouse";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    int i = 0;

    while (i < 8) {
        Altseed::Mouse::GetInstance()->RefreshInputState();

        Altseed::ButtonState state = Altseed::Mouse::GetInstance()->GetMouseButtonState(static_cast<Altseed::MouseButtons>(i));
        EXPECT_EQ(Altseed::ButtonState::Free, state);

        i++;
    }

    auto cursor = Altseed::Cursor::Create(u"TestData/Input/altseed_logo.png", Altseed::Vector2I(16, 16));
    if (cursor != nullptr) {
        Altseed::Mouse::GetInstance()->SetCursorImage(cursor);
    }
    Altseed::Core::Terminate();
}

// function for SetWheelCallBack test.
void WheelTestFunction(double x, double y) {
    //    std::cout << "called wheel test function.\n";
    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
}

TEST(Mouse, GetMouseInput) {
    char16_t s16[] = u"Mouse inputs";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    Altseed::Mouse::GetInstance()->Altseed::Mouse::SetWheelCallback(WheelTestFunction);

    Altseed::Mouse::GetInstance()->SetCursorMode(Altseed::CursorMode::Hidden);
    Altseed::CursorMode mode = Altseed::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, Altseed::CursorMode::Hidden);

    Altseed::Mouse::GetInstance()->SetCursorMode(Altseed::CursorMode::Disable);
    mode = Altseed::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, Altseed::CursorMode::Disable);

    Altseed::Mouse::GetInstance()->SetCursorMode(Altseed::CursorMode::Normal);
    mode = Altseed::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, Altseed::CursorMode::Normal);

    for (int count = 0; Altseed::Core::GetInstance()->DoEvent() && count < 10; count++) {
        // testing MouseButton inputs.
        for (int i = 0; i < 8; i++) {
            auto bs = Altseed::Mouse::GetInstance()->GetMouseButtonState((Altseed::MouseButtons)i);
            if (bs != Altseed::ButtonState::Free) std::cout << i;
        }

        // testing wheel input.
        float wheel = Altseed::Mouse::GetInstance()->GetWheel();
        if (wheel != 0) {
            //            std::cout << wheel << "\n";
        }
        std::cout << std::endl;
    }

    Altseed::Core::Terminate();
}

TEST(Mouse, Position) {
    char16_t s16[] = u"Mouse position";

    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));

    Altseed::Mouse::GetInstance()->SetPosition(Altseed::Vector2F(320, 240));
    Altseed::Vector2F result = Altseed::Mouse::GetInstance()->GetPosition();
    EXPECT_EQ(result.X, 320);
    EXPECT_EQ(result.Y, 240);

    Altseed::Core::Terminate();
}

// TEST(Mouse, CursorMode) {
//    char16_t s16[] = u"Mouse position";
//
//    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::Configuration::Create()));
//}
