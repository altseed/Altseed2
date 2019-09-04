#pragma once

#include <memory>
#include "../Common/Int8Array.h"
#include "../BaseObject.h"
#include "BaseFileReader.h"

namespace altseed {

class File;

class StaticFile : public BaseObject {
private:
    std::shared_ptr<File> file_;
    BaseFileReader* m_fileReader;

public:
    StaticFile(BaseFileReader* reader);
    virtual ~StaticFile();

    Int8Array& GetBuffer() const;

    const char16_t* GetPath() const;

    void* GetData() const;

    int32_t GetSize();

    bool GetIsInPackage() const;
};

}  // namespace altseed