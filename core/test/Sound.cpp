#include <Core.h>
#include <Sound/SoundMixer.h>
#include <Sound/Sound.h>
#include <gtest/gtest.h>
#include <string>
#define STR(var) #var

using namespace std::string_literals;

namespace asd = altseed;

TEST(Sound, Initialize) {
    
    char16_t s16[] = u"test";

    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::CoreOption()));
    
    int i = 0;
    
    while (asd::Core::DoEvent())
    {
    }

    asd::Core::Terminate();
}