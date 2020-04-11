#include "Rendered.h"

#include "CullingSystem.h"

namespace Altseed {
Rendered::Rendered() : cullingSystem_(CullingSystem::GetInstance()), isDrawn_(false) { cullingSystem_->Register(this); }
Rendered::~Rendered() {
    cullingSystem_->Unregister(this);
    cullingSystem_ = nullptr;
}
const Matrix44F& Rendered::GetTransform() const { return transform_; }

void Rendered::SetTransform(const Matrix44F& transform) {
    transform_ = transform;
    cullingSystem_->RequestUpdateAABB(this);
}

}  // namespace Altseed