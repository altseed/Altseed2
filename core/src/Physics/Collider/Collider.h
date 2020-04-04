#pragma once

#include <memory>
#include <vector>
#include <box2d/box2d.h>

#include "../../BaseObject.h"
#include "../../Math/Matrix44F.h"
#include "../../Math/Vector2F.h"

namespace Altseed {

class Collider : public BaseObject {
protected:
    b2Transform transform_;
    Matrix44F transformMatrix_;

public:
    Collider();

    virtual bool GetIsCollidedWith(std::shared_ptr<Collider> shape) = 0;
};
    
} // namespace Altseed
