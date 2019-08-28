#include "StaticFile.h"

namespace altseed {
StaticFile::StaticFile() {}
StaticFile::~StaticFile() {}

Int8Array& StaticFile::GetBuffer() const { return Int8Array(); }

char16_t* StaticFile::GetPath() const { return nullptr; }

void* StaticFile::GetData() const { return nullptr; }

int32_t StaticFile::GetSize() { return int32_t(); }

bool StaticFile::GetIsInPackage() const { return false; }

}  // namespace altseed