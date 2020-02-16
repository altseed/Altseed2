#include <Common/StringHelper.h>
#include <Logger/Log.h>
#include <gtest/gtest.h>

static const auto log_filename = u"Log_test.txt";

TEST(Log, Initialize) {
    EXPECT_TRUE(Altseed::Log::Initialize(log_filename));
    Altseed::Log::Terminate();
}

TEST(Log, null) {
    EXPECT_TRUE(Altseed::Log::Initialize(nullptr));
    Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::Core, u"Hello, world");
    Altseed::Log::Terminate();
}

TEST(Log, Write) {
    EXPECT_TRUE(Altseed::Log::Initialize(log_filename));

    const auto categories = {
        Altseed::LogCategory::Core,
        Altseed::LogCategory::Engine,
        Altseed::LogCategory::User,
    };

    const auto levels = {
        Altseed::LogLevel::Trace,
        Altseed::LogLevel::Debug,
        Altseed::LogLevel::Info,
        Altseed::LogLevel::Warning,
        Altseed::LogLevel::Error,
        Altseed::LogLevel::Critical,
        Altseed::LogLevel::Off,
    };

    for (const auto category : categories) {
        for (const auto level : levels) {
            Altseed::Log::GetInstance()->Write(
                category,
                level,
                u"caetgory:{0}, level:{1}, nyan:{2}, にゃーん:{3}",
                static_cast<int>(category),
                static_cast<int>(level),
                "nyan",
                "にゃーん");
        }
    }

    Altseed::Log::Terminate();
}
