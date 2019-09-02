#pragma once

#include <zip.h>
#include <string>
#include "../BaseObject.h"

namespace altseed {
class PackFile : public BaseObject {
private:
    zip_t* m_zip;

public:
    PackFile(zip_t* zipPtr);
    virtual ~PackFile();

	zip_file* Load(const std::u16string& path);
    bool Exists(const std::u16string& path);
};
}  // namespace altseed