#pragma once

#include <memory>
#include <string>
#include "PackFile.h"

namespace altseed {
class FileRoot {
private:
    PackFile* m_packFile;
    std::wstring m_path;

public:
    FileRoot(const std::wstring& path);
};
}  // namespace altseed