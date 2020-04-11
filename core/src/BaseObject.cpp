#include "BaseObject.h"

#include "Common/StringHelper.h"
#include "Core.h"

namespace Altseed {

BaseObject::BaseObject() : reference_(1) {
    core_ = Core::GetInstance();

    // for Core
    if (core_ != nullptr) {
        id_ = core_->Register(this);
    }
}

BaseObject::~BaseObject() {
    // for Core
    if (core_ != nullptr) {
        core_->Unregister(this);
        core_ = nullptr;
    }

    ASD_ASSERT(reference_ == 0, std::string("BaseObject ") + utf16_to_utf8(instanceName_) + std::string(" must be deleted by Release"));
}

const char16_t* BaseObject::GetInstanceName() const { return instanceName_.c_str(); }

void BaseObject::SetInstanceName(const std::u16string& instanceName) { instanceName_ = instanceName; }

void BaseObject::SetInstanceName(const char* instanceName) { SetInstanceName(utf8_to_utf16(instanceName)); }

}  // namespace Altseed