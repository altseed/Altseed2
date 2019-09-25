#pragma once

#include <map>
#include <memory>
#include "ResourceContainer.h"

namespace altseed {

enum class ResourceType : int32_t { StaticFile, StreamFile, Texture2D, MAX };

class Resources {
private:
    static std::shared_ptr<Resources> instance;

    std::map<ResourceType, std::shared_ptr<ResourceContainer>> m_containers;

public:
    static bool Initialize();

    static void Terminate();

    static std::shared_ptr<Resources>& GetInstance() { return instance; }

    const std::shared_ptr<ResourceContainer>& GetResourceContainer(ResourceType type);

    const int32_t GetResourcesCount(ResourceType type);

    void Clear();

    void Relaod();
};
}  // namespace altseed