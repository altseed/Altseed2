#include "Rendered.h"

#include "CullingSystem.h"

namespace Altseed2 {
Rendered::Rendered() : cullingSystem_(CullingSystem::GetInstance()) {}
Rendered::~Rendered() {
    if (cullingSystem_ != nullptr) {
        auto exists = cullingSystem_->GetIsExists(this);
        ASD_ASSERT(!exists, "Rendered must be unregisterd from culling system.");
    }
}

void Rendered::OnTerminating() {
    // Comment out to debug easily
    // cullingSystem_ = nullptr;
}

const Matrix44F& Rendered::GetTransform() const { return transform_; }

void Rendered::SetTransform(const Matrix44F& transform) {
    transform_ = transform;
    cullingSystem_->RequestUpdateAABB(this);
}

}  // namespace Altseed2