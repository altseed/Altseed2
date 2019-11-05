#pragma once

#include "MathTemplate.h"

namespace altseed {

struct Vector2DI {
public:
    int32_t X;

    int32_t Y;

    Vector2DI();

    Vector2DI(int32_t x, int32_t y);

    bool operator==(const Vector2DI& o);

    bool operator!=(const Vector2DI& o);

    Vector2DI operator-();

    Vector2DI operator+(const Vector2DI& right);

    Vector2DI operator-(const Vector2DI& right);

    Vector2DI operator*(const Vector2DI& right);

    Vector2DI operator/(const Vector2DI& right);

    Vector2DI operator*(int32_t right);

    Vector2DI operator/(int32_t right);

    Vector2DI& operator+=(const Vector2DI& right);

    Vector2DI& operator-=(const Vector2DI& right);

    Vector2DI& operator*=(const Vector2DI& right);

    Vector2DI& operator/=(const Vector2DI& right);

    Vector2DI& operator*=(int32_t right);

    Vector2DI& operator/=(int32_t right);
    Vector2DF To2DF() const;

    static Vector2DI DivideByScalar(const Vector2DI& v1, float v2);
};
}  // namespace altseed