#include <gtest/gtest.h>

#include <memory>

#include "Graphics/Graphics.h"
#include "Graphics/Sprite.h"

TEST(Grapgics, Initialize) {
    EXPECT_TRUE(altseed::Graphics::Intialize());

    int count = 0;

    auto s1 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(0.0, 0.0), LLGI::Vec2F(0.3, 0.3), nullptr);
    auto s2 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(-0.5, 0.0), LLGI::Vec2F(0.3, 0.3), nullptr);
    altseed::Graphics::GetInstance()->Sprites.push_back(s1);
    altseed::Graphics::GetInstance()->Sprites.push_back(s2);

    while (count++ < 1000) EXPECT_TRUE(altseed::Graphics::GetInstance()->Update());

    altseed::Graphics::Terminate();
}