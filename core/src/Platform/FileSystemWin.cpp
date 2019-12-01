#pragma once

#include <filesystem>
namespace fs = std::filesystem;

#include "FileSystem.h"
#include "FileSystemWin.h"

namespace altseed {
bool FileSystemWin::GetIsFile(const std::u16string& path) { return fs::is_regular_file(path); }

bool FileSystemWin::GetIsDirectory(const std::u16string& path) { return fs::is_directory(path); }

int32_t FileSystemWin::GetLastWriteTime(const std::u16string& path) { return fs::last_write_time(path).time_since_epoch().count(); }
}  // namespace altseed