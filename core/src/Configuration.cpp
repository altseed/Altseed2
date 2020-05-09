#include "Configuration.h"

#include "BaseObject.h"

namespace Altseed {

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

bool Configuration::GetConsoleLoggingEnabled() const { return consoleLoggingEnabled_; }

void Configuration::SetConsoleLoggingEnabled(bool consoleLoggingEnabled) { consoleLoggingEnabled_ = consoleLoggingEnabled; }

bool Configuration::GetFileLoggingEnabled() const { return fileLoggingEnabled_; }

void Configuration::SetFileLoggingEnabled(bool fileLoggingEnabled) { fileLoggingEnabled_ = fileLoggingEnabled; }

bool Configuration::GetToolEnabled() const { return toolEnabled_; }

void Configuration::SetToolEnabled(bool toolEnabled) { toolEnabled_ = toolEnabled; }

const char16_t* Configuration::GetLogFileName() { return logFileName_.c_str(); }

void Configuration::SetLogFileName(const char16_t* logFilename) { logFileName_ = std::u16string(logFilename); }

}  // namespace Altseed