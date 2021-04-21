#include "ImageFont.h"

#include <string>

#include "../IO/File.h"
#include "../Logger/Log.h"
#include "Graphics.h"

namespace Altseed2 {
ImageFont::ImageFont(std::shared_ptr<Font> baseFont) : baseFont_(baseFont), Font(u"") {}

void ImageFont::AddImageGlyph(const int32_t character, std::shared_ptr<TextureBase> texture) { imageGlyphs_[character] = texture; }
std::shared_ptr<TextureBase> ImageFont::GetImageGlyph(const int32_t character) {
    if (imageGlyphs_.count(character) > 0) return imageGlyphs_[character];
    return nullptr;
}
}  // namespace Altseed2