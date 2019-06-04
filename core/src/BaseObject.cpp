#include "BaseObject.h"
#include "Core.h"

namespace altseed {

BaseObject::BaseObject() : reference_(1) {
    core_ = Core::GetInstance();
    core_->Register(this);
}

BaseObject::~BaseObject() {
    core_->Unregister(this);
    core_ = nullptr;
    reference_ = 0;
}

}  // namespace altseed