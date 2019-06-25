#include <Core.h>
#include <Input/Mouse.h>
#include <gtest/gtest.h>
#include <string>
#define STR(var) #var

using namespace std::string_literals;

namespace asd = altseed;

TEST(Mouse, Initialize) {
    
    char16_t s16[] = u"Mouse";
    
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::CoreOption()));
    
    int i = 0;
    
    while (i < 8) {
        asd::Mouse::GetInstance()->RefreshInputState();
        
        asd::ButtonState state = asd::Mouse::GetInstance()->GetMouseButtonState(static_cast<asd::MouseButtons>(i));
        EXPECT_EQ(asd::ButtonState::Free, state);
        
        i ++;
    }
    
    asd::Core::Terminate();
}

// function for SetWheelCallBack test.
void WheelTestFunction(double x, double y){
//    std::cout << "called wheel test function.\n";
    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
}

TEST(Mouse, GetMouseInput) {
    
    char16_t s16[] = u"Mouse inputs";
    
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::CoreOption()));
    
    asd::Mouse::GetInstance()->asd::Mouse::SetWheelCallback(WheelTestFunction);
    
    asd::Mouse::GetInstance()->SetCursorMode(asd::CursorMode::Hidden);
    asd::CursorMode mode = asd::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, asd::CursorMode::Hidden);
    
    asd::Mouse::GetInstance()->SetCursorMode(asd::CursorMode::Disable);
    mode = asd::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, asd::CursorMode::Disable);
    
    asd::Mouse::GetInstance()->SetCursorMode(asd::CursorMode::Normal);
    mode = asd::Mouse::GetInstance()->GetCursorMode();
    EXPECT_EQ(mode, asd::CursorMode::Normal);
    
    while(asd::Core::GetInstance()->DoEvent())
    {
        // testing MouseButton inputs.
        for(int i=0;i<8;i++){
            auto bs = asd::Mouse::GetInstance()->GetMouseButtonState((asd::MouseButtons)i);
            if (bs != asd::ButtonState::Free)
                std::cout << i;
        }
        
        // testing wheel input.
        float wheel = asd::Mouse::GetInstance()->GetWheel();
        if (wheel != 0)
        {
//            std::cout << wheel << "\n";
        }
    }
    
    asd::Core::Terminate();
}

TEST(Mouse, Position) {
    
    char16_t s16[] = u"Mouse position";
    
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::CoreOption()));
    
    asd::Mouse::GetInstance()->SetPosition(320, 240);
    double x, y;
    asd::Mouse::GetInstance()->GetPosition(x, y);
    EXPECT_EQ(x, 320);
    EXPECT_EQ(y, 240);
    
    asd::Core::Terminate();
}

//TEST(Mouse, CursorMode) {
//    char16_t s16[] = u"Mouse position";
//
//    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::CoreOption()));
//}
