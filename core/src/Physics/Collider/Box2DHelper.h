#pragma once

#include <box2d/box2d.h>

#include "../../Math/Matrix44F.h"
#include "../../Math/Vector2F.h"
#include "../../Math/Vector3F.h"

namespace Altseed2 {

class Box2DHelper {
public:
    /**
    @brief 変形行列をAltseed2->Box2Dに変換
    @param transform 変換したいAltseed2の変形行列
    @return Box2Dの変形行列
    */
    static b2Transform ToBox2D_Mat(const Matrix44F& transform);
    /**

    @brief 変形行列をBox2D->Altseed2に変換
    @param transform 変換したいBox2Dの変形行列
    @return Altseed2の変形行列
    */
    static Matrix44F ToAsd_Mat(const b2Transform& transform);

    /**
    @brief 2次元ベクトルをAltseed2->Box2Dに変換
    @param vector 変換したいAltseed2の2次元ベクトル
    @return Box2Dの2次元ベクトル
    */
    static b2Vec2 ToBox2D_Vec(const Vector2F& vector);

    /**
    @brief 3次元ベクトルをAltseed2->Box2Dに変換
    @param vector 変換したいAltseed2の3次元ベクトル
    @return Box2Dの3次元ベクトル
    */
    static b2Vec3 ToBox2D_Vec(const Vector3F& vector);

    /**
    @brief 2次元ベクトルをBox2D->Altseed2に変換
    @param vector 変換したいAltseed2の2次元ベクトル
    @return Box2Dの2次元ベクトル
    */
    static Vector2F ToAsd_Vec(const b2Vec2& vector);

    /**
    @brief 3次元ベクトルをBox2D->Altseed2に変換
    @param vector 変換したいAltseed3の2次元ベクトル
    @return Box2Dの3次元ベクトル
    */
    static Vector3F ToAsd_Vec(const b2Vec3& vector);

    /**
    @brief 3回転行列をAltseed2->Box2Dに変換
    @param rotation 変換したいAltseed2の回転行列
    @return Box2Dの回転を表すオブジェクト
    */
    static b2Rot ToBox2D_Rot(const Matrix44F& rotation);

    /**
    @brief 3回転行列をBox2D->Altseed2に変換
    @param rotation 変換したいBox2Dの回転を表すオブジェクト
    @return Altseed2の回転行列
    */
    static Matrix44F ToAsd_Rot(const b2Rot& rotation);
};

}  // namespace Altseed2
