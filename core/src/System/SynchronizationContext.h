#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <vector>

#include "../BaseObject.h"

namespace Altseed2 {

class SynchronizationContext : public BaseObject {
private:
    static std::shared_ptr<SynchronizationContext> instance_;

    struct Event {
        std::function<void()> f;

        void Call() { f(); }
    };

    std::vector<std::unique_ptr<Event>> events_;

public:
    void AddEvent(const std::function<void()>& f);

    void Run();

    static void Initialize();

    static void Terminate();

    static std::shared_ptr<SynchronizationContext>& GetInstance();
};

}  // namespace Altseed2