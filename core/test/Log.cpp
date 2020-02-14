#include <Core.h>
#include <Logger/Log.h>
#include <gtest/gtest.h>
#include <string>

TEST(Log, Initialize) {
    EXPECT_TRUE(Altseed::Log::Initialize(u"Log.txt"));
    Altseed::Log::Terminate();
}

TEST(Log, Write) {
    EXPECT_TRUE(Altseed::Log::Initialize(u"Log.txt"));

    auto categories = {
        Altseed::LogCategory::Core,
        Altseed::LogCategory::Engine,
        Altseed::LogCategory::User,
    };

    auto levels = {
        Altseed::LogLevel::Trace,
        Altseed::LogLevel::Debug,
        Altseed::LogLevel::Info,
        Altseed::LogLevel::Warning,
        Altseed::LogLevel::Error,
        Altseed::LogLevel::Critical,
        //    Altseed::LogLevel::Off,
    };

    for(const auto category : categories)
    {
        Altseed::Log::GetInstance()->SetLevel(category, Altseed::LogLevel::Trace);
    }


    for (const auto category : categories) {
        for (const auto level : levels) {
            Altseed::Log::GetInstance()->Write(category, level, u"Sample, にゃおーん, 😆😆😆😆");
            Altseed::Log::GetInstance()->Write(category, level, u"Sample");
            Altseed::Log::GetInstance()->Write(category, level, u"caetgory:{0}, level:{1}, nyan:{2}, にゃーん:{3}", (int32_t)category, (int32_t)level, "nyan", "にゃーん");
        }
    }

    Altseed::Log::Terminate();
}