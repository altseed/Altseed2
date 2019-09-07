#include "StreamFile.h"
#include "File.h"

namespace altseed {
StreamFile::StreamFile(BaseFileReader* reader) : m_fileReader(reader) { file_ = File::GetInstance(); }

StreamFile::~StreamFile() { m_fileReader->Release(); }

int32_t StreamFile::GetSize() const { return m_fileReader->GetSize(); }

int32_t StreamFile::GetCurrentPosition() const { return m_fileReader->GetPosition(); }

int32_t StreamFile::Read(int32_t size) {
    if (GetCurrentPosition() == GetSize()) return 0;

    std::vector<uint8_t> buffer;
    int readSize = size;

    if (GetCurrentPosition() + size >= GetSize()) readSize = GetSize() - GetCurrentPosition();

    m_fileReader->ReadBytes(buffer, readSize);
    for (auto i : buffer) {
        m_buffer.push_back(i);
    }
    return readSize;
}

Int8Array& StreamFile::GetTempBuffer() { return m_buffer; }

int32_t StreamFile::GetTempBufferSize() { return m_buffer.size(); }

bool StreamFile::GetIsInPackage() const { return m_fileReader->GetIsInPackage(); }

bool StreamFile::Reload() {
    if (m_fileReader->GetIsInPackage()) return false;
    auto path = m_fileReader->GetFullPath();

    m_fileReader->Release();
    m_buffer.clear();

    m_fileReader = new BaseFileReader(path);
}

}  // namespace altseed