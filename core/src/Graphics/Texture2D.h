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
#include "TextureBase.h"

namespace Altseed {
class Texture2D : public TextureBase {
private:
    static std::mutex mtx;

    std::u16string sourcePath_;

protected:
    Texture2D(){};

public:
    Texture2D(std::shared_ptr<Resources>& resources, std::shared_ptr<LLGI::Texture>& texture, const std::u16string& sourcePath);
    virtual ~Texture2D();

    bool Reload() override;
    static std::shared_ptr<Texture2D> Load(const char16_t* path);
    const char16_t* GetPath() const;
};
}  // namespace Altseed
