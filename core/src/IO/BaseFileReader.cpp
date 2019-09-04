#include "BaseFileReader.h"

namespace altseed {
BaseFileReader::BaseFileReader(const std::u16string& path) : BaseObject(), m_path(path), m_length(-1), m_position(0) {}
BaseFileReader::~BaseFileReader() {}
int64_t BaseFileReader::GetSize() { return 0; }
void BaseFileReader::ReadBytes(std::vector<uint8_t>& buffer, const int64_t count) {}
uint32_t BaseFileReader::ReadUInt32() { return uint32_t(); }
uint64_t BaseFileReader::ReadUInt64() { return uint64_t(); }
void BaseFileReader::ReadAllBytes(std::vector<uint8_t>& buffer) { ReadBytes(buffer, GetSize()); }
void BaseFileReader::Seek(const int64_t offset, const SeekOrigin origin) {}
bool BaseFileReader::GetIsInPackage() const { return false; }
}  // namespace altseed