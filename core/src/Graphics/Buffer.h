#pragma once

#include <LLGI.Base.h>

#include "../BaseObject.h"

namespace Altseed2 {

enum class BufferUsageType {
    Index = (int32_t)LLGI::BufferUsageType::Index,
    Vertex = (int32_t)LLGI::BufferUsageType::Vertex,
    Constant = (int32_t)LLGI::BufferUsageType::Constant,
    Compute = (int32_t)LLGI::BufferUsageType::Compute,
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