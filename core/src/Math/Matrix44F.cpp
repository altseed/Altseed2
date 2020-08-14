

#include "Matrix44F.h"

#include <box2d/box2d.h>

#include "Vector2F.h"
#include "Vector3F.h"
#include "Vector4F.h"

namespace Altseed2 {

Matrix44F::Matrix44F() { SetIdentity(); }

Matrix44F& Matrix44F::SetIdentity() {
    memset(Values, 0, sizeof(float) * 16);
    Values[0][0] = 1.0f;
    Values[1][1] = 1.0f;
    Values[2][2] = 1.0f;
    Values[3][3] = 1.0f;
    return *this;
}

Matrix44F& Matrix44F::SetTransposed() {
    for (int32_t c = 0; c < 4; c++) {
        for (int32_t r = c; r < 4; r++) {
            float v = Values[r][c];
            Values[r][c] = Values[c][r];
            Values[c][r] = v;
        }
    }

    return *this;
}

Matrix44F& Matrix44F::SetInverted() {
    auto e = 0.00001f;

    float a11 = this->Values[0][0];
    float a12 = this->Values[0][1];
    float a13 = this->Values[0][2];
    float a14 = this->Values[0][3];
    float a21 = this->Values[1][0];
    float a22 = this->Values[1][1];
    float a23 = this->Values[1][2];
    float a24 = this->Values[1][3];
    float a31 = this->Values[2][0];
    float a32 = this->Values[2][1];
    float a33 = this->Values[2][2];
    float a34 = this->Values[2][3];
    float a41 = this->Values[3][0];
    float a42 = this->Values[3][1];
    float a43 = this->Values[3][2];
    float a44 = this->Values[3][3];

    /* �s�񎮂̌v�Z */
    float b11 = +a22 * (a33 * a44 - a43 * a34) - a23 * (a32 * a44 - a42 * a34) + a24 * (a32 * a43 - a42 * a33);
    float b12 = -a12 * (a33 * a44 - a43 * a34) + a13 * (a32 * a44 - a42 * a34) - a14 * (a32 * a43 - a42 * a33);
    float b13 = +a12 * (a23 * a44 - a43 * a24) - a13 * (a22 * a44 - a42 * a24) + a14 * (a22 * a43 - a42 * a23);
    float b14 = -a12 * (a23 * a34 - a33 * a24) + a13 * (a22 * a34 - a32 * a24) - a14 * (a22 * a33 - a32 * a23);

    float b21 = -a21 * (a33 * a44 - a43 * a34) + a23 * (a31 * a44 - a41 * a34) - a24 * (a31 * a43 - a41 * a33);
    float b22 = +a11 * (a33 * a44 - a43 * a34) - a13 * (a31 * a44 - a41 * a34) + a14 * (a31 * a43 - a41 * a33);
    float b23 = -a11 * (a23 * a44 - a43 * a24) + a13 * (a21 * a44 - a41 * a24) - a14 * (a21 * a43 - a41 * a23);
    float b24 = +a11 * (a23 * a34 - a33 * a24) - a13 * (a21 * a34 - a31 * a24) + a14 * (a21 * a33 - a31 * a23);

    float b31 = +a21 * (a32 * a44 - a42 * a34) - a22 * (a31 * a44 - a41 * a34) + a24 * (a31 * a42 - a41 * a32);
    float b32 = -a11 * (a32 * a44 - a42 * a34) + a12 * (a31 * a44 - a41 * a34) - a14 * (a31 * a42 - a41 * a32);
    float b33 = +a11 * (a22 * a44 - a42 * a24) - a12 * (a21 * a44 - a41 * a24) + a14 * (a21 * a42 - a41 * a22);
    float b34 = -a11 * (a22 * a34 - a32 * a24) + a12 * (a21 * a34 - a31 * a24) - a14 * (a21 * a32 - a31 * a22);

    float b41 = -a21 * (a32 * a43 - a42 * a33) + a22 * (a31 * a43 - a41 * a33) - a23 * (a31 * a42 - a41 * a32);
    float b42 = +a11 * (a32 * a43 - a42 * a33) - a12 * (a31 * a43 - a41 * a33) + a13 * (a31 * a42 - a41 * a32);
    float b43 = -a11 * (a22 * a43 - a42 * a23) + a12 * (a21 * a43 - a41 * a23) - a13 * (a21 * a42 - a41 * a22);
    float b44 = +a11 * (a22 * a33 - a32 * a23) - a12 * (a21 * a33 - a31 * a23) + a13 * (a21 * a32 - a31 * a22);

    // �s�񎮂̋t����������
    float Det = (a11 * b11) + (a12 * b21) + (a13 * b31) + (a14 * b41);
    if ((-e <= Det) && (Det <= +e)) {
        return *this;
    }

    float InvDet = 1.0f / Det;

    Values[0][0] = b11 * InvDet;
    Values[0][1] = b12 * InvDet;
    Values[0][2] = b13 * InvDet;
    Values[0][3] = b14 * InvDet;
    Values[1][0] = b21 * InvDet;
    Values[1][1] = b22 * InvDet;
    Values[1][2] = b23 * InvDet;
    Values[1][3] = b24 * InvDet;
    Values[2][0] = b31 * InvDet;
    Values[2][1] = b32 * InvDet;
    Values[2][2] = b33 * InvDet;
    Values[2][3] = b34 * InvDet;
    Values[3][0] = b41 * InvDet;
    Values[3][1] = b42 * InvDet;
    Values[3][2] = b43 * InvDet;
    Values[3][3] = b44 * InvDet;

    return *this;
}

Matrix44F Matrix44F::GetInverted() const {
    Matrix44F o = (*this);
    o.SetInverted();
    return o;
}

Matrix44F& Matrix44F::SetLookAtRH(const Vector3F& eye, const Vector3F& at, const Vector3F& up) {
    // F=���ʁAR=�E�����AU=�����
    Vector3F F = (eye - at).GetNormal();
    Vector3F R = Vector3F::Cross(up, F).GetNormal();
    Vector3F U = Vector3F::Cross(F, R).GetNormal();

    Values[0][0] = R.X;
    Values[0][1] = R.Y;
    Values[0][2] = R.Z;
    Values[0][3] = 0.0f;

    Values[1][0] = U.X;
    Values[1][1] = U.Y;
    Values[1][2] = U.Z;
    Values[1][3] = 0.0f;

    Values[2][0] = F.X;
    Values[2][1] = F.Y;
    Values[2][2] = F.Z;
    Values[2][3] = 0.0f;

    Values[0][3] = -Vector3F::Dot(R, eye);
    Values[1][3] = -Vector3F::Dot(U, eye);
    Values[2][3] = -Vector3F::Dot(F, eye);
    Values[3][3] = 1.0f;
    return *this;
}

Matrix44F& Matrix44F::SetLookAtLH(const Vector3F& eye, const Vector3F& at, const Vector3F& up) {
    // F=���ʁAR=�E�����AU=�����
    Vector3F F = (at - eye).GetNormal();
    Vector3F R = Vector3F::Cross(up, F).GetNormal();
    Vector3F U = Vector3F::Cross(F, R).GetNormal();

    Values[0][0] = R.X;
    Values[0][1] = R.Y;
    Values[0][2] = R.Z;
    Values[0][3] = 0.0f;

    Values[1][0] = U.X;
    Values[1][1] = U.Y;
    Values[1][2] = U.Z;
    Values[1][3] = 0.0f;

    Values[2][0] = F.X;
    Values[2][1] = F.Y;
    Values[2][2] = F.Z;
    Values[2][3] = 0.0f;

    Values[0][3] = -Vector3F::Dot(R, eye);
    Values[1][3] = -Vector3F::Dot(U, eye);
    Values[2][3] = -Vector3F::Dot(F, eye);
    Values[3][3] = 1.0f;
    return *this;
}

Matrix44F& Matrix44F::SetPerspectiveFovRH(float ovY, float aspect, float zn, float zf) {
    float yScale = 1 / tanf(ovY / 2);
    float xScale = yScale / aspect;

    Values[0][0] = xScale;
    Values[1][0] = 0;
    Values[2][0] = 0;
    Values[3][0] = 0;

    Values[0][1] = 0;
    Values[1][1] = yScale;
    Values[2][1] = 0;
    Values[3][1] = 0;

    Values[0][2] = 0;
    Values[1][2] = 0;
    Values[2][2] = zf / (zn - zf);
    Values[3][2] = -1;

    Values[0][3] = 0;
    Values[1][3] = 0;
    Values[2][3] = zn * zf / (zn - zf);
    Values[3][3] = 0;
    return *this;
}

Matrix44F& Matrix44F::SetPerspectiveFovRH_OpenGL(float ovY, float aspect, float zn, float zf) {
    float yScale = 1 / tanf(ovY / 2);
    float xScale = yScale / aspect;
    float dz = zf - zn;

    Values[0][0] = xScale;
    Values[1][0] = 0;
    Values[2][0] = 0;
    Values[3][0] = 0;

    Values[0][1] = 0;
    Values[1][1] = yScale;
    Values[2][1] = 0;
    Values[3][1] = 0;

    Values[0][2] = 0;
    Values[1][2] = 0;
    Values[2][2] = -(zf + zn) / dz;
    Values[3][2] = -1.0f;

    Values[0][3] = 0;
    Values[1][3] = 0;
    Values[2][3] = -2.0f * zn * zf / dz;
    Values[3][3] = 0.0f;

    return *this;
}

Matrix44F& Matrix44F::SetPerspectiveFovLH(float ovY, float aspect, float zn, float zf) {
    float yScale = 1 / tanf(ovY / 2);
    float xScale = yScale / aspect;

    Values[0][0] = xScale;
    Values[1][0] = 0;
    Values[2][0] = 0;
    Values[3][0] = 0;

    Values[0][1] = 0;
    Values[1][1] = yScale;
    Values[2][1] = 0;
    Values[3][1] = 0;

    Values[0][2] = 0;
    Values[1][2] = 0;
    Values[2][2] = zf / (zf - zn);
    Values[3][2] = 1;

    Values[0][3] = 0;
    Values[1][3] = 0;
    Values[2][3] = -zn * zf / (zf - zn);
    Values[3][3] = 0;
    return *this;
}

Matrix44F& Matrix44F::SetOrthographicRH(float width, float height, float zn, float zf) {
    Values[0][0] = 2 / width;
    Values[1][0] = 0;
    Values[2][0] = 0;
    Values[3][0] = 0;

    Values[0][1] = 0;
    Values[1][1] = 2 / height;
    Values[2][1] = 0;
    Values[3][1] = 0;

    Values[0][2] = 0;
    Values[1][2] = 0;
    Values[2][2] = 1 / (zn - zf);
    Values[3][2] = 0;

    Values[0][3] = 0;
    Values[1][3] = 0;
    Values[2][3] = zn / (zn - zf);
    Values[3][3] = 1;
    return *this;
}

Matrix44F& Matrix44F::SetOrthographicLH(float width, float height, float zn, float zf) {
    Values[0][0] = 2 / width;
    Values[1][0] = 0;
    Values[2][0] = 0;
    Values[3][0] = 0;

    Values[0][1] = 0;
    Values[1][1] = 2 / height;
    Values[2][1] = 0;
    Values[3][1] = 0;

    Values[0][2] = 0;
    Values[1][2] = 0;
    Values[2][2] = 1 / (zf - zn);
    Values[3][2] = 0;

    Values[0][3] = 0;
    Values[1][3] = 0;
    Values[2][3] = zn / (zn - zf);
    Values[3][3] = 1;
    return *this;
}

Matrix44F& Matrix44F::SetTranslation(float x, float y, float z) {
    SetIdentity();
    Values[0][3] = x;
    Values[1][3] = y;
    Values[2][3] = z;
    return *this;
}

Matrix44F& Matrix44F::SetRotationX(float angle) {
    float c, s;
    SinCos(angle, s, c);

    Values[0][0] = 1.0f;
    Values[1][0] = 0.0f;
    Values[2][0] = 0.0f;
    Values[3][0] = 0.0f;

    Values[0][1] = 0.0f;
    Values[1][1] = c;
    Values[2][1] = s;
    Values[3][1] = 0.0f;

    Values[0][2] = 0.0f;
    Values[1][2] = -s;
    Values[2][2] = c;
    Values[3][2] = 0.0f;

    Values[0][3] = 0.0f;
    Values[1][3] = 0.0f;
    Values[2][3] = 0.0f;
    Values[3][3] = 1.0f;
    return *this;
}

Matrix44F& Matrix44F::SetRotationY(float angle) {
    float c, s;
    SinCos(angle, s, c);

    Values[0][0] = c;
    Values[1][0] = 0.0f;
    Values[2][0] = -s;
    Values[3][0] = 0.0f;

    Values[0][1] = 0.0f;
    Values[1][1] = 1.0f;
    Values[2][1] = 0.0f;
    Values[3][1] = 0.0f;

    Values[0][2] = s;
    Values[1][2] = 0.0f;
    Values[2][2] = c;
    Values[3][2] = 0.0f;

    Values[0][3] = 0.0f;
    Values[1][3] = 0.0f;
    Values[2][3] = 0.0f;
    Values[3][3] = 1.0f;
    return *this;
}

Matrix44F& Matrix44F::SetRotationZ(float angle) {
    float c, s;
    SinCos(angle, s, c);

    Values[0][0] = c;
    Values[1][0] = s;
    Values[2][0] = 0.0f;
    Values[3][0] = 0.0f;

    Values[0][1] = -s;
    Values[1][1] = c;
    Values[2][1] = 0.0f;
    Values[3][1] = 0.0f;

    Values[0][2] = 0.0f;
    Values[1][2] = 0.0f;
    Values[2][2] = 1;
    Values[3][2] = 0.0f;

    Values[0][3] = 0.0f;
    Values[1][3] = 0.0f;
    Values[2][3] = 0.0f;
    Values[3][3] = 1.0f;
    return *this;
}

Matrix44F& Matrix44F::SetRotationAxis(const Vector3F& axis, float angle) {
    const float c = cosf(angle);
    const float s = sinf(angle);
    const float cc = 1.0f - c;

    Values[0][0] = cc * (axis.X * axis.X) + c;
    Values[1][0] = cc * (axis.X * axis.Y) + (axis.Z * s);
    Values[2][0] = cc * (axis.Z * axis.X) - (axis.Y * s);

    Values[0][1] = cc * (axis.X * axis.Y) - (axis.Z * s);
    Values[1][1] = cc * (axis.Y * axis.Y) + c;
    Values[2][1] = cc * (axis.Y * axis.Z) + (axis.X * s);

    Values[0][2] = cc * (axis.Z * axis.X) + (axis.Y * s);
    Values[1][2] = cc * (axis.Y * axis.Z) - (axis.X * s);
    Values[2][2] = cc * (axis.Z * axis.Z) + c;

    Values[0][3] = 0.0f;
    Values[1][3] = 0.0f;
    Values[2][3] = 0.0f;
    return *this;
}

Matrix44F& Matrix44F::SetQuaternion(float x, float y, float z, float w) {
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

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

Matrix44F& Matrix44F::SetScale(float x, float y, float z) {
    memset(Values, 0, sizeof(float) * 16);
    Values[0][0] = x;
    Values[1][1] = y;
    Values[2][2] = z;
    Values[3][3] = 1.0f;
    return *this;
}

Vector3F Matrix44F::Transform3D(const Vector3F& in) const {
    float values[4];

    for (int i = 0; i < 4; i++) {
        values[i] = 0;
        values[i] += in.X * Values[i][0];
        values[i] += in.Y * Values[i][1];
        values[i] += in.Z * Values[i][2];
        values[i] += Values[i][3];
    }

    Vector3F o;
    o.X = values[0] / values[3];
    o.Y = values[1] / values[3];
    o.Z = values[2] / values[3];
    return o;
}

Vector4F Matrix44F::Transform4D(const Vector4F& in) const {
    float values[4];

    for (int i = 0; i < 4; i++) {
        values[i] = 0;
        values[i] += in.X * Values[i][0];
        values[i] += in.Y * Values[i][1];
        values[i] += in.Z * Values[i][2];
        values[i] += in.W * Values[i][3];
    }

    Vector4F o;
    o.X = values[0];
    o.Y = values[1];
    o.Z = values[2];
    o.W = values[3];
    return o;
}

Matrix44F Matrix44F::operator*(const Matrix44F& right) const {
    Matrix44F o_;
    Mul(o_, *this, right);
    return o_;
}

Vector3F Matrix44F::operator*(const Vector3F& right) const { return Transform3D(right); }

Vector4F Matrix44F::operator*(const Vector4F& right) const { return Transform4D(right); }

Matrix44F& Matrix44F::Mul(Matrix44F& o, const Matrix44F& in1, const Matrix44F& in2) {
    Matrix44F _in1 = in1;
    Matrix44F _in2 = in2;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float v = 0.0f;
            for (int k = 0; k < 4; k++) {
                v += _in1.Values[i][k] * _in2.Values[k][j];
            }
            o.Values[i][j] = v;
        }
    }
    return o;
}
Matrix44F::operator Matrix44F_C() const {
    auto m = Matrix44F_C();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m.Values[i][j] = Values[i][j];
        }
    }
    return m;
}

Matrix44F_C::operator Matrix44F() const {
    auto m = Matrix44F();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m.Values[i][j] = Values[i][j];
        }
    }
    return m;
}

void Matrix44F::CalcFromTransform2D(const Matrix44F& transform, double& radian, Vector2F& position, Vector2F& scale) {
    Matrix44F rotation;
    CalcFromTransform2D(transform, rotation, position, scale);
    radian = atan2(rotation.Values[1][0], rotation.Values[0][0]);
}

void Matrix44F::CalcFromTransform2D(const Matrix44F& transform, Matrix44F& rotation, Vector2F& position, Vector2F& scale) {
    position.X = transform.Values[0][3];
    position.Y = transform.Values[1][3];

    scale.X = sqrt(transform.Values[0][0] * transform.Values[0][0] + transform.Values[1][0] * transform.Values[1][0] + transform.Values[2][0] * transform.Values[2][0]);
    scale.Y = sqrt(transform.Values[0][1] * transform.Values[0][1] + transform.Values[1][1] * transform.Values[1][1] + transform.Values[2][1] * transform.Values[2][1]);

    Matrix44F revertScale;
    revertScale.SetScale(scale.X == 0 ? 1 : 1 / scale.X, scale.Y == 0 ? 1 : 1 / scale.Y, 1);
    rotation = transform * revertScale;
}

void Matrix44F::CalcFromTransform3D(const Matrix44F& transform, Matrix44F& rotation, Vector3F& position, Vector3F& scale) {
    position.X = transform.Values[0][3];
    position.Y = transform.Values[1][3];
    position.Z = transform.Values[2][3];

    scale.X = sqrt(transform.Values[0][0] * transform.Values[0][0] + transform.Values[1][0] * transform.Values[1][0] + transform.Values[2][0] * transform.Values[2][0]);
    scale.Y = sqrt(transform.Values[0][1] * transform.Values[0][1] + transform.Values[1][1] * transform.Values[1][1] + transform.Values[2][1] * transform.Values[2][1]);
    scale.Z = sqrt(transform.Values[0][2] * transform.Values[0][2] + transform.Values[1][2] * transform.Values[1][2] + transform.Values[2][2] * transform.Values[2][2]);

    Matrix44F revertScale;
    revertScale.SetScale(scale.X == 0 ? 1 : 1 / scale.X, scale.Y == 0 ? 1 : 1 / scale.Y, scale.Z == 0 ? 1 : 1 / scale.X);
    rotation = transform * revertScale;
}

}  // namespace Altseed2
