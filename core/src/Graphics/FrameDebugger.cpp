#include "FrameDebugger.h"

#include "../Common/StringHelper.h"
#include "../Logger/Log.h"

namespace Altseed {

std::shared_ptr<FrameDebugger> FrameDebugger::instance_;

std::shared_ptr<FrameDebugger>& FrameDebugger::GetInstance() { return instance_; }

bool FrameDebugger::Initialize() {
    FrameDebugger::instance_ = MakeAsdShared<FrameDebugger>();
    return true;
}

void FrameDebugger::Start() { isEnabled_ = true; }

void FrameDebugger::DumpToLog() {
    FrameDebugger::GetInstance()->Write(u"================ Frame Debug Start ================");
    for (auto&& e : events_) {
        switch (e->Type) {
            case FrameEventType::Clear: {
                Write(u"Clear");
            } break;
            case FrameEventType::SetRenderTarget: {
                auto e2 = static_cast<FrameEventSetRenderTarget*>(e.get());
                Write(u"SetRenderTarget: Target Size:({0}, {1}) Ptr:{2}", e2->TargetSize.X, e2->TargetSize.Y, e2->Ptr);
            } break;
            case FrameEventType::BeginRenderPass: {
                Write(u"BeginRenderPass");
            } break;
            case FrameEventType::EndRenderPass: {
                Write(u"EndRenderPass");
            } break;
            case FrameEventType::EndFrame: {
                Write(u"EndFrame");
            } break;
            case FrameEventType::Render: {
                auto e2 = static_cast<FrameEventRender*>(e.get());
                Write(u"Render: IndexCount:{0}", e2->IndexCount);
            } break;
            case FrameEventType::Draw: {
                auto e2 = static_cast<FrameEventDraw*>(e.get());
                Write(u"Draw: VertexCount:{0} IndexCount:{1}", e2->VbCount, e2->IbCount);
            } break;
            default:
                FrameDebugger::GetInstance()->Write(u"Unknown Event");
                break;
        }
    }
    FrameDebugger::GetInstance()->Write(u"================  Frame Debug End  ================");

    events_.clear();
}

void FrameDebugger::Clear() {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEvent>();
    e->Type = FrameEventType::Clear;
    events_.push_back(e);
}

void FrameDebugger::SetRenderTarget(const std::shared_ptr<RenderTexture>& target) {
    if (!isEnabled_) return;

    auto e = MakeAsdShared<FrameEventSetRenderTarget>();
    e->Type = FrameEventType::SetRenderTarget;
    e->TargetSize = target->GetSize();
    e->Ptr = reinterpret_cast<int64_t>(target.get());
    events_.push_back(e);
}

void FrameDebugger::BeginRenderPass() {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEvent>();
    e->Type = FrameEventType::BeginRenderPass;
    events_.push_back(e);
}

void FrameDebugger::EndRenderPass() {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEvent>();
    e->Type = FrameEventType::EndRenderPass;
    events_.push_back(e);
}

void FrameDebugger::EndFrame() {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEvent>();
    e->Type = FrameEventType::EndFrame;
    events_.push_back(e);

    isEnabled_ = false;
}

void FrameDebugger::Draw(const int32_t vbCount, const int32_t ibCount) {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEventDraw>();
    e->Type = FrameEventType::Draw;
    e->VbCount = vbCount;
    e->IbCount = ibCount;
    events_.push_back(e);
}

void FrameDebugger::Render(const int32_t indexCount) {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEventRender>();
    e->Type = FrameEventType::Render;
    e->IndexCount = indexCount;
    events_.push_back(e);
}

template <typename... Args>
void FrameDebugger::Write(const char16_t* format, const Args&... args) {
    auto& logger = Log::GetInstance();
    logger->Write(LogCategory::Graphics, LogLevel::Trace, format, args...);
}

}  // namespace Altseed