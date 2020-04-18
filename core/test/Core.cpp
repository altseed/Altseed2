#include <Core.h>
#include <gtest/gtest.h>

TEST(Core, Initialize) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::Configuration::Create()));
    Altseed::Core::Terminate();
}
