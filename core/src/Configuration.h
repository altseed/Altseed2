#pragma once

#include "BaseObject.h"

namespace Altseed {

class Configuration : public BaseObject {
private:
    bool isFullscreen_ = false;
    bool isResizable_ = false;
    bool consoleLoggingEnabled_ = false;
    bool fileLoggingEnabled_ = false;
    bool toolEnabled_ = false;
    std::u16string logFileName_ = u"Log.txt";

public:
    Configuration();
    ~Configuration();
    static std::shared_ptr<Configuration> Create();

    bool GetIsFullscreen() const;
    void SetIsFullscreen(bool isFullscreen);

    bool GetIsResizable() const;
    void SetIsResizable(bool isResizable);

    bool GetConsoleLoggingEnabled() const;
    void SetConsoleLoggingEnabled(bool fileLoggingEnabled);

    bool GetFileLoggingEnabled() const;
    void SetFileLoggingEnabled(bool enabeldFileLogging);

    bool GetToolEnabled() const;
    void SetToolEnabled(bool toolEnabled);

    const char16_t* GetLogFileName();
    void SetLogFileName(const char16_t* logFileName);
};

}  // namespace Altseed