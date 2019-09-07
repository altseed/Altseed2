#pragma once

#include "../BaseObject.h"

namespace altseed {

class Resource : public BaseObject {
public:
    virtual bool Reload() = 0;
};

}  // namespace altseed