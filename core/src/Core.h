#pragma once

#include <stdint.h>
#include <stdio.h>

#include <memory>
#include <mutex>
#include <set>

namespace altseed {

class BaseObject;

struct CoreOption {
    bool IsFullscreenMode = false;
    bool IsResizable = false;
};

class Core {
private:
    static std::shared_ptr<Core> instance;

    //! mutex for a list of baseObjects
    std::mutex baseObjectMtx_;

    //! list of baseObjects
    std::set<BaseObject*> baseObjects;

public:
    //! register a base object
    void Register(BaseObject* o) {
        std::lock_guard<std::mutex> lock(baseObjectMtx_);
        baseObjects.insert(o);
    }

    //! unregister a base object
    void Unregister(BaseObject* o) {
        std::lock_guard<std::mutex> lock(baseObjectMtx_);
        baseObjects.erase(o);
    }

    //! get the number of base objects
    int32_t GetBaseObjectCount() const { return (int32_t)baseObjects.size(); }

    //! Initialize core and create a singleton
    static bool Initialize(const char16_t* title, int32_t width, int32_t height, const CoreOption& option);

    //! Terminate core and dispose the singleton
    static void Terminate();

    //! Get instance
    static std::shared_ptr<Core>& GetInstance();

    bool DoEvent();
};
}  // namespace altseed
