#pragma once

#include "SoundMixer.h"
#include "../Common/Resources.h"

#include <OpenSoundMixer.h>

namespace altseed
{

class SoundMixer;
class Resources;

/**
@brief  音源のクラス
*/
class Sound : public Resource
{
private:
    std::shared_ptr<Resources> m_resources;
    std::shared_ptr<SoundMixer> m_manager;

    osm::Sound* m_sound;

    const char16_t* m_filePath;
    const bool m_isDecompressed;
    
public:
    Sound(std::shared_ptr<Resources>& resources, std::shared_ptr<SoundMixer>& manager, const char16_t* filePath, osm::Sound* sound, bool isDecompressed);
    virtual ~Sound();

    /**
    @brief  ループポイントの開始地点(秒)を取得する
    @return 開始地点(秒)
    */
    virtual float GetLoopStartingPoint() const;

    /**
    @brief  ループポイントの開始地点(秒)を設定する
    @param  startingPoint   開始地点(秒)
    */
    virtual void SetLoopStartingPoint(float startingPoint) const;

    /**
    @brief  ループポイントの終了地点(秒)を取得する
    @return 終了地点(秒)
    */
    virtual float GetLoopEndPoint() const;

    /**
    @brief  ループポイントの終了地点(秒)を設定する
    @param  endPoint   終了地点(秒)
    */
    virtual void SetLoopEndPoint(float endPoint) const;

	/**
	@brief	ループするかを取得する
	@return	ループするか?
	*/
	virtual bool GetIsLoopingMode() const;

	/**
	@brief  ループするかを設定する
	@param  isLoopingMode   ループするか?
	*/
	virtual void SetIsLoopingMode(bool isLoopingMode);

	/**
	@brief	音の長さを取得する
	@return	長さ(秒)
	*/
	virtual float GetLength();

#if !SWIG

	osm::Sound* GetSound() { return m_sound; }

	bool Reload() override;

#endif

};

} // namespace altseed
