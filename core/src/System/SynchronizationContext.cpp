#include "SynchronizationContext.h"

namespace Altseed {

std::shared_ptr<SynchronizationContext> SynchronizationContext::instance_;

void SynchronizationContext::AddEvent(const std::function<void()>& f) {
    auto e = std::make_unique<Event>();
    e->f = f;
    events_.push_back(std::move(e));
}

void SynchronizationContext::Run() {
    for (auto& e : events_) {
        e->Call();
    }
}

void SynchronizationContext::Initialize() { instance_ = MakeAsdShared<SynchronizationContext>(); }

void SynchronizationContext::Terminate() { instance_.reset(); }

std::shared_ptr<SynchronizationContext>& SynchronizationContext::GetInstance() { return instance_; }

}  // namespace Altseed