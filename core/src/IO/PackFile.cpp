#include "PackFile.h"

namespace altseed {

PackFile::PackFile(const std::u16string& path) { m_path = path; }

PackFile::PackFile(const std::u16string& path, const std::u16string& password) {}

PackFile::~PackFile() {}

zip_file* PackFile::Load(const std::u16string& path) { 
	return nullptr; 
}

bool PackFile::Exists(const std::u16string& path) { 
	return false; 
}

}  // namespace altseed