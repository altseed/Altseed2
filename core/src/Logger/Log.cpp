#include "Log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

#include "../Common/Assertion.h"
#include "../Common/StringHelper.h"

namespace Altseed {

std::shared_ptr<Log> Log::instance_;

bool Log::Initialize(const char16_t* filename) {
    try {
        instance_ = MakeAsdShared<Log>();
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(utf16_to_utf8(filename).c_str());
        auto multi_sink = spdlog::sinks_init_list({console_sink, file_sink});
        instance_->loggers[LogCategory::Core] = std::make_shared<spdlog::logger>("Core", multi_sink);
        instance_->loggers[LogCategory::Engine] = std::make_shared<spdlog::logger>("Engine", multi_sink);
        instance_->loggers[LogCategory::User] = std::make_shared<spdlog::logger>("User", multi_sink);
        return true;
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
        // ASD_ASSERT(false, "Log initialization failed: " + std::string(ex.what()));
        return false;
    }
}

void Log::Terminate() { instance_ = nullptr; }

std::shared_ptr<Log>& Log::GetInstance() { return instance_; }

void Log::SetLevel(LogCategory category, LogLevel level) {
    loggers[category]->set_level((spdlog::level::level_enum)level);
}

}  // namespace Altseed
