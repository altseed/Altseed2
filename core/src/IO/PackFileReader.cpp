#include "PackFileReader.h"

#include <algorithm>
#include <iterator>

namespace Altseed2 {
PackFileReader::PackFileReader(zip_file* zipFile, const std::u16string& path, const zip_stat_t* stat)
    : BaseFileReader(std::shared_ptr<std::ifstream>(nullptr), path, true), m_zipFile(zipFile), m_isUseBuffer(false) {
    if (stat != nullptr) {
        std::unique_lock<std::recursive_mutex> lock(readerMtx_);

        length_ = stat->size;
        m_buffer.resize(length_);
        zip_fread(m_zipFile, reinterpret_cast<char*>(&m_buffer[0]), length_);
        m_isUseBuffer = true;
        delete stat;
    }
}

PackFileReader::~PackFileReader() { zip_fclose(m_zipFile); }

int64_t PackFileReader::GetSize() {
    if (length_ < 0) {
        std::unique_lock<std::recursive_mutex> lock(readerMtx_);

        zip_fseek(m_zipFile, 0, SEEK_END);
        length_ = zip_ftell(m_zipFile);

        zip_fseek(m_zipFile, position_, SEEK_SET);
    }

    return length_;
}

void PackFileReader::ReadBytes(std::vector<uint8_t>& buffer, const int64_t count) {
    std::unique_lock<std::recursive_mutex> lock(readerMtx_);

    if (position_ + count > GetSize() || count < 0) {
        buffer.resize(0);
        buffer.clear();
        return;
    }

    if (m_isUseBuffer)
        std::copy(m_buffer.begin() + position_, m_buffer.begin() + position_ + count, std::back_inserter(buffer));
    else {
        buffer.resize(count);
        zip_fread(m_zipFile, reinterpret_cast<char*>(&buffer[0]), count);
    }

    position_ += count;
}

void PackFileReader::Seek(const int64_t offset, const SeekOrigin origin) {
    std::unique_lock<std::recursive_mutex> lock(readerMtx_);

    switch (origin) {
        case SeekOrigin::Begin:
            if (!m_isUseBuffer) zip_fseek(m_zipFile, offset, SEEK_SET);
            position_ = offset;
            break;
        case SeekOrigin::Current:
            if (!m_isUseBuffer) zip_fseek(m_zipFile, offset, SEEK_CUR);
            position_ += offset;
            break;
        case SeekOrigin::End:
            if (!m_isUseBuffer) zip_fseek(m_zipFile, offset, SEEK_CUR);
            position_ = GetSize();
            break;
        default:
            break;
    }
}

bool PackFileReader::GetIsInPackage() const { return true; }

}  // namespace Altseed2