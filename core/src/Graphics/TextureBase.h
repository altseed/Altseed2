#pragma once

#include <LLGI.Base.h>

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "../Common/Resource.h"
#include "../Common/Resources.h"
#include "../Common/ThreadSafeMap.h"
#include "../Math/Vector2I.h"

namespace Altseed2 {

enum class TextureWrapMode : int32_t {
    Clamp,
    Repeat,
};

enum class TextureFilterType : int32_t {
    Nearest,
    Linear,
};

enum class TextureFormatType : int32_t {
    R8G8B8A8_UNORM = 0,
    R16G16B16A16_FLOAT = 1,
    R32G32B32A32_FLOAT = 2,
    R8G8B8A8_UNORM_SRGB = 3,
    R16G16_FLOAT = 4,
    R8_UNORM = 5,
    // BC1 = 6,
    // BC2 = 7,
    // BC3 = 8,
    // BC1_SRGB = 9,
    // BC2_SRGB = 10,
    // BC3_SRGB = 11,
    D32 = 12,
    D32S8 = 13,
    D24S8 = 14,
};

LLGI::TextureFormatType textureFormatToLLGI(const TextureFormatType& format);
TextureFormatType textureFormatFromLLGI(const LLGI::TextureFormatType& format);

class TextureBase : public Resource {
private:
    static ThreadSafeMap<std::u16string, std::mutex> mtxs;
    std::shared_ptr<LLGI::Texture> texture_ = nullptr;
    Vector2I size_;
    TextureWrapMode wrapMode_;
    TextureFilterType filterMode_;
    TextureFormatType format_;

public:
    TextureBase(const std::shared_ptr<LLGI::Texture>& texture);
    virtual ~TextureBase();

    Vector2I GetSize() const;

    TextureWrapMode GetWrapMode() const;
    void SetWrapMode(TextureWrapMode wrapMode);

    TextureFilterType GetFilterType() const;
    void SetFilterType(TextureFilterType filterMode);

    TextureFormatType GetFormat() const;

    virtual bool Save(const char16_t* path);

    void OnTerminating() override;

    std::shared_ptr<LLGI::Texture>& GetNativeTexture() { return texture_; }
};
}  // namespace Altseed2
