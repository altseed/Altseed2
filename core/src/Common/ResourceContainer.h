﻿#pragma once

#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "../Platform/FileSystem.h"
#include "Resource.h"

#if !USE_CBG

namespace Altseed2 {
class ResourceContainer {
public:
    class ResourceInfomation {
    private:
        std::weak_ptr<Resource> m_resourcePtr;
        Resource* rawPtr_;
        std::u16string m_path;
        int32_t m_modifiedTime;

    public:
        ResourceInfomation(std::shared_ptr<Resource> resource, std::u16string path) {
            m_resourcePtr = resource;
            rawPtr_ = resource.get();
            m_path = path;
            m_modifiedTime = ResourceContainer::GetModifiedTime(path);
        }

        std::shared_ptr<Resource> GetResourcePtr() {
            auto res = m_resourcePtr.lock();
            if (res != nullptr) return res;
            res = CreateAndAddSharedPtr<Resource>(rawPtr_);
            m_resourcePtr = res;
            return res;
        }

        const std::u16string& GetPath() { return m_path; }

        const int32_t GetModifiedTime() { return m_modifiedTime; }

        bool Reload(int32_t time) {
            m_modifiedTime = time;

            auto locked = GetResourcePtr();

            if (locked == nullptr) return false;
            return locked->Reload();
        }
    };

private:
    std::map<std::u16string, std::shared_ptr<ResourceInfomation>> resources;
    std::mutex resourceMtx_;

public:
    ResourceContainer() {}

    const std::map<std::u16string, std::shared_ptr<ResourceInfomation>>& GetAllResouces() { return resources; }

    std::shared_ptr<Resource> Get(const std::u16string key) {
        std::lock_guard<std::mutex> lock(resourceMtx_);
        if (resources.count(key) > 0) return resources[key]->GetResourcePtr();
        return nullptr;
    }

    void Register(const std::u16string path, std::shared_ptr<ResourceInfomation> resource) {
        std::lock_guard<std::mutex> lock(resourceMtx_);
        resources[path] = resource;
    }

    void Unregister(const std::u16string path) {
        if (resources.count(path) == 0) return;
        std::lock_guard<std::mutex> lock(resourceMtx_);
        resources.erase(path);
    }

    void Clear() {
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

    static int32_t GetModifiedTime(const std::u16string path) {
        auto time = FileSystem::GetLastWriteTime(path);
        return time;
    }
};

}  // namespace Altseed2

#endif