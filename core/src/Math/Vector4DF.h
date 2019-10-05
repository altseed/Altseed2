#pragma once

#include "MathTemplate.h"
#include "Vector4DI.h"

namespace altseed {

struct Vector4DF {
public:
    float X;
    float Y;
    float Z;
    float W;

    Vector4DF();
    Vector4DF(float x, float y, float z, float w);

    float GetLength() const { return sqrt(GetSquaredLength()); }
    float GetSquaredLength() const { return X * X + Y * Y + Z * Z + W * W; }
    void SetLength(float value) {
        float length = GetLength();
        (*this) *= (value / length);
    }

    Vector4DF GetNormal() {
        float length = GetLength();
        return Vector4DF(X / length, Y / length, Z / length, W / length);
    }
    void Normalize() {
        float length = GetLength();
        (*this) /= length;
    }

    bool operator==(const Vector4DF& o);
    bool operator!=(const Vector4DF& o);

    Vector4DF operator-();
    Vector4DF operator+(const Vector4DF& o) const;
    Vector4DF operator-(const Vector4DF& o) const;
    Vector4DF operator*(const Vector4DF& o) const;
    Vector4DF operator/(const Vector4DF& o) const;
    Vector4DF operator*(const float& o) const;
    Vector4DF operator/(const float& o) const;
    Vector4DF& operator+=(const Vector4DF& o);
    Vector4DF& operator-=(const Vector4DF& o);
    Vector4DF& operator*=(const Vector4DF& o);
    Vector4DF& operator/=(const Vector4DF& o);
    Vector4DF& operator*=(const float& o);
    Vector4DF& operator/=(const float& o);

    static float Dot(const Vector4DF& v1, const Vector4DF& v2);
    static float Distance(const Vector4DF& v1, const Vector4DF& v2);

    Vector4DI To4DI() const;
};
}  // namespace altseed