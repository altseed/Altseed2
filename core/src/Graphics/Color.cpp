#include "Color.h"
#include "Graphics.h"

namespace Altseed {
Color::Color() : A(TextureDefaultColor), R(TextureDefaultColor), G(TextureDefaultColor), B(TextureDefaultColor) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : A(a), R(r), G(g), B(b) {}

Color Color::operator*(const Color& right) {
    return Color(
            R * right.R / TextureDefaultColor,
            G * right.G / TextureDefaultColor,
            B * right.B / TextureDefaultColor,
            A * right.A / TextureDefaultColor);
}

Color& Color::operator*=(const Color& right) {
    R = R * right.R / TextureDefaultColor;
    G = G * right.G / TextureDefaultColor;
    B = B * right.B / TextureDefaultColor;
    A = A * right.A / TextureDefaultColor;
    return *this;
}

bool Color::operator==(const Color& right) { return R == right.R && G == right.G && B == right.B && A == right.A; }

Color::operator Color_C() const { return Color_C{R, G, B, A}; }

Color_C::operator Color() const { return Color(R, G, B, A); }

}  // namespace Altseed