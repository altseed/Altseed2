#pragma once

#include <LLGI.Base.h>

#include "../BaseObject.h"
#include "../StdIntCBG.h"

namespace Altseed2 {

enum class BufferUsageType : int32_t {
    Index = 1 << 0,
    Vertex = 1 << 1,
    Constant = 1 << 2,
    Compute = 1 << 3,
    MapRead = 1 << 4,
    MapWrite = 1 << 5,
    CopySrc = 1 << 6,
    CopyDst = 1 << 7,
};


inline BufferUsageType operator|(BufferUsageType lhs, BufferUsageType rhs) {
    return static_cast<BufferUsageType>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

inline BufferUsageType operator&(BufferUsageType lhs, BufferUsageType rhs) {
    return static_cast<BufferUsageType>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

class Buffer : public BaseObject {
private:
    std::shared_ptr<LLGI::Buffer> buffer_ = nullptr;

public:
    Buffer(std::shared_ptr<LLGI::Buffer> buffer);

    static std::shared_ptr<Buffer> Create(BufferUsageType usage, int32_t size);

    void* Lock();
    void Unlock();

    int32_t GetSize();

    BufferUsageType GetBufferUsage();

#if !USE_CBG
    std::shared_ptr<LLGI::Buffer> GetLL() { return buffer_; }
#endif
};

}  // namespace Altseed2