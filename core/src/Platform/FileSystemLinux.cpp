#pragma once

#if __GNUC__ >= 8
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include "FileSystem.h"

namespace Altseed {
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

}  // namespace Altseed