#include "Configuration.h"

#include "BaseObject.h"

namespace Altseed2 {

bool CoreModulesHasBit(CoreModules a, CoreModules b) {
    return (static_cast<int32_t>(a) & static_cast<int32_t>(b)) != 0;
}

CoreModules operator|(CoreModules a, CoreModules b) {
    return static_cast<CoreModules>(static_cast<int32_t>(a) | static_cast<int32_t>(b));
}

std::shared_ptr<Configuration> Configuration::Create() {
    auto res = MakeAsdShared<Configuration>();
    return res;
}

Configuration::Configuration() {}
Configuration::~Configuration() {}

bool Configuration::GetIsFullscreen() const { return isFullscreen_; }

void Configuration::SetIsFullscreen(bool isFullscreenMode) { isFullscreen_ = isFullscreenMode; }

bool Configuration::GetIsResizable() const { return isResizable_; }

void Configuration::SetIsResizable(bool isResizable) { isResizable_ = isResizable; }

GraphicsDeviceType Configuration::GetDeviceType() const { return deviceType_; }

void Configuration::SetDeviceType(GraphicsDeviceType deviceType) { deviceType_ = deviceType; }

bool Configuration::GetWaitVSync() const { return waitVSync_; }

void Configuration::SetWaitVSync(bool waitVSync) { waitVSync_ = waitVSync; }

CoreModules Configuration::GetEnabledCoreModules() const { return coreModules_; }

void Configuration::SetEnabledCoreModules(CoreModules coreModules) { coreModules_ = coreModules; }

bool Configuration::GetConsoleLoggingEnabled() const { return consoleLoggingEnabled_; }

void Configuration::SetConsoleLoggingEnabled(bool consoleLoggingEnabled) { consoleLoggingEnabled_ = consoleLoggingEnabled; }

bool Configuration::GetFileLoggingEnabled() const { return fileLoggingEnabled_; }

void Configuration::SetFileLoggingEnabled(bool fileLoggingEnabled) { fileLoggingEnabled_ = fileLoggingEnabled; }

const char16_t* Configuration::GetLogFileName() { return logFileName_.c_str(); }

void Configuration::SetLogFileName(const char16_t* logFilename) {
    logFileName_ = logFilename == nullptr ? u"" : std::u16string(logFilename);
}

}  // namespace Altseed2