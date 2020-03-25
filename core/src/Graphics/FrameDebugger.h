#pragma once

#include <memory>
#include <vector>

#include "../BaseObject.h"
#include "../LLGI/src/LLGI.Texture.h"
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

    bool isEnabled_;
    std::vector<std::shared_ptr<FrameEvent>> events_;

    template <typename... Args>
    void Write(const char16_t* format, const Args&... args);

    int32_t renderTargetCount = 0;

public:
    static bool Initialize();
    static std::shared_ptr<FrameDebugger>& GetInstance();

    void Start();
    void DumpToLog();

    void Clear();
    void SetRenderTarget(const std::shared_ptr<RenderTexture>& target);
    void SetRenderTargetWithRealScreen();
    void BeginRenderPass();
    void EndRenderPass();
    void EndFrame();
    bool Draw(const int32_t vbCount, const int32_t ibCount);
    void Render(const int32_t indexCount);
    void Uniform(const ShaderStageType stageType, const std::u16string name, const Vector4F& vector);
    void Uniform(const ShaderStageType stageType, const std::u16string name, const Matrix44F& matrix);
    void Texture(const ShaderStageType stageType, const std::u16string name);

    void DumpTexture();
};
}  // namespace Altseed