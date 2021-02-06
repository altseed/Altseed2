#include "Profiler.h"

namespace Altseed2 {
void Profiler::StartCapture() {
    ::profiler::setEnabled(true);
    //EASY_PROFILER_ENABLE;
    //::profiler::startCapture();
}

void Profiler::StopCapture() {
    // ::profiler::stopCapture();
}

void Profiler::StartListen(int port) {
    ::profiler::startListen(port);
}

void Profiler::DumpToFile(const char16_t* path) {
    ::profiler::dumpBlocksToFile(utf16_to_utf8(path).c_str());
}
}  // namespace Altseed2