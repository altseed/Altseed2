﻿#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "../Common/ResourceContainer.h"
#include "../Common/Resources.h"
#include "FileRoot.h"
#include "StaticFile.h"
#include "StreamFile.h"

namespace Altseed {

class File : public BaseObject {
private:
    static std::shared_ptr<File> instance;

    std::shared_ptr<Resources> m_resources;

    std::vector<std::shared_ptr<FileRoot>> m_roots;

    std::mutex m_rootMtx;

public:
    static bool Initialize(std::shared_ptr<Resources> resources);

    static void Terminate();

    static std::shared_ptr<File>& GetInstance();

    std::shared_ptr<StaticFile> CreateStaticFile(const char16_t* path);

    std::shared_ptr<StreamFile> CreateStreamFile(const char16_t* path);

	std::shared_ptr<BaseFileReader> CreateFileReader(const char16_t* path);

    bool AddRootDirectory(const char16_t* path);

    bool AddRootPackageWithPassword(const char16_t* path, const char16_t* password);

    bool AddRootPackage(const char16_t* path);

    void ClearRootDirectories();

    bool Exists(const char16_t* path) const;

    bool Pack(const char16_t* srcPath, const char16_t* dstPath) const;

    bool PackWithPassword(const char16_t* srcPath, const char16_t* dstPath, const char16_t* password) const;

private:
    bool MakePackage(zip_t* zipPtr, const std::u16string& path, bool isEncrypt = false) const;
};

}  // namespace Altseed