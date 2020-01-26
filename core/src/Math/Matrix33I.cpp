#include "Matrix33I.h"

namespace Altseed {
Matrix33I::Matrix33I() { SetIdentity(); }

Matrix33I& Matrix33I::SetIdentity() {
    memset(Values, 0, sizeof(int32_t) * 9);
    Values[0][0] = 1;
    Values[1][1] = 1;
    Values[2][2] = 1;

    return *this;
}

Matrix33I& Matrix33I::SetTransposed() {
    for (int32_t c = 0; c < 3; c++) {
        for (int32_t r = c; r < 3; r++) {
            int32_t v = Values[r][c];
            Values[r][c] = Values[c][r];
            Values[c][r] = v;
        }
    }

    return *this;
}

Matrix33I& Matrix33I::SetTranslation(int32_t x, int32_t y) {
    SetIdentity();

    Values[0][2] = x;
    Values[1][2] = y;

    return *this;
}

Matrix33I& Matrix33I::SetScale(int32_t x, int32_t y) {
    SetIdentity();

    Values[0][0] = x;
    Values[1][1] = y;
    return *this;
}

Vector2DI Matrix33I::Transform2D(const Vector2DI& in) const {
    int32_t values[3];

    for (int i = 0; i < 2; i++) {
        values[i] = 0;
        values[i] += in.X * Values[i][0];
        values[i] += in.Y * Values[i][1];
        values[i] += 1 * Values[i][2];
    }

    Vector2DI o;
    o.X = values[0];
    o.Y = values[1];
    return o;
}

Vector3DI Matrix33I::Transform3D(const Vector3DI& in) const {
    int32_t values[3];

    for (int i = 0; i < 3; i++) {
        values[i] = 0;
        values[i] += in.X * Values[i][0];
        values[i] += in.Y * Values[i][1];
        values[i] += in.Z * Values[i][2];
    }

    Vector3DI o;
    o.X = values[0];
    o.Y = values[1];
    o.Z = values[2];
    return o;
}

Matrix33I Matrix33I::operator*(const Matrix33I& right) {
    Matrix33I result;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.Values[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                result.Values[i][j] += Values[i][k] * right.Values[k][j];
            }
        }
    }

    return result;
}

Vector3DI Matrix33I::operator*(const Vector3DI& right) {
    int32_t elements[3] = {0, 0, 0};
    int32_t rop[3] = {right.X, right.Y, right.Z};

    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 3; ++k) {
            elements[i] += Values[i][k] * rop[k];
        }
    }

    Vector3DI result;
    result.X = elements[0];
    result.Y = elements[1];
    result.Z = elements[2];

    return result;
}
}  // namespace Altseed