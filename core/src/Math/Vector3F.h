#pragma once

#include "MathTemplate.h"
#include "Vector3I.h"

namespace Altseed {

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
    static Vector3F Add(Vector3F v1, Vector3F v2) { return Vector3F(v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z); }
    static Vector3F Subtract(Vector3F v1, Vector3F v2);
    static Vector3F Divide(const Vector3F& v1, const Vector3F& v2) { return Vector3F(v1.X / v2.X, v1.Y / v2.Y, v1.Z / v2.Z); }
    static Vector3F DivideByScalar(const Vector3F& v1, float v2) { return Vector3F(v1.X / v2, v1.Y / v2, v1.Z / v2); }
    static float Distance(const Vector3F& v1, const Vector3F& v2);

    Vector3I To3DI() const;
};
}  // namespace Altseed