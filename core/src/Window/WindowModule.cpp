#include "WindowModule.h"
#include <GLFW/glfw3.h>

namespace altseed {

bool WindowModule::Initialize() {
    if (!glfwInit()) return false;

	instance = std::make_shared<WindowModule>();

	// common window setting
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	return true;
}

void WindowModule::Terminate() { glfwTerminate(); }

}  // namespace altseed