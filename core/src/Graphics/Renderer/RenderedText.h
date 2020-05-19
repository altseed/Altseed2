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
    float characterSpace_;
    float lineGap_;

public:
    static std::shared_ptr<RenderedText> Create();

    float GetWeight() const { return weight_; }

    void SetWeight(float weight) { weight_ = weight; }

    std::shared_ptr<Material> GetMaterial() const { return material_; }
    void SetMaterial(const std::shared_ptr<Material>& material) { material_ = material; }

    Color GetColor() const { return color_; }
    void SetColor(const Color color) { color_ = color; }

    std::shared_ptr<Font> GetFont() const { return font_; }

    void SetFont(const std::shared_ptr<Font>& font) {
        font_ = font;
        lineGap_ = (float)font_->GetLineGap();
        cullingSystem_->RequestUpdateAABB(this);
    }

    const char16_t* GetText() const { return text_.c_str(); }

    void SetIsEnableKerning(bool isEnableKerning) { isEnableKerning_ = isEnableKerning; }
    bool GetIsEnableKerning() { return isEnableKerning_; }

    void SetWritingDirection(WritingDirection wrintingDirection) {
        writingDirection_ = wrintingDirection;
        cullingSystem_->RequestUpdateAABB(this);
    }

    WritingDirection GetWritingDirection() { return writingDirection_; }

    void SetCharacterSpace(float characterSpace) {
        characterSpace_ = characterSpace;
        cullingSystem_->RequestUpdateAABB(this);
    }

    float GetCharacterSpace() { return characterSpace_; }

    void SetLineGap(float lineGap) {
        lineGap_ = lineGap;
        cullingSystem_->RequestUpdateAABB(this);
    }

    float GetLineGap() { return lineGap_; }

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