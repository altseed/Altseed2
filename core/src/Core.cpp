#include "Core.h"

namespace altseed {

std::shared_ptr<Core> Core::instance = nullptr;

bool Core::Initialize() { return false; }

void Core::Terminate() {}

std::shared_ptr<Core>& Core::GetInstance() { return instance; }

}  // namespace altseed