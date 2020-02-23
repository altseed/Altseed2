#pragma once

#include <array>

#include "MathTemplate.h"
#include "Vector2I.h"

namespace Altseed {

struct RectI_C;

struct RectI {
public:
    int X;

    int Y;

    int Width;

    int Height;

    RectI();

    RectI(int x, int y, int width, int height);

    RectI(Vector2I position, Vector2I size);

    Vector2I GetPosition() const;

    Vector2I GetSize() const;

    std::array<Vector2I, 4> GetVertexes() const;

    bool operator==(const RectI& other) const;

    RectF ToF() const;
    operator RectI_C() const;
};

struct RectI_C {
    int X;

    int Y;

    int Width;

    int Height;

    operator RectI() const;
};
}  // namespace Altseed