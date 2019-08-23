#pragma once

#include <memory>
#include "../Common/Int8Array.h"
#include "../BaseObject.h"

namespace altseed {
class File;

class StreamFile : public BaseObject {
private:
    std::shared_ptr<File> file_;

public:
    StreamFile();
    virtual ~StreamFile();

    int32_t GetSize() const;

    int32_t GetCurrentPosition() const;

    int32_t Read(int32_t size);

    Int8Array& GetTempBuffer();

    int32_t GetTempBufferSize();
};

}  // namespace altseed