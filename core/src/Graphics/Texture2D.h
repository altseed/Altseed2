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

namespace altseed {
class Texture2D : public Resource {
private:
    static std::map<std::u16string, std::shared_ptr<std::mutex>> mtxs;

    std::shared_ptr<Resources> m_resources;

    std::vector<uint8_t> m_buffer;
    std::shared_ptr<LLGI::Texture> m_texture;

    int32_t m_width;
    int32_t m_height;

public:
    Texture2D(std::shared_ptr<Resources>& resources, std::shared_ptr<LLGI::Texture>& texture, uint8_t* data, int32_t width, int32_t height);
    virtual ~Texture2D();

    bool Reload() override;

    Vector2DI GetSize() { return Vector2DI(m_width, m_height); }
    std::shared_ptr<LLGI::Texture>& GetNativeTexture() { return m_texture; }

    static Texture2D* Load(const char16_t* path);
};
}  // namespace altseed