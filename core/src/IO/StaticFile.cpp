#include "StaticFile.h"
#include <vector>
#include "File.h"

namespace altseed {
StaticFile::StaticFile(BaseFileReader* reader) : m_fileReader(reader) { file_ = File::GetInstance(); }
StaticFile::~StaticFile() { m_fileReader->Release(); }

Int8Array& StaticFile::GetBuffer() const {
    std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    Int8Array res;
    for (auto i : buffer) {
        res.push_back((int8_t)i);
	}
    return res;
}

const char16_t* StaticFile::GetPath() const { return m_fileReader->GetFullPath().c_str(); }

void* StaticFile::GetData() const { 
	std::vector<uint8_t> buffer;
    m_fileReader->ReadAllBytes(buffer);
    return buffer.data();
}

int32_t StaticFile::GetSize() { return m_fileReader->GetSize(); }

bool StaticFile::GetIsInPackage() const { return m_fileReader->GetIsInPackage(); }

}  // namespace altseed