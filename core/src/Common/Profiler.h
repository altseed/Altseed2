#pragma once

#define EASY_PROFILER_STATIC
#include <easy/profiler.h>

#include "../BaseObject.h"
#include "StringHelper.h"

namespace Altseed2 {

class ProfilerBlockDescriptor : public BaseObject {
    const ::profiler::BaseBlockDescriptor* descriptor_;

public:
    ProfilerBlockDescriptor(const ::profiler::BaseBlockDescriptor* descriptor);
    virtual ~ProfilerBlockDescriptor() = default;

    const ::profiler::BaseBlockDescriptor* GetDescriptor() const;
};

class ProfilerBlock : public BaseObject {
    std::shared_ptr<ProfilerBlockDescriptor> desc_;
    std::string name_;

public:
    ProfilerBlock(std::shared_ptr<ProfilerBlockDescriptor> desc, const char* name);
    virtual ~ProfilerBlock() = default;
    std::string& GetName() { return name_; }
    std::shared_ptr<ProfilerBlockDescriptor>& GetDescriptor() { return desc_; }
};

class Profiler {
public:
    static std::shared_ptr<ProfilerBlock> CreateBlock(std::shared_ptr<ProfilerBlockDescriptor> desc, const char* name);

    static void BeginBlock(std::shared_ptr<ProfilerBlock> block);

    static void EndBlock();

    static std::shared_ptr<ProfilerBlockDescriptor> RegisterDescription(const char* _compiletimeName, const char* _filename, int _line, ::profiler::color_t _color);

    static void StartCapture();

    static void StopCapture();

    static void StartListen(int port);

    static void DumpToFileAndStopCapture(const char16_t* path);
};

}  // namespace Altseed2