#include "ResourceContainer.h"

#include "../Core.h"

namespace Altseed {
std::shared_ptr<Resource> ResourceContainer::ResourceInfomation::GetResourcePtr() {
    if (!m_resourcePtr.expired()) return m_resourcePtr.lock();
    if (Core::GetInstance()->GetIsRegistered(rawPtr_)) {
        auto tmp = CreateAndAddSharedPtr<Resource>(rawPtr_);
        m_resourcePtr = tmp;
        return tmp;
    }
    return nullptr;
}
}  // namespace Altseed
