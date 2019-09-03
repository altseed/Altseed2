#include "PackFile.h"
#include "../Common/StringHelper.h"

namespace altseed {

PackFile::PackFile(zip_t* zipPtr) : m_zip(zipPtr) {}

PackFile::~PackFile() { zip_close(m_zip); }

zip_file_t* PackFile::Load(const std::u16string& path) { return zip_fopen(m_zip, utf16_to_utf8(path).c_str(), ZIP_FL_COMPRESSED); }

bool PackFile::Exists(const std::u16string& path) { return zip_name_locate(m_zip, utf16_to_utf8(path).c_str(), ZIP_FL_ENC_GUESS) != -1; }

}  // namespace altseed