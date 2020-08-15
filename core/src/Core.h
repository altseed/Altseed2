#pragma once

#include <stdint.h>
#include <stdio.h>

#include <memory>
#include <mutex>
#include <set>

#include "BaseObject.h"
#include "Configuration.h"
#include "FPS.h"

namespace Altseed2 {

class BaseObject;

class Core : public BaseObject {
private:
    static std::shared_ptr<Core> instance;

    //! mutex for a list of baseObjects
    std::mutex baseObjectMtx_;

    //! list of baseObjects
    std::set<BaseObject*> baseObjects_;

    std::unique_ptr<FPS> fps_;

    std::shared_ptr<Configuration> config_;

    int32_t maxBaseObjectId_;

public:
    //! register a base object
    int32_t Register(BaseObject* o);

    //! unregister a base object
    void Unregister(BaseObject* o);

    //! get the number of base objects
    int32_t GetBaseObjectCount();

    //! print all object's name
    void PrintAllBaseObjectName();

    //! Initialize core and create a singleton
    static bool Initialize(const char16_t* title, int32_t width, int32_t height, std::shared_ptr<Configuration> config);
    static bool Initialize(int32_t width, int32_t height);

    //! Terminate core and dispose the singleton
    static void Terminate();

    //! Get instance
    static std::shared_ptr<Core>& GetInstance();

    Core();

    bool DoEvent();

    const float GetDeltaSecond();

    const float GetCurrentFPS();

    const int32_t GetTargetFPS();
    void SetTargetFPS(int32_t fps);

    const FramerateMode GetFramerateMode();
    void SetFramerateMode(FramerateMode framerateMode);
};
}  // namespace Altseed2
