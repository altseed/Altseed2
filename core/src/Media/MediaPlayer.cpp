#include "MediaPlayer.h"

#include "Platform/MediaPlayer_FFmpeg.h"
#include "Platform/MediaPlayer_Impl.h"

#ifdef _WIN32
#include "Platform/MediaPlayer_WMF.h"
#endif

#ifdef __APPLE__
#include "Platform/MediaPlayer_AVF.h"
#endif

namespace Altseed2 {

MediaPlayer::MediaPlayer() {
#ifdef _WIN32
    impl_ = std::make_shared<MediaPlayer_WMF>();
#elif defined(__APPLE__)
    impl_ = std::make_shared<MediaPlayer_AVF>();
#else
    impl_ = std::make_shared<MediaPlayer_FFmpeg>();
#endif
}

bool MediaPlayer::Play(bool isLoopingMode) {
    return impl_->Play(isLoopingMode);
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

std::shared_ptr<MediaPlayer> MediaPlayer::Load(const char16_t* path) {
    auto ret = MakeAsdShared<MediaPlayer>();
    if (ret->impl_->SetSourceFromPath(path)) {
        return ret;
    }

    return nullptr;
}

}  // namespace Altseed2