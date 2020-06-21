#include "LLGIWindow.h"

namespace Altseed2 {

LLGIWindow::LLGIWindow(GLFWwindow* glfwWindow_) : glfwWindow(glfwWindow_) {}

void* LLGIWindow::GetNativePtr(int32_t index) {
#ifdef _WIN32
    if (index == 0) {
        return glfwGetWin32Window(glfwWindow);
    }

    return GetModuleHandle(0);
#endif

#ifdef __APPLE__
    return glfwGetCocoaWindow(glfwWindow);
#endif

#ifdef __linux__
    if (index == 0) {
        return glfwGetX11Display();
    }

    return reinterpret_cast<void*>(glfwGetX11Window(glfwWindow));
#endif
}

LLGI::Vec2I LLGIWindow::GetWindowSize() const {
    int w, h;
    glfwGetWindowSize(glfwWindow, &w, &h);
    return LLGI::Vec2I(w, h);
}

LLGI::Vec2I LLGIWindow::GetFrameBufferSize() const {
    int w, h;
    glfwGetFramebufferSize(glfwWindow, &w, &h);
    return LLGI::Vec2I(w, h);
}

}  // namespace Altseed2
