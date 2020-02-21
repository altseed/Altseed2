#include "SoundMixer.h"

namespace Altseed {

std::shared_ptr<SoundMixer> SoundMixer::_instance = nullptr;

SoundMixer::SoundMixer() {
    Sound::m_manager = CreateSharedPtr(osm::Manager::Create());
    Sound::m_resources = Resources::GetInstance();

    if (Sound::m_manager != nullptr) {
        Sound::m_manager->AddRef();
    }
}

SoundMixer::~SoundMixer() {
    if (Sound::m_manager != nullptr) {
        Sound::m_manager->Finalize();
        Sound::m_manager->Release();
    }
}

bool SoundMixer::Initialize(bool isReloadingEnabled) {
    _instance = CreateSharedPtr(new SoundMixer());

    if(_instance == nullptr) { return false; }
    if(!Sound::m_manager->Initialize()) { return false; }

    return true;
}

void SoundMixer::Terminate() {
    _instance = nullptr;
}

std::shared_ptr<SoundMixer>& SoundMixer::GetInstance() { return _instance; }

int32_t SoundMixer::Play(std::shared_ptr<Sound> sound) {
    if (Sound::m_manager == nullptr) return -1;
    if (sound == nullptr) return -1;

    return Sound::m_manager->Play(sound->GetSound().get());
}

bool SoundMixer::GetIsPlaying(int32_t id) {
    if (Sound::m_manager == nullptr) return false;
    return Sound::m_manager->IsPlaying(id);
}

void SoundMixer::StopAll() {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->StopAll();
}

void SoundMixer::Stop(int32_t id) {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->Stop(id);
}

void SoundMixer::Pause(int32_t id) {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->Pause(id);
}

void SoundMixer::Resume(int32_t id) {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->Resume(id);
}

void SoundMixer::Seek(int32_t id, float position) {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->Seek(id, position);
}

void SoundMixer::SetVolume(int32_t id, float volume) {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->SetVolume(id, volume);
}

void SoundMixer::FadeIn(int32_t id, float second) {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->FadeIn(id, second);
}

void SoundMixer::FadeOut(int32_t id, float second) {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->FadeOut(id, second);
}

void SoundMixer::Fade(int32_t id, float second, float targetedVolume) {
    if (Sound::m_manager == nullptr) return;
    return Sound::m_manager->Fade(id, second, targetedVolume);
}

bool SoundMixer::GetIsPlaybackSpeedEnabled(int32_t id) {
    if (Sound::m_manager == nullptr) return false;
    return Sound::m_manager->GetIsPlaybackSpeedEnabled(id);
}

void SoundMixer::SetIsPlaybackSpeedEnabled(int32_t id, bool isPlaybackSpeedEnabled) {
    if (Sound::m_manager == nullptr) return;
    Sound::m_manager->SetIsPlaybackSpeedEnabled(id, isPlaybackSpeedEnabled);
}

float SoundMixer::GetPlaybackSpeed(int32_t id) {
    if (Sound::m_manager == nullptr) return 1.0f;
    return Sound::m_manager->GetPlaybackSpeed(id);
}

void SoundMixer::SetPlaybackSpeed(int32_t id, float playbackSpeed) {
    if (Sound::m_manager == nullptr) return;
    Sound::m_manager->SetPlaybackSpeed(id, playbackSpeed);
}

float SoundMixer::GetPanningPosition(int32_t id) {
    if (Sound::m_manager == nullptr) return 0.0f;
    return Sound::m_manager->GetPanningPosition(id);
}

void SoundMixer::SetPanningPosition(int32_t id, float panningPosition) {
    if (Sound::m_manager == nullptr) return;
    Sound::m_manager->SetPanningPosition(id, panningPosition);
}

float SoundMixer::GetPlaybackPercent(int32_t id) {
    if (Sound::m_manager == nullptr) return 0.0f;
    return Sound::m_manager->GetPlaybackPercent(id);
}

void SoundMixer::GetSpectrumData(int32_t id, std::vector<float>& spectrums, int32_t samplingRate, osm::FFTWindow window) {
    if (Sound::m_manager == nullptr) return;
    Sound::m_manager->GetSpectrumData(id, spectrums, samplingRate, window);
}

void SoundMixer::Reload() {
    auto container = Sound::m_resources->GetResourceContainer(ResourceType::Sound);
    for (auto sound : container->GetAllResouces()) sound.second->Reload(0);
}

}  // namespace Altseed