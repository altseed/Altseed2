#include <Configuration.h>
#include <Core.h>
#include <gtest/gtest.h>

TEST(Configuration, Initialize) {
    auto config = Altseed::Configuration::Create();
    EXPECT_EQ(config->GetIsFullscreen(), false);
    EXPECT_EQ(config->GetIsResizable(), false);
    EXPECT_EQ(config->GetConsoleLoggingEnabled(), true);
    EXPECT_EQ(std::u16string(config->GetLogFileName()), u"Log.txt");

    config->SetIsFullscreen(true);
    config->SetIsResizable(true);
    config->SetConsoleLoggingEnabled(false);
    config->SetLogFileName(u"Log-configtest.txt");

    EXPECT_EQ(config->GetIsFullscreen(), true);
    EXPECT_EQ(config->GetIsResizable(), true);
    EXPECT_EQ(config->GetConsoleLoggingEnabled(), false);
    EXPECT_EQ(std::u16string(config->GetLogFileName()), u"Log-configtest.txt");

    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, config));

    Altseed::Core::Terminate();
}