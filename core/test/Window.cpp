#include <Core.h>
#include <Window/Window.h>
#include <gtest/gtest.h>

#include <string>

#include "TestHelper.h"

TEST(Window, Base) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Window);
    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 150, 150, config));

    int i = 0;
    while (Altseed2::Window::GetInstance()->DoEvent() && i < 16) {
        Altseed2::Window::GetInstance()->SetSize(150 + i / 2, 150 + i / 3);

        for (int l = 0; l < 10; l++) Altseed2::Window::GetInstance()->DoEvent();

        int32_t w, h;
        Altseed2::Window::GetInstance()->GetSize(w, h);

#ifdef __linux__
        ASSERT_NEAR(w, 150 + i / 2, 2);
        ASSERT_NEAR(h, 150 + i / 3, 2);
#else
        EXPECT_EQ(w, 150 + i / 2);
        EXPECT_EQ(h, 150 + i / 3);
#endif

        std::u16string title = u"Test";
        Altseed2::Window::GetInstance()->SetTitle(title.c_str());
        Altseed2::Window::GetInstance()->DoEvent();

        EXPECT_EQ(std::u16string(Altseed2::Window::GetInstance()->GetTitle()), title);

        i++;
    }

    Altseed2::Core::Terminate();
}
