

#if defined(_M_X86) && defined(__x86__)
#include <emmintrin.h>
#endif
#include "Matrix44I.h"
#include "Vector3DI.h"


namespace Altseed {


Vector3DI::Vector3DI() : X(0), Y(0), Z(0) {}


Vector3DI::Vector3DI(int32_t x, int32_t y, int32_t z) : X(x), Y(y), Z(z) {}


bool Vector3DI::operator==(const Vector3DI& o) { return X == o.X && Y == o.Y && Z == o.Z; }


bool Vector3DI::operator!=(const Vector3DI& o) { return !(X == o.X && Y == o.Y && Z == o.Z); }

bool Vector3DI::operator>(const Vector3DI& o) const {
    if (X != o.X) return X > o.X;
    if (Y != o.Y) return Y > o.Y;
    if (Z != o.Z) return Z > o.Z;
    return false;
}

bool Vector3DI::operator<(const Vector3DI& o) const {
    if (X != o.X) return X < o.X;
    if (Y != o.Y) return Y < o.Y;
    if (Z != o.Z) return Z < o.Z;
    return false;
}


Vector3DI Vector3DI::operator-() { return Vector3DI(-X, -Y, -Z); }


Vector3DI Vector3DI::operator+(const Vector3DI& o) const { return Vector3DI(X + o.X, Y + o.Y, Z + o.Z); }


Vector3DI Vector3DI::operator-(const Vector3DI& o) const { return Vector3DI(X - o.X, Y - o.Y, Z - o.Z); }


Vector3DI Vector3DI::operator*(const Vector3DI& o) const { return Vector3DI(X * o.X, Y * o.Y, Z * o.Z); }


Vector3DI Vector3DI::operator/(const Vector3DI& o) const { return Vector3DI(X / o.X, Y / o.Y, Z / o.Z); }


Vector3DI Vector3DI::operator*(const int32_t& o) const { return Vector3DI(X * o, Y * o, Z * o); }


Vector3DI Vector3DI::operator/(const int32_t& o) const { return Vector3DI(X / o, Y / o, Z / o); }


Vector3DI& Vector3DI::operator+=(const Vector3DI& o) {
    X += o.X;
    Y += o.Y;
    Z += o.Z;
    return *this;
}


Vector3DI& Vector3DI::operator-=(const Vector3DI& o) {
    X -= o.X;
    Y -= o.Y;
    Z -= o.Z;
    return *this;
}


Vector3DI& Vector3DI::operator*=(const int32_t& o) {
    X *= o;
    Y *= o;
    Z *= o;
    return *this;
}


Vector3DI& Vector3DI::operator/=(const int32_t& o) {
    X /= o;
    Y /= o;
    Z /= o;
    return *this;
}


int32_t Vector3DI::Dot(const Vector3DI& v1, const Vector3DI& v2) { return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z; }


Vector3DI Vector3DI::Cross(const Vector3DI& v1, const Vector3DI& v2) {
    Vector3DI o;

    int32_t x = v1.Y * v2.Z - v1.Z * v2.Y;
    int32_t y = v1.Z * v2.X - v1.X * v2.Z;
    int32_t z = v1.X * v2.Y - v1.Y * v2.X;
    o.X = x;
    o.Y = y;
    o.Z = z;
    return o;
}


Vector3DI Vector3DI::Subtract(Vector3DI v1, Vector3DI v2) {
    Vector3DI o = Vector3DI();
    o.X = v1.X - v2.X;
    o.Y = v1.Y - v2.Y;
    o.Z = v1.Z - v2.Z;
    return o;
}


float Vector3DI::Distance(const Vector3DI& v1, const Vector3DI& v2) {
    int32_t dx = v1.X - v2.X;
    int32_t dy = v1.Y - v2.Y;
    int32_t dz = v1.Z - v2.Z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}



Vector3DF Vector3DI::To3DF() const { return Vector3DF(X, Y, Z); }

}  // namespace Altseed
