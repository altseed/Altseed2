#include "RectF.h"

#include "RectI.h"
#include "Vector2F.h"

using namespace std;

namespace Altseed {
RectF::RectF() : X(0), Y(0), Width(0), Height(0) {}

RectF::RectF(float x, float y, float width, float height) : X(x), Y(y), Width(width), Height(height) {}

RectF::RectF(Vector2F position, Vector2F size) : X(position.X), Y(position.Y), Width(size.X), Height(size.Y) {}

Vector2F RectF::GetPosition() const { return Vector2F(X, Y); }

Vector2F RectF::GetSize() const { return Vector2F(Width, Height); }

array<Vector2F, 4> RectF::GetVertexes() const {
    array<Vector2F, 4> ret;

    ret[0] = Vector2F(X, Y);
    ret[1] = Vector2F(X + Width, Y);
    ret[2] = Vector2F(X + Width, Y + Height);
    ret[3] = Vector2F(X, Y + Height);

    return ret;
}

bool RectF::operator!=(const RectF& right) { return X != right.X || Y != right.Y || Width != right.Width || Height != right.Height; }

RectI RectF::ToI() const { return RectI((int32_t)X, (int32_t)Y, (int32_t)Width, (int32_t)Height); }
}  // namespace Altseed