#pragma once

#if __GNUC__ >= 8
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include "FileSystemLinux.h"
#include "FileSystem.h"

namespace altseed {
bool FileSystemLinux::GetIsFile(const std::u16string& path) { return fs::is_regular_file(path); }

bool FileSystemLinux::GetIsDirectory(const std::u16string& path) { return fs::is_directory(path); }

int32_t FileSystemLinux::GetLastWriteTime(const std::u16string& path) { return fs::last_write_time(path).time_since_epoch().count(); }
}  // namespace altseed