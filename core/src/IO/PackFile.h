#pragma once

#include <zip.h>

#include <string>

#include "../BaseObject.h"

namespace Altseed2 {
class PackFile : public BaseObject {
private:
    zip_t* m_zip;
    bool m_isUsePassword;

public:
    PackFile(zip_t* zipPtr, bool isUsePassword = false);
    virtual ~PackFile();

    zip_file_t* Load(const std::u16string& path);
    bool Exists(const std::u16string& path);
    zip_stat_t* GetZipStat(const std::u16string& path);
    bool GetIsUsePassword();
};
}  // namespace Altseed2