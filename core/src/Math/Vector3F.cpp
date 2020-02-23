

#if defined(_M_X86) && defined(__x86__)
#include <emmintrin.h>
#endif
#include "Matrix44F.h"
#include "Vector3F.h"

namespace Altseed {

inline float Rsqrt(float x) {
#if defined(_M_X86) && defined(__x86__)
    _mm_store_ss(&x, _mm_rsqrt_ss(_mm_load_ss(&x)));
    return x;
#else
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf * x * x);
    x = x * (1.5f - xhalf * x * x);
    return x;
#endif
}

Vector3F::Vector3F() : X(0.0f), Y(0.0f), Z(0.0f) {}

Vector3F::Vector3F(float x, float y, float z) : X(x), Y(y), Z(z) {}

bool Vector3F::operator==(const Vector3F& o) { return X == o.X && Y == o.Y && Z == o.Z; }

bool Vector3F::operator!=(const Vector3F& o) { return !(X == o.X && Y == o.Y && Z == o.Z); }

bool Vector3F::operator>(const Vector3F& o) const {
    if (X != o.X) return X > o.X;
    if (Y != o.Y) return Y > o.Y;
    if (Z != o.Z) return Z > o.Z;
    return false;
}

bool Vector3F::operator<(const Vector3F& o) const {
    if (X != o.X) return X < o.X;
    if (Y != o.Y) return Y < o.Y;
    if (Z != o.Z) return Z < o.Z;
    return false;
}

Vector3F Vector3F::operator-() { return Vector3F(-X, -Y, -Z); }

Vector3F Vector3F::operator+(const Vector3F& o) const { return Vector3F(X + o.X, Y + o.Y, Z + o.Z); }

Vector3F Vector3F::operator-(const Vector3F& o) const { return Vector3F(X - o.X, Y - o.Y, Z - o.Z); }

Vector3F Vector3F::operator*(const Vector3F& o) const { return Vector3F(X * o.X, Y * o.Y, Z * o.Z); }

Vector3F Vector3F::operator/(const Vector3F& o) const { return Vector3F(X / o.X, Y / o.Y, Z / o.Z); }

Vector3F Vector3F::operator*(const float& o) const { return Vector3F(X * o, Y * o, Z * o); }

Vector3F Vector3F::operator/(const float& o) const { return Vector3F(X / o, Y / o, Z / o); }

Vector3F& Vector3F::operator+=(const Vector3F& o) {
    X += o.X;
    Y += o.Y;
    Z += o.Z;
    return *this;
}

Vector3F& Vector3F::operator-=(const Vector3F& o) {
    X -= o.X;
    Y -= o.Y;
    Z -= o.Z;
    return *this;
}

Vector3F& Vector3F::operator*=(const float& o) {
    X *= o;
    Y *= o;
    Z *= o;
    return *this;
}

Vector3F& Vector3F::operator/=(const float& o) {
    X /= o;
    Y /= o;
    Z /= o;
    return *this;
}

float Vector3F::Dot(const Vector3F& v1, const Vector3F& v2) { return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z; }

Vector3F Vector3F::Cross(const Vector3F& v1, const Vector3F& v2) {
    Vector3F o;

    float x = v1.Y * v2.Z - v1.Z * v2.Y;
    float y = v1.Z * v2.X - v1.X * v2.Z;
    float z = v1.X * v2.Y - v1.Y * v2.X;
    o.X = x;
    o.Y = y;
    o.Z = z;
    return o;
}

float Vector3F::Distance(const Vector3F& v1, const Vector3F& v2) {
    float dx = v1.X - v2.X;
    float dy = v1.Y - v2.Y;
    float dz = v1.Z - v2.Z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

Vector3I Vector3F::To3I() const { return Vector3I((int32_t)X, (int32_t)Y, (int32_t)Z); }

}  // namespace Altseed
