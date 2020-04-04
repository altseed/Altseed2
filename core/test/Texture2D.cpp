#include <Core.h>
#include <Graphics/Texture2D.h>
#include <IO/File.h>
#include <gtest/gtest.h>

#include <chrono>
#include <string>
#include <thread>

#include "Graphics/Graphics.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/Renderer.h"
#include "Logger/Log.h"

TEST(Texture2D, Base) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::Configuration::Create()));

    // pack files
    EXPECT_TRUE(Altseed::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(Altseed::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // load texture, and compare no-package and package without password
    std::shared_ptr<Altseed::Texture2D> testPng = nullptr;
    EXPECT_NE(testPng = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    std::shared_ptr<Altseed::Texture2D> testPngPack = nullptr;
    EXPECT_NE(testPngPack = Altseed::Texture2D::Load(u"AltseedPink.png"), nullptr);
    EXPECT_EQ(testPng->GetSize().X, testPngPack->GetSize().X);
    std::shared_ptr<Altseed::Texture2D> testJpg = nullptr;
    EXPECT_NE(testJpg = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.jpg"), nullptr);
    std::shared_ptr<Altseed::Texture2D> testJpgPack = nullptr;
    EXPECT_NE(testJpgPack = Altseed::Texture2D::Load(u"AltseedPink.jpg"), nullptr);
    EXPECT_EQ(testJpg->GetSize().X, testJpgPack->GetSize().X);
    std::shared_ptr<Altseed::Texture2D> testGif = nullptr;
    EXPECT_NE(testGif = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.gif"), nullptr);
    std::shared_ptr<Altseed::Texture2D> testGifPack = nullptr;
    EXPECT_NE(testGifPack = Altseed::Texture2D::Load(u"AltseedPink.gif"), nullptr);
    EXPECT_EQ(testGif->GetSize().X, testGifPack->GetSize().X);
    std::shared_ptr<Altseed::Texture2D> nonImage = nullptr;
    EXPECT_EQ(nonImage = Altseed::Texture2D::Load(u"test.txt"), nullptr);
    std::shared_ptr<Altseed::Texture2D> notExist = nullptr;
    EXPECT_EQ(notExist = Altseed::Texture2D::Load(u"not_exsist.png"), nullptr);

    // cache test
    std::shared_ptr<Altseed::Texture2D> testCache = nullptr;
    EXPECT_NE(testCache = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    EXPECT_EQ(testPng, testCache);

    Altseed::Core::Terminate();
}

TEST(Texture2D, Async) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::Configuration::Create()));

    // pack files
    EXPECT_TRUE(Altseed::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(Altseed::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    std::shared_ptr<Altseed::Texture2D> test1 = nullptr;
    std::shared_ptr<Altseed::Texture2D> test2 = nullptr;
    std::shared_ptr<Altseed::Texture2D> test3 = nullptr;
    std::shared_ptr<Altseed::Texture2D> testCache = nullptr;
    std::shared_ptr<Altseed::Texture2D> testPack1 = nullptr;
    std::shared_ptr<Altseed::Texture2D> testPack2 = nullptr;
    std::shared_ptr<Altseed::Texture2D> testPack3 = nullptr;
    std::shared_ptr<Altseed::Texture2D> testPackCache = nullptr;

    std::thread thread1([&]() -> void {
        test1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
        test3 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.gif");
        testPack1 = Altseed::Texture2D::Load(u"AltseedPink.png");
        testPack3 = Altseed::Texture2D::Load(u"AltseedPink.gif");
        testCache = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    });

    std::thread thread2([&]() -> void {
        test2 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");
        testPack2 = Altseed::Texture2D::Load(u"AltseedPink.gif");
        testPackCache = Altseed::Texture2D::Load(u"AltseedPink.png");
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

    Altseed::Core::Terminate();
}

TEST(Texture2D, Save) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::Configuration::Create()));

    auto instance = Altseed::Graphics::GetInstance();

    std::shared_ptr<Altseed::Texture2D> test = nullptr;
    EXPECT_NE(test = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);

    test->Save(u"copy.png");

    std::shared_ptr<Altseed::Texture2D> copy = nullptr;
    EXPECT_NE(copy = Altseed::Texture2D::Load(u"copy.png"), nullptr);

    auto s1 = Altseed::RenderedSprite::Create();
    auto s2 = Altseed::RenderedSprite::Create();

    auto scale = Altseed::Matrix44F();
    scale.SetScale(0.5f, 0.5f, 0);

    s1->SetTexture(test);
    s1->SetTransform(scale);
    s1->SetSrc(Altseed::RectF(0, 0, test->GetSize().X, test->GetSize().Y));

    auto position = Altseed::Matrix44F();
    position.SetTranslation(200, 200, 0);
    s2->SetTexture(copy);
    s2->SetTransform(position * scale);
    s2->SetSrc(Altseed::RectF(0, 0, copy->GetSize().X, copy->GetSize().Y));

    int count = 0;
    while (count++ < 10 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->DrawSprite(s2);

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Texture2D, Cache) {
    auto config = Altseed::Configuration::Create();
    config->SetFileLoggingEnabled(true);
    config->SetLogFileName(u"cache.txt"); 
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, config));

    auto start = std::chrono::system_clock::now();  // 計測開始時間
    std::shared_ptr<Altseed::Texture2D> testPng = nullptr;
    EXPECT_NE(testPng = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    auto end = std::chrono::system_clock::now();  // 計測終了時間
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();  //処理に要した時間をミリ秒に変換

    // cache test
    auto start2 = std::chrono::system_clock::now();
    std::shared_ptr<Altseed::Texture2D> testCache = nullptr;
    EXPECT_NE(testCache = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    auto end2 = std::chrono::system_clock::now();  // 計測終了時間
    EXPECT_EQ(testPng, testCache);
    int elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();  //処理に要した時間をミリ秒に変換

    Altseed::Log::GetInstance()->Write(
            Altseed::LogCategory::Core, Altseed::LogLevel::Info, u"{0}, {1}", static_cast<int>(elapsed), static_cast<int>(elapsed2));

    Altseed::Core::Terminate();
}