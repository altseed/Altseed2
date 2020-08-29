#include <Core.h>
#include <gtest/gtest.h>

#include "TestHelper.h"

TEST(Core, Initialize) {
    auto coreModules = Altseed2::CoreModules::Window | Altseed2::CoreModules::File | Altseed2::CoreModules::Keyboard | Altseed2::CoreModules::Mouse | Altseed2::CoreModules::Joystick | Altseed2::CoreModules::Joystick | Altseed2::CoreModules::Graphics;
    auto config = Altseed2TestConfig(coreModules);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));
    Altseed2::Core::Terminate();
}
