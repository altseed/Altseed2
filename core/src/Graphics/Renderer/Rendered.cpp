#include "Rendered.h"

namespace Altseed {

const Matrix44F& Rendered::GetTransform() const { return transform_; }

void Rendered::SetTransform(const Matrix44F& transform) { transform_ = transform; }

}  // namespace Altseed