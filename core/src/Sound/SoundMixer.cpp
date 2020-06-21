#include "SoundMixer.h"
#include "../Logger/Log.h"

namespace Altseed2 {

std::shared_ptr<SoundMixer> SoundMixer::instance_ = nullptr;

bool SoundMixer::Initialize(bool isReloadingEnabled) {
    instance_ = CreateSharedPtr(new SoundMixer());
    if (instance_ == nullptr) {
        return false;
    }

    instance_->m_manager = CreateSharedPtr(osm::Manager::Create());
    instance_->m_resources = Resources::GetInstance();

    if (!instance_->m_manager->Initialize()) {
        instance_->isSoundMixerEnabled_ = false;
        return false;
    }

    instance_->isSoundMixerEnabled_ = true;
    return true;
}

void SoundMixer::Terminate() {
    if (instance_->m_manager != nullptr) {
        instance_->m_manager->Finalize();
    }

    instance_ = nullptr;
}

std::shared_ptr<SoundMixer>& SoundMixer::GetInstance() { return instance_; }

int32_t SoundMixer::Play(std::shared_ptr<Sound> sound) {
    if (!isSoundMixerEnabled_) return -1;
    if (m_manager == nullptr) return -1;
    if (sound == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"SoundMixer::Play: failed, sound is null");
        return -1;
    }

    return m_manager->Play(sound->GetSound().get());
}

bool SoundMixer::GetIsPlaying(int32_t id) {
    if (!isSoundMixerEnabled_) return false;
    if (m_manager == nullptr) return false;
    return m_manager->IsPlaying(id);
}

void SoundMixer::StopAll() {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->StopAll();
}

void SoundMixer::Stop(int32_t id) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->Stop(id);
}

void SoundMixer::Pause(int32_t id) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->Pause(id);
}

void SoundMixer::Resume(int32_t id) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->Resume(id);
}

void SoundMixer::SetVolume(int32_t id, float volume) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->SetVolume(id, volume);
}

void SoundMixer::FadeIn(int32_t id, float second) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->FadeIn(id, second);
}

void SoundMixer::FadeOut(int32_t id, float second) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->FadeOut(id, second);
}

void SoundMixer::Fade(int32_t id, float second, float targetedVolume) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->Fade(id, second, targetedVolume);
}

bool SoundMixer::GetIsPlaybackSpeedEnabled(int32_t id) {
    if (!isSoundMixerEnabled_) return false;
    if (m_manager == nullptr) return false;
    return m_manager->GetIsPlaybackSpeedEnabled(id);
}

void SoundMixer::SetIsPlaybackSpeedEnabled(int32_t id, bool isPlaybackSpeedEnabled) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    m_manager->SetIsPlaybackSpeedEnabled(id, isPlaybackSpeedEnabled);
}

float SoundMixer::GetPlaybackSpeed(int32_t id) {
    if (!isSoundMixerEnabled_) return 1.0f;
    if (m_manager == nullptr) return 1.0f;
    return m_manager->GetPlaybackSpeed(id);
}

void SoundMixer::SetPlaybackSpeed(int32_t id, float playbackSpeed) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    m_manager->SetPlaybackSpeed(id, playbackSpeed);
}

float SoundMixer::GetPanningPosition(int32_t id) {
    if (!isSoundMixerEnabled_) return 0.0f;
    if (m_manager == nullptr) return 0.0f;
    return m_manager->GetPanningPosition(id);
}

void SoundMixer::SetPanningPosition(int32_t id, float panningPosition) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    m_manager->SetPanningPosition(id, panningPosition);
}

float SoundMixer::GetPlaybackPosition(int32_t id) {
    if (!isSoundMixerEnabled_) return 0.0f;
    if (m_manager == nullptr) return 0.0f;
    return m_manager->GetPlaybackPosition(id);
}

void SoundMixer::SetPlaybackPosition(int32_t id, float position) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    return m_manager->SetPlaybackPosition(id, position);
}

void SoundMixer::GetSpectrum(int32_t id, std::shared_ptr<FloatArray>& spectrums, FFTWindow window) {
    if (!isSoundMixerEnabled_) return;
    if (m_manager == nullptr) return;
    m_manager->GetSpectrum(id, spectrums->GetVector(), window);
}

void SoundMixer::Reload() {
    auto container = m_resources->GetResourceContainer(ResourceType::Sound);
    for (auto sound : container->GetAllResouces()) sound.second->Reload(0);
}

}  // namespace Altseed2