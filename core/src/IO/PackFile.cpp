#include "PackFile.h"
#include "../Common/StringHelper.h"

namespace altseed {

PackFile::PackFile(zip_t* zipPtr, bool isUsePassword) : m_zip(zipPtr), m_isUsePassword(isUsePassword) {}

PackFile::~PackFile() { zip_close(m_zip); }

zip_file_t* PackFile::Load(const std::u16string& path) { return zip_fopen(m_zip, utf16_to_utf8(path).c_str(), ZIP_FL_UNCHANGED); }

bool PackFile::Exists(const std::u16string& path) { return zip_name_locate(m_zip, utf16_to_utf8(path).c_str(), ZIP_FL_ENC_GUESS) != -1; }

zip_stat_t* PackFile::GetZipStat(const std::u16string& path) {
    zip_stat_t* res = new zip_stat_t();
    if (zip_stat(m_zip, utf16_to_utf8(path).c_str(), ZIP_FL_UNCHANGED, res) == -1) {
        delete res;
        return nullptr;
	}
    return res;
}

bool PackFile::GetIsUsePassword() { return m_isUsePassword; }

}  // namespace altseed