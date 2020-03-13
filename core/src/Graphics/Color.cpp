#include "Color.h"
#include "Graphics.h"

namespace Altseed {
Color::Color() : A(TEXTURE_DEFAULT_COLOR), R(TEXTURE_DEFAULT_COLOR), G(TEXTURE_DEFAULT_COLOR), B(TEXTURE_DEFAULT_COLOR) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : A(a), R(r), G(g), B(b) {}

Color Color::operator*(const Color& right) {
    return Color(
        R * right.R / TEXTURE_DEFAULT_COLOR,
        G * right.G / TEXTURE_DEFAULT_COLOR,
        B * right.B / TEXTURE_DEFAULT_COLOR,
        A * right.A / TEXTURE_DEFAULT_COLOR
    );
}

Color& Color::operator*=(const Color& right) {
    R = R * right.R / TEXTURE_DEFAULT_COLOR;
    G = G * right.G / TEXTURE_DEFAULT_COLOR;
    B = B * right.B / TEXTURE_DEFAULT_COLOR;
    A = A * right.A / TEXTURE_DEFAULT_COLOR;
    return *this;
}

bool Color::operator==(const Color& right) { return R == right.R && G == right.G && B == right.B && A == right.A; }

Color::operator Color_C() const { return Color_C{R, G, B, A}; }

Color_C::operator Color() const { return Color(R, G, B, A); }

}  // namespace Altseed