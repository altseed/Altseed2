
#include "Sound.h"

#include "SoundMixer.h"

namespace altseed
{

Sound::Sound(SoundMixer* manager, osm::Sound* sound, bool isDecompressed)
    : m_manager(manager), m_sound(sound), m_isDecompressed(isDecompressed)
{
    
}

Sound::~Sound()
{
    auto s = (SoundMixer*)m_manager;
}

float Sound::GetLoopStartingPoint() const
{
    return m_sound->GetLoopStartingPoint();
}

void Sound::SetLoopStartingPoint(float startingPoint) const
{
    m_sound->SetLoopStartingPoint(startingPoint);
}

float Sound::GetLoopEndPoint() const
{
    return m_sound->GetLoopEndPoint();
}

void Sound::SetLoopEndPoint(float endPoint) const
{
    m_sound->SetLoopEndPoint(endPoint);
}

bool Sound::GetIsLoopingMode() const
{
    return m_sound->GetIsLoopingMode();
}

void Sound::SetIsLoopingMode(bool isLoopingMode)
{
    m_sound->SetIsLoopingMode(isLoopingMode);
}

float Sound::GetLength()
{
    return m_sound->GetLength();
}

void Sound::Reload(uint8_t* data, int32_t size)
{
    
}

} // namespace altseed