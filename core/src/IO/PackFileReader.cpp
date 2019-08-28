#include "PackFileReader.h"

namespace altseed {
PackFileReader::PackFileReader(zip_file* zipFile, const std::u16string& path) : BaseFileReader(path) {}
PackFileReader::~PackFileReader() {}
int PackFileReader::GetSize() { return 0; }
void PackFileReader::ReadBytes(std::vector<uint8_t>& buffer, const int64_t count, int64_t globalPos) {}
uint32_t PackFileReader::ReadUInt32(int64_t globalPos) { return uint32_t(); }
uint64_t PackFileReader::ReadUInt64(int64_t globalPos) { return uint64_t(); }
void PackFileReader::ReadAllBytes(std::vector<uint8_t>& buffer, int64_t globalPos) {}
void PackFileReader::Seek(const int64_t offset, const SeekOrigin origin) {}
}  // namespace altseed