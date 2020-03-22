#pragma once

#include <memory>
#include <vector>

#include "../BaseObject.h"
#include "../Math/Vector2I.h"
#include "RenderTexture.h"

namespace Altseed {

enum class FrameEventType {
    Clear,
    SetRenderTarget,
    BeginRenderPass,
    EndRenderPass,
    EndFrame,
    Render,
    Draw,
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

class FrameEventDraw : public FrameEvent {
public:
    int32_t VbCount;
    int32_t IbCount;
};

class FrameEventRender : public FrameEvent {
public:
    int32_t IndexCount;
};

class FrameDebugger : public BaseObject {
private:
    static std::shared_ptr<FrameDebugger> instance_;

    bool isEnabled_;
    std::vector<std::shared_ptr<FrameEvent>> events_;

    template <typename... Args>
    void Write(const char16_t* format, const Args&... args);

public:
    static bool Initialize();
    static std::shared_ptr<FrameDebugger>& GetInstance();

    void Start();
    void DumpToLog();

    void Clear();
    void SetRenderTarget(const std::shared_ptr<RenderTexture>& target);
    void BeginRenderPass();
    void EndRenderPass();
    void EndFrame();
    void Draw(const int32_t vbCount, const int32_t ibCount);
    void Render(const int32_t indexCount);
};
}  // namespace Altseed