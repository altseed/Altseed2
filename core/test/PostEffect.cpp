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
#include "Graphics/Graphics.h"
#include "Graphics/Material.h"
#include "Graphics/Renderer/CullingSystem.h"
#include "Graphics/Renderer/RenderedCamera.h"
#include "Graphics/Renderer/RenderedPolygon.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Shader.h"
#include "Logger/Log.h"


TEST(PostEffect, Base) {
    const char* PostEffectCode = R"(
    Texture2D mainTex : register(t0);
    SamplerState mainSamp : register(s0);
    cbuffer Consts : register(b1)
    {
        float4 time;
    };
    struct PS_INPUT
    {
        float4  Position : SV_POSITION;
        float4  Color    : COLOR0;
        float2  UV1 : UV0;
        float2  UV2 : UV1;
    };
    float4 main(PS_INPUT input) : SV_TARGET 
    { 
        if (input.UV1.x > 0.5) {
            return float4(input.UV1, 1.0, 1.0);
        }

        float x = frac(input.UV1.x + time.x * 0.5 - floor(input.UV1.y * 10) * 0.1);

        float4 tex = mainTex.Sample(mainSamp, float2(x, input.UV1.y));
        
        return float4(tex.xyz, 1.0);
    }
    )";

    auto config = Altseed::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed::Core::Initialize(u"PostEffectBase", 1280, 720, config));

    auto instance = Altseed::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto t1 = Altseed::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed::RectF(0, 0, 400, 400));

    auto ps = Altseed::Shader::Create(u"posteffect", Altseed::utf8_to_utf16(PostEffectCode).c_str(), Altseed::ShaderStageType::Pixel);
    auto material = Altseed::MakeAsdShared<Altseed::Material>();
    material->SetShader(ps);

    std::shared_ptr<Altseed::RenderTexture> buffer = nullptr;

    int count = 0;
    while (count++ < 180 && instance->DoEvents()) {
        Altseed::CullingSystem::GetInstance()->UpdateAABB();
        Altseed::CullingSystem::GetInstance()->Cull(Altseed::RectF(Altseed::Vector2F(), Altseed::Window::GetInstance()->GetSize().To2F()));

        material->SetVector4F(u"time", Altseed::Vector4F(count / 180.0, 0.0, 0.0, 0.0));
        EXPECT_TRUE(instance->BeginFrame());

        Altseed::Renderer::GetInstance()->DrawSprite(s1);
        Altseed::Renderer::GetInstance()->Render();

        if (buffer == nullptr) {
            EXPECT_NE(cmdList->GetScreenTexture(), nullptr);
            buffer = Altseed::RenderTexture::Create(cmdList->GetScreenTexture()->GetSize());
        }
        cmdList->CopyTexture(cmdList->GetScreenTexture(), buffer);
        material->SetTexture(u"mainTex", buffer);
        cmdList->RenderToRenderTarget(material);

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed::Core::Terminate();
}
