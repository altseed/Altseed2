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
            case FrameEventType::SetRenderTarget: {
                auto e2 = static_cast<FrameEventSetRenderTarget*>(e.get());
                Write(u"SetRenderTarget: Target Size:({0}, {1}) Ptr:{2}", e2->TargetSize.X, e2->TargetSize.Y, e2->Ptr);
            } break;
            case FrameEventType::EndCommandList: {
                Write(u"EndCommandList");
            } break;
            default:
                FrameDebugger::GetInstance()->Write(u"Unknown Event");
                break;
        }
    }
    FrameDebugger::GetInstance()->Write(u"================  Frame Debug End  ================");

    events_.clear();
}

void FrameDebugger::EndFrame() {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEvent>();
    e->Type = FrameEventType::EndCommandList;
    events_.push_back(e);

    isEnabled_ = false;
}

void FrameDebugger::SetRenderTarget(const std::shared_ptr<RenderTexture>& target) {
    if (!isEnabled_) return;

    auto e = MakeAsdShared<FrameEventSetRenderTarget>();
    e->Type = FrameEventType::SetRenderTarget;
    e->TargetSize = target->GetSize();
    e->Ptr = reinterpret_cast<int64_t>(target.get());
    events_.push_back(e);
}

template <typename... Args>
void FrameDebugger::Write(const char16_t* format, const Args&... args) {
    auto& logger = Log::GetInstance();
    logger->Write(LogCategory::Graphics, LogLevel::Trace, format, args...);
}

}  // namespace Altseed