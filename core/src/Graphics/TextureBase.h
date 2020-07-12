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
class TextureBase : public Resource {
private:
    static ThreadSafeMap<std::u16string, std::mutex> mtxs;

protected:
    std::shared_ptr<Resources> resources_ = nullptr;
    std::shared_ptr<LLGI::Texture> texture_ = nullptr;
    Vector2I size_;

    TextureBase(){};

public:
    TextureBase(std::shared_ptr<Resources>& resources, std::shared_ptr<LLGI::Texture>& texture);
    virtual ~TextureBase();

    Vector2I GetSize() const;

    virtual bool Save(const char16_t* path);

    void OnTerminating() override;

    std::shared_ptr<LLGI::Texture>& GetNativeTexture() { return texture_; }
};
}  // namespace Altseed2
