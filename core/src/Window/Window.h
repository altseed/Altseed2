#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../BaseObject.h"
#include "../Common/PlatformIncludes.h"
#include "../Math/Vector2I.h"

namespace Altseed2 {

struct WindowInitializationParameter {
    std::u16string Title;
    int32_t WindowWidth = 0;
    int32_t WindowHeight = 0;
    bool IsFullscreenMode = false;
    bool IsResizable = false;
};

class Window : public BaseObject {
private:
    static std::shared_ptr<Window> instance_;

    GLFWwindow* mainWindow_;
    std::vector<GLFWwindow*> subWindows;

    std::u16string title_;

public:
    static bool Initialize(const WindowInitializationParameter& parameter);

    static void Terminate();

    static std::shared_ptr<Window>& GetInstance();

    void SetTitle(const char16_t* title);

    const char16_t* GetTitle() const;

    void SetSize(int32_t width, int32_t height);

    void SetSize(Vector2I_C value);

    void GetSize(int32_t& width, int32_t& height) const;

    Vector2I GetSize() const;

    GLFWwindow* GetNativeWindow() const { return mainWindow_; }

    bool DoEvent();

    void GetMonitorSize(int32_t& width, int32_t& height);
};

}  // namespace Altseed2