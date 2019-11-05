#include <Core.h>
#include <Graphics/Texture2D.h>
#include <IO/File.h>
#include <gtest/gtest.h>
#include <string>
#include <thread>

namespace asd = altseed;

TEST(Texture2D, Base) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));

    // pack files
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // load texture, and compare no-package and package without password
    asd::Texture2D* testPng = nullptr;
    EXPECT_NE(testPng = asd::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    asd::Texture2D* testPngPack = nullptr;
    EXPECT_NE(testPngPack = asd::Texture2D::Load(u"AltseedPink.png"), nullptr);
    EXPECT_EQ(testPng->GetSize().X, testPngPack->GetSize().X);
    asd::Texture2D* testJpg = nullptr;
    EXPECT_NE(testJpg = asd::Texture2D::Load(u"TestData/IO/AltseedPink.jpg"), nullptr);
    asd::Texture2D* testJpgPack = nullptr;
    EXPECT_NE(testJpgPack = asd::Texture2D::Load(u"AltseedPink.jpg"), nullptr);
    EXPECT_EQ(testJpg->GetSize().X, testJpgPack->GetSize().X);
    asd::Texture2D* testGif = nullptr;
    EXPECT_NE(testGif = asd::Texture2D::Load(u"TestData/IO/AltseedPink.gif"), nullptr);
    asd::Texture2D* testGifPack = nullptr;
    EXPECT_NE(testGifPack = asd::Texture2D::Load(u"AltseedPink.gif"), nullptr);
    EXPECT_EQ(testGif->GetSize().X, testGifPack->GetSize().X);
    asd::Texture2D* nonImage = nullptr;
    EXPECT_EQ(nonImage = asd::Texture2D::Load(u"test.txt"), nullptr);
    asd::Texture2D* notExist = nullptr;
    EXPECT_EQ(notExist = asd::Texture2D::Load(u"not_exsist.png"), nullptr);

    // cache test
    asd::Texture2D* testCache = nullptr;
    EXPECT_NE(testCache = asd::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    EXPECT_EQ(testPng, testCache);

    asd::Core::Terminate();
}

TEST(Texture2D, Async) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));

    // pack files
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    asd::Texture2D* test1 = nullptr;
    asd::Texture2D* test2 = nullptr;
    asd::Texture2D* test3 = nullptr;
    asd::Texture2D* testCache = nullptr;
    asd::Texture2D* testPack1 = nullptr;
    asd::Texture2D* testPack2 = nullptr;
    asd::Texture2D* testPack3 = nullptr;
    asd::Texture2D* testPackCache = nullptr;

    std::thread thread1([&]() -> void {
        test1 = asd::Texture2D::Load(u"TestData/IO/AltseedPink.png");
        test3 = asd::Texture2D::Load(u"TestData/IO/AltseedPink.gif");
        testPack1 = asd::Texture2D::Load(u"AltseedPink.png");
        testPack3 = asd::Texture2D::Load(u"AltseedPink.gif");
        testCache = asd::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    });

    std::thread thread2([&]() -> void {
        test2 = asd::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");
        testPack2 = asd::Texture2D::Load(u"AltseedPink.gif");
        testPackCache = asd::Texture2D::Load(u"AltseedPink.png");
    });

    thread1.join();
    thread2.join();

	EXPECT_NE(test1, nullptr);
    EXPECT_NE(test2, nullptr);
    EXPECT_NE(test3, nullptr);
    EXPECT_NE(testCache, nullptr);
    EXPECT_NE(testPack1, nullptr);
    EXPECT_NE(testPack2, nullptr);
    EXPECT_NE(testPack3, nullptr);
    EXPECT_NE(testPackCache, nullptr);

	EXPECT_EQ(testCache, test1);
    EXPECT_EQ(testPackCache, testPack1);

    asd::Core::Terminate();
}