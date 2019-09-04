#pragma once

#include <zip.h>
#include "BaseFileReader.h"

namespace altseed {

class PackFileReader : public BaseFileReader {
private:
    zip_file* m_zipFile;

public:
    PackFileReader(zip_file* zipFile, const std::u16string& path);
    virtual ~PackFileReader();

    int64_t GetSize() override;

    void ReadBytes(std::vector<uint8_t>& buffer, const int64_t count) override;

    void Seek(const int64_t offset, const SeekOrigin origin = SeekOrigin::Begin) override;

	bool GetIsInPackage() const override;
};
}  // namespace altseed