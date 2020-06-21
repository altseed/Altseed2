#include "Vector2F.h"

#include "Vector2I.h"

namespace Altseed2 {
Vector2F::Vector2F() : X(0.0f), Y(0.0f) {}

Vector2F::Vector2F(float x, float y) : X(x), Y(y) {}

bool Vector2F::operator==(const Vector2F& right) { return X == right.X && Y == right.Y; }

bool Vector2F::operator!=(const Vector2F& right) { return X != right.X || Y != right.Y; }

bool Vector2F::operator>(const Vector2F& o) const {
    if (X != o.X) return X > o.X;
    if (Y != o.Y) return Y > o.Y;
    return false;
}

bool Vector2F::operator<(const Vector2F& o) const {
    if (X != o.X) return X < o.X;
    if (Y != o.Y) return Y < o.Y;
    return false;
}

Vector2F Vector2F::operator-() { return Vector2F(-X, -Y); }

Vector2F Vector2F::operator+(const Vector2F& right) const { return Vector2F(X + right.X, Y + right.Y); }

Vector2F Vector2F::operator-(const Vector2F& right) const { return Vector2F(X - right.X, Y - right.Y); }

Vector2F Vector2F::operator*(const Vector2F& right) const { return Vector2F(X * right.X, Y * right.Y); }

Vector2F Vector2F::operator/(const Vector2F& right) const { return Vector2F(X / right.X, Y / right.Y); }

Vector2F Vector2F::operator*(float right) const { return Vector2F(X * right, Y * right); }

Vector2F Vector2F::operator/(float right) const { return Vector2F(X / right, Y / right); }

Vector2F& Vector2F::operator+=(const Vector2F& right) {
    X += right.X;
    Y += right.Y;
    return *this;
}

Vector2F& Vector2F::operator-=(const Vector2F& right) {
    X -= right.X;
    Y -= right.Y;
    return *this;
}

Vector2F& Vector2F::operator*=(const Vector2F& right) {
    X *= right.X;
    Y *= right.Y;
    return *this;
}

Vector2F& Vector2F::operator/=(const Vector2F& right) {
    X /= right.X;
    Y /= right.Y;
    return *this;
}

Vector2F& Vector2F::operator*=(float right) {
    X *= right;
    Y *= right;
    return *this;
}

Vector2F& Vector2F::operator/=(float right) {
    X /= right;
    Y /= right;
    return *this;
}

Vector2I Vector2F::To2I() const { return Vector2I((int32_t)X, (int32_t)Y); }

Vector2F::operator Vector2F_C() const { return Vector2F_C{X, Y}; }

Vector2F_C::operator Vector2F() const { return Vector2F(X, Y); }

}  // namespace Altseed2
