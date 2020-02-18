#include <Common/StringHelper.h>
#include <Configuration.h>
#include <Core.h>
#include <Logger/Log.h>
#include <gtest/gtest.h>

static const std::u16string log_filename = u"Log_test.txt";
static const auto bools = {true, false};

TEST(Log, Initialize) {
    for (const auto c : bools) {
        for(const auto f : bools) {
            EXPECT_TRUE(Altseed::Log::Initialize(c, f, log_filename.c_str()));
            Altseed::Log::GetInstance()->SetLevel(Altseed::LogCategory::Core, Altseed::LogLevel::Info);
            Altseed::Log::GetInstance()->Info(Altseed::LogCategory::Core, u"Hello, world");
            Altseed::Log::Terminate();
        }
    }
}

TEST(Log, WriteWithConfiguration) {
    auto config = Altseed::Configuration::Create();

    for (const auto c : bools) {
        for(const auto f : bools) {
            config->SetEnabledConsoleLogging(c);
            config->SetEnabledFileLogging(f);
            config->SetLogFilename(log_filename.c_str());
            EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, config));
            Altseed::Log::GetInstance()->SetLevel(Altseed::LogCategory::Core, Altseed::LogLevel::Info);
            Altseed::Log::GetInstance()->Info(Altseed::LogCategory::Core, u"Hello, world");
            Altseed::Core::Terminate();
        }
    }
}

TEST(Log, Write) {
    EXPECT_TRUE(Altseed::Log::Initialize(true, true, log_filename.c_str()));

    const auto categories = {
            Altseed::LogCategory::Core,
            Altseed::LogCategory::Engine,
            Altseed::LogCategory::User,
    };

    const auto levels = {
            Altseed::LogLevel::Trace,
            Altseed::LogLevel::Debug,
            Altseed::LogLevel::Info,
            Altseed::LogLevel::Warn,
            Altseed::LogLevel::Error,
            Altseed::LogLevel::Critical,
            Altseed::LogLevel::Off,
    };

    for (const auto category : categories) {
        for (const auto level : levels) {
            Altseed::Log::GetInstance()->Write(category, level, u"caetgory:{0}, level:{1}, nyan:{2}, 日本語", static_cast<int>(category), static_cast<int>(level), "nyan");
        }

        Altseed::Log::GetInstance()->Trace(category, u"Trace Log");
        Altseed::Log::GetInstance()->Debug(category, u"Debug Log");
        Altseed::Log::GetInstance()->Info(category, u"Info Log");
        Altseed::Log::GetInstance()->Warn(category, u"Warn Log");
        Altseed::Log::GetInstance()->Error(category, u"Error Log");
        Altseed::Log::GetInstance()->Critical(category, u"Critical Log");
    }

    Altseed::Log::Terminate();
}