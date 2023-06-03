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

    const auto offset = 100.0f;

    auto pipeline1 = Altseed2::ComputePipelineState::Create();
    EXPECT_TRUE(pipeline1 != nullptr);

    auto cs = Altseed2::ShaderCompiler::GetInstance()->Compile("", "CS1", csCode1, Altseed2::ShaderStageType::Compute)->GetValue();
    EXPECT_TRUE(cs != nullptr);
    pipeline1->SetShader(cs);
    pipeline1->SetVector4F(u"offset", Altseed2::Vector4F(offset, 0, 0, 0));

    auto pipeline2 = Altseed2::ComputePipelineState::Create();
    EXPECT_TRUE(pipeline2 != nullptr);
    auto cs2 = Altseed2::ShaderCompiler::GetInstance()->Compile("", "CS2", csCode2, Altseed2::ShaderStageType::Compute)->GetValue();
    EXPECT_TRUE(cs2 != nullptr);
    pipeline2->SetShader(cs2);
    pipeline2->SetVector4F(u"offset", Altseed2::Vector4F(offset, 0, 0, 0));

    int dataSize = 256;

    auto input = Altseed2::Buffer::Create(Altseed2::BufferUsageType::MapWrite | Altseed2::BufferUsageType::CopySrc, sizeof(InputData) * dataSize);
    EXPECT_TRUE(input != nullptr);
    {
        auto data = (InputData*)input->Lock();
        for (int i = 0; i < dataSize; i++) {
            data[i].value1 = (float)i * 2;
            data[i].value2 = (float)i * 2 + 1;
        }
        input->Unlock();
    }

    auto inputBuffer = Altseed2::Buffer::Create(Altseed2::BufferUsageType::Compute | Altseed2::BufferUsageType::CopyDst, sizeof(InputData) * dataSize);
    EXPECT_TRUE(inputBuffer != nullptr);

    auto output1 = Altseed2::Buffer::Create(Altseed2::BufferUsageType::Compute | Altseed2::BufferUsageType::CopySrc, sizeof(OutputData) * dataSize);
    auto output2 = Altseed2::Buffer::Create(Altseed2::BufferUsageType::Compute | Altseed2::BufferUsageType::CopySrc, sizeof(OutputData) * dataSize);

    EXPECT_TRUE(output1 != nullptr);
    EXPECT_TRUE(output2 != nullptr);

    auto output1Dst = Altseed2::Buffer::Create(Altseed2::BufferUsageType::MapRead | Altseed2::BufferUsageType::CopyDst, sizeof(OutputData) * dataSize);
    auto output2Dst = Altseed2::Buffer::Create(Altseed2::BufferUsageType::MapRead | Altseed2::BufferUsageType::CopyDst, sizeof(OutputData) * dataSize);

    EXPECT_TRUE(output1Dst != nullptr);
    EXPECT_TRUE(output2Dst != nullptr);

    instance->GetCommandList()->Begin();

    instance->GetCommandList()->CopyBuffer(input, inputBuffer);

    instance->GetCommandList()->BeginComputePass();

    instance->GetCommandList()->SetComputeBuffer(inputBuffer, sizeof(InputData), 0);
    instance->GetCommandList()->SetComputeBuffer(output1, sizeof(OutputData), 1);
    instance->GetCommandList()->SetComputePipelineState(pipeline1);
    instance->GetCommandList()->Dispatch(dataSize, 1, 1);

    instance->GetCommandList()->SetComputeBuffer(inputBuffer, sizeof(InputData), 0);
    instance->GetCommandList()->SetComputeBuffer(output2, sizeof(OutputData), 1);
    instance->GetCommandList()->SetComputePipelineState(pipeline2);
    instance->GetCommandList()->Dispatch(dataSize, 1, 1);

    instance->GetCommandList()->EndComputePass();

    instance->GetCommandList()->CopyBuffer(output1, output1Dst);
    instance->GetCommandList()->CopyBuffer(output2, output2Dst);

    instance->GetCommandList()->End();
    instance->ExecuteCommandList();
    instance->WaitFinish();

    auto readValues = (InputData*)input->Lock();
    auto output1Values = (OutputData*)output1Dst->Lock();
    auto output2Values = (OutputData*)output2Dst->Lock();

    EXPECT_TRUE(readValues != nullptr);
    EXPECT_TRUE(output1Values != nullptr);
    EXPECT_TRUE(output2Values != nullptr);

    for (int i = 0; i < dataSize; i++) {
        EXPECT_EQ(output1Values[i].value, readValues[i].value1 * readValues[i].value2 + offset);
        EXPECT_EQ(output2Values[i].value, readValues[i].value1 * readValues[i].value2 * offset);
    }

    input->Unlock();
    output1Dst->Unlock();
    output2Dst->Unlock();

    Altseed2::Core::Terminate();
}