#include <dirent.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../Common/StringHelper.h"
#include "FileSystem.h"

namespace Altseed2 {
bool FileSystem::GetIsFile(const std::u16string& path) {
    struct stat st;

    if (stat(utf16_to_utf8(path).c_str(), &st) != 0) {
        return false;
    }
    return (st.st_mode & S_IFMT) == S_IFREG;
}

bool FileSystem::GetIsDirectory(const std::u16string& path) {
    struct stat st;

    if (stat(utf16_to_utf8(path).c_str(), &st) != 0) {
        return false;
    }
    return (st.st_mode & S_IFMT) == S_IFDIR;
}

int32_t FileSystem::GetLastWriteTime(const std::u16string& path) {
    struct stat st;

    if (stat(utf16_to_utf8(path).c_str(), &st) != 0) {
        return 0;
    }

    return st.st_mtime;
}

void FileSystem::GetChildPaths(const std::u16string& path, std::vector<std::u16string>& childPaths) {
    childPaths.clear();

    struct dirent** namelist;
    auto num = scandir(utf16_to_utf8(path).c_str(), &namelist, NULL, NULL);

    for (int32_t i = 0; i < num; i++) {
        auto child = utf8_to_utf16(namelist[i]->d_name);
        if (child == u"." || child == u"..") continue;
        auto tmpPath = path;
        if (tmpPath.back() != u'/') tmpPath += u'/';
        childPaths.push_back(tmpPath + child);
    }
    free(namelist);
}

int32_t FileSystem::GetFileSize(const std::u16string& path) {
    struct stat st;

    if (stat(utf16_to_utf8(path).c_str(), &st) != 0) {
        return 0;
    }

    return st.st_size;
}

bool FileSystem::CreateDirectory(const std::u16string& path) {
    if (mkdir(utf16_to_utf8(path).c_str(), 0755) != 0) {
        return false;
    }

    return true;
}

std::u16string FileSystem::GetParentPath(const std::u16string& path) {
    char* tmp = new char[utf16_to_utf8(path).size() + 1];
    strcpy(tmp, utf16_to_utf8(path).c_str());
    std::u16string res(utf8_to_utf16(dirname(tmp)));
    delete[] tmp;
    return res;
}

std::u16string FileSystem::GetAbusolutePath(const std::u16string& path) {
    auto path8 = utf16_to_utf8(path);
    char resolved_path[1024];
    realpath(path8.c_str(), resolved_path);
    return utf8_to_utf16(resolved_path);
}

bool FileSystem::GetIsAbsolutePath(const std::u16string& path) {
    // TODO : make better
    return GetAbusolutePath(path) == path;
}

std::u16string FileSystem::NormalizePath(const std::u16string& path) {
    std::u16string res = path;
    std::replace(res.begin(), res.end(), u'\\', u'/');
    return res;
}

std::u16string FileSystem::GetFileName(const std::u16string& path, bool withExtension) {
    char* tmp = new char[utf16_to_utf8(path).size() + 1];
    strcpy(tmp, utf16_to_utf8(path).c_str());
    const std::u16string filename(utf8_to_utf16(basename(tmp)));

    if (withExtension) {
        delete[] tmp;
        return filename;
    } else {
        const size_t lastindex = filename.find_last_of(u".");
        const std::u16string rawname = filename.substr(0, lastindex);
        delete[] tmp;
        return rawname;
    }
}

}  // namespace Altseed2
