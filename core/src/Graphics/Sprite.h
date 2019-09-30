#pragma once
#include <array>
#include "Graphics.h"

namespace altseed {
class Sprite {
private:
    LLGI::Vec2F Position;
    LLGI::Vec2F Size;
    LLGI::Texture* Texture;

public:
    Sprite(LLGI::Vec2F position, LLGI::Vec2F size, LLGI::Texture* texture);
    LLGI::Vec2F GetPosition() const { return Position; }
    LLGI::Vec2F GetSize() const { return Size; }
    std::array<LLGI::Vec2F, 4> GetVertex();
    LLGI::Texture* GetTexture() { return Texture; }
};
}  // namespace altseed
