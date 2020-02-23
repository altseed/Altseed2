
#include "Graphics/BuildinShader.h"
#include "Graphics/Graphics.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"

#include <Core.h>
#include <gtest/gtest.h>

#include <memory>

#include "Graphics/Color.h"
#include "Graphics/Font.h"
#include "Graphics/Camera.h"
#include "Graphics/CommandList.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Tool/Tool.h"

TEST(Font, Basic) {
#if defined(__APPLE__) || defined(__linux__)
    return;
#endif

    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 1280, 720, Altseed::Configuration::Create()));

    int count = 0;

    auto instance = Altseed::Graphics::GetInstance();

    auto font = Altseed::Font::LoadDynamicFont(u"TestData/Font/mplus-1m-regular.ttf", 100, Altseed::Color(255, 0, 0, 255));

    auto shader = instance->GetBuildinShader()->Create(Altseed::BuildinShaderType::FontUnlitPS);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(shader);

    std::vector<std::shared_ptr<Altseed::RenderedSprite>> sprites;
    const char16_t* text = u"こんにちは！ Hello World";
    Altseed::Vector2F position(100, 100);
    for (int32_t i = 0; i < std::char_traits<char16_t>::length(text); i++) {
        auto glyph = font->GetGlyph(text[i]);
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

        if (i != std::char_traits<char16_t>::length(text) - 1) position += Altseed::Vector2F(font->GetKerning(text[i], text[i + 1]), 0);
    }

    while (count++ < 100 && instance->DoEvents()) {
        EXPECT_TRUE(instance->BeginFrame());
        for (auto& s : sprites) {
            Altseed::Renderer::GetInstance()->DrawSprite(s);
        }
        instance->GetCommandList()->SetRenderTargetWithScreen();
        Altseed::Renderer::GetInstance()->Render(instance->GetCommandList());
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}
