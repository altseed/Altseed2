#pragma once

#include "MathTemplate.h"
#include "Vector4I.h"

namespace Altseed2 {

struct Vector4F_C;

struct Vector4F {
public:
    float X;
    float Y;
    float Z;
    float W;

    Vector4F();
    Vector4F(float x, float y, float z, float w);

    float GetLength() const { return sqrt(GetSquaredLength()); }
    float GetSquaredLength() const { return X * X + Y * Y + Z * Z + W * W; }
    void SetLength(float value) {
        float length = GetLength();
        (*this) *= (value / length);
    }

    Vector4F GetNormal() {
        float length = GetLength();
        return Vector4F(X / length, Y / length, Z / length, W / length);
    }
    void Normalize() {
        float length = GetLength();
        (*this) /= length;
    }

    bool operator==(const Vector4F& o);
    bool operator!=(const Vector4F& o);

    Vector4F operator-();
    Vector4F operator+(const Vector4F& o) const;
    Vector4F operator-(const Vector4F& o) const;
    Vector4F operator*(const Vector4F& o) const;
    Vector4F operator/(const Vector4F& o) const;
    Vector4F operator*(const float& o) const;
    Vector4F operator/(const float& o) const;
    Vector4F& operator+=(const Vector4F& o);
    Vector4F& operator-=(const Vector4F& o);
    Vector4F& operator*=(const Vector4F& o);
    Vector4F& operator/=(const Vector4F& o);
    Vector4F& operator*=(const float& o);
    Vector4F& operator/=(const float& o);

    static float Dot(const Vector4F& v1, const Vector4F& v2);
    static float Distance(const Vector4F& v1, const Vector4F& v2);

    Vector4I To4I() const;

    operator Vector4F_C() const;
};

struct Vector4F_C {
public:
    float X;
    float Y;
    float Z;
    float W;

    operator Vector4F() const;
};
}  // namespace Altseed2