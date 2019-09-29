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
    /**
            @brief	オブジェクトを生成し、単位行列で初期化する。
    */
    Matrix33F();

    /**
            @brief	行列の値
    */
    float Values[3][3];

    /**
            @brief	単位行列を設定する。
    */
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

    /**
            @brief	平行移動の行列を設定する。
	*/
    Matrix33F& SetTranslation(float x, float y);

    /**
    @brief	回転行列を設定する。
    */
    Matrix33F& SetRotation(float angle);

    /**
            @brief	拡大・縮小行列を設定する。
    */
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

    /**
    @brief	3×3行列の掛け算を計算する。
            */
    Matrix33F operator*(const Matrix33F& right);

    Vector3DF operator*(const Vector3DF& right);
};
}  // namespace asd