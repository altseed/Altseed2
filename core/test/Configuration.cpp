#include <Configuration.h>
#include <Core.h>
#include <Graphics/CommandList.h>
#include <Graphics/Renderer/CullingSystem.h>
#include <Graphics/Renderer/RenderedSprite.h>
#include <Graphics/Renderer/Renderer.h>
#include <gtest/gtest.h>

#include "TestHelper.h"

TEST(Configuration, Initialize) {
    auto config = Altseed2::Configuration::Create();
    EXPECT_EQ(config->GetIsFullscreen(), false);
    EXPECT_EQ(config->GetIsResizable(), false);
    EXPECT_EQ(config->GetConsoleLoggingEnabled(), false);
    EXPECT_EQ(config->GetFileLoggingEnabled(), false);
    EXPECT_EQ(config->GetEnabledCoreModules(), Altseed2::CoreModules::Default);
    EXPECT_EQ(std::u16string(config->GetLogFileName()), u"Log.txt");
    EXPECT_EQ(std::u16string(config->GetToolSettingFileName()), u"imgui.ini");

    auto coreModuels = Altseed2::CoreModules::Graphics;

    // config->SetIsFullscreen(true);
    config->SetIsResizable(true);
    config->SetConsoleLoggingEnabled(true);
    config->SetFileLoggingEnabled(true);
    config->SetEnabledCoreModules(coreModuels);
    config->SetLogFileName(u"Log-configtest.txt");
    config->SetToolSettingFileName(u"toolsettinggilename-configtest.ini");

    // EXPECT_EQ(config->GetIsFullscreen(), true);
    EXPECT_EQ(config->GetIsResizable(), true);
    EXPECT_EQ(config->GetConsoleLoggingEnabled(), true);
    EXPECT_EQ(config->GetFileLoggingEnabled(), true);
    EXPECT_EQ(config->GetEnabledCoreModules(), coreModuels);
    EXPECT_EQ(std::u16string(config->GetLogFileName()), u"Log-configtest.txt");
    EXPECT_EQ(std::u16string(config->GetToolSettingFileName()), u"toolsettinggilename-configtest.ini");

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    Altseed2::Core::Terminate();
}

TEST(Configuration, GraphicsOnly) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    auto s2 = Altseed2::RenderedSprite::Create();

    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 128, 128));

    auto trans = Altseed2::Matrix44F();
    trans.SetTranslation(200, 200, 0);
    s2->SetTexture(t2);
    s2->SetTransform(trans);
    s2->SetSrc(Altseed2::RectF(128, 128, 256, 256));

    while (count++ < 10 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->DrawSprite(s2);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take screenshot
        if (count == 5) {
            // Altseed2::Graphics::GetInstance()->TakeScreenshot(u"SpriteTexture.png");
        }
    }

    Altseed2::Core::Terminate();
}