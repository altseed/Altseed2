#pragma once

#include "../BaseObject.h"

#if !USE_CBG

namespace Altseed2 {

class Resource : public BaseObject {
public:
    Resource() = default;
    virtual ~Resource() = default;
    virtual bool Reload() = 0;
};

}  // namespace Altseed2

#endif