#include "FileRoot.h"
namespace Altseed2 {
FileRoot::FileRoot(const std::u16string& path) : m_packFile(nullptr), m_path(path) {
    if (m_path.back() != u'\\' && m_path.back() != u'/') m_path += u'/';
}
FileRoot::FileRoot(const std::u16string& path, std::shared_ptr<PackFile> packFile) : m_packFile(packFile), m_path(path) {}
FileRoot::~FileRoot() {}
std::u16string& FileRoot::GetPath() { return m_path; }
std::shared_ptr<PackFile> FileRoot::GetPackFile() { return m_packFile; }
bool FileRoot::IsPack() { return m_packFile != nullptr; }
}  // namespace Altseed2
