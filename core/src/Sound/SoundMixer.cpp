#include "SoundMixer.h"

namespace altseed
{

SoundMixer::SoundMixer(File* file, bool isReloadingEnabled)
{
	m_manager = osm::Manager::Create();

	if(m_manager->Initialize())
	{

	}
	else
	{
		if(m_manager != nullptr) m_manager->Release();
	}

	SoundSourcesContainer = std::make_shared<ResourceContainer>();
}

SoundMixer::~SoundMixer()
{
	if (m_manager != nullptr)
	{
		m_manager->Finalize();
		m_manager->Release();
	}
}

Sound* SoundMixer::CreateSound(const char16_t* path, bool isDecompressed)
{
	return nullptr;
}

int32_t SoundMixer::Play(Sound* sound)
{
	if (m_manager == nullptr) return -1;
	if (sound == nullptr) return -1;
	auto s = (Sound*)sound;

	return m_manager->Play(s->GetSound());
}

bool SoundMixer::GetIsPlaying(int32_t id)
{
	if (m_manager == nullptr) return false;
	return m_manager->IsPlaying(id);
}

void SoundMixer::StopAll()
{
	if (m_manager == nullptr) return;
	return m_manager->StopAll();
}

void SoundMixer::Stop(int32_t id)
{
	if (m_manager == nullptr) return;
	return m_manager->Stop(id);
}

void SoundMixer::Pause(int32_t id)
{
	if (m_manager == nullptr) return;
	return m_manager->Pause(id);
}

void SoundMixer::Resume(int32_t id)
{
	if (m_manager == nullptr) return;
	return m_manager->Resume(id);	
}

void SoundMixer::Seek(int32_t id, float position)
{
	if (m_manager == nullptr) return;
	return m_manager->Seek(id, position);
}

void SoundMixer::SetVolume(int32_t id, float volume)
{
	if (m_manager == nullptr) return;
	return m_manager->SetVolume(id, volume);
}

void SoundMixer::FadeIn(int32_t id, float second)
{
	if (m_manager == nullptr) return;
	return m_manager->FadeIn(id, second);
}

void SoundMixer::FadeOut(int32_t id, float second)
{
	if (m_manager == nullptr) return;
	return m_manager->FadeOut(id, second);
}

void SoundMixer::Fade(int32_t id, float second, float targetedVolume)
{
	if (m_manager == nullptr) return;
	return m_manager->Fade(id, second, targetedVolume);
}

bool SoundMixer::GetIsPlaybackSpeedEnabled(int32_t id)
{
	if (m_manager == nullptr) return false;
	return m_manager->GetIsPlaybackSpeedEnabled(id);
}

void SoundMixer::SetIsPlaybackSpeedEnabled(int32_t id, bool isPlaybackSpeedEnabled)
{
	if (m_manager == nullptr) return;
	m_manager->SetIsPlaybackSpeedEnabled(id, isPlaybackSpeedEnabled);
}

float SoundMixer::GetPlaybackSpeed(int32_t id)
{
	if (m_manager == nullptr) return 1.0f;
	return m_manager->GetPlaybackSpeed(id);
}

void SoundMixer::SetPlaybackSpeed(int32_t id, float playbackSpeed)
{
	if (m_manager == nullptr) return;
	m_manager->SetPlaybackSpeed(id, playbackSpeed);
}

float SoundMixer::GetPanningPosition(int32_t id)
{
	if (m_manager == nullptr) return 0.0f;
	return m_manager->GetPanningPosition(id);
}

void SoundMixer::SetPanningPosition(int32_t id, float panningPosition)
{
	if (m_manager == nullptr) return;
	m_manager->SetPanningPosition(id, panningPosition);
}

float SoundMixer::GetPlaybackPercent(int32_t id)
{
	if (m_manager == nullptr) return 0.0f;
	return m_manager->GetPlaybackPercent(id);
}

void SoundMixer::GetSpectrumData(int32_t id, float* spectrums, int32_t samplingRate, osm::FFTWindow window)
{
	if (m_manager == nullptr) return;
	m_manager->GetSpectrumData(id, spectrums, samplingRate, window);
}

void SoundMixer::Reload()
{
	
}

} // namespace altseed