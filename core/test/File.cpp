#include <Core.h>
#include <gtest/gtest.h>
#include <string>

namespace asd = altseed;

TEST(File, FileRoot) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));
	//TODO: FileRoot Unit Test
    asd::Core::Terminate();
}