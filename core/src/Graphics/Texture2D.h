#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include "../Common/Resource.h"
#include "../Common/Resources.h"

namespace altseed {
class Texture2D : public Resource {
private:
    static std::map<std::u16string, std::shared_ptr<std::mutex>> mtxs;

    std::shared_ptr<Resources> m_resources;

    std::vector<uint8_t> m_buffer;

    int32_t m_width;
    int32_t m_height;

public:
    Texture2D(std::shared_ptr<Resources> resources, uint8_t* data, int32_t width, int32_t height);
    virtual ~Texture2D();

    bool Reload() override;

    std::tuple<int32_t, int32_t> GetSize() { return std::make_tuple(m_width, m_height); }

    static Texture2D* Load(const char16_t* path);
};
}  // namespace altseed