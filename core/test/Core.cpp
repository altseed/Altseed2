#include <gtest/gtest.h>
#include <Core.h>

TEST(Core, Initialize) {

	EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::CoreOption()));
    Altseed::Core::Terminate();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}