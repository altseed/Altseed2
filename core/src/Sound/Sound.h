#pragma once

#include <OpenSoundMixer.h>

#include "../Common/Resources.h"
#include "../Common/ThreadSafeMap.h"
#include "SoundMixer.h"

namespace Altseed2 {

class SoundMixer;
class Resources;

/**
@brief  音源のクラス
*/
class Sound : public Resource {
private:
    std::shared_ptr<osm::Sound> m_sound;

    std::u16string m_filePath;
    const bool m_isDecompressed;

    std::shared_ptr<Resources> resources_;

    static std::mutex mtx;

public:
    Sound(std::u16string filePath, std::shared_ptr<osm::Sound> sound, bool isDecompressed, std::shared_ptr<Resources> resources);
    virtual ~Sound();

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

    const char16_t* GetPath() const;

    bool GetIsDecompressed() const;

#if !USE_CBG

    std::shared_ptr<osm::Sound> GetSound() { return m_sound; }

#endif
    bool Reload() override;
};

}  // namespace Altseed2
