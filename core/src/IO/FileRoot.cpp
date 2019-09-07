#include "FileRoot.h"
namespace altseed {
FileRoot::FileRoot(const std::u16string& path) : m_packFile(nullptr), m_path(path) {
    if (m_path.back() != u'\\' && m_path.back() != u'/') m_path += u'/';
}
FileRoot::FileRoot(const std::u16string& path, PackFile* packFile) : m_packFile(packFile), m_path(path) {}
FileRoot::~FileRoot() {
    if (IsPack()) m_packFile->Release();
}
std::u16string& FileRoot::GetPath() { return m_path; }
PackFile* FileRoot::GetPackFile() { return m_packFile; }
bool FileRoot::IsPack() { return m_packFile != nullptr; }
}  // namespace altseed
