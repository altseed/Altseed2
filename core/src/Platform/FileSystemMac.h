#pragma once

#include "FileSystem.h"

namespace altseed {

class FileSystemMac : public FileSystem {
    bool GetIsFile(const std::u16string& path) override;
    bool GetIsDirectory(const std::u16string& path) override;
    int32_t GetLastWriteTime(const std::u16string& path) override;
};
}  // namespace altseed