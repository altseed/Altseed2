#pragma once

#include "../BaseObject.h"

namespace Altseed2 {

class Resource : public BaseObject {
public:
    Resource() = default;
    virtual ~Resource() = default;
    virtual bool Reload() = 0;
};

}  // namespace Altseed2