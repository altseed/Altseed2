#include "BaseFileReader.h"

namespace altseed {
BaseFileReader::BaseFileReader(const std::u16string& path) : BaseObject() {}
BaseFileReader::~BaseFileReader() {}
int BaseFileReader::GetSize() { return 0; }
void BaseFileReader::ReadBytes(std::vector<uint8_t>& buffer, const int64_t count, int64_t globalPos) {}
uint32_t BaseFileReader::ReadUInt32(int64_t globalPos) { return uint32_t(); }
uint64_t BaseFileReader::ReadUInt64(int64_t globalPos) { return uint64_t(); }
void BaseFileReader::ReadAllBytes(std::vector<uint8_t>& buffer, int64_t globalPos) {}
void BaseFileReader::Seek(const int64_t offset, const SeekOrigin origin) {}
}  // namespace altseed