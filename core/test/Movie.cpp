#include <Core.h>
#include <Graphics/CommandList.h>
#include <Graphics/Graphics.h>
#include <Graphics/Renderer/CullingSystem.h>
#include <Graphics/Renderer/RenderedSprite.h>
#include <Graphics/Renderer/Renderer.h>
#include <Media/MediaPlayer.h>
#include <gtest/gtest.h>

#include <string>

#include "TestHelper.h"

TEST(Movie, Basic) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Movie.Basic", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::RenderTexture::Create({640, 480});

    auto s1 = Altseed2::RenderedSprite::Create();

    Altseed2::CullingSystem::GetInstance()->Register(s1);
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 640, 480));

    auto movie = Altseed2::MediaPlayer::Load(u"TestData/Movie/Test1.mp4");

    ASSERT_TRUE(t1 != nullptr);
    ASSERT_TRUE(movie != nullptr);

    movie->Play(false);

    while (count++ < 10 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        movie->WriteToTexture2D(t1);

        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Movie.Basic.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::Core::Terminate();
}
