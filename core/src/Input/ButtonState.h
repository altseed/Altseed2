#pragma once

namespace altseed {

enum class ButtonState : int32_t {
    Free,
    Push,
    Hold,
    Release,
};
}