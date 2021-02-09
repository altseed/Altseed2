#pragma once

#include <map>
#include <memory>

#include "../BaseObject.h"
#include "../StdIntCBG.h"
#include "ResourceContainer.h"

namespace Altseed2 {

enum class ResourceType : int32_t { StaticFile,
                                    StreamFile,
                                    Texture2D,
                                    Font,
                                    Sound,
                                    MAX };

class Resources : public BaseObject {
private:
    static std::shared_ptr<Resources> instance;

    std::map<ResourceType, std::shared_ptr<ResourceContainer>> m_containers;

public:
#if !USE_CBG
    static bool Initialize();

    static void Terminate();
#endif

    static std::shared_ptr<Resources>& GetInstance();

#if !USE_CBG

    const std::shared_ptr<ResourceContainer>& GetResourceContainer(ResourceType type);

#endif

    const int32_t GetResourcesCount(ResourceType type);

    void Clear();

    void Reload();
};
}  // namespace Altseed2