#include "SoundMixer.h"

namespace Altseed {

std::shared_ptr<SoundMixer> SoundMixer::_instance = nullptr;

SoundMixer::SoundMixer() {
    m_manager = osm::Manager::Create();
    m_resources = Resources::GetInstance();

    if (m_manager != nullptr) {
        m_manager->AddRef();
    }
}

SoundMixer::~SoundMixer() {
    if (m_manager != nullptr) {
        m_manager->Finalize();
        m_manager->Release();
    }
}

bool SoundMixer::Initialize(bool isReloadingEnabled) {
    _instance = CreateSharedPtr(new SoundMixer());

    if(_instance == nullptr) { return false; }
    if (!_instance->m_manager->Initialize()) { return false; }

    return true;
}

void SoundMixer::Terminate() {
    _instance = nullptr;
}

std::shared_ptr<SoundMixer>& SoundMixer::GetInstance() { return _instance; }

std::shared_ptr<Sound> SoundMixer::CreateSound(const char16_t* path, bool isDecompressed) {
    if (m_manager == nullptr) return nullptr;

    // Create file instance & null check
    auto fileInstance = File::GetInstance();
    if (fileInstance == nullptr) return nullptr;

    // Create static file & null check
    auto staticFile = fileInstance->CreateStaticFile(path);
    if (staticFile == nullptr) return nullptr;

	// Get data & Create OSM sound & null check
	auto sound = m_manager->CreateSound(staticFile->GetData(), staticFile->GetSize(), isDecompressed);
	if(sound == nullptr)
	{
		staticFile->Release();
		return nullptr;
	}

	// Create sound & register to container
	auto soundRet = std::make_shared<Sound>(m_resources, GetInstance(), path, sound, isDecompressed);
	auto soundContainer = m_resources->GetResourceContainer(ResourceType::Sound);
	auto soundInfo = std::make_shared<ResourceContainer::ResourceInfomation>(soundRet, path);
	soundContainer->Register(path, soundInfo);

    return soundRet;
}

int32_t SoundMixer::Play(std::shared_ptr<Sound> sound) {
    if (m_manager == nullptr) return -1;
    if (sound == nullptr) return -1;

    return m_manager->Play(sound->GetSound());
}

bool SoundMixer::GetIsPlaying(int32_t id) {
    if (m_manager == nullptr) return false;
    return m_manager->IsPlaying(id);
}

void SoundMixer::StopAll() {
    if (m_manager == nullptr) return;
    return m_manager->StopAll();
}

void SoundMixer::Stop(int32_t id) {
    if (m_manager == nullptr) return;
    return m_manager->Stop(id);
}

void SoundMixer::Pause(int32_t id) {
    if (m_manager == nullptr) return;
    return m_manager->Pause(id);
}

void SoundMixer::Resume(int32_t id) {
    if (m_manager == nullptr) return;
    return m_manager->Resume(id);
}

void SoundMixer::Seek(int32_t id, float position) {
    if (m_manager == nullptr) return;
    return m_manager->Seek(id, position);
}

void SoundMixer::SetVolume(int32_t id, float volume) {
    if (m_manager == nullptr) return;
    return m_manager->SetVolume(id, volume);
}

void SoundMixer::FadeIn(int32_t id, float second) {
    if (m_manager == nullptr) return;
    return m_manager->FadeIn(id, second);
}

void SoundMixer::FadeOut(int32_t id, float second) {
    if (m_manager == nullptr) return;
    return m_manager->FadeOut(id, second);
}

void SoundMixer::Fade(int32_t id, float second, float targetedVolume) {
    if (m_manager == nullptr) return;
    return m_manager->Fade(id, second, targetedVolume);
}

bool SoundMixer::GetIsPlaybackSpeedEnabled(int32_t id) {
    if (m_manager == nullptr) return false;
    return m_manager->GetIsPlaybackSpeedEnabled(id);
}

void SoundMixer::SetIsPlaybackSpeedEnabled(int32_t id, bool isPlaybackSpeedEnabled) {
    if (m_manager == nullptr) return;
    m_manager->SetIsPlaybackSpeedEnabled(id, isPlaybackSpeedEnabled);
}

float SoundMixer::GetPlaybackSpeed(int32_t id) {
    if (m_manager == nullptr) return 1.0f;
    return m_manager->GetPlaybackSpeed(id);
}

void SoundMixer::SetPlaybackSpeed(int32_t id, float playbackSpeed) {
    if (m_manager == nullptr) return;
    m_manager->SetPlaybackSpeed(id, playbackSpeed);
}

float SoundMixer::GetPanningPosition(int32_t id) {
    if (m_manager == nullptr) return 0.0f;
    return m_manager->GetPanningPosition(id);
}

void SoundMixer::SetPanningPosition(int32_t id, float panningPosition) {
    if (m_manager == nullptr) return;
    m_manager->SetPanningPosition(id, panningPosition);
}

float SoundMixer::GetPlaybackPercent(int32_t id) {
    if (m_manager == nullptr) return 0.0f;
    return m_manager->GetPlaybackPercent(id);
}

void SoundMixer::GetSpectrumData(int32_t id, std::vector<float>& spectrums, int32_t samplingRate, osm::FFTWindow window) {
    if (m_manager == nullptr) return;
    m_manager->GetSpectrumData(id, spectrums, samplingRate, window);
}

void SoundMixer::Reload() {
    auto container = m_resources->GetResourceContainer(ResourceType::Sound);
    for(auto sound : container->GetAllResouces()) sound.second->Reload(0);
}

}  // namespace Altseed