#include "PackFileReader.h"
#include <algorithm>
#include <iterator>

namespace altseed {
PackFileReader::PackFileReader(zip_file* zipFile, const std::u16string& path, const zip_stat_t* stat)
    : BaseFileReader(path), m_zipFile(zipFile), m_isUseBuffer(false) {
    if (stat != nullptr) {
        std::unique_lock<std::recursive_mutex> lock(m_readerMtx);

        m_length = stat->size;
        m_buffer.resize(m_length);
        zip_fread(m_zipFile, reinterpret_cast<char*>(&m_buffer[0]), m_length);
        m_isUseBuffer = true;
        delete stat;
    }
}

PackFileReader::~PackFileReader() { zip_fclose(m_zipFile); }

int64_t PackFileReader::GetSize() {
    if (m_length < 0) {
        std::unique_lock<std::recursive_mutex> lock(m_readerMtx);

        zip_fseek(m_zipFile, 0, SEEK_END);
        m_length = zip_ftell(m_zipFile);

        zip_fseek(m_zipFile, m_position, SEEK_SET);
    }

    return m_length;
}

void PackFileReader::ReadBytes(std::vector<uint8_t>& buffer, const int64_t count) {
    std::unique_lock<std::recursive_mutex> lock(m_readerMtx);

    if (m_position + count > GetSize() || count < 0) {
        buffer.resize(0);
        buffer.clear();
        return;
    }

    if (m_isUseBuffer)
        std::copy(m_buffer.begin() + m_position, m_buffer.begin() + m_position + count, std::back_inserter(buffer));
    else {
        buffer.resize(count);
        zip_fread(m_zipFile, reinterpret_cast<char*>(&buffer[0]), count);
    }

    m_position += count;
}

void PackFileReader::Seek(const int64_t offset, const SeekOrigin origin) {
    std::unique_lock<std::recursive_mutex> lock(m_readerMtx);

    switch (origin) {
        case SeekOrigin::Begin:
            if (!m_isUseBuffer) zip_fseek(m_zipFile, offset, SEEK_SET);
            m_position = offset;
            break;
        case SeekOrigin::Current:
            if (!m_isUseBuffer) zip_fseek(m_zipFile, offset, SEEK_CUR);
            m_position += offset;
            break;
        case SeekOrigin::End:
            if (!m_isUseBuffer) zip_fseek(m_zipFile, offset, SEEK_CUR);
            m_position = GetSize();
            break;
        default:
            break;
    }
}

bool PackFileReader::GetIsInPackage() const { return true; }

}  // namespace altseed