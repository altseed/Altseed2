#pragma once
#include "Vector2F.h"
#include "Vector3F.h"

namespace Altseed2 {
/**
        @brief	3×3行列を表す構造体。
        @note
        [0,0][0,1]
        [1,0][1,1]
        */
struct Matrix33F_C;

struct Matrix33F {
public:
    Matrix33F();

    float Values[3][3];

    Matrix33F& SetIdentity();

    /**
    @brief	転置行列を設定する。
    @return	このインスタンスへの参照
    */
    Matrix33F& SetTransposed();

    /**
    @brief	逆行列を設定する。
    @return	このインスタンスへの参照
    */
    Matrix33F& SetInverted();

    /**
    @brief	逆行列を取得する。
    @return	逆行列
    */
    Matrix33F GetInverted();

    Matrix33F& SetTranslation(float x, float y);

    Matrix33F& SetRotation(float angle);

    Matrix33F& SetScale(float x, float y);

    /**
    @brief	行列でベクトルを変形させる。
    @param	in	変形前ベクトル
    @return	変形後ベクトル
    */
    Vector2F Transform2D(const Vector2F& in) const;

    /**
    @brief	行列でベクトルを変形させる。
    @param	in	変形前ベクトル
    @return	変形後ベクトル
    */
    Vector3F Transform3D(const Vector3F& in) const;

    Matrix33F operator*(const Matrix33F& right);

    Vector3F operator*(const Vector3F& right);

    operator Matrix33F_C() const;
};

struct Matrix33F_C {
    float Values[3][3];

    operator Matrix33F() const;
};
}  // namespace Altseed2