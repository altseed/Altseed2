#pragma once

#include <memory>
#include <string>
#include <vector>
#include "WindowObject.h"

namespace altseed {

struct WindowInitializationParameter {
    std::u16string Title;
    int32_t WindowWidth = 0;
    int32_t WindowHeight = 0;
    bool IsFullscreenMode = false;
    bool IsResizable = false;
};

class WindowModule {
private:
    static std::shared_ptr<WindowModule> instance;

    std::vector<WindowObject*> windows;

public:
    static bool Initialize();

    static void Terminate();

    static std::shared_ptr<WindowModule> GetInstance() { return instance; }

    WindowObject* CreateWindow(const WindowInitializationParameter& parameter, WindowObject* parent = nullptr);

    bool DoEvent();

    int32_t GetWindowCount() const;

    WindowObject* GetWindowObjectByIndex(int32_t index) const;

    void GetMonitorSize(int32_t& width, int32_t& height);
};

}  // namespace altseed