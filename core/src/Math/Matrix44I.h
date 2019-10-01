#pragma once

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "MathTemplate.h"
#include "Vector3DI.h"
#include "Vector4DI.h"
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace altseed {
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

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
    /**
            @brief	オブジェクトを生成し、単位行列で初期化する。
    */
    Matrix44I();

    /**
            @brief	行列の値
    */
    float Values[4][4];

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
            @brief	逆行列を設定する。
            @return	このインスタンスへの参照
    */
    Matrix44I& SetInverted();

    /**
            @brief	逆行列を取得する。
            @return	逆行列
    */
    Matrix44I GetInverted() const;

    /**
            @brief	カメラ行列(右手系)を設定する。
            @param	eye	カメラの位置
            @param	at	カメラの注視点
            @param	up	カメラの上方向
            @return	このインスタンスへの参照
    */
    Matrix44I& SetLookAtRH(const Vector3DI& eye, const Vector3DI& at, const Vector3DI& up);

    /**
            @brief	カメラ行列(左手系)を設定する。
            @param	eye	カメラの位置
            @param	at	カメラの注視点
            @param	up	カメラの上方向
            @return	このインスタンスへの参照
    */
    Matrix44I& SetLookAtLH(const Vector3DI& eye, const Vector3DI& at, const Vector3DI& up);

    /**
            @brief	射影行列(右手系)を設定する。
            @param	ovY	Y方向への視野角(ラジアン)
            @param	aspect	画面のアスペクト比
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44I& SetPerspectiveFovRH(float ovY, float aspect, float zn, float zf);

    /**
            @brief	OpenGL用射影行列(右手系)を設定する。
            @param	ovY	Y方向への視野角(ラジアン)
            @param	aspect	画面のアスペクト比
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44I& SetPerspectiveFovRH_OpenGL(float ovY, float aspect, float zn, float zf);

    /**
            @brief	射影行列(左手系)を設定する。
            @param	ovY	Y方向への視野角(ラジアン)
            @param	aspect	画面のアスペクト比
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44I& SetPerspectiveFovLH(float ovY, float aspect, float zn, float zf);

    /**
            @brief	正射影行列(右手系)を設定する。
            @param	width	横幅
            @param	height	縦幅
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44I& SetOrthographicRH(float width, float height, float zn, float zf);

    /**
            @brief	正射影行列(左手系)を設定する。
            @param	width	横幅
            @param	height	縦幅
            @param	zn	最近距離
            @param	zf	最遠距離
            @return	このインスタンスへの参照
    */
    Matrix44I& SetOrthographicLH(float width, float height, float zn, float zf);

    /**
            @brief	並行移動行列を設定する。
            @param	x	X方向移動量
            @param	y	Y方向移動量
            @param	z	Z方向移動量
            @return	このインスタンスへの参照
    */
    Matrix44I& SetTranslation(float x, float y, float z);

    /**
            @brief	X軸回転行列(右手)を設定する。
            @param	angle	X軸回転量(ラジアン)
            @return	このインスタンスへの参照
    */
    Matrix44I& SetRotationX(float angle);

    /**
            @brief	Y軸回転行列(右手)を設定する。
            @param	angle	Y軸回転量(ラジアン)
            @return	このインスタンスへの参照
    */
    Matrix44I& SetRotationY(float angle);

    /**
            @brief	Z軸回転行列(右手)を設定する。
            @param	angle	Z軸回転量(ラジアン)
            @return	このインスタンスへの参照
    */
    Matrix44I& SetRotationZ(float angle);

    /**
    @brief	任意軸の反時計回転行列(右手)を設定する。
    @param	axis	軸
    @param	angle	回転量(ラジアン)
    @return	このインスタンスへの参照
    */
    Matrix44I& SetRotationAxis(const Vector3DI& axis, float angle);

    /**
    @brief	クオータニオンを元に回転行列(右手)を設定する。
    @param	x	クオータニオン
    @param	y	クオータニオン
    @param	z	クオータニオン
    @param	w	クオータニオン
    @return	このインスタンスへの参照
    */
    Matrix44I& SetQuaternion(float x, float y, float z, float w);

    /**
    @brief	拡大行列を設定する。
    @param	x	X方向拡大率
    @param	y	Y方向拡大率
    @param	z	Z方向拡大率
    @return	このインスタンスへの参照
    */
    Matrix44I& SetScale(float x, float y, float z);

    /**
    @brief	行列でベクトルを変形させる。
    @param	in	変形前ベクトル
    @return	変形後ベクトル
    */
    Vector3DI Transform3D(const Vector3DI& in) const;

    /**
    @brief	行列でベクトルを変形させる。
    @param	in	変形前ベクトル
    @return	変形後ベクトル
    */
    Vector4DI Transform4D(const Vector4DI& in) const;

    Matrix44I operator*(const Matrix44I& right) const;

    Vector3DI operator*(const Vector3DI& right) const;

    Vector4DI operator*(const Vector4DI& right) const;

    /**
            @brief	乗算を行う。
            @param	o	出力先
            @param	in1	行列1
            @param	in2	行列2
            @return	出力先の参照
    */
    static Matrix44I& Mul(Matrix44I& o, const Matrix44I& in1, const Matrix44I& in2);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}  // namespace altseed
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------