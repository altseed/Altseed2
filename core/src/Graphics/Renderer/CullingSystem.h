#pragma once

#include <box2d/b2_dynamic_tree.h>

#include <map>
#include <set>

#include "../../BaseObject.h"

namespace Altseed {
class Rendered;
class CullingSystem : public BaseObject {
private:
    static std::shared_ptr<CullingSystem> instance_;

    b2DynamicTree dynamicTree_;
    std::map<int32_t, std::shared_ptr<Rendered>> proxyIdRenderedMap_;
    std::map<std::shared_ptr<Rendered>, int32_t> renderedProxyIdMap_;
    std::map<int32_t, b2AABB> proxyIdAABBMap_;

    std::set<int32_t> updateIds_;

public:
    CullingSystem();
    virtual ~CullingSystem();

    static std::shared_ptr<CullingSystem>& GetInstance() { return instance_; }

    static bool Initialize();

    static void Terminate();

    void Register(std::shared_ptr<Rendered> rendered);
    void RequestUpdate(std::shared_ptr<Rendered> rendered);
    void Update();
    void Unregister(std::shared_ptr<Rendered> rendered);
};

}  // namespace Altseed