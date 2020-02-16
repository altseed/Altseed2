#include "StaticFile.h"

#include <memory>
#include <vector>

#include "File.h"

namespace Altseed {
std::mutex StaticFile::m_staticFileMtx;

StaticFile::StaticFile(std::shared_ptr<BaseFileReader> reader) : m_fileReader(reader) {
    file_ = File::GetInstance();
    std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    m_buffer = std::make_shared<Int8Array>();
    for (auto i : buffer) {
        m_buffer->push_back(i);
    }
}

StaticFile::~StaticFile() {}

std::shared_ptr<StaticFile> StaticFile::Create(const char16_t* path) {
    std::lock_guard<std::mutex> lock(m_staticFileMtx);

    auto resources = Resources::GetInstance();
    auto cache = std::dynamic_pointer_cast<StaticFile>(resources->GetResourceContainer(ResourceType::StaticFile)->Get(path));
    if (cache != nullptr) {
        cache->AddRef();
        return cache;
    }

    auto reader = File::GetInstance()->CreateFileReader(path);

    if (reader == nullptr) return nullptr;

    auto res = std::make_shared<StaticFile>(reader);

    resources->GetResourceContainer(ResourceType::StaticFile)
            ->Register(path, std::make_shared<ResourceContainer::ResourceInfomation>(res, path));
    return res;
}

const std::shared_ptr<Int8Array>& StaticFile::GetBuffer() const { return m_buffer; }

const char16_t* StaticFile::GetPath() const { return m_fileReader->GetFullPath().c_str(); }

const void* StaticFile::GetData() const { return m_buffer->data(); }

int32_t StaticFile::GetSize() { return m_fileReader->GetSize(); }

bool StaticFile::GetIsInPackage() const { return m_fileReader->GetIsInPackage(); }

bool StaticFile::Reload() {
    if (m_fileReader->GetIsInPackage()) return false;
    auto path = m_fileReader->GetFullPath();

    m_fileReader->Release();
    m_buffer->clear();

    m_fileReader = std::make_shared<BaseFileReader>(path);
    std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    for (auto i : buffer) {
        m_buffer->push_back(i);
    }
    return true;
}

}  // namespace Altseed