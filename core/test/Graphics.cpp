#define _USE_MATH_DEFINES
#include "Graphics/Graphics.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "Common/StringHelper.h"
#include "Graphics/BuiltinShader.h"
#include "Graphics/Camera.h"
#include "Graphics/Color.h"
#include "Graphics/CommandList.h"
#include "Graphics/Font.h"
#include "Graphics/FrameDebugger.h"
#include "Graphics/Material.h"
#include "Graphics/Renderer/CullingSystem.h"
#include "Graphics/Renderer/RenderedCamera.h"
#include "Graphics/Renderer/RenderedPolygon.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/RenderedText.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "Logger/Log.h"
#include "Math/Matrix44F.h"
#include "Tool/Tool.h"

TEST(Graphics, Initialize) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"Initialize", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();
    EXPECT_TRUE(instance != nullptr);

    while (count++ < 10 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, Shader) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"Initialize", 800, 600, Altseed::Configuration::Create()));

    auto shader = Altseed::Graphics::GetInstance()->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::SpriteUnlitPS);

    EXPECT_TRUE(shader != nullptr);

    EXPECT_TRUE(shader->GetStageType() == Altseed::ShaderStageType::Pixel);

    Altseed::Log::GetInstance()->Trace(Altseed::LogCategory::User, shader->GetCode());

    Altseed::Core::Terminate();
}

TEST(Graphics, BasicPolygonTextureRender) {
    auto config = Altseed::Configuration::Create();
    config->SetFileLoggingEnabled(true);
    config->SetConsoleLoggingEnabled(true);
    config->SetLogFileName(u"BasicPolygonTextureRender.txt");

    EXPECT_TRUE(Altseed::Core::Initialize(u"BasicPolygonTextureRender", 1280, 720, config));
    Altseed::Log::GetInstance()->SetLevel(Altseed::LogCategory::Graphics, Altseed::LogLevel::Trace);

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    while (count++ < 10 && instance->DoEvents()) {
        if (count == 2) Altseed::FrameDebugger::GetInstance()->Start();
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

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        if (count == 2) Altseed::FrameDebugger::GetInstance()->DumpToLog();
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

    while (count++ < 10 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->DrawPolygon(v1, ib, t1);
        Altseed::Renderer::GetInstance()->DrawPolygon(v2, ib);

        Altseed::Renderer::GetInstance()->Render();

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

    while (count++ < 10 && instance->DoEvents()) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->DrawSprite(s2);

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take screenshot
        if (count == 5) {
            // Altseed::Graphics::GetInstance()->TakeScreenshot(u"SpriteTexture.png");
        }
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, RenderedText) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderedText", 1280, 720, Altseed::Configuration::Create()));

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100);

    std::vector<std::shared_ptr<Altseed::RenderedText>> texts;

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"Hello, world! こんにちは");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 0, 0));
        texts.push_back(t);
    }

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"色を指定する。");
        t->SetColor(Altseed::Color(0, 0, 255, 255));
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 100.0f, 0));
        texts.push_back(t);
    }

    auto weitText = Altseed::RenderedText::Create();
    {
        weitText->SetText(u"太さを指定する。");
        weitText->SetFont(font);
        weitText->SetTransform(Altseed::Matrix44F().SetTranslation(0, 200.0f, 0));
        texts.push_back(weitText);
    }

    auto fontGenyomin = Altseed::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", 100);
    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(fontGenyomin);
        t->SetText(u"𠀋 𡈽 𡌛 𡑮 𡢽 𠮟 𡚴 𡸴 𣇄 𣗄 𣜿 𣝣 𣳾 𤟱 𥒎 𥔎 𥝱 𥧄 𥶡 𦫿 𦹀 𧃴 𧚄 𨉷");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 300.0f, 0));
        texts.push_back(t);
    }

    auto rotatedText = Altseed::RenderedText::Create();
    {
        rotatedText->SetFont(font);
        rotatedText->SetText(u"くるくるまわる");
        texts.push_back(rotatedText);
    }

    {
        auto imageFont = Altseed::Font::CreateImageFont(font);
        imageFont->AddImageGlyph(u'〇', Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png"));
        auto imageFontText = Altseed::RenderedText::Create();
        imageFontText->SetFont(imageFont);
        imageFontText->SetText(u"Altseed〇Altseed");
        imageFontText->SetTransform(Altseed::Matrix44F().SetTranslation(0, 500.0f, 0));
        texts.push_back(imageFontText);
    }

    auto rotatedTrans = Altseed::Matrix44F().SetTranslation(600.0f, 400.0f, 0.0f);
    Altseed::Matrix44F rotatedRot;

    auto instance = Altseed::Graphics::GetInstance();

    for (int count = 0; count++ < 100 && instance->DoEvents();) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        weitText->SetWeight(count / 20.0f - 2.5f);
        rotatedText->SetTransform(rotatedTrans * rotatedRot.SetRotationZ(4 * count * M_PI / 180.0));

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, RenderedPolygon) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderedPolygon", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto polygon = Altseed::RenderedPolygon::Create();

    auto vertexes = Altseed::MakeAsdShared<Altseed::Vector2FArray>();
    vertexes->Resize(12);
    vertexes->GetVector()[0] = Altseed::Vector2F(0, 0);
    for (int i = 0; i <= 10; ++i) {
        float argument = 0.2 * M_PI * i;
        float pos_x = (i % 2 ? 100 : 200) * -sin(argument);
        float pos_y = (i % 2 ? 100 : 200) * -cos(argument);
        vertexes->GetVector()[i + 1] = Altseed::Vector2F(pos_x, pos_y);
    }
    polygon->SetVertexesByVector2F(vertexes);

    for (int i = 0; i < 12; ++i) polygon->GetVertexes()->GetVector()[i].Col = Altseed::Color(255, 0, 0, 255);

    auto transform = Altseed::Matrix44F();
    transform.SetTranslation(250, 250, 0);
    polygon->SetTransform(transform);

    while (count++ < 100 && instance->DoEvents()) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->DrawPolygon(polygon);
        Altseed::Renderer::GetInstance()->Render();

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
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->SetCamera(camera);
        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->DrawSprite(s2);

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, RenderTexture) {
    auto config = Altseed::Configuration::Create();
    config->SetFileLoggingEnabled(true);
    config->SetConsoleLoggingEnabled(true);
    config->SetLogFileName(u"RenderTexture.txt");
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderTexture", 1280, 720, config));
    Altseed::Log::GetInstance()->SetLevel(Altseed::LogCategory::Graphics, Altseed::LogLevel::Trace);

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);
    t1->SetInstanceName("t1");

    auto rt = Altseed::RenderTexture::Create(Altseed::Vector2I(200, 200));
    rt->SetInstanceName("rt");

    auto s1 = Altseed::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed::RectF(0, 0, 200, 200));

    auto s2 = Altseed::RenderedSprite::Create();
    {
        auto transform = Altseed::Matrix44F().SetTranslation(200, 200, 0);
        s2->SetTransform(transform);
        s2->SetTexture(rt);
        s2->SetSrc(Altseed::RectF(0, 0, 200, 200));
    }
    auto camera = Altseed::RenderedCamera::Create();
    { camera->SetTargetTexture(rt); }

    auto camera2 = Altseed::RenderedCamera::Create();

    while (count++ < 60 && instance->DoEvents()) {
        if (count == 2) Altseed::FrameDebugger::GetInstance()->Start();

        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        auto r = Altseed::Renderer::GetInstance();
        r->SetCamera(camera);
        r->DrawSprite(s1);
        r->Render();

        r->SetCamera(camera2);
        r->DrawSprite(s2);
        r->Render();

        EXPECT_TRUE(instance->EndFrame());
        if (count == 2) Altseed::FrameDebugger::GetInstance()->DumpToLog();
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, BackgroundBugcheck) {
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

    while (count++ < 10 && instance->DoEvents()) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        instance->GetCommandList()->SetRenderTargetWithScreen();

        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->DrawSprite(s2);

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, Culling) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"SpriteTexture", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");

    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed::RenderedSprite::Create();

    s1->SetTexture(t1);
    s1->SetSrc(Altseed::RectF(0, 0, 128, 128));

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 80);
    auto t = Altseed::RenderedText::Create();
    t->SetFont(font);
    t->SetText((u"Drawing Rendered: " +
                Altseed::utf8_to_utf16(std::to_string(Altseed::CullingSystem::GetInstance()->GetDrawingRenderedCount())))
                       .c_str());
    t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 0, 0));

    while (count++ < 1000 && instance->DoEvents()) {
        auto trans = Altseed::Matrix44F();
        trans.SetTranslation(200, 300 + count, 0);
        s1->SetTransform(trans);

        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        t->SetText((u"Drawing Rendered: " +
                    Altseed::utf8_to_utf16(std::to_string(Altseed::CullingSystem::GetInstance()->GetDrawingRenderedCount())))
                           .c_str());

        Altseed::Renderer::GetInstance()->DrawText(t);
        Altseed::Renderer::GetInstance()->DrawSprite(s1);

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, CullingTooManySprite) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"SpriteTexture", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");

    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed::RenderedSprite::Create();

    s1->SetTexture(t1);
    s1->SetSrc(Altseed::RectF(0, 0, 128, 128));

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 40);
    auto t = Altseed::RenderedText::Create();
    t->SetFont(font);
    t->SetText((u"FPS: " + Altseed::utf8_to_utf16(std::to_string(Altseed::Core::GetInstance()->GetCurrentFPS())) + u"Drawing Rendered: " +
                Altseed::utf8_to_utf16(std::to_string(Altseed::CullingSystem::GetInstance()->GetDrawingRenderedCount())))
                       .c_str());
    t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 0, 0));

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;

    while (count++ < 1000 && Altseed::Core::GetInstance()->DoEvent() && instance->DoEvents()) {
        auto trans = Altseed::Matrix44F();
        trans.SetTranslation(200, 300 + count, 0);
        s1->SetTransform(trans);

        for (int32_t i = 0; i < 10; i++) {
            auto s2 = Altseed::RenderedSprite::Create();
            s2->SetTexture(t1);
            s2->SetSrc(Altseed::RectF(0, 0, 128, 128));
            s2->SetTransform(Altseed::Matrix44F().SetTranslation(0, 1000, 0));
            sprites.push_back(s2);
        }

        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        t->SetText((u"FPS: " + Altseed::utf8_to_utf16(std::to_string(Altseed::Core::GetInstance()->GetCurrentFPS())) +
                    u" Drawing Rendered: " +
                    Altseed::utf8_to_utf16(std::to_string(Altseed::CullingSystem::GetInstance()->GetDrawingRenderedCount())))
                           .c_str());

        Altseed::Renderer::GetInstance()->DrawText(t);
        Altseed::Renderer::GetInstance()->DrawSprite(s1);

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Graphics, RenderToRenderTexture) {
    auto config = Altseed::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed::Core::Initialize(u"RnderToRenderTexture", 1280, 720, config));

    auto instance = Altseed::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed::RectF(0, 0, 400, 400));

    auto ps = Altseed::Shader::Create(u"grayscale", instance->GetBuiltinShader()->GetGrayScaleShader(), Altseed::ShaderStageType::Pixel);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(ps);

    auto target = Altseed::RenderTexture::Create(Altseed::Vector2I(500, 500));

    auto s2 = Altseed::RenderedSprite::Create();
    s2->SetTexture(target);
    s2->SetSrc(Altseed::RectF(0, 0, 500, 500));
    s2->SetTransform(Altseed::Matrix44F().SetTranslation(400.0f, 400.0f, 0));

    int count = 0;
    while (count++ < 180 && instance->DoEvents()) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));

        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->Render();

        material->SetTexture(u"mainTex", cmdList->GetScreenTexture());
        cmdList->RenderToRenderTexture(material, target);

        Altseed::Renderer::GetInstance()->DrawSprite(s2);
        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}