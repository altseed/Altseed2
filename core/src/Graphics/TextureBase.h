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

class TextureBase : public Resource {
private:
    static ThreadSafeMap<std::u16string, std::mutex> mtxs;

protected:
    std::shared_ptr<Resources> resources_ = nullptr;
    std::shared_ptr<LLGI::Texture> texture_ = nullptr;
    Vector2I size_;
    TextureWrapMode wrapMode_;
    TextureFilterType filterMode_;

    TextureBase(){};

public:
    TextureBase(std::shared_ptr<Resources>& resources, std::shared_ptr<LLGI::Texture>& texture);
    virtual ~TextureBase();

    Vector2I GetSize() const;

    TextureWrapMode GetWrapMode() const;
    void SetWrapMode(TextureWrapMode wrapMode);

    TextureFilterType GetFilterType() const;
    void SetFilterType(TextureFilterType filterMode);

    virtual bool Save(const char16_t* path);

    void OnTerminating() override;

    std::shared_ptr<LLGI::Texture>& GetNativeTexture() { return texture_; }
};
}  // namespace Altseed2
