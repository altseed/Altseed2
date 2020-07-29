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

LLGI::TextureFormatType textureFormatToLLGI(const TextureFormatType& format) {
    switch (format) {
        case TextureFormatType::R8G8B8A8_UNORM:
            return LLGI::TextureFormatType::R8G8B8A8_UNORM;
        case TextureFormatType::R16G16B16A16_FLOAT:
            return LLGI::TextureFormatType::R16G16B16A16_FLOAT;
        case TextureFormatType::R32G32B32A32_FLOAT:
            return LLGI::TextureFormatType::R32G32B32A32_FLOAT;
        case TextureFormatType::R8G8B8A8_UNORM_SRGB:
            return LLGI::TextureFormatType::R8G8B8A8_UNORM_SRGB;
        case TextureFormatType::R16G16_FLOAT:
            return LLGI::TextureFormatType::R16G16_FLOAT;
        case TextureFormatType::R8_UNORM:
            return LLGI::TextureFormatType::R8_UNORM;
        case TextureFormatType::BC1:
            return LLGI::TextureFormatType::BC1;
        case TextureFormatType::BC2:
            return LLGI::TextureFormatType::BC2;
        case TextureFormatType::BC3:
            return LLGI::TextureFormatType::BC3;
        case TextureFormatType::BC1_SRGB:
            return LLGI::TextureFormatType::BC1_SRGB;
        case TextureFormatType::BC2_SRGB:
            return LLGI::TextureFormatType::BC2_SRGB;
        case TextureFormatType::BC3_SRGB:
            return LLGI::TextureFormatType::BC3_SRGB;
        case TextureFormatType::D32:
            return LLGI::TextureFormatType::D32;
        case TextureFormatType::D32S8:
            return LLGI::TextureFormatType::D32S8;
        case TextureFormatType::D24S8:
            return LLGI::TextureFormatType::D24S8;
        default:
            Log::GetInstance()->Error(LogCategory::Core, u"textureFormatToLLGI: Unexpected TextureFormatType");
            return LLGI::TextureFormatType::R8G8B8A8_UNORM;
    }
}

TextureFormatType textureFormatFromLLGI(const LLGI::TextureFormatType& format) {
    switch (format) {
        case LLGI::TextureFormatType::R8G8B8A8_UNORM:
            return TextureFormatType::R8G8B8A8_UNORM;
        case LLGI::TextureFormatType::R16G16B16A16_FLOAT:
            return TextureFormatType::R16G16B16A16_FLOAT;
        case LLGI::TextureFormatType::R32G32B32A32_FLOAT:
            return TextureFormatType::R32G32B32A32_FLOAT;
        case LLGI::TextureFormatType::R8G8B8A8_UNORM_SRGB:
            return TextureFormatType::R8G8B8A8_UNORM_SRGB;
        case LLGI::TextureFormatType::R16G16_FLOAT:
            return TextureFormatType::R16G16_FLOAT;
        case LLGI::TextureFormatType::R8_UNORM:
            return TextureFormatType::R8_UNORM;
        case LLGI::TextureFormatType::BC1:
            return TextureFormatType::BC1;
        case LLGI::TextureFormatType::BC2:
            return TextureFormatType::BC2;
        case LLGI::TextureFormatType::BC3:
            return TextureFormatType::BC3;
        case LLGI::TextureFormatType::BC1_SRGB:
            return TextureFormatType::BC1_SRGB;
        case LLGI::TextureFormatType::BC2_SRGB:
            return TextureFormatType::BC2_SRGB;
        case LLGI::TextureFormatType::BC3_SRGB:
            return TextureFormatType::BC3_SRGB;
        case LLGI::TextureFormatType::D32:
            return TextureFormatType::D32;
        case LLGI::TextureFormatType::D32S8:
            return TextureFormatType::D32S8;
        case LLGI::TextureFormatType::D24S8:
            return TextureFormatType::D24S8;
        default:
            Log::GetInstance()->Error(LogCategory::Core, u"textureFormatToLLGI: Unexpected TextureFormatType");
            return TextureFormatType::R8G8B8A8_UNORM;
    }
}

ThreadSafeMap<std::u16string, std::mutex> TextureBase::mtxs;

TextureBase::TextureBase(const std::shared_ptr<LLGI::Texture>& texture)
    : texture_(texture), wrapMode_(TextureWrapMode::Repeat), filterMode_(TextureFilterType::Linear) {
    size_.X = texture->GetSizeAs2D().X;
    size_.Y = texture->GetSizeAs2D().Y;
    format_ = textureFormatFromLLGI(texture_->GetFormat());

    SetInstanceName(__FILE__);
}

TextureBase::~TextureBase() { texture_ = nullptr; }

Vector2I TextureBase::GetSize() const { return size_; }

TextureWrapMode TextureBase::GetWrapMode() const { return wrapMode_; }

void TextureBase::SetWrapMode(TextureWrapMode wrapMode) { wrapMode_ = wrapMode; }

TextureFilterType TextureBase::GetFilterType() const { return filterMode_; }

void TextureBase::SetFilterType(TextureFilterType filterMode) { filterMode_ = filterMode; }

TextureFormatType TextureBase::GetFormat() const { return format_; }

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
