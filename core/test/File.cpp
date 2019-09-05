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
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/pack/", u"TestData/IO/password.pack", u"altseed"));

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // create static file, and compare no-package and package without password
    asd::StaticFile* test = nullptr;
    EXPECT_NE(test = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/test.txt"), nullptr);
    EXPECT_FALSE(test->GetIsInPackage());
    asd::StaticFile* testPack = nullptr;
    EXPECT_NE(testPack = asd::File::GetInstance()->CreateStaticFile(u"test.txt"), nullptr);
    EXPECT_TRUE(testPack->GetIsInPackage());
    EXPECT_EQ(test->GetSize(), testPack->GetSize());
    EXPECT_EQ(test->GetBuffer(), testPack->GetBuffer());

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackageWithPassword(u"TestData/IO/password.pack", u"altseed"));

    // cache test
    asd::StaticFile* testCache = nullptr;
    EXPECT_NE(testCache = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/test.txt"), nullptr);
    EXPECT_FALSE(testCache->GetIsInPackage());
    EXPECT_EQ(test, testCache);

    // clear cache
    asd::File::GetInstance()->ClearCache();

    asd::StaticFile* testPack2 = nullptr;
    EXPECT_NE(testPack2 = asd::File::GetInstance()->CreateStaticFile(u"test.txt"), nullptr);
    EXPECT_TRUE(testPack2->GetIsInPackage());
    EXPECT_NE(testPack, testPack2);
    EXPECT_NE(testPack->GetSize(), testPack2->GetSize());
    EXPECT_NE(testPack->GetBuffer(), testPack2->GetBuffer());

    // create static file, and compare no-package and package with password
    asd::StaticFile* test3 = nullptr;
    EXPECT_NE(test3 = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/pack/test.txt"), nullptr);
    EXPECT_EQ(test3->GetSize(), testPack2->GetSize());
    EXPECT_EQ(test3->GetBuffer(), testPack2->GetBuffer());

    asd::Core::Terminate();
}