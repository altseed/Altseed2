#include "TestHelper.h"

std::shared_ptr<Altseed2::Configuration> Altseed2TestConfig(Altseed2::CoreModules coreModules) {
    auto config = Altseed2::Configuration::Create();
    if (config == nullptr) return nullptr;
    config->SetConsoleLoggingEnabled(true);
    config->SetEnabledCoreModules(coreModules);
    return config;
}
