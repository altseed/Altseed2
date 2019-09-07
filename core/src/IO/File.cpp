#include "File.h"
#include <zip.h>
#include <filesystem>
#include <fstream>
#include <stack>
#include "../Common/StringHelper.h"
#include "PackFileReader.h"
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

StaticFile* File::CreateStaticFile(const char16_t* path) {
    StaticFile* cache = (StaticFile*)m_staticFileCache.Get(path);
    if (cache != nullptr) {
        cache->AddRef();
        return cache;
    }

    BaseFileReader* reader = nullptr;
    for (auto i = m_roots.rbegin(), e = m_roots.rend(); i != e; ++i) {
        if ((*i)->IsPack()) {
            if ((*i)->GetPackFile()->Exists(path)) {
                auto zipFile = (*i)->GetPackFile()->Load(path);
                if (zipFile == nullptr) {
                    // TODO: log failure to get zip_file
                    continue;
                }
                zip_stat_t* stat = nullptr;
                if ((*i)->GetPackFile()->GetIsUsePassword()) stat = (*i)->GetPackFile()->GetZipStat(path);
                reader = new PackFileReader(zipFile, path, stat);
                break;
            }
        } else if (std::filesystem::is_regular_file((*i)->GetPath() + path)) {
            reader = new BaseFileReader(path);
        }
    }

    if (reader == nullptr) return nullptr;

    auto res = new StaticFile(reader);

    m_staticFileCache.Register(path, std::make_shared<ResourceContainer::ResourceInfomation>((Resource*)res, path));
    return res;
}

StreamFile* File::CreateStreamFile(const char16_t* path) {
    StreamFile* cache = (StreamFile*)m_streamFileCache.Get(path);
    if (cache != nullptr) {
        cache->AddRef();
        return cache;
    }

    BaseFileReader* reader = nullptr;
    for (auto i = m_roots.rbegin(), e = m_roots.rend(); i != e; ++i) {
        if ((*i)->IsPack()) {
            if ((*i)->GetPackFile()->Exists(path)) {
                auto zipFile = (*i)->GetPackFile()->Load(path);
                if (zipFile == nullptr) {
                    // TODO: log failure to get zip_file
                    continue;
                }
                zip_stat_t* stat = nullptr;
                if ((*i)->GetPackFile()->GetIsUsePassword()) stat = (*i)->GetPackFile()->GetZipStat(path);
                reader = new PackFileReader(zipFile, path, stat);
                break;
            }
        } else if (std::filesystem::is_regular_file((*i)->GetPath() + path)) {
            reader = new BaseFileReader(path);
        }
    }

    if (reader == nullptr) return nullptr;

    auto res = new StreamFile(reader);

    m_streamFileCache.Register(path, std::make_shared<ResourceContainer::ResourceInfomation>((Resource*)res, path));
    return res;
}

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

    m_roots.push_back(std::make_shared<FileRoot>(path, new PackFile(zip_, true)));
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

void File::ClearCache() {
    m_staticFileCache.Clear();
    m_streamFileCache.Clear();
}

void File::Reload() {
    m_staticFileCache.Reload();
    m_streamFileCache.Reload();
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
                if (isEncrypt && zip_file_set_encryption(zipPtr, index, ZIP_EM_AES_256, nullptr) == -1) {
                    zip_source_free(zipSource);
                    return false;
                }
            }
        }
    }

    return true;
}

}  // namespace altseed