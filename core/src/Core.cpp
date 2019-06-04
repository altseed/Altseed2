#include "Core.h"

namespace altseed {

std::shared_ptr<Core> Core::instance = nullptr;

bool Core::Initialize() {
    Core::instance = std::make_shared<Core>();
    return Core::instance != nullptr;
}

void Core::Terminate() {
    // dispose objects
    for (auto item : Core::instance->baseObjects) {
        delete item;
    }

    Core::instance = nullptr;
}

std::shared_ptr<Core>& Core::GetInstance() { return instance; }

}  // namespace altseed