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

    bool GetIsFullscreenMode() const;
    void SetIsFullscreenMode(bool isFullscreenMode);

    bool GetIsResizable() const;
    void SetIsResizable(bool isResizable);

    bool GetEnabledConsoleLogging() const;
    void SetEnabledConsoleLogging(bool enabledConsoleLogging);

    bool GetEnabledFileLogging() const;
    void SetEnabledFileLogging(bool enabeldFileLogging);

    const char16_t* GetLogFilename();
    void SetLogFilename(const char16_t* logFilename);
};

}  // namespace Altseed