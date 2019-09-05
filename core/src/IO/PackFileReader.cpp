#include "PackFileReader.h"

namespace altseed {
PackFileReader::PackFileReader(zip_file* zipFile, const std::u16string& path) : BaseFileReader(path), m_zipFile(zipFile) {}

PackFileReader::~PackFileReader() { zip_fclose(m_zipFile); }

int64_t PackFileReader::GetSize() {
    if (m_length < 0) {
        zip_fseek(m_zipFile, 0, SEEK_END);
        m_length = zip_ftell(m_zipFile);

        zip_fseek(m_zipFile, m_position, SEEK_SET);
    }

    return m_length;
}

void PackFileReader::ReadBytes(std::vector<uint8_t>& buffer, const int64_t count) {
    if (m_position + count > GetSize() || count < 0) {
        buffer.resize(0);
        buffer.clear();
        return;
    }

    buffer.resize(count);
    zip_fread(m_zipFile, reinterpret_cast<char*>(&buffer[0]), count);

    m_position += count;
}

void PackFileReader::Seek(const int64_t offset, const SeekOrigin origin) {
    switch (origin) {
        case SeekOrigin::Begin:
            zip_fseek(m_zipFile, offset, SEEK_SET);
            m_position = offset;
            break;
        case SeekOrigin::Current:
            zip_fseek(m_zipFile, offset, SEEK_CUR);
            m_position += offset;
            break;
        case SeekOrigin::End:
            zip_fseek(m_zipFile, offset, SEEK_CUR);
            m_position = zip_ftell(m_zipFile);
            break;
        default:
            break;
    }
}

bool PackFileReader::GetIsInPackage() const { return true; }

}  // namespace altseed