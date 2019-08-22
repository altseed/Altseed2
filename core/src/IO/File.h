#pragma once

#include <memory>
#include <vector>
#include "FileRoot.h"
#include "StaticFile.h"
#include "StreamFile.h"

namespace altseed {

class File {
private:
    static std::shared_ptr<File> instance;

	std::vector<std::shared_ptr<FileRoot>> m_roots;

public:
    static bool Initialize();

    static void Terminate();

    static std::shared_ptr<File>& GetInstance();

    StaticFile* CreateStaticFile(const char16_t* path);

    StreamFile* CreateStreamFile(const char16_t* path);

    void AddRootDirectory(const char16_t* path);

    void AddRootPackageWithPassword(const char16_t* path, const char16_t* password);

    void AddRootPackage(const char16_t* path);

    void ClearRootDirectories();

    bool Exists(const char16_t* path) const;
};

}  // namespace altseed