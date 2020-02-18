#include <Configuration.h>
#include <Core.h>
#include <gtest/gtest.h>

TEST(Configuration, Initialize) {
  auto config = Altseed::Configuration::Create();
  EXPECT_EQ(config->GetIsFullscreenMode(), false);
  EXPECT_EQ(config->GetIsResizable(), false);
  EXPECT_EQ(std::u16string(config->GetLogFilename()), u"Log.txt");

  config->SetIsFullscreenMode(true);
  config->SetIsResizable(true);
  config->SetLogFilename(u"Log-configtest.txt");

  EXPECT_EQ(config->GetIsFullscreenMode(), true);
  EXPECT_EQ(config->GetIsResizable(), true);
  EXPECT_EQ(std::u16string(config->GetLogFilename()), u"Log-configtest.txt");

  EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, config));

  Altseed::Core::Terminate();
}