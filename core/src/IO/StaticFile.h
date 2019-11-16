#pragma once

#include <memory>
#include "../BaseObject.h"
#include "../Common/Int8Array.h"
#include "../Common/Resource.h"
#include "BaseFileReader.h"

namespace altseed {

class File;

class StaticFile : public Resource {
private:
    std::shared_ptr<File> file_;
    BaseFileReader* m_fileReader;
    Int8Array m_buffer;

public:
    StaticFile(BaseFileReader* reader);
    virtual ~StaticFile();

    const Int8Array& GetBuffer() const;

    const char16_t* GetPath() const;

    const void* GetData() const;

    int32_t GetSize();

    bool GetIsInPackage() const;

    bool Reload() override;
};

}  // namespace altseed