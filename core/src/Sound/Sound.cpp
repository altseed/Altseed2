#include "Sound.h"

#include "../Logger/Log.h"

namespace Altseed {

std::mutex Sound::mtx;

Sound::Sound(const char16_t* filePath, std::shared_ptr<osm::Sound> sound, bool isDecompressed, std::shared_ptr<Resources> resources)
    : m_filePath(filePath), m_sound(sound), m_isDecompressed(isDecompressed), resources_(resources) {
    SetInstanceName(__FILE__);
}

Sound::~Sound() {
    std::lock_guard<std::mutex> lock(mtx);
    resources_->GetResourceContainer(ResourceType::Sound)->Unregister(GetPath());
    resources_ = nullptr;
}

std::shared_ptr<Sound> Sound::Load(const char16_t* path, bool isDecompressed) {
    std::lock_guard<std::mutex> lock(mtx);

    auto soundMixer = SoundMixer::GetInstance();
    if (soundMixer->m_manager == nullptr) return nullptr;

    auto cache = std::dynamic_pointer_cast<Sound>(soundMixer->m_resources->GetResourceContainer(ResourceType::Sound)->Get(path));
    if (cache != nullptr && cache->GetRef() > 0) {
        return cache;
    }

    // Create static file & null check
    auto staticFile = StaticFile::Create(path);
    if (staticFile == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Sound::Load: Failed to create file from '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    // Get data & Create OSM sound & null check
    auto sound = CreateSharedPtr(soundMixer->m_manager->CreateSound(staticFile->GetData(), staticFile->GetSize(), isDecompressed));
    if (sound == nullptr) {
        Log::GetInstance()->Error(
                LogCategory::Core, u"Font::LoadDynamicFont: Failed to create sound from '{0}'", utf16_to_utf8(path).c_str());
        return nullptr;
    }

    // Create sound & register to container
    auto soundRet = MakeAsdShared<Sound>(path, sound, isDecompressed, soundMixer->m_resources);
    auto soundContainer = soundMixer->m_resources->GetResourceContainer(ResourceType::Sound);
    auto soundInfo = std::make_shared<ResourceContainer::ResourceInfomation>(soundRet, path);
    soundContainer->Register(path, soundInfo);

    return soundRet;
}

float Sound::GetLoopStartingPoint() const { return m_sound->GetLoopStartingPoint(); }

void Sound::SetLoopStartingPoint(float startingPoint) const { m_sound->SetLoopStartingPoint(startingPoint); }

float Sound::GetLoopEndPoint() const { return m_sound->GetLoopEndPoint(); }

void Sound::SetLoopEndPoint(float endPoint) const { m_sound->SetLoopEndPoint(endPoint); }

bool Sound::GetIsLoopingMode() const { return m_sound->GetIsLoopingMode(); }

void Sound::SetIsLoopingMode(bool isLoopingMode) { m_sound->SetIsLoopingMode(isLoopingMode); }

float Sound::GetLength() { return m_sound->GetLength(); }

const char16_t* Sound::GetPath() const { return m_filePath; }

bool Sound::GetIsDecompressed() const { return m_isDecompressed; }

bool Sound::Reload() {
    /*
    auto ls = m_sound->GetLoopStartingPoint();
    auto le = m_sound->GetLoopEndPoint();
    auto lm = m_sound->GetIsLoopingMode();

    m_sound = m_manager->CreateSound()
    */

    return false;
}

}  // namespace Altseed