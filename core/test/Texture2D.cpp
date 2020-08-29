#include <Core.h>
#include <Graphics/Texture2D.h>
#include <IO/File.h>
#include <gtest/gtest.h>

#include <chrono>
#include <string>
#include <thread>

#include "Graphics/CommandList.h"
#include "Graphics/Graphics.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/Renderer.h"
#include "Logger/Log.h"
#include "TestHelper.h"

TEST(Texture2D, Base) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);
    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    // pack files
    EXPECT_TRUE(Altseed2::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // load texture, and compare no-package and package without password
    std::shared_ptr<Altseed2::Texture2D> testPng = nullptr;
    EXPECT_NE(testPng = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    std::shared_ptr<Altseed2::Texture2D> testPngPack = nullptr;
    EXPECT_NE(testPngPack = Altseed2::Texture2D::Load(u"AltseedPink.png"), nullptr);
    EXPECT_EQ(testPng->GetSize().X, testPngPack->GetSize().X);
    std::shared_ptr<Altseed2::Texture2D> testJpg = nullptr;
    EXPECT_NE(testJpg = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.jpg"), nullptr);
    std::shared_ptr<Altseed2::Texture2D> testJpgPack = nullptr;
    EXPECT_NE(testJpgPack = Altseed2::Texture2D::Load(u"AltseedPink.jpg"), nullptr);
    EXPECT_EQ(testJpg->GetSize().X, testJpgPack->GetSize().X);
    std::shared_ptr<Altseed2::Texture2D> testGif = nullptr;
    EXPECT_NE(testGif = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.gif"), nullptr);
    std::shared_ptr<Altseed2::Texture2D> testGifPack = nullptr;
    EXPECT_NE(testGifPack = Altseed2::Texture2D::Load(u"AltseedPink.gif"), nullptr);
    EXPECT_EQ(testGif->GetSize().X, testGifPack->GetSize().X);
    std::shared_ptr<Altseed2::Texture2D> nonImage = nullptr;
    EXPECT_EQ(nonImage = Altseed2::Texture2D::Load(u"test.txt"), nullptr);
    std::shared_ptr<Altseed2::Texture2D> notExist = nullptr;
    EXPECT_EQ(notExist = Altseed2::Texture2D::Load(u"not_exsist.png"), nullptr);

    // cache test
    std::shared_ptr<Altseed2::Texture2D> testCache = nullptr;
    EXPECT_NE(testCache = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    EXPECT_EQ(testPng, testCache);

    Altseed2::Core::Terminate();
}

TEST(Texture2D, Async) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    // pack files
    EXPECT_TRUE(Altseed2::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(Altseed2::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    std::shared_ptr<Altseed2::Texture2D> test1 = nullptr;
    std::shared_ptr<Altseed2::Texture2D> test2 = nullptr;
    std::shared_ptr<Altseed2::Texture2D> test3 = nullptr;
    std::shared_ptr<Altseed2::Texture2D> testCache = nullptr;
    std::shared_ptr<Altseed2::Texture2D> testPack1 = nullptr;
    std::shared_ptr<Altseed2::Texture2D> testPack2 = nullptr;
    std::shared_ptr<Altseed2::Texture2D> testPack3 = nullptr;
    std::shared_ptr<Altseed2::Texture2D> testPackCache = nullptr;

    std::thread thread1([&]() -> void {
        test1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
        test3 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.gif");
        testPack1 = Altseed2::Texture2D::Load(u"AltseedPink.png");
        testPack3 = Altseed2::Texture2D::Load(u"AltseedPink.gif");
        testCache = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    });

    std::thread thread2([&]() -> void {
        test2 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");
        testPack2 = Altseed2::Texture2D::Load(u"AltseedPink.gif");
        testPackCache = Altseed2::Texture2D::Load(u"AltseedPink.png");
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

    Altseed2::Core::Terminate();
}

TEST(Texture2D, Save) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    auto instance = Altseed2::Graphics::GetInstance();

    std::shared_ptr<Altseed2::Texture2D> test = nullptr;
    EXPECT_NE(test = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);

    test->Save(u"copy.png");

    std::shared_ptr<Altseed2::Texture2D> copy = nullptr;
    EXPECT_NE(copy = Altseed2::Texture2D::Load(u"copy.png"), nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    auto s2 = Altseed2::RenderedSprite::Create();

    auto scale = Altseed2::Matrix44F();
    scale.SetScale(0.5f, 0.5f, 0);

    s1->SetTexture(test);
    s1->SetTransform(scale);
    s1->SetSrc(Altseed2::RectF(0, 0, test->GetSize().X, test->GetSize().Y));

    auto position = Altseed2::Matrix44F();
    position.SetTranslation(200, 200, 0);
    s2->SetTexture(copy);
    s2->SetTransform(position * scale);
    s2->SetSrc(Altseed2::RectF(0, 0, copy->GetSize().X, copy->GetSize().Y));

    int count = 0;
    while (count++ < 10 && instance->DoEvents()) {
        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->DrawSprite(s2);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed2::Core::Terminate();
}

void* Texture2D_Cache_Func(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed2::Texture2D> cbg_ret = Altseed2::Texture2D::Load(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Texture2D>(cbg_ret);
}

TEST(Texture2D, Cache) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    config->SetFileLoggingEnabled(true);
    config->SetLogFileName(u"cache.txt");
    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    auto start = std::chrono::system_clock::now();  // 計測開始時間
    std::shared_ptr<Altseed2::Texture2D> testPng = Altseed2::CreateSharedPtr((Altseed2::Texture2D*)Texture2D_Cache_Func(u"TestData/IO/AltseedPink.png"));
    EXPECT_NE(testPng, nullptr);
    auto end = std::chrono::system_clock::now();  // 計測終了時間
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();  //処理に要した時間をミリ秒に変換

    // cache test
    auto start2 = std::chrono::system_clock::now();
    std::shared_ptr<Altseed2::Texture2D> testCache =
            Altseed2::CreateSharedPtr((Altseed2::Texture2D*)Texture2D_Cache_Func(u"TestData/IO/AltseedPink.png"));
    EXPECT_NE(testCache, nullptr);
    auto end2 = std::chrono::system_clock::now();  // 計測終了時間
    EXPECT_EQ(testPng, testCache);
    int elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();  //処理に要した時間をミリ秒に変換

    Altseed2::Log::GetInstance()->Write(
            Altseed2::LogCategory::Core, Altseed2::LogLevel::Info, u"{0}, {1}", static_cast<int>(elapsed), static_cast<int>(elapsed2));
    Altseed2::Log::GetInstance()->Write(
            Altseed2::LogCategory::Core, Altseed2::LogLevel::Info, u"{0}, {1}", (uintptr_t)testPng.get(), (uintptr_t)testCache.get());
    Altseed2::Core::Terminate();
}