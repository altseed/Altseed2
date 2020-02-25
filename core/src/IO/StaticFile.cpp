#include "StaticFile.h"

#include <memory>
#include <vector>

#include "File.h"

namespace Altseed {
std::mutex StaticFile::m_staticFileMtx;

StaticFile::StaticFile(std::shared_ptr<BaseFileReader> reader) : m_fileReader(reader) {
    std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    m_buffer = MakeAsdShared<Int8Array>();
    for (auto i : buffer) {
        m_buffer->GetVector().push_back(i);
    }
}

StaticFile::~StaticFile() {}

std::shared_ptr<StaticFile> StaticFile::Create(const char16_t* path) {
    std::lock_guard<std::mutex> lock(m_staticFileMtx);

    auto resources = Resources::GetInstance();
    auto cache = std::dynamic_pointer_cast<StaticFile>(resources->GetResourceContainer(ResourceType::StaticFile)->Get(path));
    if (cache != nullptr) {
        return cache;
    }

    auto reader = File::GetInstance()->CreateFileReader(path);

    if (reader == nullptr) return nullptr;

    auto res = MakeAsdShared<StaticFile>(reader);

    resources->GetResourceContainer(ResourceType::StaticFile)
            ->Register(path, std::make_shared<ResourceContainer::ResourceInfomation>(res, path));
    return res;
}

const std::shared_ptr<Int8Array>& StaticFile::GetBuffer() const { return m_buffer; }

const char16_t* StaticFile::GetPath() const { return m_fileReader->GetFullPath().c_str(); }

const void* StaticFile::GetData() const { return m_buffer->GetData(); }

int32_t StaticFile::GetSize() { return m_fileReader->GetSize(); }

bool StaticFile::GetIsInPackage() const { return m_fileReader->GetIsInPackage(); }

bool StaticFile::Reload() {
    if (m_fileReader->GetIsInPackage()) return false;
    auto path = m_fileReader->GetFullPath();

    m_buffer->Clear();

    m_fileReader = MakeAsdShared<BaseFileReader>(path);
    std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    for (auto i : buffer) {
        m_buffer->GetVector().push_back(i);
    }
    return true;
}

}  // namespace Altseed