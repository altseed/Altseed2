#pragma once

#include <fstream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "../BaseObject.h"

#if !USE_CBG

namespace Altseed2 {

enum class SeekOrigin { Begin,
                        Current,
                        End };

class BaseFileReader : public BaseObject {
private:
    std::shared_ptr<std::ifstream> file_;

protected:
    int64_t position_;
    int64_t length_;
    std::u16string path_;
    std::recursive_mutex readerMtx_;

    //! for PackFileReader
    BaseFileReader(const std::u16string& path);

public:
    BaseFileReader(std::shared_ptr<std::ifstream>& file, const std::u16string& path);
    virtual ~BaseFileReader();

    int64_t GetPosition() const { return position_; }
    const std::u16string& GetFullPath() const { return path_; }

    virtual int64_t GetSize();

    virtual void ReadBytes(std::vector<uint8_t>& buffer, const int64_t count);
    uint32_t ReadUInt32();
    uint64_t ReadUInt64();
    void ReadAllBytes(std::vector<uint8_t>& buffer);

    virtual void Seek(const int64_t offset, const SeekOrigin origin = SeekOrigin::Begin);

    virtual bool GetIsInPackage() const;

    //! for core
    void Close();
};
}  // namespace Altseed2

#endif