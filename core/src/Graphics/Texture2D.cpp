#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include <libpng16/png.h>
#include <stb_image.h>

#include "../Common/Resources.h"
#include "../Common/StringHelper.h"
#include "../IO/File.h"
#include "../Logger/Log.h"
#include "Graphics.h"

namespace Altseed {
ThreadSafeMap<std::u16string, std::mutex> Texture2D::mtxs;

Texture2D::Texture2D(std::shared_ptr<Resources>& resources, std::shared_ptr<LLGI::Texture>& texture, const std::u16string& sourcePath) {
    sourcePath_ = sourcePath;
    resources_ = resources;
    m_texture = texture;
    size_.X = m_texture->GetSizeAs2D().X;
    size_.Y = m_texture->GetSizeAs2D().Y;

    SetInstanceName(__FILE__);
}

Texture2D::~Texture2D() {
    if (sourcePath_ != u"") {
        resources_->GetResourceContainer(ResourceType::Texture2D)->Unregister(sourcePath_);
        resources_ = nullptr;
    }

    m_texture = nullptr;
}

bool Texture2D::Reload() { return false; }

const char16_t* Texture2D::GetPath() const { return sourcePath_.c_str(); }

Vector2I Texture2D::GetSize() const { return size_; }

void Texture2D::Save(const char16_t* path) {
    FILE* f;
    fopen_s(&f, utf16_to_utf8(path).c_str(), "wb");

    png_structp pp = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop ip = png_create_info_struct(pp);

    png_init_io(pp, f);
    png_set_IHDR(
            pp,
            ip,
            GetSize().X,
            GetSize().Y,
            8,
            PNG_COLOR_TYPE_RGBA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);

    png_bytep raw1D = (png_bytep)malloc(GetSize().Y * png_get_rowbytes(pp, ip));
    png_bytepp raw2D = (png_bytepp)malloc(GetSize().Y * sizeof(png_bytep));
    for (int i = 0; i < GetSize().Y; i++) raw2D[i] = &raw1D[i * png_get_rowbytes(pp, ip)];

    auto buf = (uint8_t*)GetNativeTexture()->Lock();
    for (size_t i = 0; i < GetSize().X * GetSize().Y * 4; i++) raw1D[i] = buf[i];
    GetNativeTexture()->Unlock();

    png_write_info(pp, ip);
    png_write_image(pp, raw2D);
    png_write_end(pp, ip);

    png_destroy_write_struct(&pp, &ip);
    fclose(f);
    free(raw1D);
    free(raw2D);
}

std::shared_ptr<Texture2D> Texture2D::Load(const char16_t* path) {
    Locked<std::mutex> locked = mtxs[path].Lock();
    std::lock_guard<std::mutex> lock(locked.Get());

    auto resources = Resources::GetInstance();
    // TODO
    auto cache = std::dynamic_pointer_cast<Texture2D>(resources->GetResourceContainer(ResourceType::Texture2D)->Get(path));
    if (cache != nullptr) {
        cache->AddRef();
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
}  // namespace Altseed