#include "RenderTexture.h"

#include "../Logger/Log.h"
#include "CommandList.h"
#include "Graphics.h"
#include "Texture2D.h"

namespace Altseed2 {

RenderTexture::RenderTexture(const std::shared_ptr<LLGI::Texture>& texture)
    : TextureBase(texture) {
    SetInstanceName(__FILE__);
}

RenderTexture::RenderTexture(Vector2I size, TextureFormatType format)
    : RenderTexture(Graphics::GetInstance()->CreateRenderTexture(size.X, size.Y, format)) {
}

RenderTexture::~RenderTexture() {}

std::shared_ptr<RenderTexture> RenderTexture::Create(Vector2I size, TextureFormatType format) { return MakeAsdShared<RenderTexture>(size, format); }

bool RenderTexture::Save(const char16_t* path) {
    RETURN_IF_NULL(path, false);
    Graphics::GetInstance()->GetCommandList()->SaveRenderTexture(path, CreateAndAddSharedPtr(this));
    return true;
}

}  // namespace Altseed2