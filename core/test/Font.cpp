
#include "Graphics/Font.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Common/StringHelper.h"
#include "Graphics/BuiltinShader.h"
#include "Graphics/Camera.h"
#include "Graphics/Color.h"
#include "Graphics/CommandList.h"
#include "Graphics/Graphics.h"
#include "Graphics/ImageFont.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/RenderedText.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "Tool/Tool.h"

TEST(Font, Basic) {
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

    auto instance = Altseed::Graphics::GetInstance();

    for (int count = 0; count++ < 10 && instance->DoEvents();) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, Weight) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderedText", 1280, 720, Altseed::Configuration::Create()));

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100);

    std::vector<std::shared_ptr<Altseed::RenderedText>> texts;

    auto t = Altseed::RenderedText::Create();
    {
        t->SetFont(font);
        t->SetText(u"Hello, world! こんにちは");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 0, 0));
        texts.push_back(t);
    }

    auto instance = Altseed::Graphics::GetInstance();

    for (int count = 0; count++ < 100 && instance->DoEvents();) {
        t->SetWeight(count / 50.0f - 1.0f);
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

// TEST(Font, Color) {
//     EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

//     int count = 0;

//     auto instance = Altseed::Graphics::GetInstance();

//     auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", 100);

//     auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
//     auto material = Altseed::MakeAsdShared<Altseed::Material>();
//     material->SetShader(shader);

//     std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
//     const std::u16string text = u"こんにちは！ Hello World";
//     Altseed::Vector2F position(100, 100);
//     for (size_t i = 0; i < text.size(); i++) {
//     int32_t character = 0;

//     char32_t tmp = 0;
//     ASD_ASSERT(i < text.size(), "buffer overrun");

//     Altseed::ConvChU16ToU32({text[i], i + 1 < text.size() ? text[i + 1] : u'\0'}, tmp);
//     character = (int32_t)tmp;
//     if (text[i] >= 0xD800 && text[i] <= 0xDBFF) {
//         i++;
//     }

//     auto glyph = font -> GetGlyph(character);
//     if (glyph == nullptr) continue;

//     auto tempPosition = position + glyph -> GetOffset().To2F() + Altseed::Vector2F(0, font->GetAscent());
//     auto sprite = Altseed::RenderedSprite::Create();
//     sprite->SetMaterial(material);
//     sprite->SetTexture(font->GetFontTexture(glyph->GetTextureIndex()));
//
//     Altseed::Matrix44F trans;
//     trans.SetTranslation(tempPosition.X, tempPosition.Y, 0);
//     sprite->SetTransform(trans);
//
//     sprite->SetSrc(Altseed::RectF(glyph->GetPosition().X, glyph->GetPosition().Y, glyph->GetSize().X, glyph->GetSize().Y));
//     sprites.push_back(sprite);

//     position += Altseed::Vector2F(glyph->GetGlyphWidth(), 0);

//     if (i != text.size() - 1) {
//         Altseed::ConvChU16ToU32({text[i + 1], i + 2 < text.size() ? text[i + 2] : u'\0'}, tmp);
//         int32_t next = static_cast<int32_t>(tmp);
//         position += Altseed::Vector2F(font->GetKerning(character, next), 0);
//     }
//}

//     float weight = 0.0f;
//     material->SetVector4F(u"weight", Altseed::Vector4F(0.5f - weight / 255.0f, 0, 0, 0));

//     while (count++ < 10 && instance->DoEvents()) {
//         EXPECT_TRUE(instance->BeginFrame());
//         for (auto& s : sprites) {
//             Altseed::Renderer::GetInstance()->DrawSprite(s);
//         }
//         Altseed::Renderer::GetInstance()->Render();
//         EXPECT_TRUE(instance->EndFrame());
//     }

//     Altseed::Core::Terminate();
// }

TEST(Font, Surrogate) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderedText", 1280, 720, Altseed::Configuration::Create()));

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", 100);

    std::vector<std::shared_ptr<Altseed::RenderedText>> texts;

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"𠀋 𡈽 𡌛 𡑮 𡢽 𠮟 𡚴 𡸴 𣇄 𣗄 𣜿 𣝣 𣳾 𤟱 𥒎 𥔎 𥝱 𥧄 𥶡 𦫿 𦹀 𧃴 𧚄 𨉷");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 0, 0));
        texts.push_back(t);
    }

    auto instance = Altseed::Graphics::GetInstance();

    for (int count = 0; count++ < 10 && instance->DoEvents();) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, ImageFont) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto baseFont = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100);
    auto font = Altseed::Font::CreateImageFont(baseFont);
    font->AddImageGlyph(u'ロ', Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png"));

    std::vector<std::shared_ptr<Altseed::RenderedText>> texts;

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font);
        t->SetText(u"AltseedロAltseed");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 0, 0));
        texts.push_back(t);
    }

    for (int count = 0; count++ < 100 && instance->DoEvents();) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, StaticFont) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderedText", 1280, 720, Altseed::Configuration::Create()));

    EXPECT_TRUE(
            Altseed::Font::GenerateFontFile(u"TestData/Font/mplus-1m-regular.ttf", u"TestData/test.a2f", 100, u"Hello, world! こんにちは"));

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100);
    auto staticFont = Altseed::Font::LoadStaticFont(u"TestData/test.a2f");

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
        t->SetFont(staticFont);
        t->SetText(u"Hello, world! こんにちは------");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 200, 0));
        texts.push_back(t);
    }

    auto instance = Altseed::Graphics::GetInstance();

    for (int count = 0; count++ < 100 && instance->DoEvents();) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, FontSize) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderedText", 1280, 720, Altseed::Configuration::Create()));

    auto font10 = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 10);
    auto font20 = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 20);
    auto font40 = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 40);
    auto font80 = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 80);
    auto font160 = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 160);

    std::vector<std::shared_ptr<Altseed::RenderedText>> texts;

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font10);
        t->SetText(
                u"親譲りの無鉄砲で小供の時から損ばかりしている。小学校に居る時分学校の二階から飛び降りて一週間ほど腰を抜かした事がある。");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 0, 0));
        texts.push_back(t);
    }

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font20);
        t->SetText(u"なぜそんな無闇をしたと聞く人があるかも知れぬ。別段深い理由でもない。");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 20, 0));
        texts.push_back(t);
    }

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font40);
        t->SetText(u"新築の二階から首を出していたら、同級生の一人が冗談に、");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 50, 0));
        texts.push_back(t);
    }

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font80);
        t->SetText(u"いくら威張っても、そこから飛び降りる事は出来まい。");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 100, 0));
        texts.push_back(t);
    }

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font160);
        t->SetText(u"弱虫やーい。");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 190, 0));
        texts.push_back(t);
    }

    auto instance = Altseed::Graphics::GetInstance();

    for (int count = 0; count++ < 1000 && instance->DoEvents();) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, Return) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderedText", 1280, 720, Altseed::Configuration::Create()));

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 30);

    std::vector<std::shared_ptr<Altseed::RenderedText>> texts;

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font);
        t->SetText(
                u"Altseed2はマルチプラットフォームな和製ゲームエンジンです。\nオブジェクト指向を用いて効率的にゲームを組み立てることができます。\nこのパッケージにはゲームエンジンのライブラリ部分のみが含まれます。\n");
        t->SetTransform(Altseed::Matrix44F().SetTranslation(0, 0, 0));
        texts.push_back(t);
    }

    auto instance = Altseed::Graphics::GetInstance();

    for (int count = 0; count++ < 1000 && instance->DoEvents();) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, Vertical) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"RenderedText", 1280, 720, Altseed::Configuration::Create()));

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 30);

    std::vector<std::shared_ptr<Altseed::RenderedText>> texts;

    {
        auto t = Altseed::RenderedText::Create();
        t->SetFont(font);
        t->SetText(
                u"Altseed2はマルチプラットフォームな和製ゲームエンジンです。\nオブジェクト指向を用いて効率的にゲームを組み立てることができ"
                u"ます。\nこのパッケージにはゲームエンジンのライブラリ部分のみが含まれます。\n");
        t->SetWritingDirection(Altseed::WritingDirection::Vertical);
        t->SetTransform(Altseed::Matrix44F().SetTranslation(300, 0, 0));
        texts.push_back(t);
    }

    auto instance = Altseed::Graphics::GetInstance();

    for (int count = 0; count++ < 1000 && instance->DoEvents();) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));
        EXPECT_TRUE(instance->BeginFrame());

        for (const auto& t : texts) {
            Altseed::Renderer::GetInstance()->DrawText(t);
        }

        Altseed::Renderer::GetInstance()->Render();

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}