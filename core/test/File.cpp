#include <Core.h>
#include <IO/File.h>
#include <gtest/gtest.h>
#include <zip.h>
#include <string>
#include <vector>
#include <thread>

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
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"testDir/test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"test dir/test.txt"));

    asd::File::GetInstance()->ClearRootDirectories();

    // pack file with password root
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackageWithPassword(u"TestData/IO/password.pack", u"altseed"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"全角　テスト.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"testDir/test.txt"));
    EXPECT_TRUE(asd::File::GetInstance()->Exists(u"test dir/test.txt"));

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
    asd::Resources::GetInstance()->Clear();

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

TEST(File, StreamFile) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));

    // pack files
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/pack/", u"TestData/IO/password.pack", u"altseed"));

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // create static file, and compare no-package and package without password
    asd::StreamFile* test = nullptr;
    EXPECT_NE(test = asd::File::GetInstance()->CreateStreamFile(u"TestData/IO/test.txt"), nullptr);
    EXPECT_FALSE(test->GetIsInPackage());
    asd::StreamFile* testPack = nullptr;
    EXPECT_NE(testPack = asd::File::GetInstance()->CreateStreamFile(u"test.txt"), nullptr);
    EXPECT_TRUE(testPack->GetIsInPackage());
    EXPECT_EQ(test->GetSize(), testPack->GetSize());
    EXPECT_EQ(test->GetTempBufferSize(), 0);
    EXPECT_EQ(testPack->GetTempBufferSize(), 0);
    for (size_t i = 0; i < test->GetSize(); i++) {
        EXPECT_EQ(test->Read(1), 1);
        EXPECT_EQ(testPack->Read(1), 1);
        EXPECT_EQ(test->GetTempBufferSize(), i + 1);
        EXPECT_EQ(testPack->GetTempBufferSize(), i + 1);
        EXPECT_EQ(test->GetTempBuffer(), test->GetTempBuffer());
    }

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackageWithPassword(u"TestData/IO/password.pack", u"altseed"));

    // cache test
    asd::StreamFile* testCache = nullptr;
    EXPECT_NE(testCache = asd::File::GetInstance()->CreateStreamFile(u"TestData/IO/test.txt"), nullptr);
    EXPECT_FALSE(testCache->GetIsInPackage());
    EXPECT_EQ(test, testCache);

    // clear cache
    asd::Resources::GetInstance()->Clear();

    asd::StreamFile* testPack2 = nullptr;
    EXPECT_NE(testPack2 = asd::File::GetInstance()->CreateStreamFile(u"test.txt"), nullptr);
    EXPECT_TRUE(testPack2->GetIsInPackage());
    EXPECT_NE(testPack, testPack2);
    EXPECT_NE(testPack->GetSize(), testPack2->GetSize());

    // create static file, and compare no-package and package with password
    asd::StreamFile* test3 = nullptr;
    EXPECT_NE(test3 = asd::File::GetInstance()->CreateStreamFile(u"TestData/IO/pack/test.txt"), nullptr);
    EXPECT_EQ(test3->GetSize(), testPack2->GetSize());
    EXPECT_EQ(test3->GetSize(), testPack2->GetSize());
    EXPECT_EQ(test3->GetTempBufferSize(), 0);
    EXPECT_EQ(testPack2->GetTempBufferSize(), 0);
    for (size_t i = 0; i < test3->GetSize(); i++) {
        EXPECT_EQ(test3->Read(1), 1);
        EXPECT_EQ(testPack2->Read(1), 1);
        EXPECT_EQ(test3->GetTempBufferSize(), i + 1);
        EXPECT_EQ(testPack2->GetTempBufferSize(), i + 1);
        EXPECT_EQ(test3->GetTempBuffer(), testPack2->GetTempBuffer());
    }

    asd::Core::Terminate();
}

TEST(File, Zenkaku) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));

    // pack files
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    asd::StaticFile* test1 = nullptr;
    asd::StaticFile* test2 = nullptr;
    asd::StaticFile* testPack1 = nullptr;
    asd::StaticFile* testPack2 = nullptr;

    test1 = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/全角 テスト.txt");
    test2 = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/全角　テスト.txt");
    testPack1 = asd::File::GetInstance()->CreateStaticFile(u"全角 テスト.txt");
    testPack2 = asd::File::GetInstance()->CreateStaticFile(u"全角　テスト.txt");

    EXPECT_NE(test1, nullptr);
    EXPECT_NE(test2, nullptr);
    EXPECT_NE(testPack1, nullptr);
    EXPECT_NE(testPack2, nullptr);

    EXPECT_NE(test1->GetBuffer(), asd::Int8Array());
    EXPECT_NE(test2->GetBuffer(), asd::Int8Array());
    EXPECT_NE(testPack1->GetBuffer(), asd::Int8Array());
    EXPECT_NE(testPack2->GetBuffer(), asd::Int8Array());

    asd::Core::Terminate();
}

TEST(File, StaticFileAsync) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));

    // pack files
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // create static file, and compare no-package and package without password
    asd::StaticFile* test1 = nullptr;
    asd::StaticFile* test2 = nullptr;
    asd::StaticFile* test3 = nullptr;
    asd::StaticFile* test4 = nullptr;
    asd::StaticFile* testCache = nullptr;
    asd::StaticFile* testPack1 = nullptr;
    asd::StaticFile* testPack2 = nullptr;
    asd::StaticFile* testPack3 = nullptr;
    asd::StaticFile* testPack4 = nullptr;
    asd::StaticFile* testPackCache = nullptr;

    std::thread thread1([&]() -> void {
        test1 = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/test.txt");
        test3 = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/全角 テスト.txt");
        testPack1 = asd::File::GetInstance()->CreateStaticFile(u"test.txt");
        testPack3 = asd::File::GetInstance()->CreateStaticFile(u"全角 テスト.txt");
        testCache = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/test.txt");
    });

    std::thread thread2([&]() -> void {
        test2 = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/space test.txt");
        test4 = asd::File::GetInstance()->CreateStaticFile(u"TestData/IO/全角　テスト.txt");
        testPack2 = asd::File::GetInstance()->CreateStaticFile(u"space test.txt");
        testPack4 = asd::File::GetInstance()->CreateStaticFile(u"全角　テスト.txt");
        testPackCache = asd::File::GetInstance()->CreateStaticFile(u"space test.txt");
    });

    thread1.join();
    thread2.join();

    EXPECT_NE(test1, nullptr);
    EXPECT_NE(test2, nullptr);
    EXPECT_NE(test3, nullptr);
    EXPECT_NE(test4, nullptr);
    EXPECT_NE(testCache, nullptr);
    EXPECT_NE(testPack1, nullptr);
    EXPECT_NE(testPack2, nullptr);
    EXPECT_NE(testPack3, nullptr);
    EXPECT_NE(testPack4, nullptr);
    EXPECT_NE(testPackCache, nullptr);

    EXPECT_EQ(testCache, test1);
    EXPECT_EQ(testPackCache, testPack2);

    EXPECT_EQ(test1->GetBuffer(), testPack1->GetBuffer());
    EXPECT_EQ(test2->GetBuffer(), testPack2->GetBuffer());
    EXPECT_EQ(test3->GetBuffer(), testPack3->GetBuffer());
    EXPECT_EQ(test4->GetBuffer(), testPack4->GetBuffer());

    asd::Core::Terminate();
}