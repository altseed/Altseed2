#include <gtest/gtest.h>
#include <Core.h>

namespace asd = altseed;

TEST(Core, Initialize) {

	EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));
    asd::Core::Terminate();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}