#pragma once

#include <memory>
#include <vector>
#include <box2d/box2d.h>

#include "../../BaseObject.h"
#include "../../Math/Vector2F.h"

namespace Altseed {

class Collider : public BaseObject {
protected:
    b2Transform b2Transform_;
    
    Vector2F translation_;
    double rotation_;

public:
    Vector2F GetTranslation() const;
    void SetTranslation(Vector2F translation);

    double GetRotation() const;
    void SetRotation(double rotation);

    virtual bool GetIsCollidedWith(std::shared_ptr<Collider> shape) = 0;
};
    
} // namespace Altseed
