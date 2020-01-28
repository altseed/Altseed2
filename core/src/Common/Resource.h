#pragma once

#include "../BaseObject.h"

namespace Altseed {

class Resource : public BaseObject {
public:
    Resource() = default;
    virtual ~Resource() = default;
    virtual bool Reload() = 0;
};

}  // namespace Altseed