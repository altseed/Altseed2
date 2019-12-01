#include "FileSystem.h"
#include "FileSystemWin.h"
#include "FileSystemLinux.h"
#include "FileSystemMac.h"

namespace altseed {
std::shared_ptr<FileSystem> FileSystem::instance_ = nullptr;

bool FileSystem::Initialize() {
#if defined(_WIN32)
    instance_ = std::make_shared<FileSystemWin>();
#elif defined(__APPLE__)
    instance_ = std::make_shared<FileSystemMac>();
#else
    instance_ = std::make_shared<FileSystemLinux>();
#endif
    return true;
}

void FileSystem::Terminate() { instance_ == nullptr; }
}  // namespace altseed