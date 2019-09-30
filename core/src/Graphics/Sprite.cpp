#include "Sprite.h"

namespace altseed {

Sprite::Sprite(LLGI::Vec2F position, LLGI::Vec2F size, LLGI::Texture* texture) : Position(position), Size(size), Texture(texture) {}

std::array<LLGI::Vec2F, 4> Sprite::GetVertex() {
    return std::array<LLGI::Vec2F, 4>{Position,
                                      LLGI::Vec2F(Position.X + Size.X, Position.Y),
                                      LLGI::Vec2F(Position.X + Size.X, Position.Y + Size.Y),
                                      LLGI::Vec2F(Position.X, Position.Y + Size.Y)};
}
}  // namespace altseed
