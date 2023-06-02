#include <Platform/FileSystem.h>
#include <gtest/gtest.h>

TEST(FileSystem, Directory) {
    if (!Altseed2::FileSystem::GetIsDirectory(u"FileSystemTestDirectory")) {
        EXPECT_TRUE(Altseed2::FileSystem::CreateDirectory(u"FileSystemTestDirectory"));
    }

    if (!Altseed2::FileSystem::GetIsDirectory(u"TestData/FileSystemTestDirectory")) {
        EXPECT_TRUE(Altseed2::FileSystem::CreateDirectory(u"TestData/FileSystemTestDirectory"));
    }
}
