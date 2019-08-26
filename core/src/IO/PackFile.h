#pragma once

#include <zip.h>
#include <string>
#include "../BaseObject.h"

namespace altseed {
class PackFile : public BaseObject {
private:
    zip* m_zip;
    std::u16string m_password;
    bool m_isUsePassword;
    std::u16string m_path;

public:
    PackFile(const std::u16string& path);
    PackFile(const std::u16string& path, const std::u16string& password);
    virtual ~PackFile();

	zip_file* Load(const std::u16string& path);
    bool Exists(const std::u16string& path);
};
}  // namespace altseed