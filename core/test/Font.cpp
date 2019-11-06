#include "Graphics/Graphics.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Graphics/Color.h"
#include "Graphics/Font.h"
#include "Graphics/Sprite.h"

namespace asd = altseed;

TEST(Font, Basic) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 1280, 720, asd::CoreOption()));

    int count = 0;

    auto instance = asd::Graphics::GetInstance();

    auto font = asd::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100, asd::Color(255, 0, 0, 255));

    auto shader = instance->CreateShader(instance->HlslPSCode);
    auto material = std::make_shared<asd::Material>();
    material->SetShader(shader);

    char16_t* text = u"Ç±ÇÒÇ…ÇøÇÕÅI Hello World";
    asd::Vector2DF position(100, 100);
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        auto texture = font->GetGlyphTexture(text[i]);
        if (texture == nullptr) continue;

        auto sprite = std::make_shared<asd::Sprite>();
        sprite->SetMaterial(material);
        sprite->SetTexture(texture->GetNativeTexture());
        sprite->SetPosition(position);
        sprite->SetSize(texture->GetSize().To2DF());
        position += asd::Vector2DF(texture->GetSize().X, 0);

		if (i != std::char_traits<char16_t>::length(text) - 1) position += asd::Vector2DF(font->GetKerning(text[i], text[i + 1]), 0);
        instance->Sprites.push_back(sprite);
    }

    while (count++ < 1000 && instance->DoEvents()) EXPECT_TRUE(instance->Update());

    asd::Graphics::Terminate();
}