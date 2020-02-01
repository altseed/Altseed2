#include "Sound.h"

namespace Altseed {

Sound::Sound(
        std::shared_ptr<Resources> resources,
        std::shared_ptr<SoundMixer> manager,
        const char16_t* filePath,
        osm::Sound* sound,
        bool isDecompressed)
    : m_resources(resources), m_manager(manager), m_filePath(filePath), m_sound(sound), m_isDecompressed(isDecompressed) {
    // Increment reference counter
    if (m_manager != nullptr) m_manager->AddRef();
}

Sound::~Sound() {
    // Safe release
    if (m_sound != nullptr) m_sound->Release();
    if (m_manager != nullptr) m_manager->Release();
}

float Sound::GetLoopStartingPoint() const { return m_sound->GetLoopStartingPoint(); }

void Sound::SetLoopStartingPoint(float startingPoint) const { m_sound->SetLoopStartingPoint(startingPoint); }

float Sound::GetLoopEndPoint() const { return m_sound->GetLoopEndPoint(); }

void Sound::SetLoopEndPoint(float endPoint) const { m_sound->SetLoopEndPoint(endPoint); }

bool Sound::GetIsLoopingMode() const { return m_sound->GetIsLoopingMode(); }

void Sound::SetIsLoopingMode(bool isLoopingMode) { m_sound->SetIsLoopingMode(isLoopingMode); }

float Sound::GetLength() { return m_sound->GetLength(); }

bool Sound::Reload() { return false; }

}  // namespace Altseed