#pragma once

#include "MathTemplate.h"
#include "Vector4DF.h"

namespace altseed {
/**
@brief	4次元ベクトル
*/
struct Vector4DI {
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
    @brief	W成分
    */
    int32_t W;

    /**
    @brief	コンストラクタ
    */
    Vector4DI();

    /**
    @brief	コンストラクタ
    @param	x	X成分
    @param	y	Y成分
    @param	z	Z成分
    @param	w	W成分
    */
    Vector4DI(int32_t x, int32_t y, int32_t z, int32_t w);

    /**
    @brief	このベクトルの長さを取得する。
    */
    float GetLength() const { return sqrt(GetSquaredLength()); }

    /**
    @brief	このベクトルの長さの二乗を取得する。
    */
    int32_t GetSquaredLength() const { return X * X + Y * Y + Z * Z + W * W; }

    bool operator==(const Vector4DI& o);
    bool operator!=(const Vector4DI& o);

    Vector4DI operator-();

    Vector4DI operator+(const Vector4DI& o) const;

    Vector4DI operator-(const Vector4DI& o) const;

    Vector4DI operator*(const Vector4DI& o) const;

    Vector4DI operator/(const Vector4DI& o) const;

    Vector4DI operator*(const int32_t& o) const;

    Vector4DI operator/(const int32_t& o) const;

    Vector4DI& operator+=(const Vector4DI& o);

    Vector4DI& operator-=(const Vector4DI& o);

    Vector4DI& operator*=(const Vector4DI& o);

    Vector4DI& operator/=(const Vector4DI& o);

    Vector4DI& operator*=(const int32_t& o);

    Vector4DI& operator/=(const int32_t& o);

    /**
    @brief	内積を取得する。
    @param	v1	v1ベクトル
    @param	v2	v2ベクトル
    @return 内積v1・v2
    */
    static int32_t Dot(const Vector4DI& v1, const Vector4DI& v2);

    /**
    @brief	2点間の距離を取得する。
    @param	v1	v1ベクトル
    @param	v2	v2ベクトル
    @return v1とv2の距離
    */
    static float Distance(const Vector4DI& v1, const Vector4DI& v2);

	/**
	@brief	Vector4DF型に変換する。
	@return	Vector4DF型
	*/
    Vector4DF To4DF() const;
};
}  // namespace altseed