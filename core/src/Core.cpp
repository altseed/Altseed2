#include "Core.h"

#include <ctime>
#include <iostream>
#include <sstream>

#include "BaseObject.h"
#include "Graphics/FrameDebugger.h"
#include "Graphics/Graphics.h"
#include "Graphics/Renderer/CullingSystem.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "IO/File.h"
#include "Input/Joystick.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Logger/Log.h"
#include "Sound/SoundMixer.h"
#include "System/SynchronizationContext.h"
#include "Tool/Tool.h"
#include "Window/Window.h"

namespace Altseed2 {
std::shared_ptr<Core> Core::instance = nullptr;

int32_t Core::Register(BaseObject* o) {
    std::lock_guard<std::mutex> lock(baseObjectMtx_);
    baseObjects_.insert(o);
    return maxBaseObjectId_++;
}

void Core::Unregister(BaseObject* o) {
    std::lock_guard<std::mutex> lock(baseObjectMtx_);
    baseObjects_.erase(o);
}

int32_t Core::GetBaseObjectCount() {
    std::lock_guard<std::mutex> lock(baseObjectMtx_);

    return (int32_t)baseObjects_.size();
}

void Core::PrintAllBaseObjectName() {
    std::lock_guard<std::mutex> lock(baseObjectMtx_);

    for (auto& o : baseObjects_) {
        std::cout << o->GetInstanceName() << std::endl;
    }
}

bool Core::Initialize(const char16_t* title, int32_t width, int32_t height, std::shared_ptr<Configuration> config) {
    RETURN_IF_NULL(config, false);

    std::cout << "Debug 1" << std::endl;

    if (!Log::Initialize(config->GetConsoleLoggingEnabled(), config->GetFileLoggingEnabled(), config->GetLogFileName())) {
        Core::instance = nullptr;
        std::cout << "Log::Initialize failed" << std::endl;
        return false;
    }

    std::cout << "Debug 2" << std::endl;

    Core::instance = MakeAsdShared<Core>();
    Core::instance->config_ = config;

    auto coreModules = config->GetEnabledCoreModules();

    std::cout << "Debug 2" << std::endl;

    if (CoreModulesHasBit(coreModules, CoreModules::RequireWindow)) {
        WindowInitializationParameter windowParameter;
        windowParameter.Title = title == nullptr ? u"" : title;
        windowParameter.WindowWidth = width;
        windowParameter.WindowHeight = height;
        windowParameter.IsFullscreenMode = config->GetIsFullscreen();
        windowParameter.IsResizable = config->GetIsResizable();

        if (!Window::Initialize(windowParameter)) {
            LOG_CRITICAL(u"Window::Initialize failed");
            Core::instance = nullptr;
            return false;
        }
    }

    std::cout << "Debug 3" << std::endl;

    if (CoreModulesHasBit(coreModules, CoreModules::Keyboard)) {
        if (!Keyboard::Initialize(Window::GetInstance())) {
            LOG_CRITICAL(u"Keyboard::Initialize failed");
            Core::instance = nullptr;
            return false;
        }
    }

    std::cout << "Debug 4" << std::endl;

    if (CoreModulesHasBit(coreModules, CoreModules::Mouse)) {
        if (!Mouse::Initialize(Window::GetInstance())) {
            LOG_CRITICAL(u"Mouse::Initialize failed");
            Core::instance = nullptr;
            return false;
        }
    }

    std::cout << "Debug 5" << std::endl;

    if (CoreModulesHasBit(coreModules, CoreModules::Joystick)) {
        if (!Joystick::Initialize()) {
            LOG_CRITICAL(u"Joystick::Initialize failed");
            Core::instance = nullptr;
            return false;
        }
    }

    std::cout << "Debug 6" << std::endl;

    if (CoreModulesHasBit(coreModules, CoreModules::RequireFile)) {
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
    }

    std::cout << "Debug 7" << std::endl;

    if (CoreModulesHasBit(coreModules, CoreModules::RequireGraphics)) {
        GraphicsInitializationParameter graphicsParameter;
        graphicsParameter.Device = config->GetDeviceType();
        graphicsParameter.WaitVSync = config->GetWaitVSync();

        if (!CullingSystem::Initialize()) {
            LOG_CRITICAL(u"CullingSystem::Initialize failed");
            Core::instance = nullptr;
            return false;
        }

        if (!Graphics::Initialize(Window::GetInstance(), graphicsParameter)) {
            LOG_CRITICAL(u"Graphics::Initialize failed");
            Core::instance = nullptr;
            return false;
        }

        if (!ShaderCompiler::Initialize(Graphics::GetInstance(), File::GetInstance())) {
            LOG_CRITICAL(u"ShaderCompiler::Initialize failed");
            Core::instance = nullptr;
            return false;
        }

        if (!FrameDebugger::Initialize()) {
            LOG_CRITICAL(u"FrameDebugger::Initialize failed");
            Core::instance = nullptr;
            return false;
        }

        if (!Renderer::Initialize(Window::GetInstance(), Graphics::GetInstance(), CullingSystem::GetInstance())) {
            LOG_CRITICAL(u"Renderer::Initialize failed");
            Core::instance = nullptr;
            return false;
        }
    }

    std::cout << "Debug 8" << std::endl;

    if (CoreModulesHasBit(coreModules, CoreModules::Sound)) {
        if (!SoundMixer::Initialize(false)) {
            LOG_CRITICAL(u"SoundMixer::Initialize failed");
            Core::instance = nullptr;
            return false;
        }
    }

    std::cout << "Debug 9" << std::endl;

    if (CoreModulesHasBit(coreModules, CoreModules::Tool)) {
        if (!Tool::Initialize(Graphics::GetInstance())) {
            LOG_CRITICAL(u"Tool::Initialize failed");
            Core::instance = nullptr;
            return false;
        }
    }

    SynchronizationContext::Initialize();

    Core::instance->fps_ = std::make_unique<FPS>();

    return Core::instance != nullptr;
}

bool Core::Initialize(int32_t width, int32_t height) {
    auto config = MakeAsdShared<Configuration>();

    return Core::Initialize(u"Altseed2", width, height, config);
}

void Core::Terminate() {
    SynchronizationContext::GetInstance()->Run();

    if (Graphics::GetInstance() != nullptr) {
        Graphics::GetInstance()->GetGraphicsLLGI()->WaitFinish();
    }

    // notify terminating to objects
    {
        std::lock_guard<std::mutex> lock(Core::instance->baseObjectMtx_);

        for (auto o : Core::instance->baseObjects_) {
            if (!o->GetIsTerminateingEnabled()) {
                continue;
            }
            o->OnTerminating();
        }
    }

    SynchronizationContext::Terminate();

    auto coreModules = Core::instance->config_->GetEnabledCoreModules();

    if (CoreModulesHasBit(coreModules, CoreModules::RequireWindow)) {
        Window::Terminate();
    }

    if (CoreModulesHasBit(coreModules, CoreModules::Keyboard)) {
        Keyboard::Terminate();
    }

    if (CoreModulesHasBit(coreModules, CoreModules::Mouse)) {
        Mouse::Terminate();
    }

    if (CoreModulesHasBit(coreModules, CoreModules::Joystick)) {
        Joystick::Terminate();
    }

    if (CoreModulesHasBit(coreModules, CoreModules::RequireFile)) {
        Resources::Terminate();
        File::Terminate();
    }

    if (CoreModulesHasBit(coreModules, CoreModules::RequireGraphics)) {
        CullingSystem::Terminate();
        Graphics::Terminate();
        ShaderCompiler::Terminate();
        Renderer::Terminate();
    }

    if (CoreModulesHasBit(coreModules, CoreModules::Sound)) {
        SoundMixer::Terminate();
    }

    if (CoreModulesHasBit(coreModules, CoreModules::Tool)) {
        Tool::Terminate();
    }

    Log::Terminate();

    Core::instance = nullptr;
}

std::shared_ptr<Core>& Core::GetInstance() { return instance; }

Core::Core() : maxBaseObjectId_(0) {}

bool Core::DoEvent() {
    Altseed2::Keyboard::GetInstance()->RefleshKeyStates();
    Altseed2::Mouse::GetInstance()->RefreshInputState();
    Altseed2::Joystick::GetInstance()->RefreshInputState();

    SynchronizationContext::GetInstance()->Run();

    Core::instance->fps_->Update();

    return Altseed2::Window::GetInstance()->DoEvent();
}

const float Core::GetDeltaSecond() { return Core::instance->fps_->GetDeltaSecond(); }

const float Core::GetCurrentFPS() { return Core::instance->fps_->GetCurrentFPS(); }

const int32_t Core::GetTargetFPS() { return Core::instance->fps_->GetTargetFPS(); }

void Core::SetTargetFPS(int32_t fps) { Core::instance->fps_->SetTarget(fps); }

const FramerateMode Core::GetFramerateMode() { return Core::instance->fps_->GetFramerateMode(); }

void Core::SetFramerateMode(FramerateMode framerateMode) { Core::instance->fps_->SetFramerateMode(framerateMode); }

}  // namespace Altseed2
