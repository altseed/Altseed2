#include "Window.h"

#include <codecvt>
#include <locale>

#include "../Common/StringHelper.h"
#include "../Logger/Log.h"

// GLFW
#if _WIN32
#ifndef GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#endif
#define GLFW_EXPOSE_NATIVE_WGL
#elif __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#else
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#include <X11/extensions/Xrandr.h>
#endif

#if _WIN32
#include <GLFW/glfw3native.h>
#endif

namespace Altseed {
std::shared_ptr<Window> Window::instance_ = nullptr;

std::shared_ptr<Window>& Window::GetInstance() { return instance_; }

bool Window::Initialize(const WindowInitializationParameter& parameter) {
    if (!glfwInit()) {
        LOG_CRITICAL(u"glfwInit failed");
        return false;
    }

    instance_ = CreateSharedPtr(new Window());

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // common window setting

#if defined(_WIN32) || defined(__APPLE__)
    // x11 requires gl to show an window (temp)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, parameter.IsResizable ? GL_TRUE : GL_FALSE);

    GLFWmonitor* monitor = nullptr;
    if (parameter.IsFullscreenMode) {
        monitor = glfwGetPrimaryMonitor();
    }

    GetInstance()->mainWindow_ =
            glfwCreateWindow(parameter.WindowWidth, parameter.WindowHeight, utf16_to_utf8(parameter.Title).c_str(), monitor, nullptr);
    if (GetInstance()->mainWindow_ == nullptr) {
        glfwTerminate();
        LOG_CRITICAL(u"mainWindow_ is null");
        return false;
    }
    // memolize title to get later
    GetInstance()->title_ = parameter.Title;

    glfwSwapInterval(1);

    glfwShowWindow(GetInstance()->mainWindow_);

    glfwSwapInterval(0);

    glfwSetWindowUserPointer(GetInstance()->mainWindow_, &GetInstance());

#ifdef __linux__
    // x11 requires interval to show an window (temp)
    glfwSwapInterval(1);
#endif

    return true;
}

void Window::Terminate() {
    ASD_VERIFY(instance_ != nullptr, "instance must be not null.")

    if (GetInstance()->mainWindow_ != nullptr) {
        glfwDestroyWindow(GetInstance()->mainWindow_);
        GetInstance()->mainWindow_ = nullptr;
        glfwTerminate();
    }

    instance_ = nullptr;
}

void Window::SetTitle(const char16_t* title) {
    title_ = title;
    auto titleUTF8 = utf16_to_utf8(title);
    glfwSetWindowTitle(GetInstance()->mainWindow_, titleUTF8.c_str());
}

const char16_t* Window::GetTitle() const { return title_.c_str(); }

void Window::SetSize(int32_t width, int32_t height) { glfwSetWindowSize(GetInstance()->mainWindow_, width, height); }

void Window::GetSize(int32_t& width, int32_t& height) const { glfwGetWindowSize(GetInstance()->mainWindow_, &width, &height); }

Vector2I Window::GetSize() const {
    int32_t width = 0;
    int32_t height = 0;
    GetSize(width, height);
    return Vector2I(width, height);
}

bool Window::DoEvent() {
    if (GetInstance()->mainWindow_ == nullptr) {
        LOG_CRITICAL(u"mainwindow_ is null");
        return false;
    }

    glfwPollEvents();

    if (glfwWindowShouldClose(GetInstance()->mainWindow_)) {
        return false;
    }

#ifdef __linux__
    // x11 requires swap to show an window (temp)
    glfwSwapBuffers(GetInstance()->mainWindow_);
#endif

    return true;
}

void Window::GetMonitorSize(int32_t& width, int32_t& height) {
    auto monitor = glfwGetPrimaryMonitor();

    if (monitor == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Window::GetMonitorSize: monitor is null");
        return;
    }

    auto videomode = glfwGetVideoMode(monitor);

    if (videomode == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Window::GetMonitorSize: videomode is null");
        return;
    }

    width = videomode->width;
    height = videomode->height;
}

}  // namespace Altseed