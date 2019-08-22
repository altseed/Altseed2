#pragma once

#include <zip.h>
#include "BaseFileReader.h"

namespace altseed {

class PackFileReader : public BaseFileReader {
private:
    zip_file* m_zipFile;

public:
    PackFileReader(zip_file* zipFile, const std::wstring& path);
    virtual ~PackFileReader();

    int GetSize();

    void ReadBytes(std::vector<uint8_t>& buffer, const int64_t count, int64_t globalPos = 0) override;
    uint32_t ReadUInt32(int64_t globalPos = 0) override;
    uint64_t ReadUInt64(int64_t globalPos = 0) override;
    void ReadAllBytes(std::vector<uint8_t>& buffer, int64_t globalPos = 0) override;

    void Seek(const int64_t offset, const SeekOrigin origin = SeekOrigin::Begin) override;
};
}  // namespace altseed