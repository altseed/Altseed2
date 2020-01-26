#include "Graphics/Graphics.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Graphics/Color.h"
#include "Graphics/Font.h"
#include "Graphics/Sprite.h"

TEST(Font, Basic) {
#if defined(__APPLE__) || defined(__linux__)
    return;
#endif

    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::CoreOption()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();
    auto renderer = instance->CreateRenderer();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100, Altseed::Color(255, 0, 0, 255));

    auto shader = Altseed::ShaderCompiler::GetInstance()->Compile(font->HlslPSCode, Altseed::ShaderStageType::Pixel);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    const char16_t* text = u"こんにちは！ Hello World";
    Altseed::Vector2DF position(100, 100);
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        auto glyph = font->GetGlyph(text[i]);
        if (glyph == nullptr) continue;

        auto tempPosition = position + glyph->GetOffset().To2DF() + Altseed::Vector2DF(0, font->GetAscent());
        auto sprite = Altseed::MakeAsdShared<Altseed::Sprite>();
        sprite->SetMaterial(material);
        sprite->SetTexture(font->GetFontTexture(glyph->GetTextureIndex())->GetNativeTexture());
        sprite->SetPosition(tempPosition);
        sprite->SetSize(glyph->GetSize().To2DF());
        auto uvs = glyph->GetUVs();
        for (int32_t i = 0; i < 4; i++) {
            sprite->SetUV(uvs[i], i);
        }
        position += Altseed::Vector2DF(glyph->GetGlyphWidth(), 0);

        if (i != std::char_traits<char16_t>::length(text) - 1) position += Altseed::Vector2DF(font->GetKerning(text[i], text[i + 1]), 0);
        renderer->Sprites.push_back(sprite);
    }

    while (count++ < 1000 && instance->DoEvents()) EXPECT_TRUE(instance->Update());

    Altseed::Core::Terminate();
}