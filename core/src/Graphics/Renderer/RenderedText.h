#pragma once

#include <box2d/box2d.h>
#include <stdio.h>

#include <memory>

#include "../Color.h"
#include "../Font.h"
#include "../Material.h"
#include "CullingSystem.h"
#include "Rendered.h"

namespace Altseed {

class RenderedText : public Rendered {
private:
    std::shared_ptr<Material> material_;
    std::shared_ptr<Font> font_;
    std::u16string text_;
    Color color_;
    float weight_;
    bool isEnableKerning_;
    WritingDirection writingDirection_;

public:
    static std::shared_ptr<RenderedText> Create();

    float GetWeight() const { return weight_; }

    void SetWeight(float weight) { weight_ = weight; }

    std::shared_ptr<Material> GetMaterial() const { return material_; }

    void SetMaterial(const std::shared_ptr<Material>& material) { material_ = material; }

    std::shared_ptr<Font> GetFont() const { return font_; }

    void SetFont(const std::shared_ptr<Font>& font) {
        font_ = font;
        cullingSystem_->RequestUpdateAABB(this);
    }

    const char16_t* GetText() const { return text_.c_str(); }

    void SetIsEnableKerning(bool isEnableKerning) { isEnableKerning_ = isEnableKerning; }

    bool GetIsEnableKerning() { return isEnableKerning_; }

    void SetWritingDirection(WritingDirection wrintingDirection) { writingDirection_ = wrintingDirection; }

    WritingDirection GetWritingDirection() { return writingDirection_; }

    //! Internal function
    const std::u16string& GetTextAsStr() const { return text_; }

    void SetText(const char16_t* text) {
        text_ = std::u16string(text);
        cullingSystem_->RequestUpdateAABB(this);
    }

    Vector2F GetTextureSize();

    b2AABB GetAABB() override;
};

}  // namespace Altseed