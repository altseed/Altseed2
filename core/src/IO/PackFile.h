#pragma once

#include <zip.h>
#include <string>
#include "../BaseObject.h"

namespace altseed {
class PackFile : public BaseObject {
private:
    zip* m_zip;
    std::wstring m_password;
    bool m_isUsePassword;
    std::wstring m_path;

public:
    PackFile(const std::wstring& path);
    PackFile(const std::wstring& path, const std::wstring& password);
    virtual ~PackFile();

	zip_file* Load(const std::wstring& path);
    bool Exists(const std::wstring& path);
};
}  // namespace altseed