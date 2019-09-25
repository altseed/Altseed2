#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../Common/Resources.h"
#include "../IO/File.h"

namespace altseed {
Texture2D::Texture2D(std::shared_ptr<Resources> resources, uint8_t* data, int32_t width, int32_t height) {
    m_width = width;
    m_height = height;
    for (int32_t i = 0; i < m_width * m_height; i++) {
        m_buffer.push_back(data[i]);
    }
}

Texture2D::~Texture2D() {}

bool Texture2D::Reload() { return false; }

Texture2D* Texture2D::Load(const char16_t* path) {
    auto resources = Resources::GetInstance();
    Texture2D* cache = (Texture2D*)resources->GetResourceContainer(ResourceType::Texture2D)->Get(path);
    if (cache != nullptr) {
        cache->AddRef();
        return cache;
    }

    auto file = File::GetInstance()->CreateStaticFile(path);
    if (file == nullptr) {
        return nullptr;
    }

    int32_t w, h, channel;
    uint8_t* data = (uint8_t*)stbi_load_from_memory((stbi_uc*)file->GetData(), file->GetSize(), &w, &h, &channel, 0);

    if (data != nullptr) {
        return nullptr;
    }

    file->Release();

    auto res = new Texture2D(resources, data, w, h);
    resources->GetResourceContainer(ResourceType::Texture2D)
            ->Register(path, std::make_shared<ResourceContainer::ResourceInfomation>((Resource*)res, path));
    return res;
}
}  // namespace altseed