#include <Core.h>
#include <gtest/gtest.h>

TEST(Core, Initialize) {
    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, Altseed2::Configuration::Create()));
    Altseed2::Core::Terminate();
}
