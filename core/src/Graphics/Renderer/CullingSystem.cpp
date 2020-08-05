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

void CullingSystem::Register(std::shared_ptr<Rendered> rendered) {
    if (renderedProxyIdMap_.count(rendered.get()) > 0) {
        Log::GetInstance()->Warn(LogCategory::Core, u"CullingSystem::Unregister: rendered is already registered in the culling system.");
        return;
    }

    auto aabb = rendered->GetAABB();
    auto id = dynamicTree_.CreateProxy(aabb, rendered.get());
    proxyIdRenderedMap_[id] = rendered.get();
    renderedProxyIdMap_[rendered.get()] = id;
    proxyIdAABBMap_[id] = aabb;
}

void CullingSystem::RequestUpdateAABB(Rendered* rendered) {
    if (renderedProxyIdMap_.count(rendered) > 0) {
        updateIds_.insert(renderedProxyIdMap_[rendered]);
    }
}

bool CullingSystem::GetIsExists(Rendered* rendered) {
    return renderedProxyIdMap_.count(rendered) > 0;
}

void CullingSystem::UpdateAABB() {
    for (auto& id : updateIds_) {
        auto it = proxyIdRenderedMap_.find(id);
        if (it == proxyIdRenderedMap_.end()) {
            Log::GetInstance()->Error(LogCategory::Core, u"CullingSystem::UpdateAABB: proxy id({0}) is not found.", id);
            continue;
        }
        auto rendered = it->second;
        if (it == proxyIdRenderedMap_.end()) {
            Log::GetInstance()->Error(LogCategory::Core, u"CullingSystem::UpdateAABB: Invalid proxy id({0}) contaminated.", id);
            continue;
        }

        auto newAABB = rendered->GetAABB();
        dynamicTree_.MoveProxy(id, newAABB, newAABB.GetCenter() - proxyIdAABBMap_[id].GetCenter());
        proxyIdAABBMap_[id] = newAABB;
    }
    updateIds_.clear();
}

void CullingSystem::Cull(RectF rect) {
    drawingRenderedIds_->Clear();

    b2AABB aabb;
    aabb.lowerBound = b2Vec2(rect.X, rect.Y);
    aabb.upperBound = b2Vec2(rect.X + rect.Width, rect.Y + rect.Height);
    dynamicTree_.Query(instance_.get(), aabb);
}

void CullingSystem::Unregister(std::shared_ptr<Rendered> rendered) {
    if (renderedProxyIdMap_.count(rendered.get()) == 0) {
        Log::GetInstance()->Warn(LogCategory::Core, u"CullingSystem::Unregister: rendered is not registered");
        return;
    }

    auto id = renderedProxyIdMap_[rendered.get()];
    dynamicTree_.DestroyProxy(id);
    renderedProxyIdMap_.erase(rendered.get());
    proxyIdRenderedMap_.erase(id);
    proxyIdAABBMap_.erase(id);
}

bool CullingSystem::QueryCallback(int32_t id) {
    auto it = proxyIdRenderedMap_.find(id);
    if (it == proxyIdRenderedMap_.end()) {
        Log::GetInstance()->Error(LogCategory::Core, u"CullingSystem::QueryCallback: proxy id({0}) is not found.", id);
        return true;
    }
    auto rendered = it->second;
    if (it == proxyIdRenderedMap_.end()) {
        Log::GetInstance()->Error(LogCategory::Core, u"CullingSystem::QueryCallback: Invalid proxy id({0}) contaminated.", id);
        return true;
    }

    drawingRenderedIds_->GetVector().push_back(rendered->GetId());
    return true;
}

}  // namespace Altseed2