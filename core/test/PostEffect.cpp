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

    auto config = Altseed2::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"PostEffectBase", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 400, 400));

    auto ps = Altseed2::Shader::Create(u"posteffect", Altseed2::utf8_to_utf16(PostEffectCode).c_str(), Altseed2::ShaderStageType::Pixel);
    auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
    material->SetShader(ps);

    std::shared_ptr<Altseed2::RenderTexture> buffer = nullptr;

    int count = 0;
    while (count++ < 180 && instance->DoEvents()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        material->SetVector4F(u"time", Altseed2::Vector4F(count / 180.0, 0.0, 0.0, 0.0));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->Render();

        if (buffer == nullptr) {
            EXPECT_NE(cmdList->GetScreenTexture(), nullptr);
            buffer = Altseed2::RenderTexture::Create(cmdList->GetScreenTexture()->GetSize());
        }
        cmdList->CopyTexture(cmdList->GetScreenTexture(), buffer);
        material->SetTexture(u"mainTex", buffer);
        cmdList->RenderToRenderTarget(material);

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed2::Core::Terminate();
}

TEST(PostEffect, Builtin) {
    auto config = Altseed2::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"PostEffect Builtin", 400, 300, config));

    auto instance = Altseed2::Graphics::GetInstance();

    Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"Sepia");
    Altseed2::Shader::Create(u"Sepia", instance->GetBuiltinShader()->GetSepiaShader(), Altseed2::ShaderStageType::Pixel);

    Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"GrayScale");
    Altseed2::Shader::Create(u"GrayScale", instance->GetBuiltinShader()->GetGrayScaleShader(), Altseed2::ShaderStageType::Pixel);

    Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"Downsample");
    Altseed2::Shader::Create(u"Downsample", instance->GetBuiltinShader()->GetDownsampleShader(), Altseed2::ShaderStageType::Pixel);

    {
        auto baseCode = instance->GetBuiltinShader()->GetGaussianBlurShader();

        {
            auto code = u"#define BLUR_X\n" + std::u16string(baseCode);
            Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"GaussianBlur_X");
            Altseed2::Shader::Create(u"GaussianBlur_X", code.c_str(), Altseed2::ShaderStageType::Pixel);
        }

        {
            auto code = u"#define BLUR_Y\n" + std::u16string(baseCode);
            Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"GaussianBlur_Y");
            Altseed2::Shader::Create(u"GaussianBlur_Y", code.c_str(), Altseed2::ShaderStageType::Pixel);
        }
    }

    {
        auto baseCode = instance->GetBuiltinShader()->GetLightBloomShader();

        {
            auto code = u"#define BLUR_X 1\n" + std::u16string(baseCode);
            Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"LightBloom_X");
            Altseed2::Shader::Create(u"LightBloom_X", code.c_str(), Altseed2::ShaderStageType::Pixel);
        }

        {
            auto code = u"#define BLUR_X 1\n#define LUM 1\n" + std::u16string(baseCode);
            Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"LightBloom_X_Lum");
            Altseed2::Shader::Create(u"LightBloom_X_Lum", code.c_str(), Altseed2::ShaderStageType::Pixel);
        }

        {
            auto code = u"#define BLUR_Y 1\n" + std::u16string(baseCode);
            Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"LightBloom_Y");
            Altseed2::Shader::Create(u"LightBloom_Y", code.c_str(), Altseed2::ShaderStageType::Pixel);
        }

        auto textureMixCode = instance->GetBuiltinShader()->GetTextureMixShader();

        {
            auto code = std::u16string(textureMixCode);
            Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"LightBloom_SUM");
            Altseed2::Shader::Create(u"LightBloom_SUM", code.c_str(), Altseed2::ShaderStageType::Pixel);
        }
    }

    Altseed2::Core::Terminate();
}

TEST(PostEffect, Sepia) {
    auto config = Altseed2::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"PostEffect Sepia", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 400, 400));

    auto ps = Altseed2::Shader::Create(u"sepia", instance->GetBuiltinShader()->GetSepiaShader(), Altseed2::ShaderStageType::Pixel);
    auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
    material->SetShader(ps);

    std::shared_ptr<Altseed2::RenderTexture> buffer = nullptr;

    int count = 0;
    while (count++ < 180 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->Render();

        if (buffer == nullptr) {
            EXPECT_TRUE(cmdList->GetScreenTexture() != nullptr);
            buffer = Altseed2::RenderTexture::Create(cmdList->GetScreenTexture()->GetSize());
        }
        cmdList->CopyTexture(cmdList->GetScreenTexture(), buffer);
        material->SetTexture(u"mainTex", buffer);
        cmdList->RenderToRenderTarget(material);

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"PostEffect.Sepia.png");
        }
    }

    Altseed2::Core::Terminate();
}

TEST(PostEffect, GrayScale) {
    auto config = Altseed2::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"PostEffect GrayScale", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 400, 400));

    auto ps = Altseed2::Shader::Create(u"GrayScale", instance->GetBuiltinShader()->GetGrayScaleShader(), Altseed2::ShaderStageType::Pixel);
    auto material = Altseed2::MakeAsdShared<Altseed2::Material>();
    material->SetShader(ps);

    std::shared_ptr<Altseed2::RenderTexture> buffer = nullptr;

    int count = 0;
    while (count++ < 180 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->Render();

        if (buffer == nullptr) {
            EXPECT_TRUE(cmdList->GetScreenTexture() != nullptr);
            buffer = Altseed2::RenderTexture::Create(cmdList->GetScreenTexture()->GetSize());
        }
        cmdList->CopyTexture(cmdList->GetScreenTexture(), buffer);
        material->SetTexture(u"mainTex", buffer);
        cmdList->RenderToRenderTarget(material);

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"PostEffect.GrayScale.png");
        }
    }

    Altseed2::Core::Terminate();
}

TEST(PostEffect, GaussianBlur) {
    auto config = Altseed2::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"PostEffect LightBloom", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 400, 400));

    auto materialX = Altseed2::MakeAsdShared<Altseed2::Material>();
    auto materialY = Altseed2::MakeAsdShared<Altseed2::Material>();

    {
        auto baseCode = std::u16string(instance->GetBuiltinShader()->GetGaussianBlurShader());
        auto codeX = u"#define BLUR_X\n" + baseCode;
        Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"GaussianBlur_X");
        materialX->SetShader(Altseed2::Shader::Create(u"X", codeX.c_str(), Altseed2::ShaderStageType::Pixel));

        auto codeY = u"#define BLUR_Y\n" + baseCode;
        Altseed2::Log::GetInstance()->Debug(Altseed2::LogCategory::Core, u"GaussianBlur_Y");
        materialY->SetShader(Altseed2::Shader::Create(u"Y", codeY.c_str(), Altseed2::ShaderStageType::Pixel));
    }

    std::shared_ptr<Altseed2::RenderTexture> tempTexture = nullptr;

    // Shader Parameter
    auto intensity = 2.0f;

    int count = 0;
    while (count++ < 180 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->Render();

        {
            Altseed2::Vector4F weights;
            float ws[3];
            float total = 0.0f;
            float const dispersion = intensity * intensity;
            for (int32_t i = 0; i < 3; i++) {
                float pos = 1.0f + 2.0f * i;
                ws[i] = expf(-0.5f * pos * pos / dispersion);
                total += ws[i] * 2.0f;
            }
            weights.X = ws[0] / total;
            weights.Y = ws[1] / total;
            weights.Z = ws[2] / total;
            weights.W = 0.0f;

            auto src = cmdList->GetScreenTexture();
            auto size = src->GetSize();

            materialX->SetTexture(u"mainTex", src);
            materialX->SetVector4F(u"weight", weights);
            // materialX->SetTextureFilterType(u"mainTex", TextureFilterType::Linear);

            if (tempTexture == nullptr) {
                tempTexture = Altseed2::RenderTexture::Create(size);
            }

            cmdList->RenderToRenderTexture(materialX, tempTexture, renderPassParameter);

            // DrawOnTexture2DWithMaterial(tempTexture, materialX);

            materialY->SetTexture(u"mainTex", tempTexture);
            materialY->SetVector4F(u"weight", weights);
            // materialY->SetTextureFilterType(u"mainTex", TextureFilterType::Linear);

            cmdList->RenderToRenderTarget(materialY);
        }

        EXPECT_TRUE(instance->EndFrame());

        // Take a screenshot
        if (count == 5) {
            Altseed2::Graphics::GetInstance()->SaveScreenshot(u"PostEffect.GaussianBlur.png");
        }
    }

    Altseed2::Core::Terminate();
}

TEST(PostEffect, LightBloom) {
    auto config = Altseed2::Configuration::Create();
    config->SetConsoleLoggingEnabled(true);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"PostEffect LightBloom", 1280, 720, config));

    auto instance = Altseed2::Graphics::GetInstance();
    auto cmdList = instance->GetCommandList();

    auto t1 = Altseed2::Texture2D::Load(u"TestData/IO/AltseedPink.png");
    EXPECT_TRUE(t1 != nullptr);

    auto s1 = Altseed2::RenderedSprite::Create();
    s1->SetTexture(t1);
    s1->SetSrc(Altseed2::RectF(0, 0, 400, 400));

    auto materialX = Altseed2::MakeAsdShared<Altseed2::Material>();
    auto materialY = Altseed2::MakeAsdShared<Altseed2::Material>();
    auto materialSum = Altseed2::MakeAsdShared<Altseed2::Material>();
    auto materialDownsample = Altseed2::MakeAsdShared<Altseed2::Material>();
    auto materialHighLuminance = Altseed2::MakeAsdShared<Altseed2::Material>();

    {
        auto codeHighLuminance = u"#define LUM_MODE\n" + std::u16string(instance->GetBuiltinShader()->GetHighLuminanceShader());
        materialHighLuminance->SetShader(
                Altseed2::Shader::Create(u"highluminance", codeHighLuminance.c_str(), Altseed2::ShaderStageType::Pixel));

        auto codeDownSample = std::u16string(instance->GetBuiltinShader()->GetDownsampleShader());
        materialDownsample->SetShader(Altseed2::Shader::Create(u"downsample", codeDownSample.c_str(), Altseed2::ShaderStageType::Pixel));

        auto baseCode = instance->GetBuiltinShader()->GetLightBloomShader();

        auto codeX = u"#define BLUR_X 1\n" + std::u16string(baseCode);
        materialX->SetShader(Altseed2::Shader::Create(u"X", codeX.c_str(), Altseed2::ShaderStageType::Pixel));

        auto codeY = u"#define BLUR_Y 1\n" + std::u16string(baseCode);
        materialY->SetShader(Altseed2::Shader::Create(u"Y", codeY.c_str(), Altseed2::ShaderStageType::Pixel));

        auto codeSum = std::u16string(instance->GetBuiltinShader()->GetTextureMixShader());
        materialSum->SetShader(Altseed2::Shader::Create(u"Sum", codeSum.c_str(), Altseed2::ShaderStageType::Pixel));
    }

    std::shared_ptr<Altseed2::RenderTexture> highLuminanceTexture = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> tempTexture0 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> tempTexture1 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> tempTexture2 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> tempTexture3 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> downsampledTexture0 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> downsampledTexture1 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> downsampledTexture2 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> downsampledTexture3 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> sumTexture0 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> sumTexture1 = nullptr;
    std::shared_ptr<Altseed2::RenderTexture> srcBuffer = nullptr;

    // Shader Parameter
    auto intensity = 10.0f;
    auto threshold = 0.1f;
    auto exposure = 2.0f;

    int count = 0;
    while (count++ < 180 && instance->DoEvents() && Altseed2::Core::GetInstance()->DoEvent()) {
        Altseed2::CullingSystem::GetInstance()->UpdateAABB();
        Altseed2::CullingSystem::GetInstance()->Cull(Altseed2::RectF(Altseed2::Vector2F(), Altseed2::Window::GetInstance()->GetSize().To2F()));

        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));

        Altseed2::Renderer::GetInstance()->DrawSprite(s1);
        Altseed2::Renderer::GetInstance()->Render();

        {
            auto src = cmdList->GetScreenTexture();
            auto size = src->GetSize();

            if (highLuminanceTexture == nullptr) {
                highLuminanceTexture = Altseed2::RenderTexture::Create(size);

                tempTexture0 = Altseed2::RenderTexture::Create(size / 2);
                tempTexture1 = Altseed2::RenderTexture::Create(size / 4);
                tempTexture2 = Altseed2::RenderTexture::Create(size / 8);
                tempTexture3 = Altseed2::RenderTexture::Create(size / 16);

                downsampledTexture0 = Altseed2::RenderTexture::Create(size / 2);
                downsampledTexture1 = Altseed2::RenderTexture::Create(size / 4);
                downsampledTexture2 = Altseed2::RenderTexture::Create(size / 8);
                downsampledTexture3 = Altseed2::RenderTexture::Create(size / 16);

                sumTexture0 = Altseed2::RenderTexture::Create(size);
                sumTexture1 = Altseed2::RenderTexture::Create(size);

                srcBuffer = Altseed2::RenderTexture::Create(size);
            }

            cmdList->CopyTexture(src, srcBuffer);

            // 高輝度抽出
            materialHighLuminance->SetTexture(u"mainTex", srcBuffer);
            materialHighLuminance->SetVector4F(u"threshold", Altseed2::Vector4F(threshold, threshold, threshold, threshold));
            materialHighLuminance->SetVector4F(u"exposure", Altseed2::Vector4F(exposure, exposure, exposure, exposure));
            cmdList->RenderToRenderTexture(materialHighLuminance, highLuminanceTexture, renderPassParameter);

            // ダウンサンプリング
            materialDownsample->SetTexture(u"mainTex", highLuminanceTexture);
            materialDownsample->SetVector4F(
                    u"imageSize", Altseed2::Vector4F(downsampledTexture0->GetSize().X, downsampledTexture0->GetSize().Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialDownsample, downsampledTexture0, renderPassParameter);

            materialDownsample->SetTexture(u"mainTex", downsampledTexture0);
            materialDownsample->SetVector4F(
                    u"imageSize", Altseed2::Vector4F(downsampledTexture1->GetSize().X, downsampledTexture1->GetSize().Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialDownsample, downsampledTexture1, renderPassParameter);

            materialDownsample->SetTexture(u"mainTex", downsampledTexture1);
            materialDownsample->SetVector4F(
                    u"imageSize", Altseed2::Vector4F(downsampledTexture2->GetSize().X, downsampledTexture2->GetSize().Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialDownsample, downsampledTexture2, renderPassParameter);

            materialDownsample->SetTexture(u"mainTex", downsampledTexture2);
            materialDownsample->SetVector4F(
                    u"imageSize", Altseed2::Vector4F(downsampledTexture3->GetSize().X, downsampledTexture3->GetSize().Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialDownsample, downsampledTexture3, renderPassParameter);

            // ブラー
            materialX->SetVector4F(u"intensity", Altseed2::Vector4F(intensity, intensity, intensity, intensity));
            materialY->SetVector4F(u"intensity", Altseed2::Vector4F(intensity, intensity, intensity, intensity));

            Altseed2::Vector2I imageSize;

            // ブラー1
            imageSize = downsampledTexture1->GetSize();
            materialX->SetTexture(u"mainTex", downsampledTexture1);
            materialX->SetVector4F(u"imageSize", Altseed2::Vector4F(imageSize.X, imageSize.Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialX, tempTexture1, renderPassParameter);

            imageSize = tempTexture1->GetSize();
            materialY->SetTexture(u"mainTex", tempTexture1);
            materialY->SetVector4F(u"imageSize", Altseed2::Vector4F(imageSize.X, imageSize.Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialY, downsampledTexture1, renderPassParameter);

            // ブラー2
            imageSize = downsampledTexture2->GetSize();
            materialX->SetTexture(u"mainTex", downsampledTexture2);
            materialX->SetVector4F(u"imageSize", Altseed2::Vector4F(imageSize.X, imageSize.Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialX, tempTexture2, renderPassParameter);

            imageSize = tempTexture2->GetSize();
            materialY->SetTexture(u"mainTex", tempTexture2);
            materialY->SetVector4F(u"imageSize", Altseed2::Vector4F(imageSize.X, imageSize.Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialY, downsampledTexture2, renderPassParameter);

            // ブラー3
            imageSize = downsampledTexture3->GetSize();
            materialX->SetTexture(u"mainTex", downsampledTexture3);
            materialX->SetVector4F(u"imageSize", Altseed2::Vector4F(imageSize.X, imageSize.Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialX, tempTexture3, renderPassParameter);

            imageSize = tempTexture3->GetSize();
            materialY->SetTexture(u"mainTex", tempTexture3);
            materialY->SetVector4F(u"imageSize", Altseed2::Vector4F(imageSize.X, imageSize.Y, 0.0f, 0.0f));
            cmdList->RenderToRenderTexture(materialY, downsampledTexture3, renderPassParameter);

            // 合計
            materialSum->SetTexture(u"mainTex1", src);
            materialSum->SetTexture(u"mainTex2", downsampledTexture1);
            materialSum->SetVector4F(u"weight", Altseed2::Vector4F(0.5f, 0.5f, 0.5f, 0.5f));
            cmdList->RenderToRenderTexture(materialSum, sumTexture0, renderPassParameter);

            materialSum->SetTexture(u"mainTex1", sumTexture0);
            materialSum->SetTexture(u"mainTex2", downsampledTexture2);
            materialSum->SetVector4F(u"weight", Altseed2::Vector4F(0.25f, 0.25f, 0.25f, 0.25f));
            cmdList->RenderToRenderTexture(materialSum, sumTexture1, renderPassParameter);

            materialSum->SetTexture(u"mainTex1", sumTexture1);
            materialSum->SetTexture(u"mainTex2", downsampledTexture3);
            materialSum->SetVector4F(u"weight", Altseed2::Vector4F(0.125f, 0.125f, 0.125f, 0.125f));
            cmdList->RenderToRenderTarget(materialSum);

            // Take a screenshot
            if (count == 5) {
                Altseed2::Graphics::GetInstance()->SaveScreenshot(u"PostEffect.LightBloom.png");
            }
        }

        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed2::Core::Terminate();
}