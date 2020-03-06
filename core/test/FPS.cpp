#include <Core.h>
#include <Graphics/Graphics.h>
#include <gtest/gtest.h>
#include <Logger/Log.h>

TEST(FPS, Update) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::Configuration::Create()));

    auto instance = Altseed::Core::GetInstance();

    static const int loopCount = 50;

    instance->SetFramerateMode(Altseed::FramerateMode::Variable);

    instance->SetTargetFPS(10000000);
    Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    for (auto i = 0; i < loopCount; i++) {
        instance->DoEvent();
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
    }

    instance->SetTargetFPS(60);
    Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    for (auto i = 0; i < loopCount; i++) {
        instance->DoEvent();
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
    }

    instance->SetFramerateMode(Altseed::FramerateMode::Constant);
    instance->SetTargetFPS(60);
    Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    instance->DoEvent();

    for (auto i = 0; i < loopCount; i++) {
        instance->DoEvent();
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"ConstantFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(static_cast<int>(fps) <= 60);
    }

    Altseed::Core::Terminate();
}

TEST(FPS, WithGraphics) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::Configuration::Create()));

    auto instance = Altseed::Core::GetInstance();

    static const int loopCount = 50;

    instance->SetFramerateMode(Altseed::FramerateMode::Variable);

    instance->SetTargetFPS(100000);
    Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    for (auto i = 0; i < loopCount && instance->DoEvent(); i++) {
        EXPECT_TRUE(Altseed::Graphics::GetInstance()->BeginFrame());
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(Altseed::Graphics::GetInstance()->EndFrame());
    }

    instance->SetTargetFPS(60);
    Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    for (auto i = 0; i < loopCount && instance->DoEvent(); i++) {
        EXPECT_TRUE(Altseed::Graphics::GetInstance()->BeginFrame());
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(Altseed::Graphics::GetInstance()->EndFrame());
    }

    instance->SetFramerateMode(Altseed::FramerateMode::Constant);
    instance->SetTargetFPS(60);
    Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"TargetFPS: {0}", instance->GetTargetFPS());

    instance->DoEvent();

    for (auto i = 0; i < loopCount && instance->DoEvent(); i++) {
        EXPECT_TRUE(Altseed::Graphics::GetInstance()->BeginFrame());
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, u"ConstantFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(static_cast<int>(fps) <= 60);
        EXPECT_TRUE(Altseed::Graphics::GetInstance()->EndFrame());
    }

    Altseed::Core::Terminate();
}