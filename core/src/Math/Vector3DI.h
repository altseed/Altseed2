#pragma once

#include "MathTemplate.h"
#include "Vector3DF.h"

namespace altseed {
/**
        @brief	3次元ベクトル
*/
struct Vector3DI {
public:
    /**
            @brief	X成分
    */
    int32_t X;

    /**
            @brief	Y成分
    */
    int32_t Y;

    /**
            @brief	Z成分
    */
    int32_t Z;

    /**
            @brief	コンストラクタ
    */
    Vector3DI();

    /**
    @brief	コンストラクタ
    @param	x	X成分
    @param	y	Y成分
    @param	z	Z成分
    */
    Vector3DI(int32_t x, int32_t y, int32_t z);

    bool operator==(const Vector3DI& o);
    bool operator!=(const Vector3DI& o);
    bool operator>(const Vector3DI& o) const;
    bool operator<(const Vector3DI& o) const;

    Vector3DI operator-();

    Vector3DI operator+(const Vector3DI& o) const;

    Vector3DI operator-(const Vector3DI& o) const;

    Vector3DI operator*(const Vector3DI& o) const;

    Vector3DI operator/(const Vector3DI& o) const;

    Vector3DI operator*(const int32_t& o) const;

    Vector3DI operator/(const int32_t& o) const;

    Vector3DI& operator+=(const Vector3DI& o);

    Vector3DI& operator-=(const Vector3DI& o);

    Vector3DI& operator*=(const Vector3DI& o);

    Vector3DI& operator/=(const Vector3DI& o);

    Vector3DI& operator*=(const int32_t& o);

    Vector3DI& operator/=(const int32_t& o);

    /**
    @brief	このベクトルの長さを取得する。
    */
    float GetLength() const { return sqrt(GetSquaredLength()); }

    /**
    @brief	このベクトルの長さの二乗を取得する。
    */
    int32_t GetSquaredLength() const { return X * X + Y * Y + Z * Z; }

    /**
    @brief	このベクトルの単位ベクトルを取得する。
    */
    Vector3DF GetNormal() {
        float length = GetLength();
        return Vector3DF(X / length, Y / length, Z / length);
    }

    /**
    @brief	内積を取得する。
    @param	v1	v1ベクトル
    @param	v2	v2ベクトル
    @return 内積v1・v2
    */
    static int32_t Dot(const Vector3DI& v1, const Vector3DI& v2);

    /**
    @brief	外積を取得する。
    @param	v1	v1ベクトル
    @param	v2	v2ベクトル
    @return 外積v1×v2
    @note
    右手の親指がv1、人差し指がv2としたとき、中指の方向を返す。
    */
    static Vector3DI Cross(const Vector3DI& v1, const Vector3DI& v2);

    /**
    @brief	加算する。
    @param	v1	v1ベクトル
    @param	v2	v2ベクトル
    @return v1+v2
    */
    static Vector3DI Add(Vector3DI v1, Vector3DI v2) { return Vector3DI(v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z); }

    /**
    @brief	減算する。
    @param	v1	v1ベクトル
    @param	v2	v2ベクトル
    @return v1-v2
    */
    static Vector3DI Subtract(Vector3DI v1, Vector3DI v2);

    /**
    @brief	除算する。
    @param	v1	値1
    @param	v2	値2
    @return	v1/v2
    */
    static Vector3DI Divide(const Vector3DI& v1, const Vector3DI& v2) { return Vector3DI(v1.X / v2.X, v1.Y / v2.Y, v1.Z / v2.Z); }

    /**
    @brief	スカラーで除算する。
    @param	v1	値1
    @param	v2	値2
    @return	v1/v2
    */
    static Vector3DI DivideByScalar(const Vector3DI& v1, float v2) { return Vector3DI(v1.X / v2, v1.Y / v2, v1.Z / v2); }

    /**
    @brief	2点間の距離を取得する。
    @param	v1	v1ベクトル
    @param	v2	v2ベクトル
    @return v1とv2の距離
    */
    static float Distance(const Vector3DI& v1, const Vector3DI& v2);

    /**
            @brief	Vector3DF型に変換する。
            @return	Vector3DF型
    */
    Vector3DF To3DF() const;
};
}  // namespace altseed