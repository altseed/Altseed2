#include "Graphics/Graphics.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Graphics/BatchRenderer.h"
#include "Graphics/Camera.h"
#include "Graphics/CommandList.h"
#include "Graphics/Sprite.h"

TEST(Graphics, BasicBatchRender) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"BasicBatchRender", 1280, 720, Altseed::CoreOption()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    while (count++ < 100 && instance->DoEvents()) {

		EXPECT_TRUE(instance->BeginFrame());
        instance->GetCommandList()->SetViewProjectionWithWindowsSize(Altseed::Vector2DI(1280, 720));

        Altseed::BatchVertex v1[4];
        Altseed::BatchVertex v2[4];

        int ib[6];
        ib[0] = 0;
        ib[1] = 1;
        ib[2] = 2;
        ib[3] = 2;
        ib[4] = 3;
        ib[5] = 0;

        v1[0].Pos.X = 10;
        v1[0].Pos.Y = 10;
        v1[0].Pos.Z = 0.5f;
        v1[0].UV1.X = 0.0f;
        v1[0].UV1.Y = 0.0f;

        v1[1].Pos.X = 110;
        v1[1].Pos.Y = 10;
        v1[1].Pos.Z = 0.5f;
        v1[1].UV1.X = 1.0f;
        v1[1].UV1.Y = 0.0f;

        v1[2].Pos.X = 110;
        v1[2].Pos.Y = 110;
        v1[2].Pos.Z = 0.5f;
        v1[2].UV1.X = 1.0f;
        v1[2].UV1.Y = 1.0f;

        v1[3].Pos.X = 10;
        v1[3].Pos.Y = 110;
        v1[3].Pos.Z = 0.5f;
        v1[3].UV1.X = 0.0f;
        v1[3].UV1.Y = 1.0f;

        for (int i = 0; i < 4; i++) {
            v1[i].Col = Altseed::Color(255, 255, 255, 255);
        }

		instance->GetCommandList()->SetDefaultRenderTarget();
        instance->GetCommandList()->Draw(v1, ib, 4, 6, t1);

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

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
        EXPECT_TRUE(instance->BeginFrame());
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
        EXPECT_TRUE(instance->BeginFrame());
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
        EXPECT_TRUE(instance->BeginFrame());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}