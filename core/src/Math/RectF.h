#pragma once

#include <array>
#include "MathTemplate.h"
#include "Vector2DF.h"

namespace altseed {

struct RectF {
public:
    float X;

    float Y;

    float Width;

    float Height;

    RectF();

    RectF(float x, float y, float width, float height);

    RectF(Vector2DF position, Vector2DF size);

    Vector2DF GetPosition() const;

    Vector2DF GetSize() const;

    std::array<Vector2DF, 4> GetVertexes() const;

    bool operator!=(const RectF& right);

    RectI ToI() const;
};

}  // namespace altseed
