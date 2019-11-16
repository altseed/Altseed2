#include "Graphics/Graphics.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Graphics/Color.h"
#include "Graphics/Font.h"
#include "Graphics/Sprite.h"

namespace asd = altseed;

TEST(Font, Basic) {

#if defined(__APPLE__) || defined(__linux__)
    return;
#endif

    EXPECT_TRUE(asd::Core::Initialize(u"test", 1280, 720, asd::CoreOption()));

    int count = 0;

    auto instance = asd::Graphics::GetInstance();

    auto font = asd::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100, asd::Color(255, 0, 0, 255));

    auto shader = instance->CreateShader(font->HlslPSCode);
    auto material = std::make_shared<asd::Material>();
    material->SetShader(shader);

    const char16_t* text = u"こんにちは！ Hello World";
    asd::Vector2DF position(100, 100);
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        auto glyph = font->GetGlyph(text[i]);
        if (glyph == nullptr) continue;

        auto tempPosition = position + glyph->GetOffset().To2DF();
        auto sprite = std::make_shared<asd::Sprite>();
        sprite->SetMaterial(material);
        sprite->SetTexture(glyph->GetNativeTexture());
        sprite->SetPosition(tempPosition);
        sprite->SetSize(glyph->GetSize().To2DF());
        position += asd::Vector2DF(glyph->GetGlyphWidth(), 0);

        if (i != std::char_traits<char16_t>::length(text) - 1) position += asd::Vector2DF(font->GetKerning(text[i], text[i + 1]), 0);
        instance->Sprites.push_back(sprite);
    }

    while (count++ < 1000 && instance->DoEvents()) EXPECT_TRUE(instance->Update());

    asd::Graphics::Terminate();
}