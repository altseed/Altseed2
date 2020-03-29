#pragma once

#include <fstream>
#include <mutex>
#include <string>
#include <vector>

#include "../BaseObject.h"

namespace Altseed {

enum class SeekOrigin { Begin, Current, End };

class BaseFileReader : public BaseObject {
private:
    std::ifstream m_file;

protected:
    int64_t m_position;
    int64_t m_length;
    std::u16string m_path;
    std::recursive_mutex m_readerMtx;

public:
    BaseFileReader(const std::u16string& path, bool isInPackage = false);
    virtual ~BaseFileReader();

    int64_t GetPosition() const { return m_position; }
    const std::u16string& GetFullPath() const { return m_path; }

    virtual int64_t GetSize();

    virtual void ReadBytes(std::vector<uint8_t>& buffer, const int64_t count);
    uint32_t ReadUInt32();
    uint64_t ReadUInt64();
    void ReadAllBytes(std::vector<uint8_t>& buffer);

    virtual void Seek(const int64_t offset, const SeekOrigin origin = SeekOrigin::Begin);

    virtual bool GetIsInPackage() const;
};
}  // namespace Altseed