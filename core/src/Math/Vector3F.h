#pragma once

#include "MathTemplate.h"
#include "Vector3I.h"

namespace Altseed {

struct Vector3F_C;

struct Vector3F {
public:
    float X;

    float Y;

    float Z;

    Vector3F();
    Vector3F(float x, float y, float z);

    bool operator==(const Vector3F& o);
    bool operator!=(const Vector3F& o);
    bool operator>(const Vector3F& o) const;
    bool operator<(const Vector3F& o) const;

    Vector3F operator-();

    Vector3F operator+(const Vector3F& o) const;

    Vector3F operator-(const Vector3F& o) const;

    Vector3F operator*(const Vector3F& o) const;

    Vector3F operator/(const Vector3F& o) const;

    Vector3F operator*(const float& o) const;

    Vector3F operator/(const float& o) const;

    Vector3F& operator+=(const Vector3F& o);

    Vector3F& operator-=(const Vector3F& o);

    Vector3F& operator*=(const Vector3F& o);

    Vector3F& operator/=(const Vector3F& o);

    Vector3F& operator*=(const float& o);

    Vector3F& operator/=(const float& o);

    float GetLength() const { return sqrt(GetSquaredLength()); }

    float GetSquaredLength() const { return X * X + Y * Y + Z * Z; }

    void SetLength(float value) {
        float length = GetLength();
        (*this) *= (value / length);
    }

    Vector3F GetNormal() {
        float length = GetLength();
        return Vector3F(X / length, Y / length, Z / length);
    }

    void Normalize() {
        float length = GetLength();
        (*this) /= length;
    }

    static float Dot(const Vector3F& v1, const Vector3F& v2);
    static Vector3F Cross(const Vector3F& v1, const Vector3F& v2);

    static float Distance(const Vector3F& v1, const Vector3F& v2);

    Vector3I To3I() const;

    operator Vector3F_C() const;
};

struct Vector3F_C {
public:
    float X;

    float Y;

    float Z;

    operator Vector3F() const;
};
}  // namespace Altseed