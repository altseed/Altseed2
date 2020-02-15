#include "Core.h"

#include "BaseObject.h"
#include "Graphics/Graphics.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "IO/File.h"
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

static const char16_t LogDirectory[] = u"Log";

std::shared_ptr<Core> Core::instance = nullptr;

bool Core::Initialize(const char16_t* title, int32_t width, int32_t height, const CoreOption& option) {
    Core::instance = MakeAsdShared<Core>();

    WindowInitializationParameter windowParameter;
    windowParameter.Title = title;
    windowParameter.WindowWidth = width;
    windowParameter.WindowHeight = height;
    windowParameter.IsFullscreenMode = option.IsFullscreenMode;
    windowParameter.IsResizable = option.IsResizable;

    std::stringstream logfile_ss;
    {
        const auto datetime = std::time(nullptr);
        const auto localtime = std::localtime(&datetime);
        logfile_ss << utf16_to_utf8(LogDirectory).c_str() << "/Log";
        logfile_ss << "_" << 1900 + localtime->tm_year;
        logfile_ss << "_" << 1 + localtime->tm_mon;
        logfile_ss << "_" << localtime->tm_mday;
        logfile_ss << "_" << localtime->tm_hour;
        logfile_ss << "_" << localtime->tm_min;
        logfile_ss << "_" << localtime->tm_sec;
        logfile_ss << ".txt";
    }

#ifdef _WIN32
#undef CreateDirectory
#endif

    if (!FileSystem::GetIsDirectory(LogDirectory) && !(FileSystem::CreateDirectory)(LogDirectory)) {
        std::cout << "Failed to create Directory: " << LogDirectory << std::endl;
        Core::instance = nullptr;
        return false;
    }

    if (!Log::Initialize(logfile_ss.str().c_str())) {
        Core::instance = nullptr;
        return false;
    }

    if (!Window::Initialize(windowParameter)) {
        Core::instance = nullptr;
        return false;
    }

    if (!Keyboard::Initialize(Window::GetInstance())) {
        Core::instance = nullptr;
        return false;
    }

    if (!Mouse::Initialize(Window::GetInstance())) {
        Core::instance = nullptr;
        return false;
    }

    if (!Resources::Initialize()) {
        Core::instance = nullptr;
        return false;
    }

    if (!File::Initialize(Resources::GetInstance())) {
        Core::instance = nullptr;
        return false;
    }

    if (!Graphics::Initialize(Window::GetInstance())) {
        Core::instance = nullptr;
        return false;
    }

    if (!ShaderCompiler::Initialize(Graphics::GetInstance())) {
        Core::instance = nullptr;
        return false;
    }

    if (!SoundMixer::Initialize(false)) {
        Core::instance = nullptr;
        return false;
    }

    if (!Renderer::Initialize(Window::GetInstance(), Graphics::GetInstance())) {
        Core::instance = nullptr;
        return false;
    }

    if (!Tool::Initialize(Graphics::GetInstance())) {
        Core::instance = nullptr;
        return false;
    }

    return Core::instance != nullptr;
}

bool Core::Initialize(int32_t width, int32_t height) {
    CoreOption option;
    option.IsFullscreenMode = false;
    option.IsResizable = false;

    return Core::Initialize(u"Altseed2", width, height, option);
}

void Core::Terminate() {
    // notify terminating to objects
    for (auto obj : Core::instance->baseObjects) {
        obj->OnTerminating();
    }

    Tool::Terminate();
    Renderer::Terminate();
    Window::Terminate();
    Keyboard::Terminate();
    Mouse::Terminate();
    Resources::Terminate();
    File::Terminate();
    Graphics::Terminate();
    ShaderCompiler::Terminate();
    Log::Terminate();

    Core::instance = nullptr;
}

std::shared_ptr<Core>& Core::GetInstance() { return instance; }

bool Core::DoEvent() {
    Altseed::Keyboard::GetInstance()->RefleshKeyStates();
    Altseed::Mouse::GetInstance()->RefreshInputState();

    return Altseed::Window::GetInstance()->DoEvent();
}

}  // namespace Altseed
