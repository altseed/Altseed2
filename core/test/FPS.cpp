#include <Core.h>
#include <Graphics/CommandList.h>
#include <Graphics/Graphics.h>
#include <Logger/Log.h>
#include <gtest/gtest.h>

#include "TestHelper.h"

TEST(FPS, Update) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::None);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    auto instance = Altseed2::Core::GetInstance();

    static const int loopCount = 10;

    instance->SetFramerateMode(Altseed2::FramerateMode::Variable);

    instance->SetTargetFPS(10000000);
    Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    for (auto i = 0; i < loopCount; i++) {
        instance->DoEvent();
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
    }

    instance->SetTargetFPS(60);
    Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    for (auto i = 0; i < loopCount; i++) {
        instance->DoEvent();
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
    }

    instance->SetFramerateMode(Altseed2::FramerateMode::Constant);
    instance->SetTargetFPS(60);
    Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    instance->DoEvent();

    for (auto i = 0; i < loopCount; i++) {
        instance->DoEvent();
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"ConstantFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(static_cast<int>(fps) <= 60);
    }

    Altseed2::Core::Terminate();
}

TEST(FPS, WithGraphics) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    auto instance = Altseed2::Core::GetInstance();

    static const int loopCount = 50;

    instance->SetFramerateMode(Altseed2::FramerateMode::Variable);

    instance->SetTargetFPS(100000);
    Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    Altseed2::RenderPassParameter renderPassParameter;
    renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
    renderPassParameter.IsColorCleared = true;
    renderPassParameter.IsDepthCleared = true;

    for (auto i = 0; i < loopCount && instance->DoEvent(); i++) {
        EXPECT_TRUE(Altseed2::Graphics::GetInstance()->BeginFrame(renderPassParameter));
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(Altseed2::Graphics::GetInstance()->EndFrame());
    }

    instance->SetTargetFPS(60);
    Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    for (auto i = 0; i < loopCount && instance->DoEvent(); i++) {
        EXPECT_TRUE(Altseed2::Graphics::GetInstance()->BeginFrame(renderPassParameter));
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(Altseed2::Graphics::GetInstance()->EndFrame());
    }

    instance->SetFramerateMode(Altseed2::FramerateMode::Constant);
    instance->SetTargetFPS(60);
    Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    instance->DoEvent();

    for (auto i = 0; i < loopCount && instance->DoEvent(); i++) {
        EXPECT_TRUE(Altseed2::Graphics::GetInstance()->BeginFrame(renderPassParameter));
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, u"ConstantFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(static_cast<int>(fps) <= 60);
        EXPECT_TRUE(Altseed2::Graphics::GetInstance()->EndFrame());
    }

    Altseed2::Core::Terminate();
}