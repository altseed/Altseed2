#pragma once

#define EASY_PROFILER_STATIC
#include <easy/profiler.h>

#include "../BaseObject.h"
#include "StringHelper.h"

namespace Altseed2 {

class ProfilerBlockDescriptor : public BaseObject {
    const ::profiler::BaseBlockDescriptor* descriptor_;

public:
    ProfilerBlockDescriptor(const ::profiler::BaseBlockDescriptor* descriptor)
        : descriptor_(descriptor) {}

    virtual ~ProfilerBlockDescriptor() = default;

    const ::profiler::BaseBlockDescriptor* GetDescriptor() const { return descriptor_; }
};

class ProfilerBlock : public BaseObject {
    ::profiler::Block block_;

public:
    ProfilerBlock(std::shared_ptr<ProfilerBlockDescriptor> desc, const char* name) : block_(desc->GetDescriptor(), name) {}
    virtual ~ProfilerBlock() = default;
    ::profiler::Block& GetBlock() { return block_; }
};

class Profiler {
public:
    static std::shared_ptr<ProfilerBlock> createBlock(std::shared_ptr<ProfilerBlockDescriptor> desc, const char* name) {
        return MakeAsdShared<ProfilerBlock>(desc, name);
    };

    static void beginBlock(std::shared_ptr<ProfilerBlock> block) {
        ::profiler::beginBlock(block->GetBlock());
    }

    static void endBlock() {
        ::profiler::endBlock();
    }

    static std::shared_ptr<ProfilerBlockDescriptor> registerDescription(const char* _autogenUniqueId, const char* _compiletimeName, const char* _filename, int _line, ::profiler::color_t _color) {
        const auto uniqueName = std::string(_filename) + " : " + std::to_string(_line);

        auto desc = ::profiler::registerDescription(profiler::EasyBlockStatus::ON, uniqueName.c_str(), uniqueName.c_str(), _filename, _line, ::profiler::BlockType::Block, _color, true);

        return MakeAsdShared<ProfilerBlockDescriptor>(desc);
    }

    static void StartCapture();

    static void StopCapture();

    static void StartListen(int port);

    static void DumpToFile(const char16_t* path);
};

}  // namespace Altseed2