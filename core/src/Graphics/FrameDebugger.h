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
    BeginCommandList,
    EndCommandList,
    Render,
};

class FrameEvent : public BaseObject {
public:
    FrameEventType Type;
};

class FrameEventSetRenderTarget : public FrameEvent {
public:
    Vector2I TargetSize;
    int64_t Ptr;
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
    void BeginCommandList();
    void Render();
    void EndFrame();
};
}  // namespace Altseed