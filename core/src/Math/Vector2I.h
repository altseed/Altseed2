#pragma once

#include "MathTemplate.h"

namespace Altseed {

struct Vector2I {
public:
    int32_t X;

    int32_t Y;

    Vector2I();

    Vector2I(int32_t x, int32_t y);

    bool operator==(const Vector2I& o);

    bool operator!=(const Vector2I& o);

    Vector2I operator-();

    Vector2I operator+(const Vector2I& right);

    Vector2I operator-(const Vector2I& right);

    Vector2I operator*(const Vector2I& right);

    Vector2I operator/(const Vector2I& right);

    Vector2I operator*(int32_t right);

    Vector2I operator/(int32_t right);

    Vector2I& operator+=(const Vector2I& right);

    Vector2I& operator-=(const Vector2I& right);

    Vector2I& operator*=(const Vector2I& right);

    Vector2I& operator/=(const Vector2I& right);

    Vector2I& operator*=(int32_t right);

    Vector2I& operator/=(int32_t right);
    Vector2F To2DF() const;

    static Vector2I DivideByScalar(const Vector2I& v1, float v2);
};
}  // namespace Altseed