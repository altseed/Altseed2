#pragma once

#include <string>
#include <memory>

namespace altseed {
class FileSystem {
public:
    static bool GetIsFile(const std::u16string& path);
    static bool GetIsDirectory(const std::u16string& path);
    static int32_t GetLastWriteTime(const std::u16string& path);
};
}  // namespace altseed