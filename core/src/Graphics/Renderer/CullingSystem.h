#pragma once

#include <box2d/b2_dynamic_tree.h>

#include <map>
#include <memory>
#include <mutex>
#include <set>

#include "../../BaseObject.h"
#include "../../Common/Array.h"
#include "../../Math/RectF.h"

namespace Altseed2 {
class Rendered;
class CullingSystem : public BaseObject {
private:
    static std::shared_ptr<CullingSystem> instance_;

    std::mutex mtx_;
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

#if !USE_CBG
    //! for Core only
    void RequestUpdateAABB(Rendered* rendered);
    bool GetIsExists(Rendered* rendered);
#endif

    void Register(std::shared_ptr<Rendered> rendered);
    void UpdateAABB();
    void Cull(RectF rect);
    void Unregister(std::shared_ptr<Rendered> rendered);

    int32_t GetDrawingRenderedCount();
    std::shared_ptr<Int32Array> GetDrawingRenderedIds();

#if !USE_CBG
    //! Don't call from external
    bool QueryCallback(int32_t id);
#endif
};

}  // namespace Altseed2