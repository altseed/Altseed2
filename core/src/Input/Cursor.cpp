#include "Cursor.h"

namespace Altseed {

Cursor::Cursor(GLFWcursor* cursor) { native_ = cursor; }

Cursor::~Cursor() { native_ = nullptr; }

static void PngReadData(png_structp png_ptr, png_bytep data, png_size_t length) {
    auto d = (uint8_t**)png_get_io_ptr(png_ptr);

    memcpy(data, *d, length);
    (*d) += length;
}

bool Cursor::LoadPNGImage(
        void* data,
        int32_t size,
        bool rev,
        int32_t& imagewidth,
        int32_t& imageheight,
        ::std::vector<uint8_t>& imagedst,
        const char16_t* path) {
    imagewidth = 0;
    imageheight = 0;
    imagedst.clear();

    int32_t png_width, png_height;
    int bit_depth, color_type, interlace_type;

    uint8_t* data_ = (uint8_t*)data;

    /* pngアクセス構造体を作成 */
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    /* リードコールバック関数指定 */
    png_set_read_fn(png, &data_, &PngReadData);

    /* png画像情報構造体を作成 */
    png_infop png_info = png_create_info_struct(png);

    /* エラーハンドリング */
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &png_info, NULL);

        //        Log::GetInstance()->Error(LogCategory::Core, u"Mouse::LoadPNGImage: Failed to read png file header from '{0}'", path);

        return false;
    }

    /* IHDRチャンク情報を取得 */
    png_read_info(png, png_info);

    png_width = png_get_image_width(png, png_info);
    png_height = png_get_image_height(png, png_info);
    bit_depth = png_get_bit_depth(png, png_info);
    color_type = png_get_color_type(png, png_info);
    /* インターレース */
    auto number_of_passes = png_set_interlace_handling(png);
    if (number_of_passes == 0) {
        number_of_passes = 1;
    }

    /* RGBA8888フォーマットに変換する */
    if (bit_depth < 8) {
        png_set_packing(png);
    } else if (bit_depth == 16) {
        png_set_strip_16(png);
    }

    uint32_t pixelBytes = 4;
    switch (color_type) {
        case PNG_COLOR_TYPE_PALETTE: {
            png_set_palette_to_rgb(png);

            png_bytep trans_alpha = NULL;
            int num_trans = 0;
            png_color_16p trans_color = NULL;

            png_get_tRNS(png, png_info, &trans_alpha, &num_trans, &trans_color);
            if (trans_alpha != NULL) {
                pixelBytes = 4;
            } else {
                pixelBytes = 3;
            }
        } break;
        case PNG_COLOR_TYPE_GRAY:
            png_set_expand_gray_1_2_4_to_8(png);
            png_set_gray_to_rgb(png);
            pixelBytes = 3;
            break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            png_set_gray_to_rgb(png);
            pixelBytes = 4;
            break;
        case PNG_COLOR_TYPE_RGB:
            pixelBytes = 3;
            break;
        case PNG_COLOR_TYPE_RGBA:
            break;
    }

    uint8_t* image = new uint8_t[png_width * png_height * pixelBytes];
    uint32_t pitch = png_width * pixelBytes;

    // 読み込み
    if (rev) {
        png_bytepp rp;
        for (auto pass = 0; pass < number_of_passes; pass++) {
            for (uint32_t i = 0; i < png_height; i++) {
                png_read_row(png, &image[(png_height - 1 - i) * pitch], NULL);
            }
        }
    } else {
        for (auto pass = 0; pass < number_of_passes; pass++) {
            for (uint32_t i = 0; i < png_height; i++) {
                png_read_row(png, &image[i * pitch], NULL);
            }
        }
    }

    imagewidth = png_get_image_width(png, png_info);
    imageheight = png_get_image_height(png, png_info);
    imagedst.resize(imagewidth * imageheight * 4);
    auto imagedst_ = imagedst.data();

    if (pixelBytes == 4) {
        memcpy(imagedst_, image, imagewidth * imageheight * 4);
    } else {
        for (int32_t y = 0; y < imageheight; y++) {
            for (int32_t x = 0; x < imagewidth; x++) {
                auto src = (x + y * imagewidth) * 3;
                auto dst = (x + y * imagewidth) * 4;
                imagedst_[dst + 0] = image[src + 0];
                imagedst_[dst + 1] = image[src + 1];
                imagedst_[dst + 2] = image[src + 2];
                imagedst_[dst + 3] = 255;
            }
        }
    }

    if (image != NULL) {
        delete[](image);
        (image) = NULL;
    }
    png_destroy_read_struct(&png, &png_info, NULL);

    return true;
}

std::shared_ptr<Cursor> Cursor::Create(const char16_t* path, Vector2I hotspot) {
    auto f = StaticFile::Create(path);
    if (f == nullptr) {
        //        Log::GetInstance()->Error(LogCategory::Core, u"Mouse::SetCursorImage: Failed to create static file from '{0}'", path);
        return;
    }

    int32_t width, height;
    std::vector<uint8_t> dst;
    if (!LoadPNGImage((void*)f->GetData(), f->GetSize(), false, width, height, dst, path)) {
        //        Log::GetInstance()->Error(LogCategory::Core, u"Mouse::LoadPNGImage: Failed to load png image from '{0}'", path);
        return;
    }

    GLFWimage img;
    img.pixels = dst.data();
    img.width = width;
    img.height = height;

    auto cursor = glfwCreateCursor(&img, hotspot.X, hotspot.Y);
    if (cursor == nullptr) {
        //        Log::GetInstance()->Error(LogCategory::Core, u"Mouse::LoadPNGImage: Failed to create cursor from '{0}'", path);
        return;
    }

    auto res = MakeAsdShared<Cursor>(cursor);

    return res;
}

};  // namespace Altseed
