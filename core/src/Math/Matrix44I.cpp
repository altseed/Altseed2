

#include "Matrix44I.h"

#include "Vector3DI.h"
#include "Vector4DI.h"

namespace Altseed {

Matrix44I::Matrix44I() { SetIdentity(); }

Matrix44I& Matrix44I::SetIdentity() {
    memset(Values, 0, sizeof(int32_t) * 16);
    Values[0][0] = 1.0f;
    Values[1][1] = 1.0f;
    Values[2][2] = 1.0f;
    Values[3][3] = 1.0f;
    return *this;
}

Matrix44I& Matrix44I::SetTransposed() {
    for (int32_t c = 0; c < 4; c++) {
        for (int32_t r = c; r < 4; r++) {
            int32_t v = Values[r][c];
            Values[r][c] = Values[c][r];
            Values[c][r] = v;
        }
    }

    return *this;
}

Matrix44I& Matrix44I::SetTranslation(int32_t x, int32_t y, int32_t z) {
    SetIdentity();
    Values[0][3] = x;
    Values[1][3] = y;
    Values[2][3] = z;
    return *this;
}

Matrix44I& Matrix44I::SetQuaternion(int32_t x, int32_t y, int32_t z, int32_t w) {
    int32_t xx = x * x;
    int32_t yy = y * y;
    int32_t zz = z * z;
    int32_t xy = x * y;
    int32_t xz = x * z;
    int32_t yz = y * z;
    int32_t wx = w * x;
    int32_t wy = w * y;
    int32_t wz = w * z;

    Values[0][0] = 1.0f - 2.0f * (yy + zz);
    Values[0][1] = 2.0f * (xy - wz);
    Values[0][2] = 2.0f * (xz + wy);
    Values[0][3] = 0.0f;

    Values[1][0] = 2.0f * (xy + wz);
    Values[1][1] = 1.0f - 2.0f * (xx + zz);
    Values[1][2] = 2.0f * (yz - wx);
    Values[1][3] = 0.0f;

    Values[2][0] = 2.0f * (xz - wy);
    Values[2][1] = 2.0f * (yz + wx);
    Values[2][2] = 1.0f - 2.0f * (xx + yy);
    Values[2][3] = 0.0f;

    Values[3][0] = 0.0f;
    Values[3][1] = 0.0f;
    Values[3][2] = 0.0f;
    Values[3][3] = 1.0f;
    return *this;
}

Matrix44I& Matrix44I::SetScale(int32_t x, int32_t y, int32_t z) {
    memset(Values, 0, sizeof(int32_t) * 16);
    Values[0][0] = x;
    Values[1][1] = y;
    Values[2][2] = z;
    Values[3][3] = 1.0f;
    return *this;
}

Vector4DI Matrix44I::Transform4D(const Vector4DI& in) const {
    int32_t values[4];

    for (int i = 0; i < 4; i++) {
        values[i] = 0;
        values[i] += in.X * Values[i][0];
        values[i] += in.Y * Values[i][1];
        values[i] += in.Z * Values[i][2];
        values[i] += in.W * Values[i][3];
    }

    Vector4DI o;
    o.X = values[0];
    o.Y = values[1];
    o.Z = values[2];
    o.W = values[3];
    return o;
}

Matrix44I Matrix44I::operator*(const Matrix44I& right) const {
    Matrix44I o_;
    Mul(o_, *this, right);
    return o_;
}

Vector4DI Matrix44I::operator*(const Vector4DI& right) const { return Transform4D(right); }

Matrix44I& Matrix44I::Mul(Matrix44I& o, const Matrix44I& in1, const Matrix44I& in2) {
    Matrix44I _in1 = in1;
    Matrix44I _in2 = in2;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int32_t v = 0.0f;
            for (int k = 0; k < 4; k++) {
                v += _in1.Values[i][k] * _in2.Values[k][j];
            }
            o.Values[i][j] = v;
        }
    }
    return o;
}

}  // namespace Altseed
