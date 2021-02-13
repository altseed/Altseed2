#pragma once

#define EASY_PROFILER_STATIC
#include <easy/profiler.h>

#include "../BaseObject.h"
#include "../Graphics/Color.h"
#include "StringHelper.h"

namespace Altseed2 {

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

class Profiler : public BaseObject {
private:
    static std::shared_ptr<Profiler> instance_;
    std::unordered_map<std::string, std::shared_ptr<ProfilerBlock>> blocks_;
    static std::shared_ptr<ProfilerBlock> CreateBlock(const char* name, const char* _filename, int _line, const Color& color);

public:
    static std::shared_ptr<Profiler>& GetInstance();

    static bool Initialize();

    static void Terminate();

    void BeginBlock(const char* name, const char* _filename, int _line, const Color& color);

    void EndBlock();

    void StartCapture();

    void StopCapture();

    void StartListen(int port);

    void DumpToFileAndStopCapture(const char16_t* path);
};

}  // namespace Altseed2