#include "Window.h"

#include <codecvt>
#include <locale>

// GLFW
#if _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
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

namespace altseed {

std::shared_ptr<Window> Window::instance = nullptr;

// http://hasenpfote36.blogspot.jp/2016/09/stdcodecvt.html
static constexpr std::codecvt_mode mode = std::codecvt_mode::little_endian;

static std::string utf16_to_utf8(const std::u16string& s) {
#if defined(_MSC_VER)
    std::wstring_convert<std::codecvt_utf8_utf16<std::uint16_t, 0x10ffff, mode>, std::uint16_t> conv;
    auto p = reinterpret_cast<const std::uint16_t*>(s.c_str());
    return conv.to_bytes(p, p + s.length());
#else
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, mode>, char16_t> conv;
    return conv.to_bytes(s);
#endif
}

std::shared_ptr<Window>& Window::GetInstance() { return instance; }

bool Window::Initialize(const WindowInitializationParameter& parameter) {
    if (!glfwInit()) return false;

    instance = std::make_shared<Window>();

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // common window setting
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
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
        return false;
    }
    // memolize title to get later
    GetInstance()->Window::title = parameter.Title;

    glfwSwapInterval(1);

    glfwShowWindow(GetInstance()->mainWindow_);

    glfwSwapInterval(0);

    glfwSetWindowUserPointer(GetInstance()->mainWindow_, &GetInstance());

    return true;
}

void Window::Terminate() {
    if (GetInstance()->mainWindow_ != nullptr) {
        glfwDestroyWindow(GetInstance()->mainWindow_);
        GetInstance()->mainWindow_ = nullptr;
        glfwTerminate();
    }
}

void Window::SetTitle(const char16_t* title) {
    Window::title = (char16_t*)title;
    auto titleUTF8 = utf16_to_utf8(title);
    glfwSetWindowTitle(GetInstance()->mainWindow_, titleUTF8.c_str());
}

char16_t* Window::GetTitle() const { return Window::title; }

void Window::SetSize(int32_t width, int32_t height) { glfwSetWindowSize(GetInstance()->mainWindow_, width, height); }

void Window::GetSize(int32_t& width, int32_t& height) { glfwGetWindowSize(GetInstance()->mainWindow_, &width, &height); }

void* Window::GetHandle() const {
#ifdef _WIN32
    return glfwGetWin32Window(GetInstance()->mainWindow_);
#else
    return nullptr;
#endif
}

bool Window::DoEvent() {
    if (GetInstance()->mainWindow_ == nullptr) return false;

    if (glfwWindowShouldClose(GetInstance()->mainWindow_)) {
        Terminate();
        return false;
    }

    glfwPollEvents();
    return true;
}

void Window::GetMonitorSize(int32_t& width, int32_t& height) {
    auto monitor = glfwGetPrimaryMonitor();

    if (monitor != nullptr) {
        auto videomode = glfwGetVideoMode(monitor);

        if (videomode != nullptr) {
            width = videomode->width;
            height = videomode->height;
        }
    }
}

}  // namespace altseed