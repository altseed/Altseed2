#pragma once

#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include "../Common/Resource.h"

#if defined(_WIN32) || defined(__APPLE__)
#include <filesystem>
namespace fs = std::filesystem;
#else

#if __GNUC__ >= 8
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#endif

namespace altseed {
class ResourceContainer {
public:
    class ResourceInfomation {
    private:
        Resource* m_resourcePtr;
        std::u16string m_path;
        fs::file_time_type m_modifiedTime;

    public:
        ResourceInfomation(Resource* resource, std::u16string path) {
            m_resourcePtr = resource;
            m_path = path;
            m_modifiedTime = ResourceContainer::GetModifiedTime(path);
        }

        Resource* GetResourcePtr() { return m_resourcePtr; }

        const std::u16string& GetPath() { return m_path; }

        const fs::file_time_type GetModifiedTime() { return m_modifiedTime; }

        bool Reload(fs::file_time_type time) {
            m_modifiedTime = time;
            return m_resourcePtr->Reload();
        }
    };

private:
    std::map<std::u16string, std::shared_ptr<ResourceInfomation>> resources;
    std::mutex resourceMtx_;

public:
    ResourceContainer() {}

    const std::map<std::u16string, std::shared_ptr<ResourceInfomation>>& GetAllResouces() { return resources; }

    Resource* Get(const std::u16string key) {
        if (resources.count(key) > 0) return resources[key]->GetResourcePtr();
        return nullptr;
    }

    void Register(const std::u16string path, std::shared_ptr<ResourceInfomation> resource) {
        {
            std::lock_guard<std::mutex> lock(resourceMtx_);
            resources[path] = resource;
        }
        resource->GetResourcePtr()->AddRef();
    }

    void Unregister(const std::u16string path) {
        if (resources.count(path) == 0) return;
        resources[path]->GetResourcePtr()->Release();
        std::lock_guard<std::mutex> lock(resourceMtx_);
        resources.erase(path);
    }

    void Clear() {
        for (auto resource : resources) {
            resource.second->GetResourcePtr()->Release();
        }
        std::lock_guard<std::mutex> lock(resourceMtx_);
        resources.clear();
    }

    void Reload() {
        for (auto resource : resources) {
            auto path = resource.second->GetPath();
            auto time = GetModifiedTime(path);

            if (resource.second->GetModifiedTime() < time) continue;

            if (!resources[resource.first]->Reload(time)) {
                // TODO: log failure to reload
            }
        }
    }

    static fs::file_time_type GetModifiedTime(const std::u16string path) {
        fs::path p(path);
        std::error_code ec;
        auto ftime = fs::last_write_time(p, ec);
        if (ec.value() != 0) {
            // TODO: log failure to get time
            return fs::file_time_type::min();
        }
        return ftime;
    }
};

}  // namespace altseed