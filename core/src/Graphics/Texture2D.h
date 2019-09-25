#pragma once

#include <memory>
#include <vector>
#include "../Common/Resource.h"
#include "../Common/Resources.h"

namespace altseed {
class Texture2D : public Resource {
private:
    std::shared_ptr<Resources> m_resources;
	
	std::vector<uint8_t> m_buffer;

    int32_t m_width;
    int32_t m_height;

public:
    Texture2D(std::shared_ptr<Resources> resources, uint8_t* data, int32_t width, int32_t height);
    virtual ~Texture2D();

	bool Reload() override;

    static Texture2D* Load(const char16_t* path);
};
}  // namespace altseed