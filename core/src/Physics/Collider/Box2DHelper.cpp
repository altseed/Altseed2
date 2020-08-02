#include "Box2DHelper.h"

namespace Altseed2 {

b2Transform Box2DHelper::ToBox2D_Mat(const Matrix44F& transform) {
    b2Transform ret;
    Matrix44F rotation;
    Vector2F position;
    Vector2F scale;
    Matrix44F::CalcFromTransform2D(transform, rotation, position, scale);
    ret.p = ToBox2D_Vec(position);
    ret.q = ToBox2D_Rot(rotation);
    return ret;
}

Matrix44F Box2DHelper::ToAsd_Mat(const b2Transform& transform) {
    Matrix44F pos;
    for (int i = 0; i < 4; i++) pos.Values[i][i] = 1;
    pos.Values[0][3] = transform.p.x;
    pos.Values[1][3] = transform.p.y;
    return pos * ToAsd_Rot(transform.q);
}

b2Vec2 Box2DHelper::ToBox2D_Vec(const Vector2F& vector) { return b2Vec2(vector.X, vector.Y); }
b2Vec3 Box2DHelper::ToBox2D_Vec(const Vector3F& vector) { return b2Vec3(vector.X, vector.Y, vector.Z); }

Vector2F Box2DHelper::ToAsd_Vec(const b2Vec2& vector) { return Vector2F(vector.x, vector.y); }
Vector3F Box2DHelper::ToAsd_Vec(const b2Vec3& vector) { return Vector3F(vector.x, vector.y, vector.z); }

b2Rot Box2DHelper::ToBox2D_Rot(const Matrix44F& rotation) {
    b2Rot ret;
    ret.c = rotation.Values[0][0];
    ret.s = rotation.Values[1][0];
    return ret;
}

Matrix44F Box2DHelper::ToAsd_Rot(const b2Rot& rotation) {
    Matrix44F ret;
    for (int i = 0; i < 4; i++) ret.Values[i][i] = 1;
    ret.Values[0][0] = rotation.c;
    ret.Values[1][0] = rotation.s;
    ret.Values[0][1] = -rotation.s;
    ret.Values[1][1] = rotation.c;
    return ret;
}

}  // namespace Altseed2