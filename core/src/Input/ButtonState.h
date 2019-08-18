#pragma once

namespace altseed {

enum class ButtonState : int32_t {
    Free = 0b00,
    Push = 0b01,
    Hold = 0b11,
    Release = 0b10,
};
}
