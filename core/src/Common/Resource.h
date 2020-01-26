#pragma once

#include "../BaseObject.h"

namespace Altseed {

class Resource : public BaseObject {
public:
    virtual bool Reload() = 0;
};

}  // namespace Altseed