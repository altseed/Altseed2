#pragma once

#include "MathTemplate.h"
#include "Vector4F.h"

namespace Altseed {

struct Vector4I_C;

struct Vector4I {
public:
    int32_t X;
    int32_t Y;
    int32_t Z;
    int32_t W;

    Vector4I();
    Vector4I(int32_t x, int32_t y, int32_t z, int32_t w);

    float GetLength() const { return sqrt(GetSquaredLength()); }

    int32_t GetSquaredLength() const { return X * X + Y * Y + Z * Z + W * W; }

    bool operator==(const Vector4I& o);
    bool operator!=(const Vector4I& o);

    Vector4I operator-();
    Vector4I operator+(const Vector4I& o) const;
    Vector4I operator-(const Vector4I& o) const;
    Vector4I operator*(const Vector4I& o) const;
    Vector4I operator/(const Vector4I& o) const;
    Vector4I operator*(const int32_t& o) const;
    Vector4I operator/(const int32_t& o) const;
    Vector4I& operator+=(const Vector4I& o);
    Vector4I& operator-=(const Vector4I& o);
    Vector4I& operator*=(const Vector4I& o);
    Vector4I& operator/=(const Vector4I& o);
    Vector4I& operator*=(const int32_t& o);
    Vector4I& operator/=(const int32_t& o);

    static int32_t Dot(const Vector4I& v1, const Vector4I& v2);
    static float Distance(const Vector4I& v1, const Vector4I& v2);

    Vector4F To4F() const;
    operator Vector4I_C() const;
};

struct Vector4I_C {
public:
    int32_t X;
    int32_t Y;
    int32_t Z;
    int32_t W;

    operator Vector4I() const;
};

}  // namespace Altseed