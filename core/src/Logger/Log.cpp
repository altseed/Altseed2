#include "Log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>
#include <vector>

#include "../Common/Assertion.h"
#include "../Common/StringHelper.h"

namespace Altseed {

std::shared_ptr<Log> Log::instance_;

bool Log::Initialize(const char16_t* filename) {
    try {
        instance_ = MakeAsdShared<Log>();

        const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> file_sink = nullptr;
        if(filename != nullptr)
        {
            file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(utf16_to_utf8(filename).c_str());
        }

        const auto create_logger = [console_sink, file_sink](const auto category, const auto name) {
            std::vector<spdlog::sink_ptr> multi_sinks = { console_sink };
            if(file_sink != nullptr) multi_sinks.push_back(file_sink);
            const auto logger = std::make_shared<spdlog::logger>(name, multi_sinks.begin(), multi_sinks.end());
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
