#include "File.h"
namespace altseed {

bool File::Initialize() { return false; }

void File::Terminate() {}

std::shared_ptr<File>& File::GetInstance() { return instance; }

StaticFile* File::CreateStaticFile(const char16_t* path) { return nullptr; }

StreamFile* File::CreateStreamFile(const char16_t* path) { return nullptr; }

void File::AddRootDirectory(const char16_t* path) {}

void File::AddRootPackageWithPassword(const char16_t* path, const char16_t* password) {}

void File::AddRootPackage(const char16_t* path) {}

void File::ClearRootDirectories() {}

bool File::Exists(const char16_t* path) const { return false; }

}  // namespace altseed