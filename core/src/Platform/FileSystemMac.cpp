#pragma once

#include <sys/stat.h>

#include "../Common/StringHelper.h"
#include "FileSystem.h"
#include "FileSystemMac.h"

namespace altseed {
bool FileSystemMac::GetIsFile(const std::u16string& path) {
    struct stat st;

    if (stat(utf16_to_utf8(path).c_str(), &st) != 0) {
        return false;
    }
    return (st.st_mode & S_IFMT) == S_IFREG;
}

bool FileSystemMac::GetIsDirectory(const std::u16string& path) {
    struct stat st;

    if (stat(utf16_to_utf8(path).c_str(), &st) != 0) {
        return false;
    }
    return (st.st_mode & S_IFMT) == S_IFDIR;
}

int32_t FileSystemMac::GetLastWriteTime(const std::u16string& path) {
    struct stat st;

    if (stat(utf16_to_utf8(path).c_str(), &st) != 0) {
        return 0;
    }

	return st.st_mtime;
}
}  // namespace altseed