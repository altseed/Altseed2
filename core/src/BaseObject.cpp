#include "BaseObject.h"

#include "Core.h"

namespace Altseed {

BaseObject::BaseObject() : reference_(1) {
    core_ = Core::GetInstance();

    // for Core
    if (core_ != nullptr) {
        core_->Register(this);
    }
}

BaseObject::~BaseObject() {
    // for Core
    if (core_ != nullptr) {
        core_->Unregister(this);
        core_ = nullptr;
    }

    ASD_ASSERT(reference_ == 0, "BaseObject must be deleted by Release");
}

}  // namespace Altseed