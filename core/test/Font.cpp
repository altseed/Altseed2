
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
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "Tool/Tool.h"

TEST(Font, Basic) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100);

    auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const std::u16string text = u"こんにちは！ Hello World";
    Altseed::Vector2F position(100, 100);
    for (size_t i = 0; i < text.size(); i++) {
        int32_t character = 0;

        char32_t tmp = 0;
        ASD_ASSERT(i < text.size(), "buffer overrun");

        Altseed::ConvChU16ToU32({text[i], i + 1 < text.size() ? text[i + 1] : u'\0'}, tmp);
        character = (int32_t)tmp;
        if (text[i] >= 0xD800 && text[i] <= 0xDBFF) {
            i++;
        }

        auto glyph = font->GetGlyph(character);
        if (glyph == nullptr) continue;

        auto tempPosition = position + glyph->GetOffset().To2F() + Altseed::Vector2F(0, font->GetAscent());
        auto sprite = Altseed::RenderedSprite::Create();
        sprite->SetMaterial(material);
        sprite->SetTexture(font->GetFontTexture(glyph->GetTextureIndex()));

        Altseed::Matrix44F trans;
        trans.SetTranslation(tempPosition.X, tempPosition.Y, 0);
        sprite->SetTransform(trans);

        sprite->SetSrc(Altseed::RectF(glyph->GetPosition().X, glyph->GetPosition().Y, glyph->GetSize().X, glyph->GetSize().Y));
        sprites.push_back(sprite);

        position += Altseed::Vector2F(glyph->GetGlyphWidth(), 0);

        if (i != text.size() - 1) {
            Altseed::ConvChU16ToU32({text[i + 1], i + 2 < text.size() ? text[i + 2] : u'\0'}, tmp);
            int32_t next = static_cast<int32_t>(tmp);
            position += Altseed::Vector2F(font->GetKerning(character, next), 0);
        }
    }

    float weight = 0.0f;
    material->SetVector4F(u"weight", Altseed::Vector4F(0.5f - weight / 255, 0, 0, 0));

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, Weight) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100);

    auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const std::u16string text = u"こんにちは！ Hello World";
    Altseed::Vector2F position(100, 100);
    for (size_t i = 0; i < text.size(); i++) {
        int32_t character = 0;

        char32_t tmp = 0;
        ASD_ASSERT(i < text.size(), "buffer overrun");

        Altseed::ConvChU16ToU32({text[i], i + 1 < text.size() ? text[i + 1] : u'\0'}, tmp);
        character = (int32_t)tmp;
        if (text[i] >= 0xD800 && text[i] <= 0xDBFF) {
            i++;
        }

        auto glyph = font->GetGlyph(character);
        if (glyph == nullptr) continue;

        auto tempPosition = position + glyph->GetOffset().To2F() + Altseed::Vector2F(0, font->GetAscent());
        auto sprite = Altseed::RenderedSprite::Create();
        sprite->SetMaterial(material);
        sprite->SetTexture(font->GetFontTexture(glyph->GetTextureIndex()));

        Altseed::Matrix44F trans;
        trans.SetTranslation(tempPosition.X, tempPosition.Y, 0);
        sprite->SetTransform(trans);

        sprite->SetSrc(Altseed::RectF(glyph->GetPosition().X, glyph->GetPosition().Y, glyph->GetSize().X, glyph->GetSize().Y));
        sprites.push_back(sprite);

        position += Altseed::Vector2F(glyph->GetGlyphWidth(), 0);

        if (i != text.size() - 1) {
            Altseed::ConvChU16ToU32({text[i + 1], i + 2 < text.size() ? text[i + 2] : u'\0'}, tmp);
            int32_t next = static_cast<int32_t>(tmp);
            position += Altseed::Vector2F(font->GetKerning(character, next), 0);
        }
    }

    while (count++ < 100 && instance->DoEvents()) {
        auto weight = count / 20.0f - 2.5f;

        EXPECT_TRUE(instance->BeginFrame());

        material->SetVector4F(u"weight", Altseed::Vector4F(0.5f - weight / 255.0f, 0, 0, 0));

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
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
//         Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
//         EXPECT_TRUE(instance->EndFrame());
//     }

//     Altseed::Core::Terminate();
// }

TEST(Font, Surrogate) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", 100);

    auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const std::u16string text = u"𠀋 𡈽 𡌛 𡑮 𡢽 𠮟 𡚴 𡸴 𣇄 𣗄 𣜿 𣝣 𣳾 𤟱 𥒎 𥔎 𥝱 𥧄 𥶡 𦫿 𦹀 𧃴 𧚄 𨉷";
    Altseed::Vector2F position(100, 100);
    for (size_t i = 0; i < text.size(); i++) {
        int32_t character = 0;

        char32_t tmp = 0;
        ASD_ASSERT(i < text.size(), "buffer overrun");

        Altseed::ConvChU16ToU32({text[i], i + 1 < text.size() ? text[i + 1] : u'\0'}, tmp);
        character = (int32_t)tmp;
        if (text[i] >= 0xD800 && text[i] <= 0xDBFF) {
            i++;
        }

        auto glyph = font->GetGlyph(character);
        if (glyph == nullptr) continue;

        auto tempPosition = position + glyph->GetOffset().To2F() + Altseed::Vector2F(0, font->GetAscent());
        auto sprite = Altseed::RenderedSprite::Create();
        sprite->SetMaterial(material);
        sprite->SetTexture(font->GetFontTexture(glyph->GetTextureIndex()));

        Altseed::Matrix44F trans;
        trans.SetTranslation(tempPosition.X, tempPosition.Y, 0);
        sprite->SetTransform(trans);

        sprite->SetSrc(Altseed::RectF(glyph->GetPosition().X, glyph->GetPosition().Y, glyph->GetSize().X, glyph->GetSize().Y));
        sprites.push_back(sprite);

        position += Altseed::Vector2F(glyph->GetGlyphWidth(), 0);

        if (i != text.size() - 1) {
            Altseed::ConvChU16ToU32({text[i + 1], i + 2 < text.size() ? text[i + 2] : u'\0'}, tmp);
            int32_t next = static_cast<int32_t>(tmp);
            position += Altseed::Vector2F(font->GetKerning(character, next), 0);
        }
    }

    float weight = 0.0f;
    material->SetVector4F(u"weight", Altseed::Vector4F(0.5f - weight / 255.0f, 0.0f, 0.0f, 0.0f));

    while (count++ < 10 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
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

    auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const std::u16string text = u"AltseedロAltseed";
    Altseed::Vector2F position(100, 100);
    for (size_t i = 0; i < text.size(); i++) {
        int32_t character = 0;
        char32_t tmp = 0;
        ASD_ASSERT(i < text.size(), "buffer overrun");

        Altseed::ConvChU16ToU32({text[i], i + 1 < text.size() ? text[i + 1] : u'\0'}, tmp);
        character = (int32_t)tmp;
        if (text[i] >= 0xD800 && text[i] <= 0xDBFF) {
            i++;
        }

        auto sprite = Altseed::RenderedSprite::Create();

        auto texture = font->GetImageGlyph(character);

        if (texture == nullptr) {
            auto glyph = font->GetGlyph(character);
            if (glyph == nullptr) continue;

            auto tempPosition = position + glyph->GetOffset().To2F() + Altseed::Vector2F(0, font->GetAscent());

            sprite->SetMaterial(material);
            sprite->SetTexture(font->GetFontTexture(glyph->GetTextureIndex()));

            Altseed::Matrix44F trans;
            trans.SetTranslation(tempPosition.X, tempPosition.Y, 0);
            sprite->SetTransform(trans);

            sprite->SetSrc(Altseed::RectF(glyph->GetPosition().X, glyph->GetPosition().Y, glyph->GetSize().X, glyph->GetSize().Y));
            position += Altseed::Vector2F(glyph->GetGlyphWidth(), 0);
        } else {
            sprite->SetTexture(texture);

            Altseed::Matrix44F trans;
            trans.SetTranslation(position.X, position.Y, 0);
            Altseed::Matrix44F scale;
            scale.SetScale((float)font->GetSize() / texture->GetSize().Y, (float)font->GetSize() / texture->GetSize().Y, 0);
            sprite->SetTransform(trans * scale);

            sprite->SetSrc(Altseed::RectF(0, 0, texture->GetSize().X, texture->GetSize().Y));

            position += Altseed::Vector2F((float)texture->GetSize().X * font->GetSize() / texture->GetSize().Y, 0);
        }

        sprites.push_back(sprite);

        if (i != text.size() - 1) {
            Altseed::ConvChU16ToU32({text[i + 1], i + 2 < text.size() ? text[i + 2] : u'\0'}, tmp);
            int32_t next = static_cast<int32_t>(tmp);
            position += Altseed::Vector2F(font->GetKerning(character, next), 0);
        }
    }

    float weight = 0.0f;
    material->SetVector4F(u"weight", Altseed::Vector4F(0.5f - weight / 255.0f, 0, 0, 0));

    while (count++ < 10 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}
