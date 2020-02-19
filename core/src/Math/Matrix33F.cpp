﻿#include "Matrix33F.h"

namespace Altseed {
Matrix33F::Matrix33F() { SetIdentity(); }

Matrix33F& Matrix33F::SetIdentity() {
    memset(Values, 0, sizeof(float) * 9);
    Values[0][0] = 1.0f;
    Values[1][1] = 1.0f;
    Values[2][2] = 1.0f;

    return *this;
}

Matrix33F& Matrix33F::SetTransposed() {
    for (int32_t c = 0; c < 3; c++) {
        for (int32_t r = c; r < 3; r++) {
            float v = Values[r][c];
            Values[r][c] = Values[c][r];
            Values[c][r] = v;
        }
    }

    return *this;
}

Matrix33F& Matrix33F::SetInverted() {
    auto e = 0.00001f;

    float a11 = this->Values[0][0];
    float a12 = this->Values[0][1];
    float a13 = this->Values[0][2];
    float a21 = this->Values[1][0];
    float a22 = this->Values[1][1];
    float a23 = this->Values[1][2];
    float a31 = this->Values[2][0];
    float a32 = this->Values[2][1];
    float a33 = this->Values[2][2];

    /* 行列式の計算 */
    float b11 = +a22 * a33 - a23 * a32;
    float b12 = +a13 * a32 - a12 * a33;
    float b13 = +a12 * a23 - a13 * a22;

    float b21 = +a23 * a31 - a21 * a33;
    float b22 = +a11 * a33 - a13 * a31;
    float b23 = +a13 * a21 - a11 * a23;

    float b31 = +a21 * a32 - a22 * a31;
    float b32 = +a12 * a31 - a11 * a32;
    float b33 = +a11 * a22 - a12 * a21;

    // 行列式の逆数をかける
    float Det = a11 * a22 * a33 + a21 * a32 * a13 + a31 * a12 * a23 - a11 * a32 * a23 - a31 * a22 * a13 - a21 * a12 * a33;
    if ((-e <= Det) && (Det <= +e)) {
        return *this;
    }

    float InvDet = 1.0f / Det;

    Values[0][0] = b11 * InvDet;
    Values[0][1] = b12 * InvDet;
    Values[0][2] = b13 * InvDet;
    Values[1][0] = b21 * InvDet;
    Values[1][1] = b22 * InvDet;
    Values[1][2] = b23 * InvDet;
    Values[2][0] = b31 * InvDet;
    Values[2][1] = b32 * InvDet;
    Values[2][2] = b33 * InvDet;

    return *this;
}

Matrix33F Matrix33F::GetInverted() {
    Matrix33F o = (*this);
    o.SetInverted();
    return o;
}

Matrix33F& Matrix33F::SetTranslation(float x, float y) {
    SetIdentity();

    Values[0][2] = x;
    Values[1][2] = y;

    return *this;
}

Matrix33F& Matrix33F::SetRotation(float angle) {
    SetIdentity();

    float sin, cos;
    SinCos(angle, sin, cos);

    Values[0][0] = cos;
    Values[0][1] = -sin;
    Values[1][0] = sin;
    Values[1][1] = cos;

    return *this;
}

Matrix33F& Matrix33F::SetScale(float x, float y) {
    SetIdentity();

    Values[0][0] = x;
    Values[1][1] = y;
    return *this;
}

Vector2F Matrix33F::Transform2D(const Vector2F& in) const {
    float values[3];

    for (int i = 0; i < 2; i++) {
        values[i] = 0;
        values[i] += in.X * Values[i][0];
        values[i] += in.Y * Values[i][1];
        values[i] += 1.0f * Values[i][2];
    }

    Vector2F o;
    o.X = values[0];
    o.Y = values[1];
    return o;
}

Vector3F Matrix33F::Transform3D(const Vector3F& in) const {
    float values[3];

    for (int i = 0; i < 3; i++) {
        values[i] = 0;
        values[i] += in.X * Values[i][0];
        values[i] += in.Y * Values[i][1];
        values[i] += in.Z * Values[i][2];
    }

    Vector3F o;
    o.X = values[0];
    o.Y = values[1];
    o.Z = values[2];
    return o;
}

Matrix33F Matrix33F::operator*(const Matrix33F& right) {
    Matrix33F result;

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

Vector3F Matrix33F::operator*(const Vector3F& right) {
    float elements[3] = {0, 0, 0};
    float rop[3] = {right.X, right.Y, right.Z};

    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 3; ++k) {
            elements[i] += Values[i][k] * rop[k];
        }
    }

    Vector3F result;
    result.X = elements[0];
    result.Y = elements[1];
    result.Z = elements[2];

    return result;
}
}  // namespace Altseed