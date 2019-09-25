#pragma once

#include "../Common/Resource.h"

namespace altseed {
class Texture2D : public Resource {
private:
public:
    static Texture2D* Load(const char* path);
};
}  // namespace altseed