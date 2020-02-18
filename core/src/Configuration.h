#pragma once

#include "BaseObject.h"

namespace Altseed {

class Configuration : public BaseObject {
private:
    bool isFullscreenMode_ = false;
    bool isResizable_ = false;
    bool enabledConsoleLogging_ = true;
    bool enabledFileLogging_ = true;
    std::u16string logFilename_ = u"Log.txt";

public:
    Configuration();
    ~Configuration();
    static std::shared_ptr<Configuration> Create();

    const bool GetIsFullscreenMode();
    void SetIsFullscreenMode(bool isFullscreenMode);

    const bool GetIsResizable();
    void SetIsResizable(bool isResizable);

    const bool GetEnabledConsoleLogging();
    void SetEnabledConsoleLogging(bool enabledConsoleLogging);

    const bool GetEnabledFileLogging();
    void SetEnabledFileLogging(bool enabeldFileLogging);

    const char16_t* GetLogFilename();
    void SetLogFilename(const char16_t* logFilename);
};

}  // namespace Altseed