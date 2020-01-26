#pragma once

#include "MathTemplate.h"
#include "Vector3DI.h"

namespace Altseed {

struct Vector3DF {
public:
    float X;

    float Y;

    float Z;

    Vector3DF();
    Vector3DF(float x, float y, float z);

    bool operator==(const Vector3DF& o);
    bool operator!=(const Vector3DF& o);
    bool operator>(const Vector3DF& o) const;
    bool operator<(const Vector3DF& o) const;

    Vector3DF operator-();

    Vector3DF operator+(const Vector3DF& o) const;

    Vector3DF operator-(const Vector3DF& o) const;

    Vector3DF operator*(const Vector3DF& o) const;

    Vector3DF operator/(const Vector3DF& o) const;

    Vector3DF operator*(const float& o) const;

    Vector3DF operator/(const float& o) const;

    Vector3DF& operator+=(const Vector3DF& o);

    Vector3DF& operator-=(const Vector3DF& o);

    Vector3DF& operator*=(const Vector3DF& o);

    Vector3DF& operator/=(const Vector3DF& o);

    Vector3DF& operator*=(const float& o);

    Vector3DF& operator/=(const float& o);

    float GetLength() const { return sqrt(GetSquaredLength()); }

    float GetSquaredLength() const { return X * X + Y * Y + Z * Z; }

    void SetLength(float value) {
        float length = GetLength();
        (*this) *= (value / length);
    }

    Vector3DF GetNormal() {
        float length = GetLength();
        return Vector3DF(X / length, Y / length, Z / length);
    }

    void Normalize() {
        float length = GetLength();
        (*this) /= length;
    }

    static float Dot(const Vector3DF& v1, const Vector3DF& v2);
    static Vector3DF Cross(const Vector3DF& v1, const Vector3DF& v2);
    static Vector3DF Add(Vector3DF v1, Vector3DF v2) { return Vector3DF(v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z); }
    static Vector3DF Subtract(Vector3DF v1, Vector3DF v2);
    static Vector3DF Divide(const Vector3DF& v1, const Vector3DF& v2) { return Vector3DF(v1.X / v2.X, v1.Y / v2.Y, v1.Z / v2.Z); }
    static Vector3DF DivideByScalar(const Vector3DF& v1, float v2) { return Vector3DF(v1.X / v2, v1.Y / v2, v1.Z / v2); }
    static float Distance(const Vector3DF& v1, const Vector3DF& v2);

    Vector3DI To3DI() const;
};
}  // namespace Altseed