#include <gtest/gtest.h>

#include "Graphics/Graphics.h"

TEST(Grapgics, Initialize) {
    EXPECT_TRUE(altseed::Graphics::Intialize());

    int count = 0;
    while (count++ < 1000) EXPECT_TRUE(altseed::Graphics::GetInstance()->Update());

    altseed::Graphics::Terminate();
}