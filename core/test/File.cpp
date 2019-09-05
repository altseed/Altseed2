#include <Core.h>
#include <IO/File.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace asd = altseed;

TEST(File, FileRoot) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));

    // pack files
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/pack/", u"TestData/IO/pack.pack"));
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/pack/", u"TestData/IO/password.pack", u"altseed"));

    // default root
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"TestData/IO/test.txt"));

    // add directory root
    EXPECT_TRUE(asd::File::GetInstance()->AddRootDirectory(u"TestData/IO/root/"));

    // directory root
    EXPECT_FALSE(asd::File::GetInstance()->Exists(u"test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"全角　テスト.txt"));

    // clear root
    asd::File::GetInstance()->ClearRootDirectories();
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"TestData/IO/test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"TestData/IO/../IO/test.txt"));
    EXPECT_FALSE(asd::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_FALSE(asd::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_FALSE(asd::File::GetInstance()->Exists(u"全角　テスト.txt"));

    // pack file root
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"全角　テスト.txt"));

    asd::File::GetInstance()->ClearRootDirectories();

    // pack file with password root
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackageWithPassword(u"TestData/IO/password.pack", u"altseed"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"全角　テスト.txt"));

    asd::Core::Terminate();
}

TEST(File, StaticFile) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));

    // pack files
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/password.pack", u"altseed"));

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // create static file, and compare no-package and package without password
    {
        asd::StaticFile* test = nullptr;
        EXPECT_NE(test = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/test.txt"), nullptr);
        asd::StaticFile* testPack = nullptr;
        EXPECT_NE(testPack = asd::File::GetInstance()->CreateStaticFile(u"test.txt"), nullptr);
        EXPECT_EQ(test->GetSize(), testPack->GetSize());
        EXPECT_EQ(test->GetBuffer(), testPack->GetBuffer());
    }

    asd::File::GetInstance()->ClearRootDirectories();

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackageWithPassword(u"TestData/IO/password.pack", u"altseed"));

    // create static file, and compare no-package and package with password
    {
        asd::StaticFile* test = nullptr;
        EXPECT_NE(test = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/test.txt"), nullptr);
        asd::StaticFile* testPack = nullptr;
        EXPECT_NE(testPack = asd::File::GetInstance()->CreateStaticFile(u"test.txt"), nullptr);
        EXPECT_EQ(test->GetSize(), testPack->GetSize());
        EXPECT_EQ(test->GetBuffer(), testPack->GetBuffer());
    }

    asd::Core::Terminate();
}