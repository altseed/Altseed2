#pragma once

#include <memory>
#include "../Common/Int8Array.h"
#include "../BaseObject.h"

namespace altseed {

class File;

class StaticFile : public BaseObject {
private:
    std::shared_ptr<File> file_;

public:
    StaticFile();
    virtual ~StaticFile();

    Int8Array& GetBuffer() const;

    char16_t* GetPath() const;

    void* GetData() const;

    int32_t GetSize();

    bool GetIsInPackage() const;
};

}  // namespace altseed