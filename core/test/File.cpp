#include <Core.h>
#include <IO/File.h>
#include <Platform/FileSystem.h>
#include <gtest/gtest.h>
#include <zip.h>

#include <string>
#include <thread>
#include <vector>

#include "TestHelper.h"

TEST(File, FileRoot) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::File);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    // pack files
    EXPECT_TRUE(Altseed2::File::GetInstance()->Pack(u"TestData/IO/pack/", u"TestData/IO/pack.pack"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->PackWithPassword(u"TestData/IO/pack/", u"TestData/IO/password.pack", u"altseed"));

    // default root
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"TestData/IO/test.txt"));

    // absolute path
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(Altseed2::FileSystem::GetAbusolutePath(u"TestData/IO/test.txt").c_str()));

    // add directory root
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootDirectory(u"TestData/IO/root/"));

    // directory root
    EXPECT_FALSE(Altseed2::File::GetInstance()->Exists(u"test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"全角　テスト.txt"));

    // clear root
    Altseed2::File::GetInstance()->ClearRootDirectories();
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"TestData/IO/test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"TestData/IO/../IO/test.txt"));
    EXPECT_FALSE(Altseed2::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_FALSE(Altseed2::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_FALSE(Altseed2::File::GetInstance()->Exists(u"全角　テスト.txt"));

    // pack file root
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"全角　テスト.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"testDir/test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"test dir/test.txt"));

    Altseed2::File::GetInstance()->ClearRootDirectories();

    // pack file with password root
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackageWithPassword(u"TestData/IO/password.pack", u"altseed"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"space test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"全角 テスト.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"全角　テスト.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"testDir/test.txt"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->Exists(u"test dir/test.txt"));

    Altseed2::Core::Terminate();
}

TEST(File, StaticFile) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::File);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    // pack files
    EXPECT_TRUE(Altseed2::File::GetInstance()->Pack(u"TestData/IO", u"TestData/IO/pack.pack"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->PackWithPassword(u"TestData/IO/pack/", u"TestData/IO/password.pack", u"altseed"));

    // add package
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // create static file, and compare no-package and package without password
    std::shared_ptr<Altseed2::StaticFile> test = nullptr;
    EXPECT_NE(test = Altseed2::StaticFile::Create(u"TestData/IO/test.txt"), nullptr);
    EXPECT_FALSE(test->GetIsInPackage());
    std::shared_ptr<Altseed2::StaticFile> testPack = nullptr;
    EXPECT_NE(testPack = Altseed2::StaticFile::Create(u"test.txt"), nullptr);
    EXPECT_TRUE(testPack->GetIsInPackage());
    EXPECT_EQ(test->GetSize(), testPack->GetSize());
    EXPECT_EQ(test->GetBuffer()->GetVector(), testPack->GetBuffer()->GetVector());

    // add package
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackageWithPassword(u"TestData/IO/password.pack", u"altseed"));

    // cache test
    std::shared_ptr<Altseed2::StaticFile> testCache = nullptr;
    EXPECT_NE(testCache = Altseed2::StaticFile::Create(u"TestData/IO/test.txt"), nullptr);
    EXPECT_FALSE(testCache->GetIsInPackage());
    EXPECT_EQ(test, testCache);

    // clear cache
    Altseed2::Resources::GetInstance()->Clear();

    std::shared_ptr<Altseed2::StaticFile> testPack2 = nullptr;
    EXPECT_NE(testPack2 = Altseed2::StaticFile::Create(u"test.txt"), nullptr);
    EXPECT_TRUE(testPack2->GetIsInPackage());
    EXPECT_NE(testPack, testPack2);
    EXPECT_NE(testPack->GetSize(), testPack2->GetSize());
    EXPECT_NE(testPack->GetBuffer()->GetVector(), testPack2->GetBuffer()->GetVector());

    // create static file, and compare no-package and package with password
    std::shared_ptr<Altseed2::StaticFile> test3 = nullptr;
    EXPECT_NE(test3 = Altseed2::StaticFile::Create(u"TestData/IO/pack/test.txt"), nullptr);
    EXPECT_EQ(test3->GetSize(), testPack2->GetSize());
    EXPECT_EQ(test3->GetBuffer()->GetVector(), testPack2->GetBuffer()->GetVector());

    Altseed2::Core::Terminate();
}

TEST(File, StreamFile) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::File);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    // pack files
    EXPECT_TRUE(Altseed2::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));
    EXPECT_TRUE(Altseed2::File::GetInstance()->PackWithPassword(u"TestData/IO/pack/", u"TestData/IO/password.pack", u"altseed"));

    // add package
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // create static file, and compare no-package and package without password
    std::shared_ptr<Altseed2::StreamFile> test = nullptr;
    EXPECT_NE(test = Altseed2::StreamFile::Create(u"TestData/IO/test.txt"), nullptr);
    EXPECT_FALSE(test->GetIsInPackage());
    std::shared_ptr<Altseed2::StreamFile> testPack = nullptr;
    EXPECT_NE(testPack = Altseed2::StreamFile::Create(u"test.txt"), nullptr);
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
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackageWithPassword(u"TestData/IO/password.pack", u"altseed"));

    // cache test
    std::shared_ptr<Altseed2::StreamFile> testCache = nullptr;
    EXPECT_NE(testCache = Altseed2::StreamFile::Create(u"TestData/IO/test.txt"), nullptr);
    EXPECT_FALSE(testCache->GetIsInPackage());
    EXPECT_EQ(test, testCache);

    // clear cache
    Altseed2::Resources::GetInstance()->Clear();

    std::shared_ptr<Altseed2::StreamFile> testPack2 = nullptr;
    EXPECT_NE(testPack2 = Altseed2::StreamFile::Create(u"test.txt"), nullptr);
    EXPECT_TRUE(testPack2->GetIsInPackage());
    EXPECT_NE(testPack, testPack2);
    EXPECT_NE(testPack->GetSize(), testPack2->GetSize());

    // create static file, and compare no-package and package with password
    std::shared_ptr<Altseed2::StreamFile> test3 = nullptr;
    EXPECT_NE(test3 = Altseed2::StreamFile::Create(u"TestData/IO/pack/test.txt"), nullptr);
    EXPECT_EQ(test3->GetSize(), testPack2->GetSize());
    EXPECT_EQ(test3->GetSize(), testPack2->GetSize());
    EXPECT_EQ(test3->GetTempBufferSize(), 0);
    EXPECT_EQ(testPack2->GetTempBufferSize(), 0);
    for (size_t i = 0; i < test3->GetSize(); i++) {
        EXPECT_EQ(test3->Read(1), 1);
        EXPECT_EQ(testPack2->Read(1), 1);
        EXPECT_EQ(test3->GetTempBufferSize(), i + 1);
        EXPECT_EQ(testPack2->GetTempBufferSize(), i + 1);
        EXPECT_EQ(test3->GetTempBuffer()->GetVector(), testPack2->GetTempBuffer()->GetVector());
    }

    Altseed2::Core::Terminate();
}

TEST(File, Zenkaku) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::File);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    // pack files
    EXPECT_TRUE(Altseed2::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    std::shared_ptr<Altseed2::StaticFile> test1 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> test2 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> testPack1 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> testPack2 = nullptr;

    test1 = Altseed2::StaticFile::Create(u"TestData/IO/全角 テスト.txt");
    test2 = Altseed2::StaticFile::Create(u"TestData/IO/全角　テスト.txt");
    testPack1 = Altseed2::StaticFile::Create(u"全角 テスト.txt");
    testPack2 = Altseed2::StaticFile::Create(u"全角　テスト.txt");

    EXPECT_NE(test1, nullptr);
    EXPECT_NE(test2, nullptr);
    EXPECT_NE(testPack1, nullptr);
    EXPECT_NE(testPack2, nullptr);

    EXPECT_NE(test1->GetBuffer()->GetCount(), 0);
    EXPECT_NE(test2->GetBuffer()->GetCount(), 0);
    EXPECT_NE(testPack1->GetBuffer()->GetCount(), 0);
    EXPECT_NE(testPack2->GetBuffer()->GetCount(), 0);

    Altseed2::Core::Terminate();
}

TEST(File, StaticFileAsync) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::File);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    // pack files
    EXPECT_TRUE(Altseed2::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // create static file, and compare no-package and package without password
    std::shared_ptr<Altseed2::StaticFile> test1 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> test2 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> test3 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> test4 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> testCache = nullptr;
    std::shared_ptr<Altseed2::StaticFile> testPack1 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> testPack2 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> testPack3 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> testPack4 = nullptr;
    std::shared_ptr<Altseed2::StaticFile> testPackCache = nullptr;

    std::thread thread1([&]() -> void {
        test1 = Altseed2::StaticFile::Create(u"TestData/IO/test.txt");
        test3 = Altseed2::StaticFile::Create(u"TestData/IO/全角 テスト.txt");
        testPack1 = Altseed2::StaticFile::Create(u"test.txt");
        testPack3 = Altseed2::StaticFile::Create(u"全角 テスト.txt");
        testCache = Altseed2::StaticFile::Create(u"TestData/IO/test.txt");
    });

    std::thread thread2([&]() -> void {
        test2 = Altseed2::StaticFile::Create(u"TestData/IO/space test.txt");
        test4 = Altseed2::StaticFile::Create(u"TestData/IO/全角　テスト.txt");
        testPack2 = Altseed2::StaticFile::Create(u"space test.txt");
        testPack4 = Altseed2::StaticFile::Create(u"全角　テスト.txt");
        testPackCache = Altseed2::StaticFile::Create(u"space test.txt");
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

    // test1->GetBuffer() == testPack1->GetBuffer();
    EXPECT_EQ(test1->GetBuffer()->GetVector(), testPack1->GetBuffer()->GetVector());
    EXPECT_EQ(test2->GetBuffer()->GetVector(), testPack2->GetBuffer()->GetVector());
    EXPECT_EQ(test3->GetBuffer()->GetVector(), testPack3->GetBuffer()->GetVector());
    EXPECT_EQ(test4->GetBuffer()->GetVector(), testPack4->GetBuffer()->GetVector());

    Altseed2::Core::Terminate();
}