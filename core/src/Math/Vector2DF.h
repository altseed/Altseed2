#pragma once

#include "MathTemplate.h"
#include "Vector2DI.h"

namespace altseed {

struct Vector2DF {
public:
    float X;

    float Y;

    Vector2DF();

    Vector2DF(float x, float y);

    float GetLength() const { return sqrt(GetSquaredLength()); }

    float GetSquaredLength() const { return X * X + Y * Y; }

    void SetLength(float value) {
        float length = GetLength();
        (*this) *= (value / length);
    }

    Vector2DF GetNormal() {
        float length = GetLength();
        return Vector2DF(X / length, Y / length);
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

    bool operator==(const Vector2DF& right);

    bool operator!=(const Vector2DF& right);

    bool operator>(const Vector2DF& o) const;
    bool operator<(const Vector2DF& o) const;

    Vector2DF operator-();

    Vector2DF operator+(const Vector2DF& right) const;

    Vector2DF operator-(const Vector2DF& right) const;

    Vector2DF operator*(const Vector2DF& right) const;

    Vector2DF operator/(const Vector2DF& right) const;

    Vector2DF operator*(float right) const;

    Vector2DF operator/(float right) const;

    Vector2DF& operator+=(const Vector2DF& right);

    Vector2DF& operator-=(const Vector2DF& right);

    Vector2DF& operator*=(const Vector2DF& right);

    Vector2DF& operator/=(const Vector2DF& right);

    Vector2DF& operator*=(float right);

    Vector2DF& operator/=(float right);

    static float Dot(const Vector2DF& v1, const Vector2DF& v2) { return v1.X * v2.X + v1.Y * v2.Y; }

    static float Cross(const Vector2DF& v1, const Vector2DF& v2) { return v1.X * v2.Y - v1.Y * v2.X; }

    static float Distance(const Vector2DF& v1, const Vector2DF& v2) {
        float dx = v1.X - v2.X;
        float dy = v1.Y - v2.Y;
        return sqrt(dx * dx + dy * dy);
    }

    static Vector2DF Add(Vector2DF v1, Vector2DF v2) { return Vector2DF(v1.X + v2.X, v1.Y + v2.Y); }

    static Vector2DF Subtract(Vector2DF v1, Vector2DF v2) { return Vector2DF(v1.X - v2.X, v1.Y - v2.Y); }

    static Vector2DF Divide(const Vector2DF& v1, const Vector2DF& v2) { return Vector2DF(v1.X / v2.X, v1.Y / v2.Y); }

    static Vector2DF DivideByScalar(const Vector2DF& v1, float v2) { return Vector2DF(v1.X / v2, v1.Y / v2); }

    Vector2DI To2DI() const;
};

}  // namespace altseed
