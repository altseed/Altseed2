#include "Texture2D.h"

#include <libpng16/png.h>
#include <stb_image.h>

#include "../Common/Resources.h"
#include "../Common/StringHelper.h"
#include "../IO/File.h"
#include "../Logger/Log.h"
#include "Graphics.h"

namespace Altseed2 {
std::mutex Texture2D::mtx;

Texture2D::Texture2D(const std::shared_ptr<Resources>& resources, const std::shared_ptr<LLGI::Texture>& texture, const std::u16string& sourcePath)
    : TextureBase(texture), resources_(resources), sourcePath_(sourcePath) {
    SetInstanceName(__FILE__);
}

Texture2D::~Texture2D() {
    std::lock_guard<std::mutex> lock(mtx);
    if (sourcePath_ != u"") {
        resources_->GetResourceContainer(ResourceType::Texture2D)->Unregister(sourcePath_);
        resources_ = nullptr;
    }
}

bool Texture2D::Reload() { return false; }

const char16_t* Texture2D::GetPath() const { return sourcePath_.c_str(); }

std::shared_ptr<Texture2D> Texture2D::Load(const char16_t* path) {
    std::lock_guard<std::mutex> lock(mtx);

    auto resources = Resources::GetInstance();
    auto cache = std::dynamic_pointer_cast<Texture2D>(resources->GetResourceContainer(ResourceType::Texture2D)->Get(path));
    if (cache != nullptr && cache->GetRef() > 0) {
        return cache;
    }

    auto file = StaticFile::Create(path);
    if (file == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Texture2D::Load: Failed to create file from '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    int32_t w, h, channel;
    uint8_t* data = (uint8_t*)stbi_load_from_memory((stbi_uc*)file->GetData(), file->GetSize(), &w, &h, &channel, 0);

    if (data == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Texture2D::Load: Failed to load data from '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    auto llgiTexture = Graphics::GetInstance()->CreateTexture(data, w, h, channel);
    if (llgiTexture == nullptr) {
        delete[] data;
        Log::GetInstance()->Error(LogCategory::Core, u"Texture2D::Load: Failed to CreateTexture from '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    auto res = MakeAsdShared<Texture2D>(resources, llgiTexture, path);
    resources->GetResourceContainer(ResourceType::Texture2D)
            ->Register(path, std::make_shared<ResourceContainer::ResourceInfomation>(res, path));

    delete[] data;

    return res;
}
}  // namespace Altseed2
