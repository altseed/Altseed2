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
    std::shared_ptr<File> file_;

    std::shared_ptr<Int8Array> m_buffer;
    BaseFileReader* m_fileReader;

public:
    StreamFile(BaseFileReader* reader);
    virtual ~StreamFile();

    int32_t GetSize() const;

    int32_t GetCurrentPosition() const;

    int32_t Read(int32_t size);

    std::shared_ptr<Int8Array>& GetTempBuffer();

    int32_t GetTempBufferSize();

    bool GetIsInPackage() const;

    bool Reload() override;
};

}  // namespace Altseed