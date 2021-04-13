#include <filesystem>
namespace fs = std::filesystem;

#include "FileSystem.h"

namespace Altseed2 {
bool FileSystem::GetIsFile(const std::u16string& path) { return fs::is_regular_file(path); }

bool FileSystem::GetIsDirectory(const std::u16string& path) { return fs::is_directory(path); }

int32_t FileSystem::GetLastWriteTime(const std::u16string& path) {
    std::error_code ec;
    return fs::last_write_time(path, ec).time_since_epoch().count();
}

void FileSystem::GetChildPaths(const std::u16string& path, std::vector<std::u16string>& childPaths) {
    childPaths.clear();
    for (const fs::directory_entry& i : fs::directory_iterator(path)) {
        childPaths.push_back(i.path().generic_u16string());
    }
}

int32_t FileSystem::GetFileSize(const std::u16string& path) { return fs::file_size(path); }

bool FileSystem::CreateDirectory(const std::u16string& path) { return fs::create_directory(path); }

std::u16string FileSystem::GetParentPath(const std::u16string& path) { return fs::path(path).parent_path().u16string(); }

std::u16string FileSystem::GetAbusolutePath(const std::u16string& path) { return fs::absolute(path).u16string(); }

bool FileSystem::GetIsAbsolutePath(const std::u16string& path) {
    return fs::path(path).is_absolute();
}

std::u16string FileSystem::NormalizePath(const std::u16string& path) {
    return path;
}

std::u16string FileSystem::GetFileName(const std::u16string& path, bool withExtension) {
    const fs::path pathObj(path);
    if (withExtension) {
        return pathObj.filename().u16string();
    } else {
        if (pathObj.has_stem()) {
            return pathObj.stem().u16string()
        } else {
            return u"";
        }
    }
}

}  // namespace Altseed2