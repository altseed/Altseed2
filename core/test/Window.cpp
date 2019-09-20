#include <Core.h>
#include <Window/Window.h>
#include <gtest/gtest.h>
#include <string>

namespace asd = altseed;

TEST(Window, Base) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 150, 150, asd::CoreOption()));

    int i = 0;
    while (asd::Window::GetInstance()->DoEvent() && i < 16) {
        asd::Window::GetInstance()->SetSize(150 + i / 2, 150 + i / 3);
        int32_t w, h;
        asd::Window::GetInstance()->GetSize(w, h);

#ifdef __linux__
        ASSERT_NEAR(w, 150 + i / 2, 2);
        ASSERT_NEAR(h, 150 + i / 3, 2);
#else
        EXPECT_EQ(w, 150 + i / 2);
        EXPECT_EQ(h, 150 + i / 3);
#endif

        std::u16string title = u"Test";
        asd::Window::GetInstance()->SetTitle(title.c_str());
        asd::Window::GetInstance()->DoEvent();

        EXPECT_EQ(std::u16string(asd::Window::GetInstance()->GetTitle()), title);

        i++;
    }

    asd::Core::Terminate();
}
