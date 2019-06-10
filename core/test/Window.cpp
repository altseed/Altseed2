#include <Core.h>
#include <Window/Window.h>
#include <gtest/gtest.h>
#include <string>

namespace asd = altseed;

TEST(Window, Base) {
    EXPECT_TRUE(asd::Core::Initialize());

    int i = 0;
    while (asd::Window::GetInstance()->DoEvent() || i < 1000) {

        asd::Window::GetInstance()->SetSize(i / 2, i / 3);
        int32_t w, h;
        asd::Window::GetInstance()->GetSize(w, h);

        EXPECT_EQ(w, i / 2);
        EXPECT_EQ(h, i / 3);

        std::u16string title;
        title = i;
        asd::Window::GetInstance()->SetTitle(title.c_str());

        EXPECT_EQ(asd::Window::GetInstance()->GetTitle(), title);

        i++;
    }

    asd::Core::Terminate();
}