#pragma once

#define EASY_PROFILER_STATIC
#include <easy/profiler.h>

#include "../BaseObject.h"
#include "../Graphics/Color.h"
#include "StringHelper.h"

namespace Altseed2 {

#if !USE_CBG

class ProfilerBlock : public BaseObject {
    const ::profiler::BaseBlockDescriptor* descriptor_;
    std::string name_;
    Color color_;

public:
    ProfilerBlock(const ::profiler::BaseBlockDescriptor* descriptor, const char* name);
    virtual ~ProfilerBlock() = default;
    std::string& GetName() { return name_; }
    const ::profiler::BaseBlockDescriptor* GetDescriptor() const { return descriptor_; }
};

#endif

class Profiler : public BaseObject {
private:
    static std::shared_ptr<Profiler> instance_;
    bool isProfilerRunning_ = false;
    std::unordered_map<std::string, std::shared_ptr<ProfilerBlock>> blocks_;
    static std::shared_ptr<ProfilerBlock> CreateBlock(const char* name, const char* _filename, int _line, const Color& color);

public:
    static std::shared_ptr<Profiler>& GetInstance();

#if !USE_CBG
    static bool Initialize();

    static void Terminate();
#endif

    void BeginBlock(const char16_t* name, const char16_t* _filename, int _line, const Color& color);

    void EndBlock();

    void StartCapture();

    void StopCapture();

    void StartListen(int port);

    void DumpToFileAndStopCapture(const char16_t* path);

    bool GetIsProfilerRunning() const;
};

}  // namespace Altseed2