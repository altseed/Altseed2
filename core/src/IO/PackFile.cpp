#include "PackFile.h"

namespace altseed {

PackFile::PackFile(const std::wstring& path) { m_path = path; }

PackFile::PackFile(const std::wstring& path, const std::wstring& password) {}

PackFile::~PackFile() {}

zip_file* PackFile::Load(const std::wstring& path) { 
	return nullptr; 
}

bool PackFile::Exists(const std::wstring& path) { 
	return false; 
}

}  // namespace altseed