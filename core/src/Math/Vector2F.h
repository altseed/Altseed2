#pragma once

#include "MathTemplate.h"
#include "Vector2I.h"

namespace Altseed {

struct Vector2F_C;

struct Vector2F {
public:
    float X;

    float Y;

    Vector2F();

    Vector2F(float x, float y);

    float GetLength() const { return sqrt(GetSquaredLength()); }

    float GetSquaredLength() const { return X * X + Y * Y; }

    void SetLength(float value) {
        float length = GetLength();
        (*this) *= (value / length);
    }

    Vector2F GetNormal() {
        float length = GetLength();
        return Vector2F(X / length, Y / length);
    }

    void Normalize() {
        float length = GetLength();
        (*this) /= length;
    }

    float GetRadian() const { return atan2(Y, X); }

    void SetRadian(float value) {
        float length = GetLength();
        SinCos(value, Y, X);
        X *= length;
        Y *= length;
    }

    float GetDegree() const { return RadianToDegree(atan2(Y, X)); }

    void SetDegree(float value) {
        float length = GetLength();
        SinCos(DegreeToRadian(value), Y, X);
        X *= length;
        Y *= length;
    }

    bool operator==(const Vector2F& right);

    bool operator!=(const Vector2F& right);

    bool operator>(const Vector2F& o) const;
    bool operator<(const Vector2F& o) const;

    Vector2F operator-();

    Vector2F operator+(const Vector2F& right) const;

    Vector2F operator-(const Vector2F& right) const;

    Vector2F operator*(const Vector2F& right) const;

    Vector2F operator/(const Vector2F& right) const;

    Vector2F operator*(float right) const;

    Vector2F operator/(float right) const;

    Vector2F& operator+=(const Vector2F& right);

    Vector2F& operator-=(const Vector2F& right);

    Vector2F& operator*=(const Vector2F& right);

    Vector2F& operator/=(const Vector2F& right);

    Vector2F& operator*=(float right);

    Vector2F& operator/=(float right);

    static float Dot(const Vector2F& v1, const Vector2F& v2) { return v1.X * v2.X + v1.Y * v2.Y; }

    static float Cross(const Vector2F& v1, const Vector2F& v2) { return v1.X * v2.Y - v1.Y * v2.X; }

    static float Distance(const Vector2F& v1, const Vector2F& v2) {
        float dx = v1.X - v2.X;
        float dy = v1.Y - v2.Y;
        return sqrt(dx * dx + dy * dy);
    }

    Vector2I To2I() const;

    operator Vector2F_C() const;
};

struct Vector2F_C {
    float X;
    float Y;

    operator Vector2F() const;
};

}  // namespace Altseed
