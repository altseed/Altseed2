#include "StaticFile.h"

#include <memory>
#include <vector>

#include "../Logger/Log.h"
#include "File.h"

namespace Altseed2 {
std::mutex StaticFile::m_staticFileMtx;

StaticFile::StaticFile(std::shared_ptr<BaseFileReader> reader, std::shared_ptr<Resources>& resources, std::u16string path)
    : sourcePath_(path), resources_(resources) {
    std::vector<uint8_t> buffer;
    reader->ReadAllBytes(buffer);

    path_ = reader->GetFullPath().c_str();
    size_ = reader->GetSize();
    isInPackage_ = reader->GetIsInPackage();

    m_buffer = MakeAsdShared<Int8Array>();
    for (auto i : buffer) {
        m_buffer->GetVector().push_back(i);
    }

    reader->Close();
}

StaticFile::~StaticFile() {
    std::lock_guard<std::mutex> lock(m_staticFileMtx);
    if (sourcePath_ != u"") {
        resources_->GetResourceContainer(ResourceType::StaticFile)->Unregister(sourcePath_);
        resources_ = nullptr;
    }
}

std::shared_ptr<StaticFile> StaticFile::Create(const char16_t* path) {
    RETURN_IF_NULL(path, nullptr);

    std::lock_guard<std::mutex> lock(m_staticFileMtx);

    auto path_ = FileSystem::NormalizePath(path);

    auto resources = Resources::GetInstance();
    auto cache = std::dynamic_pointer_cast<StaticFile>(resources->GetResourceContainer(ResourceType::StaticFile)->Get(path_));
    if (cache != nullptr && cache->GetRef() > 0) {
        return cache;
    }

    auto reader = File::GetInstance()->CreateFileReader(path_.c_str());

    if (reader == nullptr) return nullptr;

    auto res = MakeAsdShared<StaticFile>(reader, resources, path_);

    resources->GetResourceContainer(ResourceType::StaticFile)
            ->Register(path_, std::make_shared<ResourceContainer::ResourceInfomation>(res, path_));
    return res;
}

const std::shared_ptr<Int8Array>& StaticFile::GetBuffer() const { return m_buffer; }

const char16_t* StaticFile::GetPath() const { return sourcePath_.c_str(); }

const void* StaticFile::GetData() const { return m_buffer->GetData(); }

int32_t StaticFile::GetSize() { return size_; }

bool StaticFile::GetIsInPackage() const { return isInPackage_; }

bool StaticFile::Reload() {
    if (isInPackage_) return false;
    auto path = path_;

    m_buffer->Clear();

    auto file = File::GetInstance()->GetStream(path);
    if (file == nullptr)
        return false;
    auto reader = MakeAsdShared<BaseFileReader>(file, path);

    path_ = reader->GetFullPath().c_str();
    size_ = reader->GetSize();
    isInPackage_ = reader->GetIsInPackage();

    std::vector<uint8_t> buffer;
    reader->ReadAllBytes(buffer);
    for (auto i : buffer) {
        m_buffer->GetVector().push_back(i);
    }
    return true;
}

}  // namespace Altseed2