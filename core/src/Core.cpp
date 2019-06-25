#include "Core.h"
#include "BaseObject.h"
#include "Window/Window.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

namespace altseed {

std::shared_ptr<Core> Core::instance = nullptr;

bool Core::Initialize(char16_t* title, int32_t width, int32_t height, const CoreOption& option) {
    Core::instance = std::make_shared<Core>();

    WindowInitializationParameter windowParameter;
    windowParameter.Title = title;
    windowParameter.WindowWidth = width;
    windowParameter.WindowHeight = height;
    windowParameter.IsFullscreenMode = option.IsFullscreenMode;
    windowParameter.IsResizable = option.IsResizable;
    Window::Initialize(windowParameter);
    
    Keyboard::Intialize(Window::GetInstance());
    
    Mouse::Intialize(Window::GetInstance());

    return Core::instance != nullptr;
}

void Core::Terminate() {
    // notify terminating to objects
    for (auto obj : Core::instance->baseObjects) {
        obj->OnTerminating();
    }

    Window::Terminate();

    Core::instance = nullptr;
}

std::shared_ptr<Core>& Core::GetInstance() { return instance; }

bool Core::DoEvent(){
    
    altseed::Keyboard::GetInstance()->RefleshKeyStates();
    altseed::Mouse::GetInstance()->RefreshInputState();
    
    return altseed::Window::GetInstance()->DoEvent();
}

}  // namespace altseed

