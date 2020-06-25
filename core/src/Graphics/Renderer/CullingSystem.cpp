#include "CullingSystem.h"

#include "../../Logger/Log.h"
#include "Rendered.h"

namespace Altseed2 {
std::shared_ptr<CullingSystem> CullingSystem::instance_ = nullptr;

CullingSystem::CullingSystem() { drawingRenderedIds_ = MakeAsdShared<Int32Array>(); }

CullingSystem::~CullingSystem() {}

std::shared_ptr<CullingSystem>& CullingSystem::GetInstance() { return instance_; }

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

void CullingSystem::RequestUpdateAABB(Rendered* rendered) { updateIds_.insert(renderedProxyIdMap_[rendered]); }

void CullingSystem::UpdateAABB() {
    for (auto& id : updateIds_) {
        auto newAABB = proxyIdRenderedMap_[id]->GetAABB();
        dynamicTree_.MoveProxy(id, newAABB, newAABB.GetCenter() - proxyIdAABBMap_[id].GetCenter());
        proxyIdAABBMap_[id] = newAABB;
    }
    updateIds_.clear();
}

void CullingSystem::Cull(RectF rect) {
    drawingRenderedIds_->Clear();

    for (auto& renderedProxyId : renderedProxyIdMap_) {
        renderedProxyId.first->SetIsDrawn(false);
    }

    b2AABB aabb;
    aabb.lowerBound = b2Vec2(rect.X, rect.Y);
    aabb.upperBound = b2Vec2(rect.X + rect.Width, rect.Y + rect.Height);
    dynamicTree_.Query(instance_.get(), aabb);
}

void CullingSystem::Unregister(Rendered* rendered) {
    auto id = renderedProxyIdMap_[rendered];
    dynamicTree_.DestroyProxy(id);
    renderedProxyIdMap_.erase(rendered);
    proxyIdRenderedMap_.erase(id);
    proxyIdAABBMap_.erase(id);
}

bool CullingSystem::QueryCallback(int32_t id) {
    if (proxyIdRenderedMap_.find(id) == proxyIdRenderedMap_.end()) {
        Log::GetInstance()->Error(LogCategory::Core, u"CullingSystem::QueryCallback: Invalid proxy id contaminated.");
    }
    drawingRenderedIds_->GetVector().push_back(proxyIdRenderedMap_[id]->GetId());
    proxyIdRenderedMap_[id]->SetIsDrawn(true);
    return true;
}

}  // namespace Altseed2