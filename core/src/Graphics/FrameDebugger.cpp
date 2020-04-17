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

void FrameDebugger::Start() {
    isEnabled_ = true;
    dumpId_ = 0;
    debugId_++;
    events_.clear();
}

void FrameDebugger::End() { isEnabled_ = false; }

void FrameDebugger::DumpToLog() {
    FrameDebugger::GetInstance()->Write(u"================ Frame Debug Start ================");
    for (auto&& e : events_) {
        switch (e->Type) {
            case FrameEventType::Clear: {
                Write(u"Clear");
            } break;
            case FrameEventType::SetRenderTarget: {
                auto e2 = static_cast<FrameEventSetRenderTarget*>(e.get());
                if (e2->Name != u"") {
                    Write(u"SetRenderTarget: Target Size:({0}, {1}) Name:{2}", e2->TargetSize.X, e2->TargetSize.Y, utf16_to_utf8(e2->Name));
                } else {
                    Write(u"SetRenderTarget: Target Size:({0}, {1}) Ptr:{2}", e2->TargetSize.X, e2->TargetSize.Y, e2->Ptr);
                }
            } break;
            case FrameEventType::SetRenderTargetWithRealScreen: {
                Write(u"SetRenderTargetWithRealScreen");
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
                Write(u"Render: IndexCount:{0} RT:{1}", e2->IndexCount, utf16_to_utf8(e2->RTImagePath));
            } break;
            case FrameEventType::Draw: {
                auto e2 = static_cast<FrameEventDraw*>(e.get());
                Write(u"Draw: VertexCount:{0} IndexCount:{1}", e2->VbCount, e2->IbCount);
            } break;
            case FrameEventType::SetVertexBuffer: {
                auto e2 = static_cast<FrameEventSetVertexBuffer*>(e.get());
                Write(u"VertexBuffer: Stride:{0} Offset:{1}", e2->Stride, e2->Offset);
            } break;
            case FrameEventType::SetIndexBuffer: {
                auto e2 = static_cast<FrameEventSetIndexBuffer*>(e.get());
                Write(u"IndexBuffer: Offset:{0}", e2->Offset);
            } break;
            case FrameEventType::Uniform: {
                auto e2 = static_cast<FrameEventUniform*>(e.get());
                auto stage = e2->StageType == ShaderStageType::Pixel ? "Pixel" : "Vertex";
                if (e2->DataType == FrameEventUniformType::Vector) {
                    auto v = e2->Vector;
                    Write(u"Uniform: Stage:{0} Name:{1} Vector:({2}, {3}, {4}, {5})", stage, utf16_to_utf8(e2->Name), v.X, v.Y, v.Z, v.W);
                } else {
                    auto m = e2->Matrix.Values;
                    Write(u"Uniform: Stage:{0} Name:{1} matrix:(\n"
                          u"{2},\t{3},\t{4},\t{5},\n"
                          u"{6},\t{7},\t{8},\t{9}, \n"
                          u"{10},\t{11},\t{12},\t{13}, \n"
                          u"{14},\t{15},\t{16},\t{17})",
                          stage,
                          utf16_to_utf8(e2->Name),
                          m[0][0],
                          m[0][1],
                          m[0][2],
                          m[0][3],
                          m[1][0],
                          m[1][1],
                          m[1][2],
                          m[1][3],
                          m[2][0],
                          m[2][1],
                          m[2][2],
                          m[2][3],
                          m[3][0],
                          m[3][1],
                          m[3][2],
                          m[3][3]);
                }

            } break;
            case FrameEventType::Texture: {
                auto e2 = static_cast<FrameEventTexture*>(e.get());
                auto stage = e2->StageType == ShaderStageType::Pixel ? "Pixel" : "Vertex";
                Write(u"Texture: Stage:{0} Name:{1}", stage, utf16_to_utf8(e2->Name));
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
    e->Name = target->GetInstanceName();
    e->TargetSize = target->GetSize();
    e->Ptr = reinterpret_cast<int64_t>(target.get());
    events_.push_back(e);
}

void FrameDebugger::SetRenderTargetWithRealScreen() {
    if (!isEnabled_) return;

    auto e = MakeAsdShared<FrameEventSetRenderTargetWithRealScreen>();
    e->Type = FrameEventType::SetRenderTargetWithRealScreen;
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

void FrameDebugger::Render(const int32_t indexCount, std::u16string rtImagePath) {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEventRender>();
    e->Type = FrameEventType::Render;
    e->IndexCount = indexCount;
    e->RTImagePath = rtImagePath;
    events_.push_back(e);
}

void FrameDebugger::SetVertexBuffer(int32_t stride, int32_t offset) {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEventSetVertexBuffer>();
    e->Type = FrameEventType::SetVertexBuffer;
    e->Stride = stride;
    e->Offset = offset;
    events_.push_back(e);
}

void FrameDebugger::SetIndexBuffer(int32_t offset) {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEventSetIndexBuffer>();
    e->Type = FrameEventType::SetIndexBuffer;
    e->Offset = offset;
    events_.push_back(e);
}

void FrameDebugger::Uniform(const ShaderStageType stageType, const std::u16string name, const Vector4F& vector) {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEventUniform>();
    e->Type = FrameEventType::Uniform;
    e->StageType = stageType;
    e->Name = name;
    e->DataType = FrameEventUniformType::Vector;
    e->Vector = vector;
    events_.push_back(e);
}

void FrameDebugger::Uniform(const ShaderStageType stageType, const std::u16string name, const Matrix44F& matrix) {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEventUniform>();
    e->Type = FrameEventType::Uniform;
    e->StageType = stageType;
    e->Name = name;
    e->DataType = FrameEventUniformType::Matrix;
    e->Matrix = matrix;
    events_.push_back(e);
}

void FrameDebugger::Texture(const ShaderStageType stageType, const std::u16string name) {
    if (!isEnabled_) return;
    auto e = MakeAsdShared<FrameEventTexture>();
    e->Type = FrameEventType::Texture;
    e->StageType = stageType;
    e->Name = name;
    events_.push_back(e);
}

std::u16string FrameDebugger::GetDebuggingRenderTargetFileNameAndMoveNext() {
    std::u16string ret;
    ret += u"rt_";
    ret += ToString(debugId_);
    ret += u"_";
    ret += ToString(dumpId_);
    ret += u".png";
    dumpId_ += 1;
    return ret;
}

bool FrameDebugger::GetIsEnabled() const { return isEnabled_; }

template <typename... Args>
void FrameDebugger::Write(const char16_t* format, const Args&... args) {
    auto& logger = Log::GetInstance();
    logger->Write(LogCategory::Graphics, LogLevel::Trace, format, args...);
}

}  // namespace Altseed