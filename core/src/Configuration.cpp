#include "BaseObject.h"
#include "Configuration.h"

namespace Altseed {

std::shared_ptr<Configuration> Configuration::Create()
{
    auto res = MakeAsdShared<Configuration>();
    return res;
}

Configuration::Configuration() {}
Configuration::~Configuration() {}

const bool Configuration::GetIsFullscreenMode() { return isFullscreenMode_; }

void Configuration::SetIsFullscreenMode(bool isFullscreenMode) { isFullscreenMode_ = isFullscreenMode; }

const bool Configuration::GetIsResizable() { return isResizable_; }

void Configuration::SetIsResizable(bool isResizable) { isResizable_ = isResizable; }

const bool Configuration::GetEnabledConsoleLogging() { return enabledConsoleLogging_;}

void Configuration::SetEnabledConsoleLogging(bool enabledConsoleLogging) { enabledConsoleLogging_  = enabledConsoleLogging; }

const bool Configuration::GetEnabledFileLogging() { return enabledFileLogging_; }

void Configuration::SetEnabledFileLogging(bool enabeldFileLogging) { enabledFileLogging_ = enabeldFileLogging; }

const char16_t* Configuration::GetLogFilename() { return logFilename_.c_str(); }

void Configuration::SetLogFilename(const char16_t* logFilename) { logFilename_ = std::u16string(logFilename); }

}  // namespace Altseed