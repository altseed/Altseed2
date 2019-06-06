#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include "../BaseObject.h"

namespace altseed {

class WindowObject : BaseObject {
private:
    GLFWwindow* window_;
    std::shared_ptr<WindowModule> windowModule_;

public:
    WindowObject(const WindowInitializationParameter& parameter, WindowObject* parent = nullptr);
    virtual ~WindowObject();

	bool DoEvent();

    void Close();

    void SetTitle(const char16_t* title);

    void SetSize(int32_t width, int32_t height);

    void GetSize(int32_t& width, int32_t& height);

    void* GetHandle() const;

    void* GetNativeWindow() const { return window_; }
};

}  // namespace altseed