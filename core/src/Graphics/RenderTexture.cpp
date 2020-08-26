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

RenderTexture::~RenderTexture() {}

std::shared_ptr<RenderTexture> RenderTexture::Create(Vector2I size, TextureFormatType format) {
    auto texture = Graphics::GetInstance()->CreateRenderTexture(size.X, size.Y, format);

    if (texture == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"RenderTexture::Create: Failed to CreateTexture");
        return nullptr;
    }

    return MakeAsdShared<RenderTexture>(texture);
}

bool RenderTexture::Save(const char16_t* path) {
    RETURN_IF_NULL(path, false);
    Graphics::GetInstance()->GetCommandList()->SaveRenderTexture(path, CreateAndAddSharedPtr(this));
    return true;
}

}  // namespace Altseed2