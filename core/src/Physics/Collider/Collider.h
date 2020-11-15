#pragma once

#include <box2d/box2d.h>

#include <memory>
#include <vector>

#include "../../BaseObject.h"
#include "../../Math/Matrix44F.h"
#include "../../Math/Vector2F.h"

namespace Altseed2 {

class Collider : public BaseObject {
protected:
    b2Transform transform_;
    Matrix44F transformMatrix_;

    Vector2F position_;
    float rotation_;

    virtual bool GetIsCollidedWith_(std::shared_ptr<Collider> collider) { throw "Not implemented."; }

public:
    Collider();

    bool GetIsCollidedWith(std::shared_ptr<Collider> collider);

    // 位置
    Vector2F GetPosition() const;
    void SetPosition(Vector2F position);

    // 回転
    float GetRotation() const;
    void SetRotation(float rotation);

    // 変形行列
    Matrix44F GetTransform() const;
    void SetTransform(const Matrix44F& transform);
};

}  // namespace Altseed2
