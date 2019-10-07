#pragma once

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "MathTemplate.h"
#include "Vector4DI.h"

namespace altseed {


/**
        @brief	4×4行列を表す構造体
        @note
        M * V[x,y,z,1] の形<BR>
        [0,0][0,1][0,2][0,3]
        [1,0][1,1][1,2][1,3]
        [2,0][2,1][2,2][2,3]
        [3,0][3,1][3,2][3,3]
*/
struct Matrix44I {
private:
public:

    Matrix44I();


    int32_t Values[4][4];

    /**
            @brief	単位行列を設定する。
            @return	このインスタンスへの参照
    */
    Matrix44I& SetIdentity();

    /**
            @brief	転置行列を設定する。
            @return	このインスタンスへの参照
    */
    Matrix44I& SetTransposed();

    /**
            @brief	並行移動行列を設定する。
            @param	x	X方向移動量
            @param	y	Y方向移動量
            @param	z	Z方向移動量
            @return	このインスタンスへの参照
    */
    Matrix44I& SetTranslation(int32_t x, int32_t y, int32_t z);

    /**
    @brief	クオータニオンを元に回転行列(右手)を設定する。
    @param	x	クオータニオン
    @param	y	クオータニオン
    @param	z	クオータニオン
    @param	w	クオータニオン
    @return	このインスタンスへの参照
    */
    Matrix44I& SetQuaternion(int32_t x, int32_t y, int32_t z, int32_t w);

    /**
    @brief	拡大行列を設定する。
    @param	x	X方向拡大率
    @param	y	Y方向拡大率
    @param	z	Z方向拡大率
    @return	このインスタンスへの参照
    */
    Matrix44I& SetScale(int32_t x, int32_t y, int32_t z);

    /**
    @brief	行列でベクトルを変形させる。
    @param	in	変形前ベクトル
    @return	変形後ベクトル
    */
    Vector4DI Transform4D(const Vector4DI& in) const;

    Matrix44I operator*(const Matrix44I& right) const;

    Vector4DI operator*(const Vector4DI& right) const;

    /**
            @brief	乗算を行う。
            @param	o	出力先
            @param	in1	行列1
            @param	in2	行列2
            @return	出力先の参照z
    */
    static Matrix44I& Mul(Matrix44I& o, const Matrix44I& in1, const Matrix44I& in2);
};


}  // namespace altseed
