#pragma once

#include <array>
#include "MathTemplate.h"
#include "Vector2DI.h"

namespace altseed {

struct RectI {
public:
    int X;

    int Y;

    int Width;

    int Height;

    RectI();

    RectI(int x, int y, int width, int height);

    RectI(Vector2DI position, Vector2DI size);

    Vector2DI GetPosition() const;

    Vector2DI GetSize() const;

    std::array<Vector2DI, 4> GetVertexes() const;

    bool operator==(const RectI& other) const;

    RectF ToF() const;
};
}  // namespace altseed