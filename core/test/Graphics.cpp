#define _USE_MATH_DEFINES
#include "Graphics/Graphics.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "Common/StringHelper.h"
#include "Graphics/BuiltinShader.h"
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
#include "TestHelper.h"
#include "Tool/Tool.h"

TEST(Graphics, Initialize) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Initialize", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();
    EXPECT_TRUE(instance != nullptr);

    while (count++ < 10 && instance->DoEvents()) {
        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed2::Core::Terminate();
}

TEST(Graphics, Shader) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Initialize", 800, 600, config));

    auto shader = Altseed2::Graphics::GetInstance()->GetBuiltinShader()->Create(Altseed2::BuiltinShaderType::SpriteUnlitPS);

    EXPECT_TRUE(shader != nullptr);

    EXPECT_TRUE(shader->GetStageType() == Altseed2::ShaderStageType::Pixel);

    Altseed2::Log::GetInstance()->Trace(Altseed2::LogCategory::User, shader->GetCode());

    Altseed2::Core::Terminate();
}

TEST(Graphics, SpriteTexture) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"SpriteTexture", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    auto s2 = Altseed2::RenderedSprite::Create();

    Altseed2::CullingSystem::GetInstance()->Register(s1);
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 128, 128));

    Altseed2::CullingSystem::GetInstance()->Register(s2);
    auto trans = Altseed2::Matrix44F();
    trans.SetTranslation(200, 200, 0);
    s2->SetTexture(t2);
    s2->SetTransform(trans);
    s2->SetSrc(Altseed2::RectF(128, 128, 256, 256));

    while (count++ < 10 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->DrawSprite(s2);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.SpriteTexture.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::CullingSystem::GetInstance()->Unregister(s2);
    Altseed2::Core::Terminate();
}

TEST(Graphics, RenderedText) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"RenderedText", 1280, 720, config));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 48);

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"Hello, world! こんにちは");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
        t->SetFontSize(100);
        texts.push_back(t);
    }

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"色を指定する。");
        t->SetColor(Altseed2::Color(0, 0, 255, 255));
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 100.0f, 0));
        t->SetFontSize(100);
        texts.push_back(t);
    }

    auto weightText = Altseed2::RenderedText::Create();
    {
        weightText->SetText(u"太さを指定する。");
        weightText->SetFont(font);
        weightText->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 200.0f, 0));
        weightText->SetFontSize(100);
        texts.push_back(weightText);
    }

    auto fontGenyomin = Altseed2::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", 48);
    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(fontGenyomin);
        t->SetText(u"𠀋 𡈽 𡌛 𡑮 𡢽 𠮟 𡚴 𡸴 𣇄 𣗄 𣜿 𣝣 𣳾 𤟱 𥒎 𥔎 𥝱 𥧄 𥶡 𦫿 𦹀 𧃴 𧚄 𨉷");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 300.0f, 0));
        t->SetFontSize(100);
        texts.push_back(t);
    }

    auto rotatedText = Altseed2::RenderedText::Create();
    {
        rotatedText->SetFont(font);
        rotatedText->SetText(u"くるくるまわる");
        rotatedText->SetFontSize(100);
        texts.push_back(rotatedText);
    }

    {
        auto imageFont = Altseed2::Font::CreateImageFont(font);
        imageFont->AddImageGlyph(u'〇', Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png"));
        auto imageFontText = Altseed2::RenderedText::Create();
        imageFontText->SetFont(imageFont);
        imageFontText->SetText(u"Altseed〇Altseed");
        imageFontText->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 500.0f, 0));
        imageFontText->SetFontSize(100);
        texts.push_back(imageFontText);
    }

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetFontSize(100);
        t->SetText(u"Altseed おるとしーど");
        const auto size = t->GetRenderingSize();
        EXPECT_TRUE(size.X > 0.0f);
        EXPECT_TRUE(size.Y > 0.0f);
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 600.0f, 0));
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    auto rotatedTrans = Altseed2::Matrix44F().SetTranslation(600.0f, 400.0f, 0.0f);
    Altseed2::Matrix44F rotatedRot;

    auto instance = Altseed2::Graphics::GetInstance();

    for (int count = 0; count++ < 100 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent();) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        // weightText->SetWeight(count / 20.0f - 2.5f);
        rotatedText->SetTransform(rotatedTrans * rotatedRot.SetRotationZ(4 * count * M_PI / 180.0));

        for (const auto& t : texts) {
            Altseed2::Renderer::GetInstance()->DrawText(t);
        }

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.RenderedText.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Graphics, RenderedText_RenderingSize) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"RenderedText_RenderingSize", 1280, 720, config));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 64);

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetFontSize(100);
        t->SetText(u"A");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0.0f, 0.0f, 0));
        texts.push_back(t);
    }

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetFontSize(100);
        t->SetText(u"A");
        const auto size = t->GetRenderingSize();
        EXPECT_TRUE(size.X > 0.0f);
        EXPECT_TRUE(size.Y > 0.0f);
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(-size.X * 0.5f, 100.0f, 0));
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    auto instance = Altseed2::Graphics::GetInstance();

    for (int count = 0; count++ < 100 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent();) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        for (const auto& t : texts) {
            Altseed2::Renderer::GetInstance()->DrawText(t);
        }

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.RenderedText_RenderingSize.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Graphics, RenderedPolygon) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"RenderedPolygon", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto polygon = Altseed2::RenderedPolygon::Create();
    Altseed2::CullingSystem::GetInstance()->Register(polygon);

    auto vertexes = Altseed2::MakeAsdShared<Altseed2::Vector2FArray>();
    vertexes->Resize(12);
    vertexes->GetVector()[0] = Altseed2::Vector2F(0, 0);
    for (int i = 0; i <= 10; ++i) {
        float argument = 0.2 * M_PI * i;
        float pos_x = (i % 2 ? 100 : 200) * -sin(argument);
        float pos_y = (i % 2 ? 100 : 200) * -cos(argument);
        vertexes->GetVector()[i + 1] = Altseed2::Vector2F(pos_x, pos_y);
    }
    polygon->CreateVertexesByVector2F(vertexes);

    for (int i = 0; i < 12; ++i) polygon->GetVertexes()->GetVector()[i].Col = Altseed2::Color(255, 0, 0, 255);

    polygon->SetDefaultIndexBuffer();

    auto transform = Altseed2::Matrix44F();
    transform.SetTranslation(250, 250, 0);
    polygon->SetTransform(transform);

    while (count++ < 100 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawPolygon(polygon);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.RenderedPolygon.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(polygon);
    Altseed2::Core::Terminate();
}

TEST(Graphics, RenderedIBPolygon) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"RenderedIBPolygon", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto polygon = Altseed2::RenderedPolygon::Create();
    Altseed2::CullingSystem::GetInstance()->Register(polygon);

    auto vertexes = Altseed2::MakeAsdShared<Altseed2::Vector2FArray>();
    vertexes->Resize(8);
    vertexes->GetVector()[0] = Altseed2::Vector2F(-100, -100);
    vertexes->GetVector()[1] = Altseed2::Vector2F(-50, -100);
    vertexes->GetVector()[2] = Altseed2::Vector2F(-50, -50);
    vertexes->GetVector()[3] = Altseed2::Vector2F(-100, -50);
    vertexes->GetVector()[4] = Altseed2::Vector2F(50, 50);
    vertexes->GetVector()[5] = Altseed2::Vector2F(100, 50);
    vertexes->GetVector()[6] = Altseed2::Vector2F(100, 100);
    vertexes->GetVector()[7] = Altseed2::Vector2F(50, 100);
    polygon->CreateVertexesByVector2F(vertexes);

    auto buffers = Altseed2::MakeAsdShared<Altseed2::Int32Array>();
    buffers->GetVector().resize(12);
    buffers->GetVector()[0] = 0;
    buffers->GetVector()[1] = 1;
    buffers->GetVector()[2] = 2;
    buffers->GetVector()[3] = 0;
    buffers->GetVector()[4] = 2;
    buffers->GetVector()[5] = 3;
    buffers->GetVector()[6] = 4;
    buffers->GetVector()[7] = 5;
    buffers->GetVector()[8] = 6;
    buffers->GetVector()[9] = 4;
    buffers->GetVector()[10] = 6;
    buffers->GetVector()[11] = 7;
    polygon->SetBuffers(buffers);

    for (int i = 0; i < 8; ++i) polygon->GetVertexes()->GetVector()[i].Col = Altseed2::Color(255, 0, 0, 255);

    auto transform = Altseed2::Matrix44F();
    transform.SetTranslation(250, 250, 0);
    polygon->SetTransform(transform);

    while (count++ < 100 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawPolygon(polygon);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.RenderedIBPolygon.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(polygon);
    Altseed2::Core::Terminate();
}

TEST(Graphics, AlphaBlend) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);
    config->SetFileLoggingEnabled(true);
    EXPECT_TRUE(Altseed2::Core::Initialize(u"AlphaBlend", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();
    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink256.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(s1);
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 256, 256));

    auto builtinShader = Altseed2::MakeAsdShared<Altseed2::BuiltinShader>();
    auto m1 = Altseed2::MakeAsdShared<Altseed2::Material>();
    m1->SetAlphaBlend(Altseed2::AlphaBlend::Add());
    m1->SetShader(builtinShader->Create(Altseed2::BuiltinShaderType::SpriteUnlitVS));
    m1->SetShader(builtinShader->Create(Altseed2::BuiltinShaderType::SpriteUnlitPS));

    auto s2 = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(s2);
    s2->SetMaterial(m1);
    s2->SetSrc(Altseed2::RectF(0, 0, 256, 256));
    s2->SetTexture(t1);

    auto trans = Altseed2::Matrix44F();
    trans.SetRotationZ(3.14159f);
    auto trans2 = Altseed2::Matrix44F();
    trans2.SetTranslation(-128, -128, 0);
    auto trans3 = Altseed2::Matrix44F();
    trans3.SetTranslation(128, 128, 0);
    s2->SetTransform(trans3 * trans * trans2);

    while (count++ < 10 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->DrawSprite(s2);

        instance->GetCommandList()->SetRenderTarget(instance->GetCommandList()->GetScreenTexture(), renderPassParameter);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.AlphaBlend.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::CullingSystem::GetInstance()->Unregister(s2);
    Altseed2::Core::Terminate();
}

TEST(Graphics, CameraBasic) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"CameraBasic", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    auto s2 = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(s1);
    Altseed2::CullingSystem::GetInstance()->Register(s2);

    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 128, 128));

    auto trans = Altseed2::Matrix44F();
    trans.SetTranslation(200, 200, 0);
    s2->SetTexture(t2);
    s2->SetTransform(trans);
    s2->SetSrc(Altseed2::RectF(128, 128, 256, 256));

    auto trans2 = Altseed2::Matrix44F();
    trans2.SetTranslation(-128, -128, 0);

    auto matView = Altseed2::Matrix44F();
    matView.SetTranslation(640, 360, 0);

    auto camera = Altseed2::RenderedCamera::Create();
    camera->SetViewMatrix((trans2 * matView).GetInverted());

    while (count++ < 100 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->SetCamera(camera);
        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->DrawSprite(s2);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.CameraBasic.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::CullingSystem::GetInstance()->Unregister(s2);
    Altseed2::Core::Terminate();
}

TEST(Graphics, RenderTexture) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    config->SetFileLoggingEnabled(true);
    config->SetLogFileName(u"RenderTexture.txt");
    EXPECT_TRUE(Altseed2::Core::Initialize(u"RenderTexture", 1280, 720, config));
    Altseed2::Log::GetInstance()->SetLevel(Altseed2::LogCategory::Graphics, Altseed2::LogLevel::Trace);

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);
    t1->SetInstanceName("t1");

    auto rt = Altseed2::RenderTexture::Create(Altseed2::Vector2I(200, 200));
    rt->SetInstanceName("rt");

    auto s1 = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(s1);
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 200, 200));

    auto s2 = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(s2);
    auto transform = Altseed2::Matrix44F().SetTranslation(200, 200, 0);
    s2->SetTransform(transform);
    s2->SetTexture(rt);
    s2->SetSrc(Altseed2::RectF(0, 0, 200, 200));

    auto matView = Altseed2::Matrix44F();
    matView.SetTranslation(100, 100, 0);

    auto camera = Altseed2::RenderedCamera::Create();
    camera->SetTargetTexture(rt);
    camera->SetViewMatrix(matView.GetInverted());

    auto matView2 = Altseed2::Matrix44F();
    matView2.SetTranslation(640, 360, 0);

    auto camera2 = Altseed2::RenderedCamera::Create();
    camera2->SetViewMatrix(matView2.GetInverted());

    while (count++ < 60 && instance->DoEvents()) {
        if (count == 2) Altseed2::FrameDebugger::GetInstance()->Start();

        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        auto r = Altseed2::Renderer::GetInstance();
        r->SetCamera(camera);
        r->DrawSprite(s1);
        r->Render();

        r->SetCamera(camera2);
        r->DrawSprite(s2);
        r->Render();

        EXPECT_TRUE(instance->EndFrame());
        if (count == 2) Altseed2::FrameDebugger::GetInstance()->DumpToLog();

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.RenderTexture.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::CullingSystem::GetInstance()->Unregister(s2);
    Altseed2::Core::Terminate();
}

TEST(Graphics, RenderTextureSave) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    config->SetFileLoggingEnabled(true);
    config->SetLogFileName(u"RenderTextureSave.txt");
    EXPECT_TRUE(Altseed2::Core::Initialize(u"RenderTextureSave", 1280, 720, config));
    Altseed2::Log::GetInstance()->SetLevel(Altseed2::LogCategory::Graphics, Altseed2::LogLevel::Trace);

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);
    t1->SetInstanceName("t1");

    auto rt = Altseed2::RenderTexture::Create(Altseed2::Vector2I(200, 200));
    rt->SetInstanceName("rt");

    auto s1 = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(s1);
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 200, 200));

    auto s2 = Altseed2::RenderedSprite::Create();
    {
        Altseed2::CullingSystem::GetInstance()->Register(s2);
        auto transform = Altseed2::Matrix44F().SetTranslation(200, 200, 0);
        s2->SetTransform(transform);
        s2->SetTexture(rt);
        s2->SetSrc(Altseed2::RectF(0, 0, 200, 200));
    }

    auto matView = Altseed2::Matrix44F();
    matView.SetTranslation(100, 100, 0);

    auto camera = Altseed2::RenderedCamera::Create();
    camera->SetTargetTexture(rt);
    camera->SetViewMatrix(matView.GetInverted());

    auto matView2 = Altseed2::Matrix44F();
    matView2.SetTranslation(640, 360, 0);

    auto camera2 = Altseed2::RenderedCamera::Create();
    camera2->SetViewMatrix(matView2.GetInverted());

    while (count++ < 60 && instance->DoEvents()) {
        if (count == 2) Altseed2::FrameDebugger::GetInstance()->Start();

        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        auto r = Altseed2::Renderer::GetInstance();
        r->SetCamera(camera);
        r->DrawSprite(s1);
        r->Render();

        r->SetCamera(camera2);
        r->DrawSprite(s2);
        r->Render();

        EXPECT_TRUE(instance->EndFrame());
        if (count == 2) Altseed2::FrameDebugger::GetInstance()->DumpToLog();

        if (count == 5) {
            rt->Save(u"Graphics.RenderTextureSave.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::CullingSystem::GetInstance()->Unregister(s2);
    Altseed2::Core::Terminate();
}

TEST(Graphics, BackgroundBugcheck) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"SpriteTexture", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    auto t2 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.jpg");

    EXPECT_TRUE(t1 != nullptr);
    EXPECT_TRUE(t2 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    auto s2 = Altseed2::RenderedSprite::Create();

    Altseed2::CullingSystem::GetInstance()->Register(s1);
    Altseed2::CullingSystem::GetInstance()->Register(s2);

    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 128, 128));

    auto trans = Altseed2::Matrix44F();
    trans.SetTranslation(200, 200, 0);
    s2->SetTexture(t2);
    s2->SetTransform(trans);
    s2->SetSrc(Altseed2::RectF(128, 128, 256, 256));

    while (count++ < 10 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->DrawSprite(s2);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.BackgroundBugcheck.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::CullingSystem::GetInstance()->Unregister(s2);
    Altseed2::Core::Terminate();
}

TEST(Graphics, VertexTextureFetch) {
    const char* psCode = R"(
Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);
Texture2D vtfTex : register(t1);
SamplerState vtfSamp : register(s1);

struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};
float4 main(PS_INPUT input) : SV_TARGET 
{ 
    float4 c;
    c = mainTex.Sample(mainSamp, input.UV1) * input.Color;
    return c;
}
)";

    const char* vsCode = R"(
cbuffer Consts : register(b0)
{
    float4x4 matView;
    float4x4 matProjection;
};
struct VS_INPUT{
    float3 Position : POSITION0;
    float4 Color : COLOR0;
    float2 UV1 : UV0;
    float2 UV2 : UV1;
};
struct VS_OUTPUT{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};

// It neeed to define on vs and ps
Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);
Texture2D vtfTex : register(t1);
SamplerState vtfSamp : register(s1);
    
VS_OUTPUT main(VS_INPUT input){
    int x = input.UV1.x;
    int y = input.UV1.y;
    int index = (y == 1 ? 1 - x : x) + 2 * y;

    float texx = vtfTex.SampleLevel(vtfSamp, float2(index/4.0f, 0/4.0f),0).r; 
    float texy = vtfTex.SampleLevel(vtfSamp, float2(index/4.0f, 1/4.0f),0).r; 
    float4 texc = vtfTex.SampleLevel(vtfSamp, float2(index/4.0f, 2/4.0f),0); 

    VS_OUTPUT output;
    float4 pos = float4(input.Position, 1.0f);
    pos = mul(matView, pos);
    pos = mul(matProjection, pos);
    output.Position = pos;
    output.UV1 = float2(texx, texy);
    output.UV2 = input.UV2;
    output.Color = texc;
        
    return output;
}
)";

    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"VertexTextureFetch", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/VTF.png");
    auto t2 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink256.png");

    auto sprite = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(sprite);
    sprite->SetTexture(t2);
    sprite->SetSrc(Altseed2::RectF(0, 0, 256, 256));

    auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
    auto vs = Altseed2::ShaderCompiler::GetInstance()->Compile("", "VS", vsCode, Altseed2::ShaderStageType::Vertex)->GetValue();
    EXPECT_TRUE(vs != nullptr);
    //auto ps = Altseed2::ShaderCompiler::GetInstance()->Compile("PS", psCode, Altseed2::ShaderStageType::Pixel);
    material->SetShader(vs);
    //material->SetShader(ps);
    material->SetTexture(u"vtfTex", t1);
    sprite->SetMaterial(material);

    Altseed2::RenderPassParameter renderPassParameter;
    renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
    renderPassParameter.IsColorCleared = true;
    renderPassParameter.IsDepthCleared = true;

    while (count++ < 10 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(sprite);
        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.VertexTextureFetch.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(sprite);
    Altseed2::Core::Terminate();
}

TEST(Graphics, Culling) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Culling", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");

    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();

    Altseed2::CullingSystem::GetInstance()->Register(s1);
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 128, 128));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 48);
    auto t = Altseed2::RenderedText::Create();
    t->SetFont(font);
    t->SetText((u"Drawing Rendered: " +
                Altseed2::utf8_to_utf16(std::to_string(Altseed2::CullingSystem::GetInstance()->GetDrawingRenderedCount())))
                       .c_str());
    t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
    t->SetFontSize(80);

    while (count++ < 100 && instance->DoEvents()) {
        auto trans = Altseed2::Matrix44F();
        trans.SetTranslation(200, 300 + count, 0);
        s1->SetTransform(trans);

        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        t->SetText((u"Drawing Rendered: " +
                    Altseed2::utf8_to_utf16(std::to_string(Altseed2::CullingSystem::GetInstance()->GetDrawingRenderedCount())))
                           .c_str());

        Altseed2::Renderer::GetInstance()->DrawText(t);
        Altseed2::Renderer::GetInstance()->DrawSprite(s1);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.Culling.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::Core::Terminate();
}

TEST(Graphics, CullingTooManySprite) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"SpriteTexture", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");

    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();

    Altseed2::CullingSystem::GetInstance()->Register(s1);
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 128, 128));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 48);
    auto t = Altseed2::RenderedText::Create();
    Altseed2::CullingSystem::GetInstance()->Register(t);
    t->SetFont(font);
    t->SetText((u"FPS: " + Altseed2::utf8_to_utf16(std::to_string(Altseed2::Core::GetInstance()->GetCurrentFPS())) + u"Drawing Rendered: " +
                Altseed2::utf8_to_utf16(std::to_string(Altseed2::CullingSystem::GetInstance()->GetDrawingRenderedCount())))
                       .c_str());
    t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
    t->SetFontSize(40);

    std::vector<std::shared_ptr<Altseed2::RenderedSprite>> sprites;

    while (count++ < 100 && Altseed2::Core::GetInstance()->DoEvent() && instance->DoEvents()) {
        auto trans = Altseed2::Matrix44F();
        trans.SetTranslation(200, 300 + count, 0);
        s1->SetTransform(trans);

        for (int32_t i = 0; i < 10; i++) {
            auto s2 = Altseed2::RenderedSprite::Create();
            s2->SetTexture(t1);
            s2->SetSrc(Altseed2::RectF(0, 0, 128, 128));
            s2->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 1000, 0));
            Altseed2::CullingSystem::GetInstance()->Register(s2);
            sprites.push_back(s2);
        }

        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        t->SetText((u"FPS: " + Altseed2::utf8_to_utf16(std::to_string(Altseed2::Core::GetInstance()->GetCurrentFPS())) +
                    u" Drawing Rendered: " +
                    Altseed2::utf8_to_utf16(std::to_string(Altseed2::CullingSystem::GetInstance()->GetDrawingRenderedCount())))
                           .c_str());

        Altseed2::Renderer::GetInstance()->DrawText(t);
        Altseed2::Renderer::GetInstance()->DrawSprite(s1);

        for (auto& s : sprites) {
            Altseed2::Renderer::GetInstance()->DrawSprite(s);
        }

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.CullingTooManySprite.png");
        }

        for (auto& s : sprites) {
            Altseed2::CullingSystem::GetInstance()->Unregister(s);
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::CullingSystem::GetInstance()->Unregister(t);
    Altseed2::Core::Terminate();
}

TEST(Graphics, RenderToRenderTexture) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"RnderToRenderTexture", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(s1);
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 400, 400));

    auto ps = Altseed2::Shader::Compile(u"grayscale", instance->GetBuiltinShader()->GetGrayScaleShader(), Altseed2::ShaderStageType::Pixel)->GetValue();
    auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
    material->SetShader(ps);

    auto target = Altseed2::RenderTexture::Create(Altseed2::Vector2I(500, 500));

    auto s2 = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(s2);
    s2->SetTexture(target);
    s2->SetSrc(Altseed2::RectF(0, 0, 500, 500));
    s2->SetTransform(Altseed2::Matrix44F().SetTranslation(400.0f, 400.0f, 0));

    int count = 0;
    while (count++ < 180 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->Render();

        material->SetTexture(u"mainTex", cmdList->GetScreenTexture());
        cmdList->RenderToRenderTexture(material, target, renderPassParameter);

        Altseed2::Renderer::GetInstance()->DrawSprite(s2);
        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.RenderToRenderTexture.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(s1);
    Altseed2::CullingSystem::GetInstance()->Unregister(s2);
    Altseed2::Core::Terminate();
}

TEST(Graphics, TextureWrapModeClamp) {
    const char* psCode = R"(
Texture2D mainTex : register(t0);
SamplerState mainSamp : register(s0);
struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};
float4 main(PS_INPUT input) : SV_TARGET 
{ 
    float4 c;
    c = mainTex.Sample(mainSamp, input.UV1 * 2.0) * input.Color;
    return c;
}
)";

    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"TextureWrapMode", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/Graphics/flower.png");
    t1->SetWrapMode(Altseed2::TextureWrapMode::Clamp);

    EXPECT_TRUE(t1 != nullptr);

    auto sprite = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(sprite);
    sprite->SetTexture(t1);
    sprite->SetSrc(Altseed2::RectF(0, 0, t1->GetSize().X, t1->GetSize().Y));

    auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
    auto ps = Altseed2::ShaderCompiler::GetInstance()->Compile("", "PS", psCode, Altseed2::ShaderStageType::Pixel)->GetValue();
    EXPECT_TRUE(ps != nullptr);
    material->SetShader(ps);
    sprite->SetMaterial(material);

    int count = 0;
    while (count++ < 10 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(sprite);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.TextureWrapModeClamp.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(sprite);
    Altseed2::Core::Terminate();
}

TEST(Graphics, ShaderFromFile) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"ShaderFromFile", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/Graphics/flower.png");

    EXPECT_TRUE(t1 != nullptr);

    auto sprite = Altseed2::RenderedSprite::Create();
    Altseed2::CullingSystem::GetInstance()->Register(sprite);
    sprite->SetTexture(t1);
    sprite->SetSrc(Altseed2::RectF(0, 0, t1->GetSize().X, t1->GetSize().Y));

    auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
    auto ps = Altseed2::Shader::CompileFromFile(u"", u"TestData/Shader/ps.fx", Altseed2::ShaderStageType::Pixel)->GetValue();
    material->SetShader(ps);
    sprite->SetMaterial(material);

    int count = 0;
    while (count++ < 10 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(sprite);

        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.ShaderFromFile.png");
        }
    }

    Altseed2::CullingSystem::GetInstance()->Unregister(sprite);
    Altseed2::Core::Terminate();
}

TEST(Graphics, ScreenTextureFormat) {
    const std::u16string PostEffectCode =
            uR"(
struct PS_INPUT
{
    float4  Position : SV_POSITION;
    float4  Color    : COLOR0;
    float2  UV1 : UV0;
    float2  UV2 : UV1;
};

float4 main(PS_INPUT input) : SV_TARGET 
{
    float h = input.UV1.x;
    float s = input.UV1.y;
    float v = 1.0;
    float3 col = ((clamp(abs(frac(h + float3(0.0, 2.0, 1.0) / 3.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0) - 1.0) * s + 1.0) * v;
    return float4(col, 1.0);
}
)";

    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"ScreenTextureFormat", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto ps = Altseed2::Shader::Compile(u"posteffect", PostEffectCode.c_str(), Altseed2::ShaderStageType::Pixel)->GetValue();
    auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
    material->SetShader(ps);

    int count = 0;
    while (count++ < 180 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        cmdList->RenderToRenderTarget(material);

        EXPECT_TRUE(instance->EndFrame());

        if (count == 90) {
            cmdList->SetScreenTextureFormat(Altseed2::TextureFormatType::R16G16_FLOAT);
        }
    }

    Altseed2::Core::Terminate();
}

TEST(Graphics, MassDrawCall) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"MassDrawCall", 1280, 720, config));

    int count = 0;
    int spriteCount = 256;
    std::vector<std::shared_ptr<Altseed2::RenderedSprite>> sprites;

    auto instance = Altseed2::Graphics::GetInstance();

    for (int i = 0; i < spriteCount; i++) {
        auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
        EXPECT_TRUE(t1 != nullptr);

        auto s = Altseed2::RenderedSprite::Create();

        Altseed2::CullingSystem::GetInstance()->Register(s);
        s->SetTexture(t1);
        s->SetSrc(Altseed2::RectF(0, 0, t1->GetSize().X, t1->GetSize().Y));
        Altseed2::Matrix44F trans, scale;
        trans.SetTranslation((i % 32) * 1280.0 / 32, (i / 32) * 720.0 / 32, 0);
        scale.SetScale(1280.0 / 32.0 / t1->GetSize().X, 720.0 / 32 / t1->GetSize().Y, 0);
        s->SetTransform(trans * scale);
        sprites.push_back(s);

        Altseed2::Resources::GetInstance()->Clear();
    }

    while (count++ < 1000 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));
        for (int i = 0; i < spriteCount; i++) {
            Altseed2::Renderer::GetInstance()->DrawSprite(sprites[i]);
        }
        Altseed2::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Graphics.MassDrawCall.png");
        }
    }

    for (int i = 0; i < spriteCount; i++) {
        Altseed2::CullingSystem::GetInstance()->Unregister(sprites[i]);
    }
    Altseed2::Core::Terminate();
}

TEST(Graphics, CompileInvalidShaderCode) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"CompileInvalidShaderCode", 600, 400, config));

    auto result = Altseed2::Shader::Compile(u"invalidShader", u"invalid shader code", Altseed2::ShaderStageType::Pixel);

    EXPECT_TRUE(result->GetValue() == nullptr);

    Altseed2::Core::Terminate();
}