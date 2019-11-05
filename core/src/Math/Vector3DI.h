#pragma once

#include "MathTemplate.h"
#include "Vector3DF.h"

namespace altseed {

struct Vector3DI {
public:
    int32_t X;

    int32_t Y;

    int32_t Z;

    Vector3DI();
    Vector3DI(int32_t x, int32_t y, int32_t z);

    bool operator==(const Vector3DI& o);
    bool operator!=(const Vector3DI& o);
    bool operator>(const Vector3DI& o) const;
    bool operator<(const Vector3DI& o) const;

    Vector3DI operator-();

    Vector3DI operator+(const Vector3DI& o) const;

    Vector3DI operator-(const Vector3DI& o) const;

    Vector3DI operator*(const Vector3DI& o) const;

    Vector3DI operator/(const Vector3DI& o) const;

    Vector3DI operator*(const int32_t& o) const;

    Vector3DI operator/(const int32_t& o) const;

    Vector3DI& operator+=(const Vector3DI& o);

    Vector3DI& operator-=(const Vector3DI& o);

    Vector3DI& operator*=(const Vector3DI& o);

    Vector3DI& operator/=(const Vector3DI& o);

    Vector3DI& operator*=(const int32_t& o);

    Vector3DI& operator/=(const int32_t& o);

    float GetLength() const { return sqrt(GetSquaredLength()); }

    int32_t GetSquaredLength() const { return X * X + Y * Y + Z * Z; }
    static int32_t Dot(const Vector3DI& v1, const Vector3DI& v2);
    static Vector3DI Cross(const Vector3DI& v1, const Vector3DI& v2);
    static Vector3DI Add(Vector3DI v1, Vector3DI v2) { return Vector3DI(v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z); }
    static Vector3DI Subtract(Vector3DI v1, Vector3DI v2);
    static Vector3DI Divide(const Vector3DI& v1, const Vector3DI& v2) { return Vector3DI(v1.X / v2.X, v1.Y / v2.Y, v1.Z / v2.Z); }
    static Vector3DI DivideByScalar(const Vector3DI& v1, float v2) { return Vector3DI(v1.X / v2, v1.Y / v2, v1.Z / v2); }
    static float Distance(const Vector3DI& v1, const Vector3DI& v2);

    Vector3DF To3DF() const;
};
}  // namespace altseed