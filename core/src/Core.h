#pragma once

#include <stdint.h>
#include <stdio.h>

#include <memory>
#include <mutex>
#include <set>

#include "BaseObject.h"
#include "Configuration.h"
#include "FPS.h"

namespace Altseed {

class BaseObject;

class Core : public BaseObject {
private:
    static std::shared_ptr<Core> instance;

    //! mutex for a list of baseObjects
    std::mutex baseObjectMtx_;

    //! list of baseObjects
    std::set<BaseObject*> baseObjects;

    std::unique_ptr<FPS> fps_;

    std::shared_ptr<Configuration> config_;

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

    //! for core
    bool GetIsRegistered(BaseObject* o) { return baseObjects.count(o) > 0; }

    //! get the number of base objects
    int32_t GetBaseObjectCount() const {
        return (int32_t)baseObjects.size();
    }

    //! Initialize core and create a singleton
    static bool Initialize(const char16_t* title, int32_t width, int32_t height, std::shared_ptr<Configuration> config);
    static bool Initialize(int32_t width, int32_t height);

    //! Terminate core and dispose the singleton
    static void Terminate();

    //! Get instance
    static std::shared_ptr<Core>& GetInstance();

    bool DoEvent();

    const float GetDeltaSecond();

    const float GetCurrentFPS();

    const int32_t GetTargetFPS();
    void SetTargetFPS(int32_t fps);

    const FramerateMode GetFramerateMode();
    void SetFramerateMode(FramerateMode framerateMode);
};
}  // namespace Altseed
