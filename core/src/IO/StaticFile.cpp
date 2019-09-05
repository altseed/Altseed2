#include "StaticFile.h"
#include <vector>
#include "File.h"

namespace altseed {
StaticFile::StaticFile(BaseFileReader* reader) : m_fileReader(reader) { file_ = File::GetInstance(); 
std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    for (auto i : buffer) {
        m_buffer.push_back(i);
    }
}
StaticFile::~StaticFile() { m_fileReader->Release(); }

const Int8Array& StaticFile::GetBuffer() const { return m_buffer; }

const char16_t* StaticFile::GetPath() const { return m_fileReader->GetFullPath().c_str(); }

void* StaticFile::GetData() const { 
	std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    return buffer.data();
}

int32_t StaticFile::GetSize() { return m_fileReader->GetSize(); }

bool StaticFile::GetIsInPackage() const { return m_fileReader->GetIsInPackage(); }

}  // namespace altseed