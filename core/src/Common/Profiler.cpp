#include "Profiler.h"

namespace Altseed2 {

ProfilerBlockDescriptor::ProfilerBlockDescriptor(const ::profiler::BaseBlockDescriptor* descriptor)
    : descriptor_(descriptor) {}

const ::profiler::BaseBlockDescriptor* ProfilerBlockDescriptor::GetDescriptor() const { return descriptor_; }

ProfilerBlock::ProfilerBlock(std::shared_ptr<ProfilerBlockDescriptor> desc, const char* name) : desc_(desc), name_(name) {}

std::shared_ptr<ProfilerBlock> Profiler::CreateBlock(std::shared_ptr<ProfilerBlockDescriptor> desc, const char* name) {
    return MakeAsdShared<ProfilerBlock>(desc, name);
};

void Profiler::BeginBlock(std::shared_ptr<ProfilerBlock> block) {
    ::profiler::beginNonScopedBlock(block->GetDescriptor()->GetDescriptor(), block->GetName().c_str());
}

void Profiler::EndBlock() {
    ::profiler::endBlock();
}

std::shared_ptr<ProfilerBlockDescriptor> Profiler::RegisterDescription(const char* _compiletimeName, const char* _filename, int _line, ::profiler::color_t _color) {
    const auto uniqueName = std::string(_filename) + " : " + std::to_string(_line);

    auto desc = ::profiler::registerDescription(profiler::EasyBlockStatus::ON, uniqueName.c_str(), uniqueName.c_str(), _filename, _line, ::profiler::BlockType::Block, _color, true);

    return MakeAsdShared<ProfilerBlockDescriptor>(desc);
}

void Profiler::StartCapture() {
    ::profiler::setEnabled(true);
}

void Profiler::StopCapture() {
    ::profiler::setEnabled(false);
}

void Profiler::StartListen(int port) {
    ::profiler::startListen(port);
}

void Profiler::DumpToFileAndStopCapture(const char16_t* path) {
    ::profiler::dumpBlocksToFile(utf16_to_utf8(path).c_str());
}
}  // namespace Altseed2