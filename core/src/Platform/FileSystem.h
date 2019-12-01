#pragma once

#include <string>
#include <memory>

namespace altseed {
class FileSystem {
private:
    static std::shared_ptr<FileSystem> instance_;

public:
    virtual bool GetIsFile(const std::u16string& path) = 0;
    virtual bool GetIsDirectory(const std::u16string& path) = 0;
    virtual bool GetLastWriteTime(const std::u16string& path) = 0;

	static bool Initialize();
    static void Terminate();
	static std::shared_ptr<FileSystem> GetInstance() { return instance_; }
};
}  // namespace altseed