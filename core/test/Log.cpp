#include <Common/StringHelper.h>
#include <Configuration.h>
#include <Core.h>
#include <Logger/Log.h>
#include <gtest/gtest.h>

static const std::u16string log_filename = u"Log_test.txt";
static const auto bools = {true, false};

TEST(Log, Initialize) {
    for (const auto c : bools) {
        for (const auto f : bools) {
            EXPECT_TRUE(Altseed2::Log::Initialize(c, f, log_filename.c_str()));
            Altseed2::Log::GetInstance()->SetLevel(Altseed2::LogCategory::Core, Altseed2::LogLevel::Info);
            Altseed2::Log::GetInstance()->Info(Altseed2::LogCategory::Core, u"Hello, world");
            Altseed2::Log::Terminate();
        }
    }
}

TEST(Log, WriteWithConfiguration) {
    auto config = Altseed2::Configuration::Create();

    for (const auto c : bools) {
        for (const auto f : bools) {
            config->SetConsoleLoggingEnabled(c);
            config->SetFileLoggingEnabled(f);
            config->SetLogFileName(log_filename.c_str());
            EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));
            Altseed2::Log::GetInstance()->SetLevel(Altseed2::LogCategory::Core, Altseed2::LogLevel::Info);
            Altseed2::Log::GetInstance()->Info(Altseed2::LogCategory::Core, u"Hello, world");
            Altseed2::Core::Terminate();
        }
    }
}

TEST(Log, Write) {
    EXPECT_TRUE(Altseed2::Log::Initialize(true, true, log_filename.c_str()));

    const auto categories = {
            Altseed2::LogCategory::Core,
            Altseed2::LogCategory::Engine,
            Altseed2::LogCategory::User,
    };

    const auto levels = {
            Altseed2::LogLevel::Trace,
            Altseed2::LogLevel::Debug,
            Altseed2::LogLevel::Info,
            Altseed2::LogLevel::Warn,
            Altseed2::LogLevel::Error,
            Altseed2::LogLevel::Critical,
            Altseed2::LogLevel::Off,
    };

    for (const auto category : categories) {
        for (const auto level : levels) {
            Altseed2::Log::GetInstance()->Write(
                    category,
                    level,
                    u"caetgory:{0}, level:{1}, nyan:{2}, 日本語",
                    static_cast<int>(category),
                    static_cast<int>(level),
                    "nyan");
        }

        Altseed2::Log::GetInstance()->Trace(category, u"Trace Log");
        Altseed2::Log::GetInstance()->Debug(category, u"Debug Log");
        Altseed2::Log::GetInstance()->Info(category, u"Info Log");
        Altseed2::Log::GetInstance()->Warn(category, u"Warn Log");
        Altseed2::Log::GetInstance()->Error(category, u"Error Log");
        Altseed2::Log::GetInstance()->Critical(category, u"Critical Log");
    }

    Altseed2::Log::Terminate();
}