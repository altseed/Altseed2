#include "Sprite.h"

namespace altseed {

Sprite::Sprite() : uvs_({LLGI::Vec2F(0.0f, 0.0f), LLGI::Vec2F(1.0f, 0.0f), LLGI::Vec2F(1.0f, 1.0f), LLGI::Vec2F(0.0f, 1.0f)}) {}

std::array<LLGI::Vec2F, 4> Sprite::GetVertex(LLGI::Vec2I windowSize) {
    return std::array<LLGI::Vec2F, 4>{
            LLGI::Vec2F(position_.X, position_.Y),
            LLGI::Vec2F(position_.X + size_.X, position_.Y),
            LLGI::Vec2F(position_.X + size_.X, position_.Y + size_.Y),
            LLGI::Vec2F(position_.X, position_.Y + size_.Y),
    };
}

}  // namespace altseed
