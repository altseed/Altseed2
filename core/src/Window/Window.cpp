#include "Window.h"

namespace altseed {

std::shared_ptr<Window> Window::instance = nullptr;

bool Window::Initialize(const WindowInitializationParameter& parameter) {
    if (!glfwInit()) return false;

	instance = std::make_shared<Window>();

	// common window setting
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	return true;
}

void Window::Terminate() { glfwTerminate(); }

}  // namespace altseed