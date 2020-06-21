#pragma once

#include <memory>

#include "../BaseObject.h"
#include "../Common/Array.h"
#include "../Common/Resources.h"
#include "BaseFileReader.h"

namespace Altseed2 {

class File;

class StaticFile : public Resource {
private:
    std::shared_ptr<Resources> resources_;

    std::shared_ptr<Int8Array> m_buffer;

    std::u16string path_;
    std::u16string sourcePath_;
    int32_t size_;
    bool isInPackage_;

    static std::mutex m_staticFileMtx;

public:
    StaticFile(std::shared_ptr<BaseFileReader> reader, std::shared_ptr<Resources>& resources, std::u16string path);
    virtual ~StaticFile();

    static std::shared_ptr<StaticFile> Create(const char16_t* path);

    const std::shared_ptr<Int8Array>& GetBuffer() const;

    const char16_t* GetPath() const;

    const void* GetData() const;

    int32_t GetSize();

    bool GetIsInPackage() const;

    bool Reload() override;
};

}  // namespace Altseed2