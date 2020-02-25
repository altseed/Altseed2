#pragma once

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "MathTemplate.h"
#include "Vector4F.h"

namespace Altseed {

/**
        @brief	4×4行列を表す構造体
        @note
        M * V[x,y,z,1] の形<BR>
        [0,0][0,1][0,2][0,3]
        [1,0][1,1][1,2][1,3]
        [2,0][2,1][2,2][2,3]
        [3,0][3,1][3,2][3,3]
*/
struct Matrix44F_C;

struct Matrix44F {
private:
public:
    Matrix44F();

    float Values[4][4];

    /**
            @brief	単位行列を設定する。
            @return	このインスタンスへの参照
    */
    Matrix44F& SetIdentity();

    /**
            @brief	転置行列を設定する。
            @return	このインスタンスへの参照
    */
    Matrix44F& SetTransposed();

    /**
            @brief	逆行列を設定する。
            @return	このインスタンスへの参照
    */
    Matrix44F& SetInverted();

    /**
            @brief	逆行列を取得する。
            @return	逆行列
    */
    Matrix44F GetInverted() const;

    /**
            @brief	カメラ行列(右手系)を設定する。
            @param	eye	カメラの位置
            @param	at	カメラの注視点
            @param	up	カメラの上方向
            @return	このインスタンスへの参照
    */
    Matrix44F& SetLookAtRH(const Vector3F& eye, const Vector3F& at, const Vector3F& up);

    /**
            @brief	カメラ行列(左手系)を設定する。
            @param	eye	カメラの位置
            @param	at	カメラの注視点
            @param	up	カメラの上方向
            @return	このインスタンスへの参照
    */
    Matrix44F& SetLookAtLH(const Vector3F& eye, const Vector3F& at, const Vector3F& up);

    /**
            @brief	射影行列(右手系)を設定する。
            @param	ovY	Y方向への視野角(ラジアン)
            @param	aspect	画面のアスペクト比
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44F& SetPerspectiveFovRH(float ovY, float aspect, float zn, float zf);

    /**
            @brief	OpenGL用射影行列(右手系)を設定する。
            @param	ovY	Y方向への視野角(ラジアン)
            @param	aspect	画面のアスペクト比
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44F& SetPerspectiveFovRH_OpenGL(float ovY, float aspect, float zn, float zf);

    /**
            @brief	射影行列(左手系)を設定する。
            @param	ovY	Y方向への視野角(ラジアン)
            @param	aspect	画面のアスペクト比
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44F& SetPerspectiveFovLH(float ovY, float aspect, float zn, float zf);

    /**
            @brief	正射影行列(右手系)を設定する。
            @param	width	横幅
            @param	height	縦幅
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44F& SetOrthographicRH(float width, float height, float zn, float zf);

    /**
            @brief	正射影行列(左手系)を設定する。
            @param	width	横幅
            @param	height	縦幅
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44F& SetOrthographicLH(float width, float height, float zn, float zf);

    /**
            @brief	並行移動行列を設定する。
            @param	x	X方向移動量
            @param	y	Y方向移動量
            @param	z	Z方向移動量
            @return	このインスタンスへの参照
    */
    Matrix44F& SetTranslation(float x, float y, float z);

    /**
            @brief	X軸回転行列(右手)を設定する。
            @param	angle	X軸回転量(ラジアン)
            @return	このインスタンスへの参照
    */
    Matrix44F& SetRotationX(float angle);

    /**
            @brief	Y軸回転行列(右手)を設定する。
            @param	angle	Y軸回転量(ラジアン)
            @return	このインスタンスへの参照
    */
    Matrix44F& SetRotationY(float angle);

    /**
            @brief	Z軸回転行列(右手)を設定する。
            @param	angle	Z軸回転量(ラジアン)
            @return	このインスタンスへの参照
    */
    Matrix44F& SetRotationZ(float angle);

    /**
    @brief	任意軸の反時計回転行列(右手)を設定する。
    @param	axis	軸
    @param	angle	回転量(ラジアン)
    @return	このインスタンスへの参照
    */
    Matrix44F& SetRotationAxis(const Vector3F& axis, float angle);

    /**
    @brief	クオータニオンを元に回転行列(右手)を設定する。
    @param	x	クオータニオン
    @param	y	クオータニオン
    @param	z	クオータニオン
    @param	w	クオータニオン
    @return	このインスタンスへの参照
    */
    Matrix44F& SetQuaternion(float x, float y, float z, float w);

    /**
    @brief	拡大行列を設定する。
    @param	x	X方向拡大率
    @param	y	Y方向拡大率
    @param	z	Z方向拡大率
    @return	このインスタンスへの参照
    */
    Matrix44F& SetScale(float x, float y, float z);

    /**
    @brief	行列でベクトルを変形させる。
    @param	in	変形前ベクトル
    @return	変形後ベクトル
    */
    Vector3F Transform3D(const Vector3F& in) const;

    /**
    @brief	行列でベクトルを変形させる。
    @param	in	変形前ベクトル
    @return	変形後ベクトル
    */
    Vector4F Transform4D(const Vector4F& in) const;

    Matrix44F operator*(const Matrix44F& right) const;

    Vector3F operator*(const Vector3F& right) const;

    Vector4F operator*(const Vector4F& right) const;

    /**
            @brief	乗算を行う。
            @param	o	出力先
            @param	in1	行列1
            @param	in2	行列2
            @return	出力先の参照
    */
    static Matrix44F& Mul(Matrix44F& o, const Matrix44F& in1, const Matrix44F& in2);

    operator Matrix44F_C() const;
};

struct Matrix44F_C {
    float Values[4][4];

    operator Matrix44F() const;
};
}  // namespace Altseed
