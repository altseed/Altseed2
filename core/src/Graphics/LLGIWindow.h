#pragma once

#include "../Common/PlatformIncludes.h"

#include "LLGI.Base.h"

namespace Altseed {
class LLGIWindow : public LLGI::Window {
private:
    GLFWwindow* glfwWindow;

public:
    LLGIWindow(GLFWwindow* glfwWindow_);
    void* GetNativePtr(int32_t index) override;
    LLGI::Vec2I GetWindowSize() const override;
    GLFWwindow* GetGlfwWindow() const { return glfwWindow; }

    bool OnNewFrame() override { return glfwWindowShouldClose(glfwWindow) == GL_FALSE; }
};

}  // namespace Altseed