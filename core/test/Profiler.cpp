#include <Common/Profiler.h>
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

TEST(Profiler, Basic) {
    Altseed2::Profiler::Initialize();

    Altseed2::Profiler::GetInstance()->StartCapture();

    Altseed2::Profiler::GetInstance()->BeginBlock("Basic1", __FILE__, __LINE__, Altseed2::Color(255, 0, 0, 255));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    Altseed2::Profiler::GetInstance()->BeginBlock("Basic2", __FILE__, __LINE__, Altseed2::Color(0, 0, 255, 255));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    Altseed2::Profiler::GetInstance()->EndBlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    Altseed2::Profiler::GetInstance()->EndBlock();

    Altseed2::Profiler::GetInstance()->DumpToFileAndStopCapture(u"Profiler.prof");

    Altseed2::Profiler::Terminate();
}
