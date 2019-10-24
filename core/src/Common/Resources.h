#pragma once

#include <map>
#include <memory>
#include "../BaseObject.h"
#include "ResourceContainer.h"

namespace altseed {

enum class ResourceType : int32_t { StaticFile, StreamFile, Texture2D, MAX };

class Resources : public BaseObject {
private:
    static std::shared_ptr<Resources> instance;

    std::map<ResourceType, std::shared_ptr<ResourceContainer>> m_containers;

public:
    static bool Initialize();

    static void Terminate();

    static std::shared_ptr<Resources>& GetInstance();

    const std::shared_ptr<ResourceContainer>& GetResourceContainer(ResourceType type);

    const int32_t GetResourcesCount(ResourceType type);

    void Clear();

    void Relaod();
};
}  // namespace altseed