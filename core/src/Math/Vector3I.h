#pragma once

#include "MathTemplate.h"
#include "Vector3F.h"

namespace Altseed {

struct Vector3I_C;

struct Vector3I {
public:
    int32_t X;

    int32_t Y;

    int32_t Z;

    Vector3I();
    Vector3I(int32_t x, int32_t y, int32_t z);

    bool operator==(const Vector3I& o);
    bool operator!=(const Vector3I& o);
    bool operator>(const Vector3I& o) const;
    bool operator<(const Vector3I& o) const;

    Vector3I operator-();

    Vector3I operator+(const Vector3I& o) const;

    Vector3I operator-(const Vector3I& o) const;

    Vector3I operator*(const Vector3I& o) const;

    Vector3I operator/(const Vector3I& o) const;

    Vector3I operator*(const int32_t& o) const;

    Vector3I operator/(const int32_t& o) const;

    Vector3I& operator+=(const Vector3I& o);

    Vector3I& operator-=(const Vector3I& o);

    Vector3I& operator*=(const Vector3I& o);

    Vector3I& operator/=(const Vector3I& o);

    Vector3I& operator*=(const int32_t& o);

    Vector3I& operator/=(const int32_t& o);

    float GetLength() const { return sqrt(static_cast<float>(GetSquaredLength()));
    }

    int32_t GetSquaredLength() const { return X * X + Y * Y + Z * Z; }
    static int32_t Dot(const Vector3I& v1, const Vector3I& v2);
    static Vector3I Cross(const Vector3I& v1, const Vector3I& v2);
    static Vector3I Add(Vector3I v1, Vector3I v2) { return Vector3I(v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z); }
    static Vector3I Subtract(Vector3I v1, Vector3I v2) { return Vector3I(v1.X - v2.X, v1.Y - v2.Y, v1.Z - v2.Z); }
    static Vector3I Divide(const Vector3I& v1, const Vector3I& v2) { return Vector3I(v1.X / v2.X, v1.Y / v2.Y, v1.Z / v2.Z); }
    static Vector3I DivideByScalar(const Vector3I& v1, float v2) { return Vector3I(v1.X / v2, v1.Y / v2, v1.Z / v2); }
    static float Distance(const Vector3I& v1, const Vector3I& v2);

    Vector3F To3F() const;
    operator Vector3I_C() const;
};

struct Vector3I_C {
public:
    int32_t X;

    int32_t Y;

    int32_t Z;

    operator Vector3I() const;
};
}  // namespace Altseed