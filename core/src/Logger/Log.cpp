#include "Log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

#include "../Common/Assertion.h"
#include "../Common/StringHelper.h"

namespace Altseed {

std::shared_ptr<Log> Log::instance_;

bool Log::Initialize(const char* filename) {
    try {
        instance_ = MakeAsdShared<Log>();
        const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename);

        auto create_logger = [console_sink, file_sink](auto category, auto name) {
            const auto multi_sink = spdlog::sinks_init_list({console_sink, file_sink});
            const auto logger = std::make_shared<spdlog::logger>(name, multi_sink);
            logger->set_level((spdlog::level::level_enum)LogLevel::Trace);
            instance_->loggers[(int32_t)category] = logger;
        };

        create_logger(LogCategory::Core, "Core");
        create_logger(LogCategory::Engine, "Engine");
        create_logger(LogCategory::User, "User");

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
    loggers[(int32_t)category]->set_level((spdlog::level::level_enum)level);
}

}  // namespace Altseed
