#pragma once

#include <stdint.h>
#include <stdio.h>
#include <memory>
#include <mutex>
#include <set>

namespace altseed {

class BaseObject;

class Core {
private:
    static std::shared_ptr<Core> instance;

    //! mutex for a list of baseObjects
    std::mutex baseObjectMtx_;

    //! list of baseObjects
    std::set<BaseObject*> baseObjects;

public:
    //! register a base object
    void Register(BaseObject* o) { throw "Unimplemented"; }

    //! unregister a base object
    void Unregister(BaseObject* o) { throw "Unimplemented"; }

	//! get the number of base objects
	int32_t GetBaseObjectCount() const { throw "Unimplemented"; }

    //! Initialize core and create a singleton
    static bool Initialize();

    //! Terminate core and dispose the singleton
    static void Terminate();

    //! Get instance
    static std::shared_ptr<Core>& GetInstance();
};
}  // namespace altseed