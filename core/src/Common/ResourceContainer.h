#pragma once

#include <chrono>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>

namespace altseed {
template <class RESOURCE>
class ResourceContainer {
public:
    class ResourceInfomation {
    private:
        RESOURCE* m_resourcePtr;
        std::u16string m_path;
        time_t m_modifiedTime;

    public:
        ResourceInfomation(RESOURCE* resource, std::u16string path) {
            m_resourcePtr = resource;
            m_path = path;
            m_modifiedTime = GetModifiedTime(path);
        }

        RESOURCE* GetResourcePtr() { return m_resourcePtr; }
        const std::u16string& GetPath() { return m_path; }
        const time_t GetModifiedTime() { return m_modifiedTime; }
    };

private:
    std::map<std::u16string, std::shared_ptr<ResourceInfomation>> resources;

public:
    ResourceContainer() {}

    const std::map<std::u16string, std::shared_ptr<ResourceInfomation>>& GetAllResouces() { return resources; }

    RESOURCE* Get(const std::u16string key) {
        if (resources.count(key) > 0) return resources[key]->GetResourcePtr();
        return nullptr;
    }

    void Register(const std::u16string path, std::shared_ptr<ResourceInfomation> resource) { resources[path] = resource; }

    void Unregister(const std::u16string path) { resources.erase(path); }

    void Reload(const std::function<ResourceInfomation(std::u16string)> reloadFunc) {
        for (auto resource : resources) {
            auto path = resource.second->GetPath();
            auto time = GetModifiedTime(path);

            if (resource.second->GetModifiedTime() == time) continue;

            resources[resource.first] = reloadFunc(path);
        }
    }

    static time_t GetModifiedTime(const std::u16string path) {
        std::filesystem::path p = path;
        std::error_code ec;
        auto ftime = std::filesystem::last_write_time(p, &ec);
        if (ec.value() != 0) {
            // TODO: log failure to get time
            return 0;
        }
        return decltype(ftime)::clock::to_time_t(ftime);
    }
};
}  // namespace altseed