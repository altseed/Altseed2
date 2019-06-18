#include <Core.h>
#include <Input/Keyboard.h>
#include <gtest/gtest.h>
#include <string>
#define STR(var) #var

using namespace std::string_literals;

namespace asd = altseed;

TEST(Keyboard, Initialize) {
    
    char16_t s16[] = u"test";

    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::CoreOption()));
    
    int i = 0;
    
    while (i < (int)asd::Keys::MAX) {
        asd::Keyboard::GetInstance()->RefleshKeyStates();
        
        asd::ButtonState state = asd::Keyboard::GetInstance()->GetKeyState(static_cast<asd::Keys>(i));
        EXPECT_EQ(asd::ButtonState::Free, state);
        
        i ++;
    }

    asd::Core::Terminate();
}

TEST(Keyboard, GetKeyState) {
    
    char16_t s16[] = u"test";
    
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::CoreOption()));
    
    while(asd::Core::GetInstance()->DoEvent())
    {
        for(int i=0;i<static_cast<int>(asd::Keys::MAX);i++){
            auto bs = asd::Keyboard::GetInstance()->GetKeyState((asd::Keys)i);
            if (bs != asd::ButtonState::Free)
                std::cout << i;
        }
    }
    
    asd::Core::Terminate();
}
