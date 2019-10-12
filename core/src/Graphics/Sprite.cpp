#include "Sprite.h"

namespace altseed {

Sprite::Sprite() {}

std::array<LLGI::Vec2F, 4> Sprite::GetVertex(LLGI::Vec2I windowSize) {
    return std::array<LLGI::Vec2F, 4>{
            LLGI::Vec2F((position_.X / windowSize.X - 0.5f) * 2.0, (-position_.Y / windowSize.Y + 0.5f) * 2.0),
            LLGI::Vec2F(((position_.X + size_.X) / windowSize.X - 0.5f) * 2.0, (-position_.Y / windowSize.Y + 0.5f) * 2.0),
            LLGI::Vec2F(((position_.X + size_.X) / windowSize.X - 0.5f) * 2.0, (-(position_.Y + size_.Y) / windowSize.Y + 0.5f) * 2.0),
            LLGI::Vec2F((position_.X / windowSize.X - 0.5f) * 2.0, (-(position_.Y + size_.Y) / windowSize.Y + 0.5f) * 2.0),
    };
}

}  // namespace altseed
