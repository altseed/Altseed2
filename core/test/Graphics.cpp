#include <gtest/gtest.h>

#include <memory>

#include <Core.h>
#include "Graphics/Sprite.h"

namespace asd = altseed;

TEST(Grapgics, Initialize) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 1280, 720, asd::CoreOption()));

    int count = 0;

    auto t1 = altseed::Graphics::GetInstance()->CreateDameyTexture(0);
    auto t2 = altseed::Graphics::GetInstance()->CreateDameyTexture(255);

    auto s1 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(-0.5, -0.5), LLGI::Vec2F(0.3, 0.3), t1);
    auto s2 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(-0.5, 0.0), LLGI::Vec2F(0.3, 0.3), t2);
    auto s3 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(-0.5, 0.5), LLGI::Vec2F(0.3, 0.3), t1);
    auto s4 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(0.0, -0.5), LLGI::Vec2F(0.3, 0.3), t2);
    auto s5 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(0.0, 0.0), LLGI::Vec2F(0.3, 0.3), t1);
    auto s6 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(0.0, 0.5), LLGI::Vec2F(0.3, 0.3), t2);
    auto s7 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(0.5, -0.5), LLGI::Vec2F(0.3, 0.3), t1);
    auto s8 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(0.5, 0.0), LLGI::Vec2F(0.3, 0.3), t2);
    auto s9 = std::make_shared<altseed::Sprite>(LLGI::Vec2F(0.5, 0.5), LLGI::Vec2F(0.3, 0.3), t1);
    altseed::Graphics::GetInstance()->Sprites.push_back(s1);
    altseed::Graphics::GetInstance()->Sprites.push_back(s2);
    altseed::Graphics::GetInstance()->Sprites.push_back(s3);
    altseed::Graphics::GetInstance()->Sprites.push_back(s4);
    altseed::Graphics::GetInstance()->Sprites.push_back(s5);
    altseed::Graphics::GetInstance()->Sprites.push_back(s6);
    altseed::Graphics::GetInstance()->Sprites.push_back(s7);
    altseed::Graphics::GetInstance()->Sprites.push_back(s8);
    altseed::Graphics::GetInstance()->Sprites.push_back(s9);

    while (count++ < 1000) EXPECT_TRUE(altseed::Graphics::GetInstance()->Update());

    altseed::Graphics::Terminate();
}