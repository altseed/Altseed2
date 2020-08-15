#pragma once

#include <box2d/box2d.h>

#include "../../BaseObject.h"
#include "../../Math/Matrix44F.h"
#include "../Color.h"

namespace Altseed2 {
class CullingSystem;
class Rendered : public BaseObject {
protected:
    Matrix44F transform_;
    std::shared_ptr<CullingSystem> cullingSystem_;

public:
    Rendered();
    virtual ~Rendered();

    const Matrix44F& GetTransform() const;
    void SetTransform(const Matrix44F& transform);

    virtual b2AABB GetAABB() { return b2AABB(); }
};

}  // namespace Altseed2