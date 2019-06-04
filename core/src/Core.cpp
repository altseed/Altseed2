#include "Core.h"
#include "BaseObject.h"

namespace altseed {

std::shared_ptr<Core> Core::instance = nullptr;

bool Core::Initialize() {
    Core::instance = std::make_shared<Core>();
    return Core::instance != nullptr;
}

void Core::Terminate() {
    // dispose objects
    while (!Core::instance->baseObjects.empty()) {
        delete *Core::instance->baseObjects.begin();
    }

    Core::instance = nullptr;
}

std::shared_ptr<Core>& Core::GetInstance() { return instance; }

}  // namespace altseed