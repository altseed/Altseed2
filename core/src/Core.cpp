#include "Core.h"

#include "BaseObject.h"
#include "Graphics/Graphics.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "IO/File.h"
#include "Input/Joystick.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Logger/Log.h"
#include "Sound/SoundMixer.h"
#include "Tool/Tool.h"
#include "Window/Window.h"

#include <ctime>
#include <iostream>
#include <sstream>

namespace Altseed {
std::shared_ptr<Core> Core::instance = nullptr;

bool Core::Initialize(const char16_t* title, int32_t width, int32_t height, std::shared_ptr<Configuration> config) {
    Core::instance = MakeAsdShared<Core>();
    Core::instance->config_ = config;

    WindowInitializationParameter windowParameter;
    windowParameter.Title = title;
    windowParameter.WindowWidth = width;
    windowParameter.WindowHeight = height;
    windowParameter.IsFullscreenMode = config->GetIsFullscreen();
    windowParameter.IsResizable = config->GetIsResizable();

    if (!Log::Initialize(config->GetConsoleLoggingEnabled(), config->GetFileLoggingEnabled(), config->GetLogFileName())) {
        Core::instance = nullptr;
        std::cout << "Log::Initialize failed" << std::endl;
        return false;
    }

    if (!Window::Initialize(windowParameter)) {
        LOG_CRITICAL(u"Window::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!Keyboard::Initialize(Window::GetInstance())) {
        LOG_CRITICAL(u"Kayboad::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!Mouse::Initialize(Window::GetInstance())) {
        LOG_CRITICAL(u"Mouse::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!Joystick::Initialize()) {
        LOG_CRITICAL(u"Joystick::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!Resources::Initialize()) {
        LOG_CRITICAL(u"Resources::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!File::Initialize(Resources::GetInstance())) {
        LOG_CRITICAL(u"File::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!Graphics::Initialize(Window::GetInstance())) {
        LOG_CRITICAL(u"Graphics::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!ShaderCompiler::Initialize(Graphics::GetInstance())) {
        LOG_CRITICAL(u"ShaderCompiler::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!SoundMixer::Initialize(false)) {
        LOG_CRITICAL(u"SoundMixer::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (!Renderer::Initialize(Window::GetInstance(), Graphics::GetInstance())) {
        LOG_CRITICAL(u"Renderer::Initialize failed");
        Core::instance = nullptr;
        return false;
    }

    if (config->GetToolEnabled()) {
        if (!Tool::Initialize(Graphics::GetInstance())) {
            LOG_CRITICAL(u"Tool::Initialize failed");
            Core::instance = nullptr;
            return false;
        }
    }

    Core::instance->fps_ = std::make_unique<FPS>();

    Altseed::Joystick::GetInstance()->RefreshConnectedState();

    return Core::instance != nullptr;
}

bool Core::Initialize(int32_t width, int32_t height) {
    auto config = MakeAsdShared<Configuration>();

    return Core::Initialize(u"Altseed2", width, height, config);
}

void Core::Terminate() {
    // notify terminating to objects
    for (auto obj : Core::instance->baseObjects) {
        obj->OnTerminating();
    }

    if (Core::instance->config_->GetToolEnabled()) Tool::Terminate();
    Renderer::Terminate();
    Window::Terminate();
    Keyboard::Terminate();
    Mouse::Terminate();
    Joystick::Terminate();
    Resources::Terminate();
    File::Terminate();
    Graphics::Terminate();
    ShaderCompiler::Terminate();
    SoundMixer::Terminate();
    Log::Terminate();

    Core::instance = nullptr;
}

std::shared_ptr<Core>& Core::GetInstance() { return instance; }

bool Core::DoEvent() {
    Altseed::Keyboard::GetInstance()->RefleshKeyStates();
    Altseed::Mouse::GetInstance()->RefreshInputState();
    Altseed::Joystick::GetInstance()->RefreshInputState();

    Core::instance->fps_->Update();

    return Altseed::Window::GetInstance()->DoEvent();
}

const float Core::GetDeltaSecond() { return Core::instance->fps_->GetDeltaSecond(); }

const float Core::GetCurrentFPS() { return Core::instance->fps_->GetCurrentFPS(); }

const int32_t Core::GetTargetFPS() { return Core::instance->fps_->GetTargetFPS(); }

void Core::SetTargetFPS(int32_t fps) { Core::instance->fps_->SetTarget(fps); }

const FramerateMode Core::GetFramerateMode() { return Core::instance->fps_->GetFramerateMode(); }

void Core::SetFramerateMode(FramerateMode framerateMode) { Core::instance->fps_->SetFramerateMode(framerateMode); }

}  // namespace Altseed
