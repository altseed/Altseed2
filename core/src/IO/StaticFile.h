#pragma once

#include <memory>
#include <vector>
#include "../BaseObject.h"

namespace altseed {

class File;

class StaticFile : public BaseObject {
private:
    std::shared_ptr<File> file_;

public:
    StaticFile();
    virtual ~StaticFile();

    std::vector<uint8_t>& GetBuffer() const;

    char16_t* GetPath() const;

    void* GetData() const;

    int32_t GetSize();

    bool GetIsInPackage() const;
};

}  // namespace altseed