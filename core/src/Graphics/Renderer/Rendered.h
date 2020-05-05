#pragma once

#include <box2d/box2d.h>

#include "../../BaseObject.h"
#include "../../Math/Matrix44F.h"
#include "../Color.h"

namespace Altseed {
class CullingSystem;
class Rendered : public BaseObject {
protected:
    Matrix44F transform_;
    std::shared_ptr<CullingSystem> cullingSystem_;
    bool isDrawn_;
    Color color_;

public:
    Rendered();
    virtual ~Rendered();
    const Matrix44F& GetTransform() const;
    void SetTransform(const Matrix44F& transform);

    bool SetIsDrawn(bool isDrawn) { return isDrawn_ = isDrawn; }
    bool GetIsDrawn() { return isDrawn_; }

    Color GetColor() const { return color_; }
    void SetColor(const Color color) { color_ = color; }

    virtual b2AABB GetAABB() { return b2AABB(); }
};

}  // namespace Altseed