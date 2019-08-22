#pragma once

#include <fstream>
#include <vector>
#include "../BaseObject.h"

namespace altseed {

enum class SeekOrigin { Begin, Current, End };

class BaseFileReader : public BaseObject {
private:
    std::ifstream m_file;

protected:
    int64_t m_position;
    int64_t m_length;
    std::wstring m_path;

public:
    BaseFileReader(const std::wstring& path);
    virtual ~BaseFileReader();

    int64_t GetPosition() const { return m_position; }
    const std::wstring& GetFullPath() const { return m_path; }

    virtual int GetSize();

    virtual void ReadBytes(std::vector<uint8_t>& buffer, const int64_t count, int64_t globalPos = 0);
    virtual uint32_t ReadUInt32(int64_t globalPos = 0);
    virtual uint64_t ReadUInt64(int64_t globalPos = 0);
    virtual void ReadAllBytes(std::vector<uint8_t>& buffer, int64_t globalPos = 0);

    virtual void Seek(const int64_t offset, const SeekOrigin origin = SeekOrigin::Begin);
};
}  // namespace altseed