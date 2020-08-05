#include "Rendered.h"

#include "CullingSystem.h"

namespace Altseed2 {
Rendered::Rendered() : cullingSystem_(CullingSystem::GetInstance()) {}
Rendered::~Rendered() {
    ASD_ASSERT(!cullingSystem_->GetIsExists(this), "Rendered must be unregisterd from culling system.");
    cullingSystem_ = nullptr;
}
const Matrix44F& Rendered::GetTransform() const { return transform_; }

void Rendered::SetTransform(const Matrix44F& transform) {
    transform_ = transform;
    cullingSystem_->RequestUpdateAABB(this);
}

}  // namespace Altseed2