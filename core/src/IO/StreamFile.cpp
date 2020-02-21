#include "StreamFile.h"

#include "File.h"

namespace Altseed {
std::mutex StreamFile::m_streamFileMtx;

StreamFile::StreamFile(std::shared_ptr<BaseFileReader> reader) : m_fileReader(reader) { m_buffer = MakeAsdShared<Int8Array>(); }

StreamFile::~StreamFile() {}

std::shared_ptr<StreamFile> StreamFile::Create(const char16_t* path) {
    std::lock_guard<std::mutex> lock(m_streamFileMtx);

    auto resources = Resources::GetInstance();
    auto cache = std::dynamic_pointer_cast<StreamFile>(resources->GetResourceContainer(ResourceType::StreamFile)->Get(path));
    if (cache != nullptr) {
        return cache;
    }

    auto reader = File::GetInstance()->CreateFileReader(path);

    if (reader == nullptr) return nullptr;

    auto res = MakeAsdShared<StreamFile>(reader);

    resources->GetResourceContainer(ResourceType::StreamFile)
            ->Register(path, std::make_shared<ResourceContainer::ResourceInfomation>(res, path));
    return res;
}

int32_t StreamFile::GetSize() const { return m_fileReader->GetSize(); }

int32_t StreamFile::GetCurrentPosition() const { return m_fileReader->GetPosition(); }

int32_t StreamFile::Read(int32_t size) {
    if (GetCurrentPosition() == GetSize()) return 0;

    std::vector<uint8_t> buffer;
    int readSize = size;

    if (GetCurrentPosition() + size >= GetSize()) readSize = GetSize() - GetCurrentPosition();

    m_fileReader->ReadBytes(buffer, readSize);
    for (auto i : buffer) {
        m_buffer->GetVector().push_back(i);
    }
    return readSize;
}

std::shared_ptr<Int8Array>& StreamFile::GetTempBuffer() { return m_buffer; }

int32_t StreamFile::GetTempBufferSize() { return m_buffer->GetCount(); }

bool StreamFile::GetIsInPackage() const { return m_fileReader->GetIsInPackage(); }

bool StreamFile::Reload() {
    if (m_fileReader->GetIsInPackage()) return false;
    auto path = m_fileReader->GetFullPath();

    m_fileReader->Release();
    m_buffer->Clear();

    m_fileReader = std::make_shared<BaseFileReader>(path);

    return true;
}

}  // namespace Altseed