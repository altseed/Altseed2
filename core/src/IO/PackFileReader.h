#pragma once

#include <zip.h>
#include "BaseFileReader.h"

namespace Altseed {

class PackFileReader : public BaseFileReader {
private:
    zip_file* m_zipFile;

    // ! libzip can not zip_ftell and zip_fseek to packed file with password
    std::vector<uint8_t> m_buffer;
    bool m_isUseBuffer;

public:
    PackFileReader(zip_file* zipFile, const std::u16string& path, const zip_stat_t* stat = nullptr);
    virtual ~PackFileReader();

    int64_t GetSize() override;

    void ReadBytes(std::vector<uint8_t>& buffer, const int64_t count) override;

    void Seek(const int64_t offset, const SeekOrigin origin = SeekOrigin::Begin) override;

    bool GetIsInPackage() const override;
};
}  // namespace Altseed