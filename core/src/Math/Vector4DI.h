#pragma once

#include "MathTemplate.h"
#include "Vector4DF.h"

namespace altseed {
struct Vector4DI {
public:
    int32_t X;
    int32_t Y;
    int32_t Z;
    int32_t W;

    Vector4DI();
    Vector4DI(int32_t x, int32_t y, int32_t z, int32_t w);

    float GetLength() const { return sqrt(GetSquaredLength()); }

    int32_t GetSquaredLength() const { return X * X + Y * Y + Z * Z + W * W; }

    bool operator==(const Vector4DI& o);
    bool operator!=(const Vector4DI& o);

    Vector4DI operator-();
    Vector4DI operator+(const Vector4DI& o) const;
    Vector4DI operator-(const Vector4DI& o) const;
    Vector4DI operator*(const Vector4DI& o) const;
    Vector4DI operator/(const Vector4DI& o) const;
    Vector4DI operator*(const int32_t& o) const;
    Vector4DI operator/(const int32_t& o) const;
    Vector4DI& operator+=(const Vector4DI& o);
    Vector4DI& operator-=(const Vector4DI& o);
    Vector4DI& operator*=(const Vector4DI& o);
    Vector4DI& operator/=(const Vector4DI& o);
    Vector4DI& operator*=(const int32_t& o);
    Vector4DI& operator/=(const int32_t& o);

    static int32_t Dot(const Vector4DI& v1, const Vector4DI& v2);
    static float Distance(const Vector4DI& v1, const Vector4DI& v2);
    Vector4DF To4DF() const;
};
}  // namespace altseed