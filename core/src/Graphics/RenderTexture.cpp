#include "RenderTexture.h"

#include "CommandList.h"
#include "Graphics.h"
#include "Texture2D.h"

namespace Altseed2 {

RenderTexture::RenderTexture(const std::shared_ptr<LLGI::Texture>& texture)
    : TextureBase(texture) {
    SetInstanceName(__FILE__);
}

RenderTexture::RenderTexture(Vector2I size)
    : RenderTexture(Graphics::GetInstance()->CreateRenderTexture(size.X, size.Y)) {
}

RenderTexture::~RenderTexture() {}

std::shared_ptr<RenderTexture> RenderTexture::Create(Vector2I size) { return MakeAsdShared<RenderTexture>(size); }

bool RenderTexture::Save(const char16_t* path) {
    Graphics::GetInstance()->GetCommandList()->SaveRenderTexture(path, CreateAndAddSharedPtr(this));
    return true;
}

}  // namespace Altseed2