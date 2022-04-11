
#include "Vector4F.h"

namespace Altseed2 {

Vector4F::Vector4F() : X(0), Y(0), Z(0), W(0) {}

Vector4F::Vector4F(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

bool Vector4F::operator==(const Vector4F& o) const { return X == o.X && Y == o.Y && Z == o.Z && W == o.W; }

bool Vector4F::operator!=(const Vector4F& o) const { return !(X == o.X && Y == o.Y && Z == o.Z && W == o.W); }

Vector4F Vector4F::operator-() const { return Vector4F(-X, -Y, -Z, -W); }

Vector4F Vector4F::operator+(const Vector4F& o) const { return Vector4F(X + o.X, Y + o.Y, Z + o.Z, W + o.W); }

Vector4F Vector4F::operator-(const Vector4F& o) const { return Vector4F(X - o.X, Y - o.Y, Z - o.Z, W - o.W); }

Vector4F Vector4F::operator*(const Vector4F& o) const { return Vector4F(X * o.X, Y * o.Y, Z * o.Z, W * o.W); }

Vector4F Vector4F::operator/(const Vector4F& o) const { return Vector4F(X / o.X, Y / o.Y, Z / o.Z, W / o.W); }

Vector4F Vector4F::operator*(const float& o) const { return Vector4F(X * o, Y * o, Z * o, W * o); }

Vector4F Vector4F::operator/(const float& o) const { return Vector4F(X / o, Y / o, Z * o, W * o); }

float Vector4F::Dot(const Vector4F& v1, const Vector4F& v2) { return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z + v1.W * v2.W; }

float Vector4F::Distance(const Vector4F& v1, const Vector4F& v2) {
    float dx = v1.X - v2.X;
    float dy = v1.Y - v2.Y;
    float dz = v1.Z - v2.Z;
    float dw = v1.W - v2.W;
    return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

Vector4I Vector4F::To4I() const { return Vector4I((int32_t)X, (int32_t)Y, (int32_t)Z, (int32_t)W); }

Vector4F::operator Vector4F_C() const { return Vector4F_C{X, Y, Z, W}; }

Vector4F_C::operator Vector4F() const { return Vector4F(X, Y, Z, W); }
}  // namespace Altseed2