#include <Core.h>
#include <Input/Mouse.h>
#include <gtest/gtest.h>

#include <string>
#define STR(var) #var

using namespace std::string_literals;

TEST(Mouse, Initialize) {
    char16_t s16[] = u"Mouse";

    EXPECT_TRUE(Altseed2::Core::Initialize(s16, 640, 480, Altseed2::Configuration::Create()));

    int i = 0;

    while (i < 8) {
        Altseed2::Mouse::GetInstance()->RefreshInputState();

        Altseed2::ButtonState state = Altseed2::Mouse::GetInstance()->GetMouseButtonState(static_cast<Altseed2::MouseButton>(i));
        EXPECT_EQ(Altseed2::ButtonState::Free, state);

        i++;
    }

    auto cursor = Altseed2::Cursor::Create(u"TestData/Input/altseed_logo.png", Altseed2::Vector2I(16, 16));
    if (cursor != nullptr) {
        Altseed2::Mouse::GetInstance()->SetCursorImage(cursor);
    }
    Altseed2::Core::Terminate();
}

// function for SetWheelCallBack test.
void WheelTestFunction(double x, double y) {
    //    std::cout << "called wheel test function.\n";
    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
}

TEST(Mouse, GetMouseInput) {
    char16_t s16[] = u"Mouse inputs";

    EXPECT_TRUE(Altseed2::Core::Initialize(s16, 640, 480, Altseed2::Configuration::Create()));

    Altseed2::Mouse::GetInstance()->Altseed2::Mouse::SetWheelCallback(WheelTestFunction);

    Altseed2::Mouse::GetInstance()->SetCursorMode(Altseed2::CursorMode::Hidden);
    Altseed2::CursorMode mode = Altseed2::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, Altseed2::CursorMode::Hidden);

    Altseed2::Mouse::GetInstance()->SetCursorMode(Altseed2::CursorMode::Disable);
    mode = Altseed2::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, Altseed2::CursorMode::Disable);

    Altseed2::Mouse::GetInstance()->SetCursorMode(Altseed2::CursorMode::Normal);
    mode = Altseed2::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, Altseed2::CursorMode::Normal);

    for (int count = 0; Altseed2::Core::GetInstance()->DoEvent() && count < 10; count++) {
        // testing MouseButton inputs.
        for (int i = 0; i < 8; i++) {
            auto bs = Altseed2::Mouse::GetInstance()->GetMouseButtonState((Altseed2::MouseButton)i);
            if (bs != Altseed2::ButtonState::Free) std::cout << i;
        }

        // testing wheel input.
        float wheel = Altseed2::Mouse::GetInstance()->GetWheel();
        if (wheel != 0) {
            //            std::cout << wheel << "\n";
        }
        std::cout << std::endl;
    }

    Altseed2::Core::Terminate();
}

TEST(Mouse, Position) {
    char16_t s16[] = u"Mouse position";

    EXPECT_TRUE(Altseed2::Core::Initialize(s16, 640, 480, Altseed2::Configuration::Create()));

    Altseed2::Mouse::GetInstance()->SetPosition(Altseed2::Vector2F(320, 240));
    Altseed2::Vector2F result = Altseed2::Mouse::GetInstance()->GetPosition();
    EXPECT_EQ(result.X, 320);
    EXPECT_EQ(result.Y, 240);

    Altseed2::Core::Terminate();
}

// TEST(Mouse, CursorMode) {
//    char16_t s16[] = u"Mouse position";
//
//    EXPECT_TRUE(Altseed2::Core::Initialize(s16, 640, 480, Altseed2::Configuration::Create()));
//}
