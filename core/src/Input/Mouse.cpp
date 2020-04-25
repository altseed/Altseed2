#include "Mouse.h"

#include <libpng16/png.h>
#include <stb_image.h>

#include "../Logger/Log.h"

namespace Altseed {

std::shared_ptr<Mouse> Mouse::instance_ = nullptr;

static double wheelTemp = 0;
static bool wheelCalled = false;
static std::function<void(double x, double y)> wheelCallback;

static void GetWheelInternal(GLFWwindow* wHandle, double x, double y) {
    wheelTemp = y;
    wheelCalled = true;

    if (wheelCallback != nullptr) {
        wheelCallback(x, y);
    }
}

bool Mouse::Initialize(std::shared_ptr<Window>& window) {
    instance_ = MakeAsdShared<Mouse>();

    instance_->window_ = window;

    instance_->currentState_.fill(false);
    instance_->oldState_.fill(false);

    glfwSetScrollCallback((GLFWwindow*)window->GetNativeWindow(), GetWheelInternal);

    return true;
}

std::shared_ptr<Mouse>& Mouse::GetInstance() { return instance_; }

void Mouse::RefreshInputState() {
    auto w = window_->GetNativeWindow();

    wheel_ = (wheelCalled) ? wheelTemp : 0;
    wheelCalled = false;

    oldState_ = currentState_;

    for (int32_t i = 0; i < KEY_NUM; i++) {
        currentState_[i] = glfwGetMouseButton(w, i) > 0;
    }
}

void Mouse::SetPosition(Vector2F vec) {
    auto w = window_->GetNativeWindow();
    glfwSetCursorPos(w, vec.X, vec.Y);
}

Vector2F Mouse::GetPosition() {
    double x, y;
    auto w = window_->GetNativeWindow();
    glfwGetCursorPos(w, &x, &y);
    return Vector2F(x, y);
}

void Mouse::SetWheelCallback(std::function<void(double x, double y)> func) { wheelCallback = func; }

float Mouse::GetWheel() const { return wheel_; }

ButtonState Mouse::GetMouseButtonState(MouseButtons button) const {
    int index = (int32_t)button;

    ASD_ASSERT(0 <= index && index < currentState_.size(), "Invalid Button.");

    return static_cast<ButtonState>((currentState_[index] ? 1 : 0) | (oldState_[index] ? 2 : 0));
}

void Mouse::SetCursorMode(CursorMode mode) {
    auto w = window_->GetNativeWindow();
    int index = (int32_t)mode;
    glfwSetInputMode(w, GLFW_CURSOR, index);
}

CursorMode Mouse::GetCursorMode() const {
    auto w = window_->GetNativeWindow();
    int index = (int32_t)glfwGetInputMode(w, GLFW_CURSOR);
    return static_cast<CursorMode>(index);
}

void Mouse::SetCursorImage(std::shared_ptr<Cursor> cursor) { glfwSetCursor((GLFWwindow*)window_->GetNativeWindow(), cursor->GetNative()); }

};  // namespace Altseed
