#include "Vector4I.h"

namespace Altseed {
Vector4I::Vector4I() : X(0), Y(0), Z(0), W(0) {}

Vector4I::Vector4I(int32_t x, int32_t y, int32_t z, int32_t w) : X(x), Y(y), Z(z), W(w) {}

bool Vector4I::operator==(const Vector4I& o) { return X == o.X && Y == o.Y && Z == o.Z && W == o.W; }

bool Vector4I::operator!=(const Vector4I& o) { return !(X == o.X && Y == o.Y && Z == o.Z && W == o.W); }

Vector4I Vector4I::operator-() { return Vector4I(-X, -Y, -Z, -W); }

Vector4I Vector4I::operator+(const Vector4I& o) const { return Vector4I(X + o.X, Y + o.Y, Z + o.Z, W + o.W); }

Vector4I Vector4I::operator-(const Vector4I& o) const { return Vector4I(X - o.X, Y - o.Y, Z - o.Z, W - o.W); }

Vector4I Vector4I::operator*(const Vector4I& o) const { return Vector4I(X * o.X, Y * o.Y, Z * o.Z, W * o.W); }

Vector4I Vector4I::operator/(const Vector4I& o) const { return Vector4I(X / o.X, Y / o.Y, Z / o.Z, W / o.W); }

Vector4I Vector4I::operator*(const int32_t& o) const { return Vector4I(X * o, Y * o, Z * o, W * o); }

Vector4I Vector4I::operator/(const int32_t& o) const { return Vector4I(X / o, Y / o, Z * o, W * o); }

int32_t Vector4I::Dot(const Vector4I& v1, const Vector4I& v2) { return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z + v1.W * v2.W; }

float Vector4I::Distance(const Vector4I& v1, const Vector4I& v2) {
    int32_t dx = v1.X - v2.X;
    int32_t dy = v1.Y - v2.Y;
    int32_t dz = v1.Z - v2.Z;
    int32_t dw = v1.W - v2.W;
    return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

Vector4F Vector4I::To4F() const { return Vector4F(X, Y, Z, W); }

Vector4I::operator Vector4I_C() const { return Vector4I_C{X, Y, Z, W}; }

Vector4I_C::operator Vector4I() const { return Vector4I(X, Y, Z, W); }
}  // namespace Altseed