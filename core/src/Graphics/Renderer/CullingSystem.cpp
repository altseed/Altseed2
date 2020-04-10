#include "CullingSystem.h"

#include "Rendered.h"

namespace Altseed {
CullingSystem::CullingSystem() {}

CullingSystem::~CullingSystem() {}

bool CullingSystem::Initialize() {
    instance_ = MakeAsdShared<CullingSystem>();
    return true;
}

void CullingSystem::Terminate() { instance_ = nullptr; }

void CullingSystem::Register(Rendered* rendered) {
    auto aabb = rendered->GetAABB();
    auto id = dynamicTree_.CreateProxy(aabb, rendered);
    proxyIdRenderedMap_[id] = rendered;
    renderedProxyIdMap_[rendered] = id;
    proxyIdAABBMap_[id] = aabb;
}

void CullingSystem::RequestUpdate(Rendered* rendered) { updateIds_.insert(renderedProxyIdMap_[rendered]); }

void CullingSystem::Update() {
    for (auto& id : updateIds_) {
        auto newAABB = proxyIdRenderedMap_[id]->GetAABB();
        dynamicTree_.MoveProxy(id, newAABB, newAABB.GetCenter() - proxyIdAABBMap_[id].GetCenter());
        proxyIdAABBMap_[id] = newAABB;
    }
}

void CullingSystem::Unregister(Rendered* rendered) {
    auto id = renderedProxyIdMap_[rendered];
    dynamicTree_.DestroyProxy(id);
    renderedProxyIdMap_.erase(rendered);
    proxyIdRenderedMap_.erase(id);
    proxyIdAABBMap_.erase(id);
}

}  // namespace Altseed