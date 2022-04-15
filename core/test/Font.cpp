
#include "Graphics/Font.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Common/StringHelper.h"
#include "Graphics/BuiltinShader.h"
#include "Graphics/Color.h"
#include "Graphics/CommandList.h"
#include "Graphics/Graphics.h"
#include "Graphics/ImageFont.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/RenderedText.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "TestHelper.h"
#include "Tool/Tool.h"

static const int32_t TestCount = 10;
static const int32_t DefaultSamplingSize = 64;

TEST(Font, LoadDynamicFont) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.LoadDynamicFont", 1280, 720, config));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", DefaultSamplingSize);

    Altseed2::Core::Terminate();
}

TEST(Font, Basic) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.Basic", 1280, 720, config));
    {
        auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", DefaultSamplingSize);

        std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

        {
            auto t = Altseed2::RenderedText::Create();
            t->SetFont(font);
            t->SetText(u"Hello, world! こんにちは");
            t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
            t->SetFontSize(100);
            texts.push_back(t);
        }

        for (const auto& t : texts) {
            Altseed2::CullingSystem::GetInstance()->Register(t);
        }

        auto instance = Altseed2::Graphics::GetInstance();

        for (int count = 0; count++ < TestCount && instance->DoEvents();) {
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

            if (count == 5) {
                Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Font.Basic.png");
            }
        }

        for (const auto& t : texts) {
            Altseed2::CullingSystem::GetInstance()->Unregister(t);
        }
    }

    Altseed2::Core::Terminate();
}

// TEST(Font, Weight) {
//     auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
//     EXPECT_TRUE(config != nullptr);

//     EXPECT_TRUE(Altseed2::Core::Initialize(u"RenderedText", 1280, 720, config));

//     auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 16);

//     std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

//     auto t = Altseed2::RenderedText::Create();
//     {
//         t->SetFont(font);
//         t->SetText(u"Hello, world! こんにちは");
//         t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
//         t->SetFontSize(100);
//         texts.push_back(t);
//     }

//     for (const auto& t : texts) {
//         Altseed2::CullingSystem::GetInstance()->Register(t);
//     }

//     auto instance = Altseed2::Graphics::GetInstance();

//     for (int count = 0; count++ < TestCount && instance->DoEvents();) {
//         t->SetWeight(count / 50.0f - 1.0f);
//         Altseed2::CullingSystem::GetInstance()->UpdateAABB();
//         Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

//         Altseed2::RenderPassParameter renderPassParameter;
//         renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
//         renderPassParameter.IsColorCleared = true;
//         renderPassParameter.IsDepthCleared = true;
//         EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

//         for (const auto& t : texts) {
//             Altseed2::Renderer::GetInstance()->DrawText(t);
//         }

//         Altseed2::Renderer::GetInstance()->Render();

//         EXPECT_TRUE(instance->EndFrame());
//     }

//     for (const auto& t : texts) {
//         Altseed2::CullingSystem::GetInstance()->Unregister(t);
//     }

//     Altseed2::Core::Terminate();
// }

// TEST(Font, Color) {
//     EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 1280, 720, Altseed2::Configuration::Create()));

//     int count = 0;

//     auto instance = Altseed2::Graphics::GetInstance();

//     auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", 32, 100);

//     auto shader = instance->GetBuiltinShader()->Create(Altseed2::BuiltinShaderType::FontUnlitPS);
//     auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
//     material->SetShader(shader);

//     std::vector<std::shared_ptr<Altseed2::RenderedSprite>> sprites;
//     const std::u16string text = u"こんにちは！ Hello World";
//     Altseed2::Vector2F position(100, 100);
//     for (size_t i = 0; i < text.size(); i++) {
//     int32_t character = 0;

//     char32_t tmp = 0;
//     ASD_ASSERT(i < text.size(), "buffer overrun");

//     Altseed2::ConvChU16ToU32({text[i], i + 1 < text.size() ? text[i + 1] : u'\0'}, tmp);
//     character = (int32_t)tmp;
//     if (text[i] >= 0xD800 && text[i] <= 0xDBFF) {
//         i++;
//     }

//     auto glyph = font -> GetGlyph(character);
//     if (glyph == nullptr) continue;

//     auto tempPosition = position + glyph -> GetOffset().To2F() + Altseed2::Vector2F(0, font->GetAscent());
//     auto sprite = Altseed2::RenderedSprite::Create();
//     sprite->SetMaterial(material);
//     sprite->SetTexture(font->GetFontTexture(glyph->GetTextureIndex()));
//
//     Altseed2::Matrix44F trans;
//     trans.SetTranslation(tempPosition.X, tempPosition.Y, 0);
//     sprite->SetTransform(trans);
//
//     sprite->SetSrc(Altseed2::RectF(glyph->GetPosition().X, glyph->GetPosition().Y, glyph->GetSize().X, glyph->GetSize().Y));
//     sprites.push_back(sprite);

//     position += Altseed2::Vector2F(glyph->GetGlyphWidth(), 0);

//     if (i != text.size() - 1) {
//         Altseed2::ConvChU16ToU32({text[i + 1], i + 2 < text.size() ? text[i + 2] : u'\0'}, tmp);
//         int32_t next = static_cast<int32_t>(tmp);
//         position += Altseed2::Vector2F(font->GetKerning(character, next), 0);
//     }
//}

//     float weight = 0.0f;
//     material->SetVector4F(u"weight", Altseed2::Vector4F(0.5f - weight / 255.0f, 0, 0, 0));

//     while (count++ < 10 && instance->DoEvents()) {
//         EXPECT_TRUE(instance->BeginFrame());
//         for (auto& s : sprites) {
//             Altseed2::Renderer::GetInstance()->DrawSprite(s);
//         }
//         Altseed2::Renderer::GetInstance()->Render();
//         EXPECT_TRUE(instance->EndFrame());
//     }

//     Altseed2::Core::Terminate();
// }

TEST(Font, Surrogate) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.Surrogate", 1280, 720, config));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", DefaultSamplingSize);

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"𠀋𡈽𡌛𡑮𡢽𠮟𡚴𡸴\n𣇄𣗄𣜿𣝣𣳾𤟱𥒎𥔎\n𥝱𥧄𥶡𦫿𦹀𧃴𧚄𨉷");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
        t->SetFontSize(100);
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    auto instance = Altseed2::Graphics::GetInstance();

    for (int count = 0; count++ < TestCount && instance->DoEvents();) {
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

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Font.Surrogate.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Font, ImageFont) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.ImageFont", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();

    auto baseFont = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", DefaultSamplingSize);
    auto font = Altseed2::Font::CreateImageFont(baseFont);
    font->AddImageGlyph(u'ロ', Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png"));

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"AltseedロAltseed");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
        t->SetFontSize(100);
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    for (int count = 0; count++ < TestCount && instance->DoEvents();) {
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

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Font.ImageFont.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Font, StaticFont) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.StaticFont", 1280, 720, config));

    const auto text =
            u"abcdefghijklmnopqrstuvwxyz\n"
            u"ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
            u"0123456789\n"
            u"Altseed2はマルチプラットフォームな和製ゲームエンジンです。\n"
            u"オブジェクト指向を用いて効率的にゲームを組み立てることができます。\n"
            u"このパッケージにはゲームエンジンのライブラリ部分のみが含まれます。\n";

    EXPECT_TRUE(
            Altseed2::Font::GenerateFontFile(u"TestData/Font/mplus-1m-regular.ttf", u"TestData/test.a2f", DefaultSamplingSize, text));

    auto staticFont = Altseed2::Font::LoadStaticFont(u"TestData/test.a2f");

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(staticFont);
        t->SetText(text);
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
        t->SetFontSize(64);
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    auto instance = Altseed2::Graphics::GetInstance();

    for (int count = 0; count++ < TestCount && instance->DoEvents();) {
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

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Font.StaticFont.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Font, FontSize) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.FontSize", 1280, 720, config));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", DefaultSamplingSize);

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(
                u"親譲りの無鉄砲で小供の時から損ばかりしている。小学校に居る時分学校の二階から飛び降りて一週間ほど腰を抜かした事がある。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
        t->SetFontSize(10);
        texts.push_back(t);
    }

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"なぜそんな無闇をしたと聞く人があるかも知れぬ。別段深い理由でもない。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 20, 0));
        t->SetFontSize(20);
        texts.push_back(t);
    }

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"新築の二階から首を出していたら、同級生の一人が冗談に、");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 50, 0));
        t->SetFontSize(40);
        texts.push_back(t);
    }

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"いくら威張っても、そこから飛び降りる事は出来まい。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 100, 0));
        t->SetFontSize(80);
        texts.push_back(t);
    }

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"弱虫やーい。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 190, 0));
        t->SetFontSize(160);
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    auto instance = Altseed2::Graphics::GetInstance();

    for (int count = 0; count++ < TestCount && instance->DoEvents();) {
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

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Font.FontSize.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Font, SamplingSize) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.SamplingSize", 1280, 720, config));

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    const auto size = 64;
    const auto offset = size + 8;

    {
        auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 32);
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(
                u"32: 親譲りの無鉄砲で小供の時から損ばかりしている。小学校に居る時分学校の二階から飛び降りて一週間ほど腰を抜かした事がある。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
        t->SetFontSize(size);
        texts.push_back(t);
    }

    {
        auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 48);
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"48: なぜそんな無闇をしたと聞く人があるかも知れぬ。別段深い理由でもない。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, offset, 0));
        t->SetFontSize(size);
        texts.push_back(t);
    }

    {
        auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 64);
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"64: 新築の二階から首を出していたら、同級生の一人が冗談に、");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, offset * 2, 0));
        t->SetFontSize(size);
        texts.push_back(t);
    }

    {
        auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 96);
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"96: いくら威張っても、そこから飛び降りる事は出来まい。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, offset * 3, 0));
        t->SetFontSize(size);
        texts.push_back(t);
    }

    {
        auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 128);
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"128: 弱虫やーい。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, offset * 4, 0));
        t->SetFontSize(size);
        texts.push_back(t);
    }

    {
        auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 176);
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"176: と囃はやしたからである。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, offset * 5, 0));
        t->SetFontSize(size);
        texts.push_back(t);
    }

    {
        auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 256);
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"256: 小使いに負ぶさって帰って来た時、おやじが大きな眼をして二階ぐらいから飛び降りて腰を抜かす奴があるかと云ったから、この次は抜かさずに飛んで見せますと答えた。");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, offset * 6, 0));
        t->SetFontSize(size);
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    auto instance = Altseed2::Graphics::GetInstance();

    for (int count = 0; count++ < TestCount && instance->DoEvents();) {
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

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Font.SamplingSize.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Font, Return) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.Return", 1280, 720, config));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", DefaultSamplingSize);

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(
                u"Altseed2はマルチプラットフォームな和製ゲームエンジンです。\nオブジェクト指向を用いて効率的にゲームを組み立てることができ"
                u"ます。\nこのパッケージにはゲームエンジンのライブラリ部分のみが含まれます。\n");
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(0, 0, 0));
        t->SetFontSize(30);
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    auto instance = Altseed2::Graphics::GetInstance();

    for (int count = 0; count++ < TestCount && instance->DoEvents();) {
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

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Font.Return.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Font, Vertical) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Font.Vertical", 1280, 720, config));

    auto font = Altseed2::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", DefaultSamplingSize);

    std::vector<std::shared_ptr<Altseed2::RenderedText>> texts;

    {
        auto t = Altseed2::RenderedText::Create();
        t->SetFont(font);
        t->SetText(
                u"Altseed2はマルチプラットフォームな和製ゲームエンジンです。\nオブジェクト指向を用いて効率的にゲームを組み立てることができ"
                u"ます。\nこのパッケージにはゲームエンジンのライブラリ部分のみが含まれます。\n");
        t->SetWritingDirection(Altseed2::WritingDirection::Vertical);
        t->SetTransform(Altseed2::Matrix44F().SetTranslation(300, 0, 0));
        t->SetFontSize(30);
        texts.push_back(t);
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Register(t);
    }

    auto instance = Altseed2::Graphics::GetInstance();

    for (int count = 0; count++ < TestCount && instance->DoEvents();) {
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

        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"Font.Vertical.png");
        }
    }

    for (const auto& t : texts) {
        Altseed2::CullingSystem::GetInstance()->Unregister(t);
    }

    Altseed2::Core::Terminate();
}

TEST(Font, GenerateFontFile) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    const auto filename = u"TestData/Font/mplus-1m-regular.ttf";
    const auto characters = u"Hello, world! こんにちは";

    EXPECT_TRUE(Altseed2::Core::Initialize(u"GenerateFontFile", 600, 400, config));

    EXPECT_TRUE(Altseed2::FileSystem::GetIsDirectory(u"TestData/Font"));
    EXPECT_TRUE(
            Altseed2::Font::GenerateFontFile(filename, u"TestData/Font/test.a2f", DefaultSamplingSize, characters));

    EXPECT_FALSE(Altseed2::FileSystem::GetIsDirectory(u"TestData/Font/NotExistedDirectory"));
    EXPECT_FALSE(
            Altseed2::Font::GenerateFontFile(filename, u"TestData/Font/NotExistedDirectory/test.a2f", DefaultSamplingSize, characters));

    Altseed2::Core::Terminate();
}
