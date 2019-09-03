#include "File.h"
#include <zip.h>
#include <filesystem>
#include <fstream>
#include <stack>
#include "../Common/StringHelper.h"
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

bool File::AddRootDirectory(const char16_t* path) {
    if (!std::filesystem::is_directory(path)) return false;
    m_roots.push_back(std::make_shared<FileRoot>(path));
    return true;
}

bool File::AddRootPackageWithPassword(const char16_t* path, const char16_t* password) {
    if (!std::filesystem::is_regular_file(path)) return false;

    int error;
    zip_t* zip_ = zip_open(utf16_to_utf8(path).c_str(), ZIP_RDONLY, &error);
    if (zip_ == nullptr) return false;

    if (zip_set_default_password(zip_, utf16_to_utf8(password).c_str()) == -1) {
        zip_close(zip_);
        return false;
    }

    m_roots.push_back(std::make_shared<FileRoot>(path, new PackFile(zip_)));
    return true;
}

bool File::AddRootPackage(const char16_t* path) {
    if (!std::filesystem::is_regular_file(path)) return false;

    int error;
    zip_t* zip_ = zip_open(utf16_to_utf8(path).c_str(), ZIP_RDONLY, &error);
    if (zip_ == nullptr) return false;

    m_roots.push_back(std::make_shared<FileRoot>(path, new PackFile(zip_)));
    return true;
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

bool File::Pack(const char16_t* srcPath, const char16_t* dstPath) const {
    if (!std::filesystem::is_directory(srcPath)) return false;

    int error;
    zip_t* zip_ = zip_open(utf16_to_utf8(dstPath).c_str(), ZIP_TRUNCATE | ZIP_CREATE, &error);
    if (zip_ == nullptr) return false;

    auto res = Pack_Imp(zip_, srcPath);
    zip_close(zip_);
    return res;
}

bool File::Pack(const char16_t* srcPath, const char16_t* dstPath, const char16_t* password) const {
    if (!std::filesystem::is_directory(srcPath)) return false;

    int error;
    zip_t* zip_ = zip_open(utf16_to_utf8(dstPath).c_str(), ZIP_TRUNCATE | ZIP_CREATE, &error);
    if (zip_ == nullptr) return false;

    if (zip_set_default_password(zip_, utf16_to_utf8(password).c_str()) == -1) {
        zip_close(zip_);
        return false;
    }

    auto res = Pack_Imp(zip_, srcPath, true);
    zip_close(zip_);
    return res;
}

bool File::Pack_Imp(zip_t* zipPtr, const std::u16string& path, bool isEncrypt) const {
    std::stack<std::u16string> children;

    std::u16string current;
    children.push(path);

    while (!children.empty()) {
        current = children.top();
        children.pop();

        for (const std::filesystem::directory_entry& i : std::filesystem::directory_iterator(current)) {
            std::u16string zipPath = i.path().generic_u16string();
            zipPath.erase(0, path.size());

            if (std::filesystem::is_directory(i)) {
                if (zip_dir_add(zipPtr, utf16_to_utf8(zipPath).c_str(), ZIP_FL_ENC_UTF_8) == -1) return false;
                children.push(i.path().generic_u16string());
            } else if (std::filesystem::is_regular_file(i)) {
                std::ifstream file(i.path(), std::ios::binary);
                if (!file.is_open()) return false;

                int size = std::filesystem::file_size(i.path());
                char* buffer = new char[size];
                file.read(buffer, size);
                zip_source_t* zipSource;
                zip_error error;
                if ((zipSource = zip_source_buffer_create(buffer, size, 1, &error)) == nullptr) return false;

                zip_int64_t index;
                if ((index = zip_file_add(zipPtr, utf16_to_utf8(zipPath).c_str(), zipSource, ZIP_FL_ENC_UTF_8)) == -1) {
                    zip_source_free(zipSource);
                    return false;
                }
                if (isEncrypt) zip_file_set_encryption(zipPtr, index, ZIP_EM_AES_256, nullptr);
            }
        }
    }

    return true;
}

}  // namespace altseed