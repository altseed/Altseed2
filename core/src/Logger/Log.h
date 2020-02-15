#pragma once

#include <spdlog/spdlog.h>
#include <memory>

#include "../BaseObject.h"
#include "../Common/Assertion.h"
#include "../Common/StringHelper.h"

namespace Altseed {
    
enum class LogLevel : int32_t {
    Trace       = SPDLOG_LEVEL_TRACE,
    Debug       = SPDLOG_LEVEL_DEBUG,
    Info = SPDLOG_LEVEL_INFO,
    Warning     = SPDLOG_LEVEL_WARN,
    Error       = SPDLOG_LEVEL_ERROR,
    Critical    = SPDLOG_LEVEL_CRITICAL,
    Off         = SPDLOG_LEVEL_OFF,
};

enum class LogCategory : int32_t { Core = 0, Engine, User };

class Log : public BaseObject {
private:
    static std::shared_ptr<Log> instance_;
    std::unordered_map<LogCategory, std::shared_ptr<spdlog::logger>> loggers;

public:
    static bool Initialize(const char* filename);

    static void Terminate();

    static std::shared_ptr<Log>& GetInstance();

    template<typename... Args>
    void Write(LogCategory category, LogLevel level, const char16_t* format, const Args&... args) {
        switch (level) {
            case LogLevel::Trace:
                Trace(category, format, args...);
                break;
            case LogLevel::Debug:
                Debug(category, format, args...);
                break;
            case LogLevel::Info:
                Info(category, format, args...);
                break;
            case LogLevel::Warning:
                Warn(category, format, args...);
                break;
            case LogLevel::Error:
                Error(category, format, args...);
                break;
            case LogLevel::Critical:
                Critical(category, format, args...);
                break;
            case LogLevel::Off:
                break;
            default:
                ASD_ASSERT(false, "Unexpected LogLevel");
                break;
        }
    }

    template<typename... Args>
    void Trace(LogCategory category, const char16_t* format, const Args&... args) {
        loggers[category]->trace(utf16_to_utf8(format).c_str(), args...);
    }

    template<typename... Args>
    void Debug(LogCategory category, const char16_t* format, const Args&... args) {
        loggers[category]->debug(utf16_to_utf8(format).c_str(), args...);
    }

    template<typename... Args>
    void Info(LogCategory category, const char16_t* format, const Args&... args) {
        loggers[category]->info(utf16_to_utf8(format).c_str(), args...);
    }

    template <typename... Args>
    void Warn(LogCategory category, const char16_t* format, const Args&... args) {
        loggers[category]->warn(utf16_to_utf8(format).c_str(), args...);
    }

    template <typename... Args>
    void Error(LogCategory category, const char16_t* format, const Args&... args) {
        loggers[category]->error(utf16_to_utf8(format).c_str(), args...);
    }

    template <typename... Args>
    void Critical(LogCategory category, const char16_t* format, const Args&... args) {
        loggers[category]->critical(utf16_to_utf8(format).c_str(), args...);
    }
    
    void SetLevel(LogCategory category, LogLevel level);
};

}  // namespace Altseed
