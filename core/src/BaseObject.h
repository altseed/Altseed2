#pragma once

#include <stdint.h>
#include <stdio.h>
#include <atomic>
#include <memory>

namespace altseed {

class Core;

class BaseObject {
private:
public:
    BaseObject();
    virtual ~BaseObject();
};

}  // namespace altseed