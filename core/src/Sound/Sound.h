#pragma once

#include <OpenSoundMixer.h>

#include "../Common/Resources.h"
#include "SoundMixer.h"

namespace Altseed {

class SoundMixer;
class Resources;

/**
@brief  音源のクラス
*/
class Sound : public Resource {
private:

    std::shared_ptr<osm::Sound> m_sound;

    const char16_t* m_filePath;
    const bool m_isDecompressed;

public:

    Sound(const char16_t* filePath, std::shared_ptr<osm::Sound> sound, bool isDecompressed);
    ~Sound();

    /**
    @brief  音を読み込む
    @param  path    音源のファイルパス
    @param  isDecompressed  音源情報を解凍するか?
    @return 音源
    */
    static std::shared_ptr<Sound> Load(const char16_t* path, bool isDecompressed);

    /**
    @brief  ループポイントの開始地点(秒)を取得する
    @return 開始地点(秒)
    */
    float GetLoopStartingPoint() const;

    /**
    @brief  ループポイントの開始地点(秒)を設定する
    @param  startingPoint   開始地点(秒)
    */
    void SetLoopStartingPoint(float startingPoint) const;

    /**
    @brief  ループポイントの終了地点(秒)を取得する
    @return 終了地点(秒)
    */
    float GetLoopEndPoint() const;

    /**
    @brief  ループポイントの終了地点(秒)を設定する
    @param  endPoint   終了地点(秒)
    */
    void SetLoopEndPoint(float endPoint) const;

    /**
    @brief	ループするかを取得する
    @return	ループするか?
    */
    bool GetIsLoopingMode() const;

    /**
    @brief  ループするかを設定する
    @param  isLoopingMode   ループするか?
    */
    void SetIsLoopingMode(bool isLoopingMode);

    /**
    @brief	音の長さを取得する
    @return	長さ(秒)
    */
    float GetLength();

#if !SWIG

    std::shared_ptr<osm::Sound> GetSound() { return m_sound; }

    bool Reload() override;

#endif
};

}  // namespace Altseed
