#include "Buffer.h"

#include "../Logger/Log.h"
#include "Graphics.h"

namespace Altseed2 {

Buffer::Buffer(std::shared_ptr<LLGI::Buffer> buffer) {
    buffer_ = buffer;
}

// ユーザーがRead,Writeを指定できるようにすべきかも
std::shared_ptr<Buffer> Buffer::Create(BufferUsageType usage, int32_t size) {
    auto graphics = Graphics::GetInstance();
    if (graphics == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Graphics is not initialized.");
        return nullptr;
    }

    auto buffer = graphics->CreateBuffer((LLGI::BufferUsageType)usage, size);

    if (buffer == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Buffer::Create: Failed to create buffer");
        return nullptr;
    }

    return MakeAsdShared<Buffer>(buffer);
}

void* Buffer::Lock() {
    return buffer_->Lock();
}

void Buffer::Unlock() {
    buffer_->Unlock();
}

int32_t Buffer::GetSize() {
    return buffer_->GetSize();
}

BufferUsageType Buffer::GetBufferUsage() {
    return (BufferUsageType)buffer_->GetBufferUsage();
}

}  // namespace Altseed2