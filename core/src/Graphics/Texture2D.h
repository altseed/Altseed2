#pragma once

#include <LLGI.Base.h>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include "../Common/Resource.h"
#include "../Common/Resources.h"
#include "../Math/Vector2DI.h"

namespace Altseed {
class Texture2D : public Resource {
private:
    static std::map<std::u16string, std::shared_ptr<std::mutex>> mtxs;

	std::u16string sourcePath_;
    std::shared_ptr<Resources> m_resources = nullptr;
    std::vector<uint8_t> m_buffer;

protected:
    std::shared_ptr<LLGI::Texture> m_texture = nullptr;
    Vector2DI size_;
    Texture2D(){};

public:
    Texture2D(std::shared_ptr<Resources>& resources, std::shared_ptr<LLGI::Texture>& texture, uint8_t* data, int32_t width, int32_t height, const std::u16string& sourcePath);
    virtual ~Texture2D();

    bool Reload() override;

    Vector2DI GetSize() const { return size_; }
    std::shared_ptr<LLGI::Texture>& GetNativeTexture() { return m_texture; }

    static std::shared_ptr<Texture2D> Load(const char16_t* path);
};
}  // namespace Altseed