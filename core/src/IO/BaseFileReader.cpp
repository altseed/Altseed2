#include "BaseFileReader.h"

#include <assert.h>

#include "../Common/StringHelper.h"

namespace Altseed2 {

BaseFileReader::BaseFileReader(const std::u16string& path, bool isInPackage) : BaseObject(), path_(path), length_(-1), position_(0) {
    if (!isInPackage) {
        std::unique_lock<std::recursive_mutex> lock(readerMtx_);

#ifdef _WIN32
        m_file.open((wchar_t*)path.c_str(), std::basic_ios<char>::in | std::basic_ios<char>::binary);
#else
        m_file.open(utf16_to_utf8(path).c_str(), std::basic_ios<char>::in | std::basic_ios<char>::binary);
#endif
        ASD_ASSERT(!m_file.fail(), utf16_to_utf8(u"fail to open file : " + path).c_str());
    }
}

BaseFileReader::~BaseFileReader() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

int64_t BaseFileReader::GetSize() {
    if (length_ < 0) {
        std::unique_lock<std::recursive_mutex> lock(readerMtx_);
        m_file.seekg(0, std::ios_base::end);
        length_ = m_file.tellg();
        m_file.clear();
        m_file.seekg(0, std::ios_base::beg);
    }
    return length_;
}

void BaseFileReader::ReadBytes(std::vector<uint8_t>& buffer, const int64_t count) {
    const auto size = GetSize();

    std::unique_lock<std::recursive_mutex> lock(readerMtx_);

    if (position_ + count > GetSize() || count < 0) {
        buffer.resize(0);
        buffer.clear();
        return;
    }

    buffer.resize(count);
    m_file.read(reinterpret_cast<char*>(&buffer[0]), count);

    position_ += count;
}
uint32_t BaseFileReader::ReadUInt32() {
    std::vector<uint8_t> buffer;
    ReadBytes(buffer, sizeof(uint32_t));

    return *reinterpret_cast<const uint32_t*>(buffer.data());
}
uint64_t BaseFileReader::ReadUInt64() {
    std::vector<uint8_t> buffer;
    ReadBytes(buffer, sizeof(uint64_t));

    return *reinterpret_cast<const uint64_t*>(buffer.data());
}
void BaseFileReader::ReadAllBytes(std::vector<uint8_t>& buffer) {
    std::unique_lock<std::recursive_mutex> lock(readerMtx_);
    const auto tmp = position_;
    position_ = 0;
    ReadBytes(buffer, GetSize());
    position_ = tmp;
}

void BaseFileReader::Seek(const int64_t offset, const SeekOrigin origin) {
    const auto size = GetSize();

    std::unique_lock<std::recursive_mutex> lock(readerMtx_);
    switch (origin) {
        case SeekOrigin::Begin:
            assert(0 <= offset && offset < size);
            m_file.seekg(offset, m_file.beg);
            position_ = offset;
            break;
        case SeekOrigin::Current:
            assert(0 <= position_ + offset && position_ + offset < size);
            m_file.seekg(offset, m_file.cur);
            position_ = offset + offset;
            break;
        case SeekOrigin::End:
            assert(0 <= offset + size && offset <= 0 && offset);
            m_file.seekg(offset, m_file.end);
            position_ = size + offset;
            break;
        default:
            assert(false);
            break;
    }
}

bool BaseFileReader::GetIsInPackage() const { return false; }
}  // namespace Altseed2