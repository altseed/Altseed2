#define _USE_MATH_DEFINES
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
#include "Graphics/Renderer/RenderedText.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "Logger/Log.h"
#include "Math/Matrix44F.h"
#include "TestHelper.h"
#include "Tool/Tool.h"

struct InputData {
    float value1;
    float value2;
};

struct OutputData {
    float value;
};

TEST(ComputeShader, Basic) {
    const char* csCode1 = R"(
struct CS_INPUT{
    float value1;
    float value2;
};

struct CS_OUTPUT{
    float value;
};

cbuffer CB : register(b0)
{
  float4 offset;
};

RWStructuredBuffer<CS_INPUT> read : register(u0);
RWStructuredBuffer<CS_OUTPUT> write : register(u1);

[numthreads(1, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
   write[dtid.x].value = read[dtid.x].value1 * read[dtid.x].value2 + offset.x;
}
)";

    const char* csCode2 = R"(
struct CS_INPUT{
    float value1;
    float value2;
};

struct CS_OUTPUT{
    float value;
};

cbuffer CB : register(b0)
{
  float4 offset;
};

RWStructuredBuffer<CS_INPUT> read : register(u0);
RWStructuredBuffer<CS_OUTPUT> write : register(u1);

[numthreads(1, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
   write[dtid.x].value = read[dtid.x].value1 * read[dtid.x].value2 * offset.x;
}
)";

    auto config = Altseed2TestConfig(Altseed2::CoreModules::Graphics);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"Initialize", 1280, 720, config));

    int count = 0;

    auto instance = Altseed2::Graphics::GetInstance();
    EXPECT_TRUE(instance != nullptr);

    auto pipeline1 = Altseed2::ComputePipelineState::Create();
    auto cs = Altseed2::ShaderCompiler::GetInstance()->Compile("", "CS1", csCode1, Altseed2::ShaderStageType::Compute)->GetValue();
    pipeline1->SetShader(cs);
    pipeline1->SetVector4F(u"offset", Altseed2::Vector4F(100, 0, 0, 0));

    auto pipeline2 = Altseed2::ComputePipelineState::Create();
    auto cs2 = Altseed2::ShaderCompiler::GetInstance()->Compile("", "CS2", csCode2, Altseed2::ShaderStageType::Compute)->GetValue();
    pipeline2->SetShader(cs2);
    pipeline2->SetVector4F(u"offset", Altseed2::Vector4F(100, 0, 0, 0));

    int dataSize = 256;

    auto read = Altseed2::Buffer::Create(Altseed2::BufferUsageType::Compute, sizeof(InputData) * dataSize);

    {
        auto data = (InputData*)read->Lock();
        for (int i = 0; i < dataSize; i++) {
            data[i].value1 = (float)i * 2;
            data[i].value2 = (float)i * 2 + 1;
        }
        read->Unlock();
    }

    auto write = Altseed2::Buffer::Create(Altseed2::BufferUsageType::Compute, sizeof(OutputData) * dataSize);
    auto write2 = Altseed2::Buffer::Create(Altseed2::BufferUsageType::Compute, sizeof(OutputData) * dataSize);

    while (count++ < 10 && instance->DoEvents()) {
        Altseed2::RenderPassParameter renderPassParameter;
        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));
        instance->GetCommandList()->PauseRenderPass();

        instance->GetCommandList()->UploadBuffer(read);
        
        instance->GetCommandList()->BeginComputePass();

        instance->GetCommandList()->SetComputeBuffer(read, sizeof(InputData), 0);
        instance->GetCommandList()->SetComputeBuffer(write, sizeof(OutputData), 1);
        instance->GetCommandList()->SetComputePipelineState(pipeline1);
        instance->GetCommandList()->Dispatch(dataSize, 1, 1);

        instance->GetCommandList()->SetComputeBuffer(read, sizeof(InputData), 0);
        instance->GetCommandList()->SetComputeBuffer(write2, sizeof(OutputData), 1);
        instance->GetCommandList()->SetComputePipelineState(pipeline2);
        instance->GetCommandList()->Dispatch(dataSize, 1, 1);

        instance->GetCommandList()->EndComputePass();

        instance->GetCommandList()->ReadbackBuffer(write);
        instance->GetCommandList()->ReadbackBuffer(write2);

        EXPECT_TRUE(instance->EndFrame());

        {
            auto data = (OutputData*)write->Read();
            for (int i = 0; i < dataSize; i++) {
                std::cout << "write[" << i << "] = " << data[i].value << std::endl;
            }
        }
        {
            auto data = (OutputData*)write2->Read();
            for (int i = 0; i < dataSize; i++) {
                std::cout << "write2[" << i << "] = " << data[i].value << std::endl;
            }
        }

        renderPassParameter.ClearColor = Altseed2::Color(50, 50, 50, 255);
        renderPassParameter.IsColorCleared = true;
        renderPassParameter.IsDepthCleared = true;
        EXPECT_TRUE(instance->BeginFrame(renderPassParameter));
        EXPECT_TRUE(instance->EndFrame());
    }

    Altseed2::Core::Terminate();
}