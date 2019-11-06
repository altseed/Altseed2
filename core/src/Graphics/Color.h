#pragma once

#include <stdint.h>

namespace altseed {
struct Color {
public:
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;

    Color();
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    Color operator*(const Color& right);
    Color& operator*=(const Color& right);
    bool operator==(const Color& right);
};
}  // namespace altseed