#pragma once

#include <memory>
#include <string>
#include <vector>

#ifdef _WIN32
#undef CreateDirectory
#endif

#if !USE_CBG

namespace Altseed2 {
class FileSystem {
public:
    static bool GetIsFile(const std::u16string& path);
    static bool GetIsDirectory(const std::u16string& path);
    static int32_t GetLastWriteTime(const std::u16string& path);
    static void GetChildPaths(const std::u16string& path, std::vector<std::u16string>& childPaths);
    static int32_t GetFileSize(const std::u16string& path);
    static bool CreateDirectory(const std::u16string& path);
    static std::u16string GetParentPath(const std::u16string& path);
    static std::u16string GetAbusolutePath(const std::u16string& path);
    static bool GetIsAbsolutePath(const std::u16string& path);
    static std::u16string NormalizePath(const std::u16string& path);
};
}  // namespace Altseed2

#endif