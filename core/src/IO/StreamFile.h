#pragma once

#include <memory>
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

    void* GetTempBuffer();

    int32_t GetTempBufferSize();
};

}  // namespace altseed