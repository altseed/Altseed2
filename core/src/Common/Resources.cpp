#include "Resources.h"

namespace altseed {

std::shared_ptr<Resources> Resources::instance = nullptr;

bool Resources::Initialize() {
    instance = std::make_shared<Resources>();
    for (int32_t i = 0; i < (int32_t)ResourceType::MAX; i++) {
        instance->m_containers[(ResourceType)i] = std::make_shared<ResourceContainer>();
    }
    return true;
}

void Resources::Terminate() { instance = nullptr; }

std::shared_ptr<Resources>& Resources::GetInstance() { return instance; }

const std::shared_ptr<ResourceContainer>& Resources::GetResourceContainer(ResourceType type) { return m_containers[type]; }

const int32_t Resources::GetResourcesCount(ResourceType type) { return m_containers[type]->GetAllResouces().size(); }

void Resources::Clear() {
    for (int32_t i = 0; i < (int32_t)ResourceType::MAX; i++) {
        m_containers[(ResourceType)i]->Clear();
    }
}

void Resources::Relaod() {
    for (int32_t i = 0; i < (int32_t)ResourceType::MAX; i++) {
        m_containers[(ResourceType)i]->Reload();
    }
}

}  // namespace altseed