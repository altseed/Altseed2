#pragma once

#include "../../BaseObject.h"
#include "../../Math/Matrix44F.h"

namespace Altseed {

class Rendered : public BaseObject {
protected:
    Matrix44F transform_;

public:
    Rendered() = default;
    virtual ~Rendered() = default;
    const Matrix44F& GetTransform() const;
    void SetTransform(const Matrix44F& transform);
};

}  // namespace Altseed