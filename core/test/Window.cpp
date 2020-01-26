#include <Core.h>
#include <Window/Window.h>
#include <gtest/gtest.h>
#include <string>

TEST(Window, Base) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 150, 150, Altseed::CoreOption()));

    int i = 0;
    while (Altseed::Window::GetInstance()->DoEvent() && i < 16) {
        Altseed::Window::GetInstance()->SetSize(150 + i / 2, 150 + i / 3);

        for (int l = 0; l < 10; l++) Altseed::Window::GetInstance()->DoEvent();

        int32_t w, h;
        Altseed::Window::GetInstance()->GetSize(w, h);

#ifdef __linux__
        ASSERT_NEAR(w, 150 + i / 2, 2);
        ASSERT_NEAR(h, 150 + i / 3, 2);
#else
        EXPECT_EQ(w, 150 + i / 2);
        EXPECT_EQ(h, 150 + i / 3);
#endif

        std::u16string title = u"Test";
        Altseed::Window::GetInstance()->SetTitle(title.c_str());
        Altseed::Window::GetInstance()->DoEvent();

        EXPECT_EQ(std::u16string(Altseed::Window::GetInstance()->GetTitle()), title);

        i++;
    }

    Altseed::Core::Terminate();
}
