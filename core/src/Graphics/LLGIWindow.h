#pragma once

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32 1
#endif

#ifdef __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA 1
#endif

#ifdef __linux__
#define GLFW_EXPOSE_NATIVE_X11 1
#undef Always
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef __linux__
#undef Always
#endif

#include "LLGI.Base.h"

namespace altseed {
class LLGIWindow : public LLGI::Window {
private:
    GLFWwindow* glfwWindow;

public:
    LLGIWindow(GLFWwindow* glfwWindow_);
    void* GetNativePtr(int32_t index) override;
    LLGI::Vec2I GetWindowSize() const override;

    bool OnNewFrame() override { return glfwWindowShouldClose(glfwWindow) == GL_FALSE; }
};

}  // namespace altseed