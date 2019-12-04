
#pragma once

#include "../BaseObject.h"

#include <OpenSoundMixer.h>

namespace altseed
{

/**
@brief  音源のクラス
*/
class Sound : public BaseObject
{
private:
    SoundMixer* m_manager;
    osm::Sound* m_sound;
    bool        m_isDecompressed = false;

protected:
    Sound(SoundMixer* manager, osm::Sound* sound, bool isDecompressed);
    virtual ~Sound();

public:

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

	void Reload(uint8_t* data, int32_t size);

#endif

};

} // namespace altseed
