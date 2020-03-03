#include <Core.h>
#include <gtest/gtest.h>
#include <Logger/Log.h>

TEST(FPS, Update) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::Configuration::Create()));

    auto instance = Altseed::Core::GetInstance();

    static const int loopCount = 50;

    for (auto i = 0; i < loopCount; i++) {
        instance->DoEvent();
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::Core, u"VariableFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
    }

    instance->SetFramerateMode(Altseed::FramerateMode::Constant);
    instance->SetTargetFPS(60);

    for (auto i = 0; i < loopCount; i++) {
        instance->DoEvent();
        auto delta = instance->GetDeltaSecond();
        auto fps = instance->GetCurrentFPS();
        Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::Core, u"ConstantFPS: 'DeltaSecond:{0}, FPS:{1}'", delta, fps);
        EXPECT_TRUE(static_cast<int>(fps) <= 60);
    }

    Altseed::Core::Terminate();
}