#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <vector>

namespace altseed {

struct WindowInitializationParameter {
    std::u16string Title;
    int32_t WindowWidth = 0;
    int32_t WindowHeight = 0;
    bool IsFullscreenMode = false;
    bool IsResizable = false;
};

class Window {
private:
    static std::shared_ptr<Window> instance;

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

    void GetSize(int32_t& width, int32_t& height);

    GLFWwindow* GetNativeWindow() const { return mainWindow_; }

    bool DoEvent();

    void GetMonitorSize(int32_t& width, int32_t& height);
};

}  // namespace altseed