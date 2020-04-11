#pragma once

#include <box2d/b2_dynamic_tree.h>

#include <map>
#include <set>

#include "../../BaseObject.h"
#include "../../Common/Array.h"
#include "../../Math/RectF.h"

namespace Altseed {
class Rendered;
class CullingSystem : public BaseObject {
private:
    static std::shared_ptr<CullingSystem> instance_;

    b2DynamicTree dynamicTree_;
    std::map<int32_t, Rendered*> proxyIdRenderedMap_;
    std::map<Rendered*, int32_t> renderedProxyIdMap_;
    std::map<int32_t, b2AABB> proxyIdAABBMap_;

    std::set<int32_t> updateIds_;

    std::shared_ptr<Int32Array> drawingRenderedIds_;

public:
    CullingSystem();
    virtual ~CullingSystem();

    static std::shared_ptr<CullingSystem>& GetInstance();

    static bool Initialize();

    static void Terminate();

    void Register(Rendered* rendered);
    void RequestUpdateAABB(Rendered* rendered);
    void UpdateAABB();
    void Cull(RectF rect);
    void Unregister(Rendered* rendered);

    int32_t GetDrawingRenderedCount() { return drawingRenderedIds_->GetCount(); }
    std::shared_ptr<Int32Array> GetDrawingRenderedIds() { return drawingRenderedIds_; }

    bool QueryCallback(int32_t id);
};

}  // namespace Altseed