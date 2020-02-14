#pragma once

#include <array>

#include "MathTemplate.h"
#include "Vector2F.h"

namespace Altseed {

struct RectF {
public:
    float X;

    float Y;

    float Width;

    float Height;

    RectF();

    RectF(float x, float y, float width, float height);

    RectF(Vector2F position, Vector2F size);

    Vector2F GetPosition() const;

    Vector2F GetSize() const;

    std::array<Vector2F, 4> GetVertexes() const;

    bool operator!=(const RectF& right);

    RectI ToI() const;
};

}  // namespace Altseed
