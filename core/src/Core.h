#pragma once

#include <stdint.h>
#include <stdio.h>
#include <memory>

namespace altseed {

class BaseObject;

class Core {
private:
    static std::shared_ptr<Core> instance;

public:
    //! Initialize core and create a singleton
    static bool Initialize();

    //! Terminate core and dispose the singleton
    static void Terminate();

    //! Get instance
    static std::shared_ptr<Core>& GetInstance() { return instance; }
};
}  // namespace altseed