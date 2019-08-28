#include "File.h"
#include <filesystem>
namespace altseed {

std::shared_ptr<File> File::instance = nullptr;

bool File::Initialize() {
    instance = std::make_shared<File>();

    // add default file root
    instance->m_roots.push_back(std::make_shared<FileRoot>(u"."));

    return true;
}

void File::Terminate() { instance = nullptr; }

std::shared_ptr<File>& File::GetInstance() { return instance; }

StaticFile* File::CreateStaticFile(const char16_t* path) { return nullptr; }

StreamFile* File::CreateStreamFile(const char16_t* path) { return nullptr; }

void File::AddRootDirectory(const char16_t* path) {
    if (std::filesystem::is_directory(path)) m_roots.push_back(std::make_shared<FileRoot>(path));
}

void File::AddRootPackageWithPassword(const char16_t* path, const char16_t* password) {
    if (!std::filesystem::is_regular_file(path)) return;
    PackFile* packFile = new PackFile(path, password);
    if (packFile == nullptr) return;
    m_roots.push_back(std::make_shared<FileRoot>(path, packFile));
}

void File::AddRootPackage(const char16_t* path) {
    if (!std::filesystem::is_regular_file(path)) return;
    PackFile* packFile = new PackFile(path);
    if (packFile == nullptr) return;
    m_roots.push_back(std::make_shared<FileRoot>(path, packFile));
}

void File::ClearRootDirectories() {
    m_roots.clear();

    // add default file root
    m_roots.push_back(std::make_shared<FileRoot>(u"."));
}

bool File::Exists(const char16_t* path) const {
    for (auto i = m_roots.rbegin(), e = m_roots.rend(); i != e; ++i) {
        if ((*i)->IsPack()) {
            if ((*i)->GetPackFile()->Exists(path)) return true;
        } else if (std::filesystem::is_regular_file((*i)->GetPath() + path))
            return true;
    }

	return false;
}

}  // namespace altseed