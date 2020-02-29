#include "Graphics/Graphics.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Graphics/Camera.h"
#include "Graphics/CommandList.h"
#include "Graphics/Renderer/RenderedCamera.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "Tool/Tool.h"

TEST(Graphics, Initialize) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"Initialize", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();
    EXPECT_TRUE(instance != nullptr);

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, BasicPolygonTextureRender) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"BasicPolygonTextureRender", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

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

        Altseed::Renderer::GetInstance()->DrawPolygon(v1, ib, 4, 6, t1);

        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, PolygonTextureRenderWithVertexArray) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"PolygonTextureRenderWithVertexArray", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");

    EXPECT_TRUE(t1 != nullptr);

    auto v1 = Altseed::MakeAsdShared<Altseed::VertexArray>();
    {
        auto& vv = v1->GetVector();
        vv.push_back(Altseed::BatchVertex{});
        vv.push_back(Altseed::BatchVertex{});
        vv.push_back(Altseed::BatchVertex{});
        vv.push_back(Altseed::BatchVertex{});

        vv[0].Pos.X = 10;
        vv[0].Pos.Y = 10;
        vv[0].Pos.Z = 0.5f;
        vv[0].UV1.X = 0.0f;
        vv[0].UV1.Y = 0.0f;

        vv[1].Pos.X = 110;
        vv[1].Pos.Y = 10;
        vv[1].Pos.Z = 0.5f;
        vv[1].UV1.X = 1.0f;
        vv[1].UV1.Y = 0.0f;

        vv[2].Pos.X = 110;
        vv[2].Pos.Y = 110;
        vv[2].Pos.Z = 0.5f;
        vv[2].UV1.X = 1.0f;
        vv[2].UV1.Y = 1.0f;

        vv[3].Pos.X = 10;
        vv[3].Pos.Y = 110;
        vv[3].Pos.Z = 0.5f;
        vv[3].UV1.X = 0.0f;
        vv[3].UV1.Y = 1.0f;

        for (int i = 0; i < 4; i++) {
            vv[i].Col = Altseed::Color(255, 255, 255, 255);
        }
    }

    auto v2 = Altseed::MakeAsdShared<Altseed::VertexArray>();
    {
        auto& vv = v2->GetVector();
        vv.push_back(Altseed::BatchVertex{});
        vv.push_back(Altseed::BatchVertex{});
        vv.push_back(Altseed::BatchVertex{});
        vv.push_back(Altseed::BatchVertex{});

        vv[0].Pos.X = 210;
        vv[0].Pos.Y = 210;
        vv[0].Pos.Z = 0.5f;
        vv[0].Col = Altseed::Color(0, 255, 255, 255);

        vv[1].Pos.X = 310;
        vv[1].Pos.Y = 210;
        vv[1].Pos.Z = 0.5f;
        vv[1].Col = Altseed::Color(255, 0, 255, 255);

        vv[2].Pos.X = 310;
        vv[2].Pos.Y = 310;
        vv[2].Pos.Z = 0.5f;
        vv[2].Col = Altseed::Color(255, 255, 0, 255);

        vv[3].Pos.X = 210;
        vv[3].Pos.Y = 310;
        vv[3].Pos.Z = 0.5f;
        vv[3].Col = Altseed::Color(255, 255, 255, 255);
    }

    auto ib = Altseed::MakeAsdShared<Altseed::Int32Array>();
    auto& ibv = ib->GetVector();
    ibv.push_back(0);
    ibv.push_back(1);
    ibv.push_back(2);
    ibv.push_back(2);
    ibv.push_back(3);
    ibv.push_back(0);

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->DrawPolygon(v1, ib, t1);
        Altseed::Renderer::GetInstance()->DrawPolygon(v2, ib);

        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, SpriteTexture) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"SpriteTexture", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    auto s1 = Altseed::RenderedSprite::Create();
    auto s2 = Altseed::RenderedSprite::Create();

    s1->SetTexture(t1);
    s1->SetSrc(Altseed::RectF(0, 0, 128, 128));

    auto trans = Altseed::Matrix44F();
    trans.SetTranslation(200, 200, 0);
    s2->SetTexture(t2);
    s2->SetTransform(trans);
    s2->SetSrc(Altseed::RectF(128, 128, 256, 256));

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->DrawSprite(s2);

        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, Tool) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"Tool", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();
    EXPECT_TRUE(instance != nullptr);

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Tool::GetInstance()->NewFrame();

        if (Altseed::Tool::GetInstance()->Begin(u"Test")) {
            Altseed::Tool::GetInstance()->Text(u"Hoge");
            Altseed::Tool::GetInstance()->End();
        }

        Altseed::Tool::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, CameraBasic) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"CameraBasic", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    auto s1 = Altseed::RenderedSprite::Create();
    auto s2 = Altseed::RenderedSprite::Create();

    s1->SetTexture(t1);
    s1->SetSrc(Altseed::RectF(0, 0, 128, 128));

    auto trans = Altseed::Matrix44F();
    trans.SetTranslation(200, 200, 0);
    s2->SetTexture(t2);
    s2->SetTransform(trans);
    s2->SetSrc(Altseed::RectF(128, 128, 256, 256));

    auto trans2 = Altseed::Matrix44F();
    trans2.SetTranslation(-128, -128, 0);

    auto camera = Altseed::RenderedCamera::Create();
    camera->SetTransform(trans2);

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->SetCamera(camera);
        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->DrawSprite(s2);

        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}