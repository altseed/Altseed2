#include "RectI.h"

#include "RectF.h"
#include "Vector2I.h"

using namespace std;

namespace Altseed2 {
RectI::RectI() : X(0), Y(0), Width(0), Height(0) {}

RectI::RectI(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height) {}

RectI::RectI(Vector2I position, Vector2I size) : X(position.X), Y(position.Y), Width(size.X), Height(size.Y) {}

Vector2I RectI::GetPosition() const { return Vector2I(X, Y); }

Vector2I RectI::GetSize() const { return Vector2I(Width, Height); }

array<Vector2I, 4> RectI::GetVertexes() const {
    array<Vector2I, 4> ret;

    ret[0] = Vector2I(X, Y);
    ret[1] = Vector2I(X + Width, Y);
    ret[2] = Vector2I(X + Width, Y + Height);
    ret[3] = Vector2I(X, Y + Height);

    return ret;
}

bool RectI::operator==(const RectI& other) const { return X == other.X && Y == other.Y && Width == other.Width && Height == other.Height; }

RectF RectI::ToF() const { return RectF(X, Y, Width, Height); }

RectI::operator RectI_C() const { return RectI_C{X, Y, Width, Height}; }

RectI_C::operator RectI() const { return RectI(X, Y, Width, Height); }
}  // namespace Altseed2