#pragma once

#include <chrono>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include "../Common/Resource.h"

namespace altseed {
class ResourceContainer {
public:
    class ResourceInfomation {
    private:
        Resource* m_resourcePtr;
        std::u16string m_path;
        std::filesystem::file_time_type m_modifiedTime;

    public:
        ResourceInfomation(Resource* resource, std::u16string path) {
            m_resourcePtr = resource;
            m_path = path;
            m_modifiedTime = ResourceContainer::GetModifiedTime(path);
        }

        Resource* GetResourcePtr() { return m_resourcePtr; }

        const std::u16string& GetPath() { return m_path; }

        const std::filesystem::file_time_type GetModifiedTime() { return m_modifiedTime; }

        bool Reload(std::filesystem::file_time_type time) {
            m_modifiedTime = time;
            return m_resourcePtr->Reload();
        }
    };

private:
    std::map<std::u16string, std::shared_ptr<ResourceInfomation>> resources;

public:
    ResourceContainer() {}

    const std::map<std::u16string, std::shared_ptr<ResourceInfomation>>& GetAllResouces() { return resources; }

    Resource* Get(const std::u16string key) {
        if (resources.count(key) > 0) return resources[key]->GetResourcePtr();
        return nullptr;
    }

    void Register(const std::u16string path, std::shared_ptr<ResourceInfomation> resource) {
        resources[path] = resource;
        resource->GetResourcePtr()->AddRef();
    }

    void Unregister(const std::u16string path) {
        if (resources.count(path) == 0) return;
        resources[path]->GetResourcePtr()->Release();
        resources.erase(path);
    }

    void Clear() {
        for (auto resource : resources) {
            resource.second->GetResourcePtr()->Release();
        }
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

    static std::filesystem::file_time_type GetModifiedTime(const std::u16string path) {
        std::filesystem::path p(path);
        std::error_code ec;
        auto ftime = std::filesystem::last_write_time(p, ec);
        if (ec.value() != 0) {
            // TODO: log failure to get time
            return std::filesystem::file_time_type::min();
        }
        return ftime;
    }
};

}  // namespace altseed