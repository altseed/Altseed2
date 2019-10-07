#pragma once
#include "Vector2DF.h"
#include "Vector3DF.h"

namespace altseed {
/**
        @brief	3×3行列を表す構造体。
        @note
        [0,0][0,1]
        [1,0][1,1]
        */
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
    Vector2DF Transform2D(const Vector2DF& in) const;

    /**
    @brief	行列でベクトルを変形させる。
    @param	in	変形前ベクトル
    @return	変形後ベクトル
    */
    Vector3DF Transform3D(const Vector3DF& in) const;


    Matrix33F operator*(const Matrix33F& right);

    Vector3DF operator*(const Vector3DF& right);
};
}  // namespace asd