#include "Graphics/Graphics.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Graphics/Camera.h"
#include "Graphics/Sprite.h"

TEST(Graphics, Initialize) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"Initialize", 1280, 720, Altseed::CoreOption()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();
    EXPECT_TRUE(instance != nullptr);
    auto renderer = instance->CreateRenderer();
    EXPECT_TRUE(renderer != nullptr);

    auto t1 = instance->CreateDameyTexture(0);
    EXPECT_TRUE(t1 != nullptr);

    auto t2 = instance->CreateDameyTexture(255);
    EXPECT_TRUE(t2 != nullptr);

    auto shader = Altseed::ShaderCompiler::GetInstance()->Compile(renderer->HlslPSCode, Altseed::ShaderStageType::Pixel);
    EXPECT_TRUE(shader != nullptr);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    EXPECT_TRUE(material != nullptr);

    material->SetShader(shader);

    {
        int c = 0;
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                auto sprite = Altseed::MakeAsdShared<Altseed::Sprite>();
                sprite->SetMaterial(material);
                sprite->SetPosition(Altseed::Vector2DF(x * 120, y * 120));
                sprite->SetSize(Altseed::Vector2DF(80, 80));
                sprite->SetTexture(c++ % 2 == 0 ? t1 : t2);
                renderer->Sprites.push_back(sprite);
            }
        }
    }

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->StartFrame());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, Texture) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"Texture", 1280, 720, Altseed::CoreOption()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();
    auto renderer = instance->CreateRenderer();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    auto shader = Altseed::ShaderCompiler::GetInstance()->Compile(renderer->HlslPSCode, Altseed::ShaderStageType::Pixel);
    auto material = std::make_shared<Altseed::Material>();
    material->SetShader(shader);

    {
        int c = 0;
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                auto sprite = Altseed::MakeAsdShared<Altseed::Sprite>();
                sprite->SetMaterial(material);
                sprite->SetPosition(Altseed::Vector2DF(x * 120, y * 120));
                sprite->SetSize(Altseed::Vector2DF(80, 80));
                sprite->SetTexture(c++ % 2 == 0 ? t1->GetNativeTexture() : t2->GetNativeTexture());
                renderer->Sprites.push_back(sprite);
            }
        }
    }

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->StartFrame());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, Camera) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"Camera", 1280, 720, Altseed::CoreOption()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();
    auto renderer = instance->CreateRenderer();

    auto t1 = instance->CreateDameyTexture(0);
    auto t2 = instance->CreateDameyTexture(255);
    auto cam = Altseed::MakeAsdShared<Altseed::Camera>();
    auto rt = Altseed::CreateSharedPtr(new Altseed::RenderTexture(Altseed::Vector2DI(256, 256)));
    cam->SetTarget(rt);
    renderer->Cameras.push_back(cam);

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);
    EXPECT_TRUE(cam != nullptr);

    auto shader = Altseed::ShaderCompiler::GetInstance()->Compile(renderer->HlslPSCode, Altseed::ShaderStageType::Pixel);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    {
        int c = 0;
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                auto sprite = Altseed::MakeAsdShared<Altseed::Sprite>();
                sprite->SetMaterial(material);
                sprite->SetPosition(Altseed::Vector2DF(x * 120, y * 120));
                sprite->SetSize(Altseed::Vector2DF(80, 80));
                sprite->SetTexture(c++ % 2 == 0 ? t1 : t2);
                renderer->Sprites.push_back(sprite);
            }
        }
    }

    {
        auto sprite = Altseed::MakeAsdShared<Altseed::Sprite>();
        sprite->SetMaterial(material);
        sprite->SetPosition(Altseed::Vector2DF(900, 100));
        sprite->SetSize(Altseed::Vector2DF(256, 256));
        sprite->SetTexture(cam->GetTarget()->GetNativeTexture());
        renderer->Sprites.push_back(sprite);
    }

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->StartFrame());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}