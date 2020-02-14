#pragma once

#include <math.h>
#include <stdint.h>

#include <cstring>

namespace Altseed {
struct Vector2F;
struct Vector2I;
struct Vector3F;
struct Vector3I;
struct Vector4F;
struct Vector4I;
struct Matrix33F;
struct Matrix44F;
struct RectF;
struct RectI;

inline float NormalizeAngle(float angle) {
    int32_t ofs = (*(int32_t*)&angle & 0x80000000) | 0x3F000000;
    return (angle - ((int)(angle * 0.159154943f + *(float*)&ofs) * 6.283185307f));
}

inline void SinCos(float x, float& s, float& c) {
    x = NormalizeAngle(x);
    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x2 * x4;
    float x8 = x4 * x4;
    float x10 = x2 * x8;
    s = x * (1.0f - x2 / 6.0f + x4 / 120.0f - x6 / 5040.0f + x8 / 362880.0f - x10 / 39916800.0f);
    c = 1.0f - x2 / 2.0f + x4 / 24.0f - x6 / 720.0f + x8 / 40320.0f - x10 / 3628800.0f;
}

const float PI = 3.14159265358979f;

static float DegreeToRadian(float degree) { return degree / 180.0f * PI; }

static float RadianToDegree(float radian) { return radian / PI * 180.0f; }
}  // namespace Altseed
