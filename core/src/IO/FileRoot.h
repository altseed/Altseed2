#pragma once

#include <memory>
#include <string>
#include "PackFile.h"

namespace Altseed {
class FileRoot {
private:
    PackFile* m_packFile;
    std::u16string m_path;

public:
    FileRoot(const std::u16string& path);
    FileRoot(const std::u16string& path, PackFile* packFile);
    ~FileRoot();

    std::u16string& GetPath();
    PackFile* GetPackFile();
    bool IsPack();
};
}  // namespace Altseed