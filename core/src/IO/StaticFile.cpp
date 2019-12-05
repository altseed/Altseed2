#include "StaticFile.h"
#include <vector>
#include "File.h"

namespace altseed {
StaticFile::StaticFile(BaseFileReader* reader) : m_fileReader(reader) {
    file_ = File::GetInstance();
    std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    m_buffer = std::make_shared<Int8Array>();
    for (auto i : buffer) {
        m_buffer->push_back(i);
    }
}
StaticFile::~StaticFile() { m_fileReader->Release(); }

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

    m_fileReader = new BaseFileReader(path);
    std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    for (auto i : buffer) {
        m_buffer->push_back(i);
    }
    return true;
}

}  // namespace altseed