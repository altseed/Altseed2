#pragma once

#include "BaseObject.h"
#include "Graphics/Graphics.h"

namespace Altseed2 {
enum class CoreModules : int32_t {
    None = 0,
    Window = 1,
    File = 1 << 1,
    Keyboard = 1 << 2,
    Mouse = 1 << 3,
    Joystick = 1 << 4,
    Graphics = 1 << 5,
    Tool = 1 << 6,
    Sound = 1 << 7,
    Default = Window | File | Keyboard | Mouse | Joystick | Joystick | Graphics | Sound,
    // internal
    RequireGraphics = Graphics | Tool,
    // internal
    RequireFile = File | Sound | RequireGraphics,
    // internal
    RequireWindow = Window | Keyboard | Mouse | Joystick | RequireGraphics,
};

CoreModules operator|(CoreModules a, CoreModules b);
bool CoreModulesHasBit(CoreModules a, CoreModules b);

class Configuration : public BaseObject {
private:
    bool isFullscreen_ = false;
    bool isResizable_ = false;
    GraphicsDeviceType deviceType_ = GraphicsDeviceType::Default;
    bool waitVSync_ = false;

    CoreModules coreModules_ = CoreModules::Default;

    bool consoleLoggingEnabled_ = false;
    bool fileLoggingEnabled_ = false;

    std::u16string logFileName_ = u"Log.txt";

public:
    Configuration();
    ~Configuration();
    static std::shared_ptr<Configuration> Create();

    bool GetIsFullscreen() const;
    void SetIsFullscreen(bool isFullscreen);

    bool GetIsResizable() const;
    void SetIsResizable(bool isResizable);

    GraphicsDeviceType GetDeviceType() const;
    void SetDeviceType(GraphicsDeviceType deviceType);

    bool GetWaitVSync() const;
    void SetWaitVSync(bool waitVSync);

    CoreModules GetEnabledCoreModules() const;
    void SetEnabledCoreModules(CoreModules modules);

    bool GetConsoleLoggingEnabled() const;
    void SetConsoleLoggingEnabled(bool fileLoggingEnabled);

    bool GetFileLoggingEnabled() const;
    void SetFileLoggingEnabled(bool enabeldFileLogging);

    const char16_t* GetLogFileName();
    void SetLogFileName(const char16_t* logFileName);
};

}  // namespace Altseed2