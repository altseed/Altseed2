#pragma once

#include <memory>

#include "../BaseObject.h"
#include "../Common/Array.h"
#include "../Common/Resource.h"
#include "BaseFileReader.h"

namespace Altseed {
class File;

class StreamFile : public Resource {
private:
    std::shared_ptr<Int8Array> m_buffer;
    std::shared_ptr<BaseFileReader> m_fileReader;

    static std::mutex m_streamFileMtx;

public:
    StreamFile(std::shared_ptr<BaseFileReader> reader);
    virtual ~StreamFile();

    static std::shared_ptr<StreamFile> Create(const char16_t* path);

    int32_t GetSize() const;

    int32_t GetCurrentPosition() const;

    int32_t Read(int32_t size);

    std::shared_ptr<Int8Array>& GetTempBuffer();

    int32_t GetTempBufferSize();

    bool GetIsInPackage() const;

    bool Reload() override;
};

}  // namespace Altseed