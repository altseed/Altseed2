#include "StreamFile.h"

#include "../Logger/Log.h"
#include "File.h"

namespace Altseed2 {
std::mutex StreamFile::m_streamFileMtx;

StreamFile::StreamFile(std::shared_ptr<BaseFileReader> reader, std::shared_ptr<Resources>& resources, std::u16string path)
    : m_fileReader(reader), sourcePath_(path), resources_(resources) {
    m_buffer = MakeAsdShared<Int8Array>();
}

StreamFile::~StreamFile() {
    std::lock_guard<std::mutex> lock(m_streamFileMtx);
    if (sourcePath_ != u"") {
        resources_->GetResourceContainer(ResourceType::StreamFile)->Unregister(sourcePath_);
        resources_ = nullptr;
    }
}

std::shared_ptr<StreamFile> StreamFile::Create(const char16_t* path) {
    RETURN_IF_NULL(path, nullptr);

    auto resources = Resources::GetInstance();
    if (resources == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"File is not initialized.");
        return nullptr;
    }

    std::lock_guard<std::mutex> lock(m_streamFileMtx);

    auto path_ = FileSystem::NormalizePath(path);

    auto cache = std::dynamic_pointer_cast<StreamFile>(resources->GetResourceContainer(ResourceType::StreamFile)->Get(path_));
    if (cache != nullptr && cache->GetRef() > 0) {
        return cache;
    }

    auto reader = File::GetInstance()->CreateFileReader(path_.c_str());

    if (reader == nullptr) return nullptr;

    auto res = MakeAsdShared<StreamFile>(reader, resources, path_);

    resources->GetResourceContainer(ResourceType::StreamFile)
            ->Register(path_, std::make_shared<ResourceContainer::ResourceInfomation>(res, path_));
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

    if (GetCurrentPosition() == GetSize())
        m_fileReader->Close();

    return readSize;
}

std::shared_ptr<Int8Array>& StreamFile::GetInt8ArrayTempBuffer() { return m_buffer; }

int32_t StreamFile::GetTempBufferSize() { return m_buffer->GetCount(); }

bool StreamFile::GetIsInPackage() const { return m_fileReader->GetIsInPackage(); }

bool StreamFile::Reload() {
    if (m_fileReader->GetIsInPackage()) return false;
    auto path = m_fileReader->GetFullPath();

    m_buffer->Clear();

    auto file = File::GetInstance()->GetStream(path);
    if (file == nullptr)
        return false;
    m_fileReader = MakeAsdShared<BaseFileReader>(file, path);

    return true;
}

const char16_t* StreamFile::GetPath() const { return sourcePath_.c_str(); }

}  // namespace Altseed2