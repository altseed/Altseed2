#pragma once

#include "BaseObject.h"

namespace Altseed {

class Configuration : public BaseObject {
private:
    bool isFullscreenMode_ = false;
    bool isResizable_ = false;
    std::u16string logFilename_ = u"Log.txt";

public:
    static std::shared_ptr<Configuration> Create();

    const bool GetIsFullscreenMode();
    void SetIsFullscreenMode(bool isFullscreenMode);

    const bool GetIsResizable();
    void SetIsResizable(bool isResizable);

    const char16_t* GetLogFilename();
    void SetLogFilename(const char16_t* logFilename);
};

}  // namespace Altseed