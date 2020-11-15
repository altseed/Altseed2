#pragma once

#include <memory>
#include <mutex>
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

    std::mutex terminatingMtx_;

public:
    Window();
    ~Window() override;

#if !USE_CBG
    static bool Initialize(const WindowInitializationParameter& parameter);

    static void Terminate();

    void OnTerminating() override;
#endif

    static std::shared_ptr<Window>& GetInstance();

    void SetTitle(const char16_t* title);

    const char16_t* GetTitle() const;

#if !USE_CBG
    void SetSize(int32_t width, int32_t height);

    void GetSize(int32_t& width, int32_t& height) const;

#endif
    void SetSize(Vector2I_C value);

    Vector2I GetSize() const;

    bool DoEvent();

#if !USE_CBG
    GLFWwindow* GetNativeWindow() const;

    void GetMonitorSize(int32_t& width, int32_t& height);

#endif
};

}  // namespace Altseed2