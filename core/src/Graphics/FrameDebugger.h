#pragma once

#include <memory>
#include <vector>

#include "../BaseObject.h"
#include "../Math/Matrix44F.h"
#include "../Math/Vector2I.h"
#include "../Math/Vector4F.h"
#include "RenderTexture.h"
#include "Shader.h"

namespace Altseed {

enum class FrameEventType {
    Clear,
    SetRenderTarget,
    SetRenderTargetWithRealScreen,
    BeginRenderPass,
    EndRenderPass,
    EndFrame,
    Render,
    Draw,
    Uniform,
    Texture,
    SetVertexBuffer,
    SetIndexBuffer,
};

enum class FrameEventUniformType {
    Vector,
    Matrix,
};

class FrameEvent : public BaseObject {
public:
    FrameEventType Type;
};

class FrameEventSetRenderTarget : public FrameEvent {
public:
    std::u16string Name;
    Vector2I TargetSize;
    int64_t Ptr;
};

class FrameEventSetRenderTargetWithRealScreen : public FrameEvent {
public:
};


class FrameEventDraw : public FrameEvent {
public:
    int32_t VbCount;
    int32_t IbCount;
};

class FrameEventRender : public FrameEvent {
public:
    int32_t IndexCount;
    std::u16string RTImagePath;
};

class FrameEventSetVertexBuffer : public FrameEvent {
public:
    int32_t Stride;
    int32_t Offset;
};

class FrameEventSetIndexBuffer : public FrameEvent {
public:
    int32_t Offset;
};

class FrameEventUniform : public FrameEvent {
public:
    ShaderStageType StageType;
    FrameEventUniformType DataType;
    std::u16string Name;
    Vector4F Vector;
    Matrix44F Matrix;
};

class FrameEventTexture : public FrameEvent {
public:
    ShaderStageType StageType;
    std::u16string Name;
};

class FrameDebugger : public BaseObject {
private:
    static std::shared_ptr<FrameDebugger> instance_;

    int32_t debugId_ = 0;
    int32_t dumpId_ = 0;
    bool isEnabled_;
    std::vector<std::shared_ptr<FrameEvent>> events_;

    template <typename... Args>
    void Write(const char16_t* format, const Args&... args);

public:
    static bool Initialize();
    static std::shared_ptr<FrameDebugger>& GetInstance();

    void Start();
    void End();
    void DumpToLog();

    void Clear();
    void SetRenderTarget(const std::shared_ptr<RenderTexture>& target);
    void SetRenderTargetWithRealScreen();
    void BeginRenderPass();
    void EndRenderPass();
    void EndFrame();

    void Render(const int32_t indexCount, std::u16string rtImagePath);
    void SetVertexBuffer(int32_t stride, int32_t offset);
    void SetIndexBuffer(int32_t offset);
    void Uniform(const ShaderStageType stageType, const std::u16string name, const Vector4F& vector);
    void Uniform(const ShaderStageType stageType, const std::u16string name, const Matrix44F& matrix);
    void Texture(const ShaderStageType stageType, const std::u16string name);

    std::u16string GetDebuggingRenderTargetFileNameAndMoveNext();

    bool GetIsEnabled() const;
};
}  // namespace Altseed