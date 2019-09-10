#pragma once

#include <memory>
#include <vector>
#include <mutex>
#include "../Common/ResourceContainer.h"
#include "FileRoot.h"
#include "StaticFile.h"
#include "StreamFile.h"

namespace altseed {

class File {
private:
    static std::shared_ptr<File> instance;

    std::vector<std::shared_ptr<FileRoot>> m_roots;

    ResourceContainer m_staticFileCache;
    ResourceContainer m_streamFileCache;

	std::mutex m_rootMtx;
    std::mutex m_staticFileMtx;
    std::mutex m_streamFileMtx;

public:
    static bool Initialize();

    static void Terminate();

    static std::shared_ptr<File>& GetInstance();

    StaticFile* CreateStaticFile(const char16_t* path);

    StreamFile* CreateStreamFile(const char16_t* path);

    bool AddRootDirectory(const char16_t* path);

    bool AddRootPackageWithPassword(const char16_t* path, const char16_t* password);

    bool AddRootPackage(const char16_t* path);

    void ClearRootDirectories();

    bool Exists(const char16_t* path) const;

    bool Pack(const char16_t* srcPath, const char16_t* dstPath) const;

    bool Pack(const char16_t* srcPath, const char16_t* dstPath, const char16_t* password) const;

    void ClearCache();

    void Reload();

private:
    bool Pack_Imp(zip_t* zipPtr, const std::u16string& path, bool isEncrypt = false) const;
};

}  // namespace altseed