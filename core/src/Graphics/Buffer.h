#pragma once

#include <LLGI.Base.h>

#include "../BaseObject.h"

namespace Altseed2 {

enum class BufferUsageType : int32_t{
    Index = 1 << 0,
    Vertex = 1 << 1,
    Constant = 1 << 2,
    Compute = 1 << 3,
};

class Buffer : public BaseObject {
private:
    std::shared_ptr<LLGI::Buffer> buffer_ = nullptr;

public:
    Buffer(std::shared_ptr<LLGI::Buffer> buffer);

    static std::shared_ptr<Buffer> Create(BufferUsageType usage, int32_t size);

    void* Lock();
    void Unlock();

    void* Read();

    int32_t GetSize();

    BufferUsageType GetBufferUsage();

#if !USE_CBG
    std::shared_ptr<LLGI::Buffer> GetLL() { return buffer_; }
#endif
};

}  // namespace Altseed2