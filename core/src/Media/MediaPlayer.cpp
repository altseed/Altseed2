#include "MediaPlayer.h"

#include "Platform/MediaPlayer_Impl.h"

namespace Altseed2 {

bool MediaPlayer::Play(bool isLoopingMode) {
    return impl_->Play(isLoopingMode);
}

bool MediaPlayer::Load(const char16_t* path) {
    return impl_->SetSourceFromPath(path);
}

bool MediaPlayer::WriteToTexture2D(std::shared_ptr<Texture2D> target) {
    return impl_->WriteToTexture2D(target);
}

Vector2I MediaPlayer::GetSize() const {
    return impl_->GetSize();
}

int32_t MediaPlayer::GetCurrentFrame() const {
    return impl_->GetCurrentFrame();
}

}  // namespace Altseed2