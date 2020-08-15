#include "BaseObject.h"

#include "Common/StringHelper.h"
#include "Core.h"

namespace Altseed2 {

BaseObject::BaseObject() : reference_(1) {
    core_ = Core::GetInstance();

    // for Core
    if (core_ != nullptr) {
        id_ = core_->Register(this);
    }
}

#ifdef NDEBUG
BaseObject::~BaseObject() {
#else
BaseObject::~BaseObject() noexcept(false) {
#endif
    // for Core
    if (core_ != nullptr) {
        core_->Unregister(this);
        core_ = nullptr;
    }

    ASD_ASSERT(reference_ == 0, std::string("BaseObject ") + utf16_to_utf8(instanceName_) + std::string(" must be deleted by Release"));
}

int32_t BaseObject::AddRef() {
    auto before = std::atomic_fetch_add_explicit(&reference_, 1, std::memory_order_consume);
    ASD_ASSERT(before != 0, std::string("BaseObject ") + utf16_to_utf8(instanceName_) + std::string(" invalid AddRef"));

    return reference_;
}

int32_t BaseObject::Release() {
    auto old = std::atomic_fetch_sub_explicit(&reference_, 1, std::memory_order_consume);

    if (old == 1) {
        delete this;
        return 0;
    }

    return reference_;
}

const char16_t* BaseObject::GetInstanceName() const { return instanceName_.c_str(); }

void BaseObject::SetInstanceName(const std::u16string& instanceName) { instanceName_ = instanceName; }

void BaseObject::SetInstanceName(const char* instanceName) { SetInstanceName(utf8_to_utf16(instanceName)); }

bool BaseObject::GetIsTerminateingEnabled() const {
    return terminateingEnabled_;
}

void BaseObject::SetIsTerminateingEnabled(bool value) {
    terminateingEnabled_ = value;
}

}  // namespace Altseed2