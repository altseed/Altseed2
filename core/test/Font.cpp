
#include "Graphics/BuiltinShader.h"
#include "Graphics/Graphics.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Common/StringHelper.h"
#include "Graphics/Camera.h"
#include "Graphics/Color.h"
#include "Graphics/CommandList.h"
#include "Graphics/Font.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/Renderer.h"
#include "Tool/Tool.h"

TEST(Font, Basic) {
#if defined(__APPLE__) || defined(__linux__)
    return;
#endif

    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100);

    auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const char16_t* text = u"こんにちは！ Hello World";
    Altseed::Vector2F position(100, 100);
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        int32_t character = 0;

        char32_t tmp = 0;
        Altseed::ConvChU16ToU32({text[i], text[i + 1]}, tmp);
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

        if (i != std::char_traits<char16_t>::length(text) - 1) position += Altseed::Vector2F(font->GetKerning(character, text[i + 1]), 0);
    }

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        material->SetVector4F(
                u"weight",
                Altseed::Vector4F(
                        0.5f - font->GetWeight() / 255,
                        0.5f - font->GetWeight() / 255,
                        0.5f - font->GetWeight() / 255,
                        0.5f - font->GetWeight() / 255));

        material->SetVector4F(u"color", Altseed::Vector4F(font->GetColor().R, font->GetColor().G, font->GetColor().B, font->GetColor().A));

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, Weight) {
#if defined(__APPLE__) || defined(__linux__)
    return;
#endif

    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100);

    auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const char16_t* text = u"こんにちは！ Hello World";
    Altseed::Vector2F position(100, 100);
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        int32_t character = 0;

        char32_t tmp = 0;
        Altseed::ConvChU16ToU32({text[i], text[i + 1]}, tmp);
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

        if (i != std::char_traits<char16_t>::length(text) - 1) position += Altseed::Vector2F(font->GetKerning(character, text[i + 1]), 0);
    }

    while (count++ < 100 && instance->DoEvents()) {
        font->SetWeight(count / 20.0f - 2.5f);
        EXPECT_TRUE(instance->BeginFrame());

        material->SetVector4F(
                u"weight",
                Altseed::Vector4F(
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f));

        material->SetVector4F(
                u"color",
                Altseed::Vector4F(
                        font->GetColor().R / 255.f, font->GetColor().G / 255.f, font->GetColor().B / 255.f, font->GetColor().A / 255.f));

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, Color) {
#if defined(__APPLE__) || defined(__linux__)
    return;
#endif

    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", 100);

    auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const char16_t* text = u"こんにちは！ Hello World";
    Altseed::Vector2F position(100, 100);
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        int32_t character = 0;

        char32_t tmp = 0;
        Altseed::ConvChU16ToU32({text[i], text[i + 1]}, tmp);
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

        if (i != std::char_traits<char16_t>::length(text) - 1) position += Altseed::Vector2F(font->GetKerning(character, text[i + 1]), 0);
    }

    while (count++ < 255 && instance->DoEvents()) {
        font->SetColor(Altseed::Color(255 - count, count, count, 255));
        EXPECT_TRUE(instance->BeginFrame());

        material->SetVector4F(
                u"weight",
                Altseed::Vector4F(
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f));

        material->SetVector4F(
                u"color",
                Altseed::Vector4F(
                        font->GetColor().R / 255.f, font->GetColor().G / 255.f, font->GetColor().B / 255.f, font->GetColor().A / 255.f));

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}

TEST(Font, Surrogate) {
#if defined(__APPLE__) || defined(__linux__)
    return;
#endif

    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/GenYoMinJP-Bold.ttf", 100);

    auto shader = instance->GetBuiltinShader()->Create(Altseed::BuiltinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const char16_t* text = u"𠀋 𡈽 𡌛 𡑮 𡢽 𠮟 𡚴 𡸴 𣇄 𣗄 𣜿 𣝣 𣳾 𤟱 𥒎 𥔎 𥝱 𥧄 𥶡 𦫿 𦹀 𧃴 𧚄 𨉷";
    Altseed::Vector2F position(100, 100);
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        int32_t character = 0;
        char32_t tmp = 0;
        Altseed::ConvChU16ToU32({text[i], text[i + 1]}, tmp);
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

        if (i != std::char_traits<char16_t>::length(text) - 1) position += Altseed::Vector2F(font->GetKerning(character, text[i + 1]), 0);
    }

    while (count++ < 255 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());

        material->SetVector4F(
                u"weight",
                Altseed::Vector4F(
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f,
                        0.5f - font->GetWeight() / 255.0f));

        material->SetVector4F(
                u"color",
                Altseed::Vector4F(
                        font->GetColor().R / 255.f, font->GetColor().G / 255.f, font->GetColor().B / 255.f, font->GetColor().A / 255.f));

        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}
