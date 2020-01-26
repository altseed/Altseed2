#pragma once

#include <memory>
#include "../BaseObject.h"
#include "../Common/Int8Array.h"
#include "../Common/Resource.h"
#include "BaseFileReader.h"

namespace Altseed {

class File;

class StaticFile : public Resource {
private:
    std::shared_ptr<File> file_;
    BaseFileReader* m_fileReader;
    std::shared_ptr<Int8Array> m_buffer;

public:
    StaticFile(BaseFileReader* reader);
    virtual ~StaticFile();

    const std::shared_ptr<Int8Array>& GetBuffer() const;

    const char16_t* GetPath() const;

    const void* GetData() const;

    int32_t GetSize();

    bool GetIsInPackage() const;

    bool Reload() override;
};

}  // namespace Altseed