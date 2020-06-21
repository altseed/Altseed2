#pragma once

#include <LLGI.Graphics.h>
#include <stdint.h>

namespace Altseed2 {

struct Color_C;

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

    operator Color_C() const;

    LLGI::Color8 ToLL() const { return LLGI::Color8(R, G, B, A); }
};

struct Color_C {
public:
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;

    operator Color() const;
};

}  // namespace Altseed2