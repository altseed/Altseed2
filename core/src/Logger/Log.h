#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <sstream>
#include <string>

#include "../BaseObject.h"
#include "../Common/Assertion.h"
#include "../Common/StringHelper.h"

namespace Altseed2 {

enum class LogLevel : int32_t {
    Trace = spdlog::level::trace,
    Debug = spdlog::level::debug,
    Info = spdlog::level::info,
    Warn = spdlog::level::warn,
    Error = spdlog::level::err,
    Critical = spdlog::level::critical,
    Off = spdlog::level::off,
};

enum class LogCategory : int32_t {
    Core = 0,
    Graphics = 1,
    Engine = 2,
    User = 3,
};

#ifdef _WIN32
#define __FILENAME__ strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__
#define LOG_CRITICAL(format, ...) Log::GetInstance()->CriticalCore(__FILENAME__, __FUNCTION__, __LINE__, format, __VA_ARGS__);
#define LOG_CRITICAL_FMT(format, ...) Log::GetInstance()->CriticalCore(__FILENAME__, __FUNCTION__, __LINE__, format, __VA_ARGS__);
#else
#define __FILENAME__ strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define LOG_CRITICAL(format) Log::GetInstance()->CriticalCore(__FILENAME__, __func__, __LINE__, format);
#define LOG_CRITICAL_FMT(format, ...) Log::GetInstance()->CriticalCore(__FILENAME__, __func__, __LINE__, format, __VA_ARGS__);
#endif

class Log : public BaseObject {
private:
    static std::shared_ptr<Log> instance_;
    bool enabledLogging_;
    std::unordered_map<int32_t, std::shared_ptr<spdlog::logger>> loggers_;

public:
    static bool Initialize(bool enabledConsoleLogging, bool enabledFileLogging, std::u16string filename);

    static void Terminate();

    static std::shared_ptr<Log>& GetInstance();

    template <typename... Args>
    void Write(LogCategory category, LogLevel level, const char16_t* format, const Args&... args) {
        if (!GetInstance()->enabledLogging_ || level == LogLevel::Off) return;

        const auto logger = loggers_[static_cast<int32_t>(category)];

        switch (level) {
            case LogLevel::Trace:
                logger->trace(utf16_to_utf8(format).c_str(), args...);
                break;
            case LogLevel::Debug:
                logger->debug(utf16_to_utf8(format).c_str(), args...);
                break;
            case LogLevel::Info:
                logger->info(utf16_to_utf8(format).c_str(), args...);
                break;
            case LogLevel::Warn:
                logger->warn(utf16_to_utf8(format).c_str(), args...);
                break;
            case LogLevel::Error:
                logger->error(utf16_to_utf8(format).c_str(), args...);
                break;
            case LogLevel::Critical:
                logger->critical(utf16_to_utf8(format).c_str(), args...);
                break;
            default:
                ASD_ASSERT(false, "Unexpected LogLevel");
                break;
        }
    }

    template <typename... Args>
    void Trace(LogCategory category, const char16_t* format, const Args&... args) {
        Write(category, LogLevel::Trace, format, args...);
    }

    template <typename... Args>
    void Debug(LogCategory category, const char16_t* format, const Args&... args) {
        Write(category, LogLevel::Debug, format, args...);
    }

    template <typename... Args>
    void Info(LogCategory category, const char16_t* format, const Args&... args) {
        Write(category, LogLevel::Info, format, args...);
    }

    template <typename... Args>
    void Warn(LogCategory category, const char16_t* format, const Args&... args) {
        Write(category, LogLevel::Warn, format, args...);
    }

    template <typename... Args>
    void Error(LogCategory category, const char16_t* format, const Args&... args) {
        Write(category, LogLevel::Error, format, args...);
    }

    template <typename... Args>
    void Critical(LogCategory category, const char16_t* format, const Args&... args) {
        Write(category, LogLevel::Critical, format, args...);
    }

    template <typename... Args>
    void CriticalCore(const char* filename, const char* funcname, const int linenum, const char16_t* format, const Args&... args) {
        std::stringstream ss;
        ss << "[" << filename << "]"
           << "[" << funcname << "]"
           << "[" << linenum << "]" << utf16_to_utf8(format).c_str();
        Write(LogCategory::Core, LogLevel::Critical, utf8_to_utf16(ss.str()).c_str(), args...);
    }

    void SetLevel(LogCategory category, LogLevel level);
};

}  // namespace Altseed2
