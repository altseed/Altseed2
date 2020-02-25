#include "Vector2I.h"

#include "Vector2F.h"

namespace Altseed {
Vector2I::Vector2I() : X(0), Y(0) {}

Vector2I::Vector2I(int32_t x, int32_t y) : X(x), Y(y) {}

bool Vector2I::operator==(const Vector2I& right) { return X == right.X && Y == right.Y; }

bool Vector2I::operator!=(const Vector2I& right) { return X != right.X || Y != right.Y; }

Vector2I Vector2I::operator-() { return Vector2I(-X, -Y); }

Vector2I Vector2I::operator+(const Vector2I& right) { return Vector2I(X + right.X, Y + right.Y); }

Vector2I Vector2I::operator-(const Vector2I& right) { return Vector2I(X - right.X, Y - right.Y); }

Vector2I Vector2I::operator*(const Vector2I& right) { return Vector2I(X * right.X, Y * right.Y); }

Vector2I Vector2I::operator/(const Vector2I& right) { return Vector2I(X / right.X, Y / right.Y); }

Vector2I Vector2I::operator*(int32_t right) { return Vector2I(X * right, Y * right); }

Vector2I Vector2I::operator/(int32_t right) { return Vector2I(X / right, Y / right); }

Vector2I& Vector2I::operator+=(const Vector2I& right) {
    X += right.X;
    Y += right.Y;
    return *this;
}

Vector2I& Vector2I::operator-=(const Vector2I& right) {
    X -= right.X;
    Y -= right.Y;
    return *this;
}

Vector2I& Vector2I::operator*=(const Vector2I& right) {
    X *= right.X;
    Y *= right.Y;
    return *this;
}

Vector2I& Vector2I::operator/=(const Vector2I& right) {
    X /= right.X;
    Y /= right.Y;
    return *this;
}

Vector2I& Vector2I::operator*=(int32_t right) {
    X *= right;
    Y *= right;
    return *this;
}

Vector2I& Vector2I::operator/=(int32_t right) {
    X /= right;
    Y /= right;
    return *this;
}
Vector2F Vector2I::To2F() const { return Vector2F(X, Y); }

Vector2I::operator Vector2I_C() const { return Vector2I_C{X, Y}; }

Vector2I_C::operator Vector2I() const { return Vector2I(X, Y); }
}  // namespace Altseed
