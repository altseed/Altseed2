#include "TextureBase.h"

#define STB_IMAGE_IMPLEMENTATION
#include <libpng16/png.h>
#include <stb_image.h>

#include "../Common/Resources.h"
#include "../Common/StringHelper.h"
#include "../IO/File.h"
#include "../Logger/Log.h"
#include "Graphics.h"

namespace Altseed2 {
ThreadSafeMap<std::u16string, std::mutex> TextureBase::mtxs;

TextureBase::TextureBase(std::shared_ptr<Resources>& resources, std::shared_ptr<LLGI::Texture>& texture) {
    resources_ = resources;
    texture_ = texture;
    size_.X = texture_->GetSizeAs2D().X;
    size_.Y = texture_->GetSizeAs2D().Y;
    wrapMode_ = TextureWrapMode::Repeat;

    SetInstanceName(__FILE__);
}

TextureBase::~TextureBase() { texture_ = nullptr; }

Vector2I TextureBase::GetSize() const { return size_; }

TextureWrapMode TextureBase::GetWrapMode() const { return wrapMode_; }

void TextureBase::SetWrapMode(TextureWrapMode wrapMode) { wrapMode_ = wrapMode; }

bool TextureBase::Save(const char16_t* path) {
    FILE* f;
#ifdef _WIN32
    fopen_s(&f, utf16_to_utf8(path).c_str(), "wb");
#else
    f = fopen(utf16_to_utf8(path).c_str(), "wb");
#endif
    if (f == NULL) return false;

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

    png_bytep raw1D = (png_bytep)malloc(size_.Y * png_get_rowbytes(pp, ip));
    png_bytepp raw2D = (png_bytepp)malloc(size_.Y * sizeof(png_bytep));
    for (int i = 0; i < GetSize().Y; i++) raw2D[i] = &raw1D[i * png_get_rowbytes(pp, ip)];

    auto buf = (uint8_t*)GetNativeTexture()->Lock();
    for (size_t i = 0; i < size_.X * size_.Y * 4; i++) raw1D[i] = buf[i];
    GetNativeTexture()->Unlock();

    png_write_info(pp, ip);
    png_write_image(pp, raw2D);
    png_write_end(pp, ip);

    png_destroy_write_struct(&pp, &ip);
    fclose(f);
    free(raw1D);
    free(raw2D);

    return true;
}

void TextureBase::OnTerminating() {
    texture_.reset();
}

}  // namespace Altseed2
