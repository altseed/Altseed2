

#if defined(_M_X86) && defined(__x86__)
#include <emmintrin.h>
#endif
#include "Matrix44I.h"
#include "Vector3I.h"

namespace Altseed2 {

Vector3I::Vector3I() : X(0), Y(0), Z(0) {}

Vector3I::Vector3I(int32_t x, int32_t y, int32_t z) : X(x), Y(y), Z(z) {}

bool Vector3I::operator==(const Vector3I& o) { return X == o.X && Y == o.Y && Z == o.Z; }

bool Vector3I::operator!=(const Vector3I& o) { return !(X == o.X && Y == o.Y && Z == o.Z); }

bool Vector3I::operator>(const Vector3I& o) const {
    if (X != o.X) return X > o.X;
    if (Y != o.Y) return Y > o.Y;
    if (Z != o.Z) return Z > o.Z;
    return false;
}

bool Vector3I::operator<(const Vector3I& o) const {
    if (X != o.X) return X < o.X;
    if (Y != o.Y) return Y < o.Y;
    if (Z != o.Z) return Z < o.Z;
    return false;
}

Vector3I Vector3I::operator-() { return Vector3I(-X, -Y, -Z); }

Vector3I Vector3I::operator+(const Vector3I& o) const { return Vector3I(X + o.X, Y + o.Y, Z + o.Z); }

Vector3I Vector3I::operator-(const Vector3I& o) const { return Vector3I(X - o.X, Y - o.Y, Z - o.Z); }

Vector3I Vector3I::operator*(const Vector3I& o) const { return Vector3I(X * o.X, Y * o.Y, Z * o.Z); }

Vector3I Vector3I::operator/(const Vector3I& o) const { return Vector3I(X / o.X, Y / o.Y, Z / o.Z); }

Vector3I Vector3I::operator*(const int32_t& o) const { return Vector3I(X * o, Y * o, Z * o); }

Vector3I Vector3I::operator/(const int32_t& o) const { return Vector3I(X / o, Y / o, Z / o); }

Vector3I& Vector3I::operator+=(const Vector3I& o) {
    X += o.X;
    Y += o.Y;
    Z += o.Z;
    return *this;
}

Vector3I& Vector3I::operator-=(const Vector3I& o) {
    X -= o.X;
    Y -= o.Y;
    Z -= o.Z;
    return *this;
}

Vector3I& Vector3I::operator*=(const int32_t& o) {
    X *= o;
    Y *= o;
    Z *= o;
    return *this;
}

Vector3I& Vector3I::operator/=(const int32_t& o) {
    X /= o;
    Y /= o;
    Z /= o;
    return *this;
}

int32_t Vector3I::Dot(const Vector3I& v1, const Vector3I& v2) { return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z; }

Vector3I Vector3I::Cross(const Vector3I& v1, const Vector3I& v2) {
    Vector3I o;

    int32_t x = v1.Y * v2.Z - v1.Z * v2.Y;
    int32_t y = v1.Z * v2.X - v1.X * v2.Z;
    int32_t z = v1.X * v2.Y - v1.Y * v2.X;
    o.X = x;
    o.Y = y;
    o.Z = z;
    return o;
}

float Vector3I::Distance(const Vector3I& v1, const Vector3I& v2) {
    int32_t dx = v1.X - v2.X;
    int32_t dy = v1.Y - v2.Y;
    int32_t dz = v1.Z - v2.Z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

Vector3F Vector3I::To3F() const { return Vector3F(X, Y, Z); }

Vector3I::operator Vector3I_C() const { return Vector3I_C{X, Y, Z}; }

Vector3I_C::operator Vector3I() const { return Vector3I(X, Y, Z); }

}  // namespace Altseed2
