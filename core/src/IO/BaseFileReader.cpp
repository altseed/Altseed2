#include "BaseFileReader.h"

#include <assert.h>

#include "../Common/StringHelper.h"

namespace Altseed2 {
BaseFileReader::BaseFileReader(const std::u16string& path) : BaseObject(), path_(path), length_(-1), position_(0), file_(nullptr) {
}

BaseFileReader::BaseFileReader(std::shared_ptr<std::ifstream>& file, const std::u16string& path) : BaseObject(), path_(path), length_(-1), position_(0), file_(file) {
    ASD_ASSERT(file_ != nullptr && file_->good(), "bad ifstream");
}

BaseFileReader::~BaseFileReader() {
    if (file_ != nullptr && file_->is_open()) {
        file_->close();
    }
}

int64_t BaseFileReader::GetSize() {
    ASD_ASSERT(file_ != nullptr, "file_ is null");

    if (length_ < 0) {
        std::unique_lock<std::recursive_mutex> lock(readerMtx_);
        file_->seekg(0, std::ios_base::end);
        length_ = file_->tellg();
        file_->clear();
        file_->seekg(0, std::ios_base::beg);
    }
    return length_;
}

void BaseFileReader::ReadBytes(std::vector<uint8_t>& buffer, const int64_t count) {
    ASD_ASSERT(file_ != nullptr, "file_ is null");
    const auto size = GetSize();

    std::unique_lock<std::recursive_mutex> lock(readerMtx_);

    if (position_ + count > GetSize() || count < 0) {
        buffer.resize(0);
        buffer.clear();
        return;
    }

    buffer.resize(count);
    file_->read(reinterpret_cast<char*>(&buffer[0]), count);

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
    ASD_ASSERT(file_ != nullptr, "file_ is null");
    const auto size = GetSize();

    std::unique_lock<std::recursive_mutex> lock(readerMtx_);
    switch (origin) {
        case SeekOrigin::Begin:
            assert(0 <= offset && offset < size);
            file_->seekg(offset, file_->beg);
            position_ = offset;
            break;
        case SeekOrigin::Current:
            assert(0 <= position_ + offset && position_ + offset < size);
            file_->seekg(offset, file_->cur);
            position_ = offset + offset;
            break;
        case SeekOrigin::End:
            assert(0 <= offset + size && offset <= 0 && offset);
            file_->seekg(offset, file_->end);
            position_ = size + offset;
            break;
        default:
            assert(false);
            break;
    }
}

bool BaseFileReader::GetIsInPackage() const { return false; }

void BaseFileReader::Close() {
    if (!GetIsInPackage() && file_ != nullptr) {
        file_->close();
    }
}
}  // namespace Altseed2