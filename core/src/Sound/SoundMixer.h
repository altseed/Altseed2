#pragma once

#include <OpenSoundMixer.h>

#include "../BaseObject.h"
#include "../Common/ResourceContainer.h"
#include "../Common/Resources.h"
#include "../Core.h"
#include "../IO/StaticFile.h"
#include "Sound.h"

namespace Altseed {

class Sound;

/**
@brief  音を管理するクラス
*/
class SoundMixer : public BaseObject {
private:
    static std::shared_ptr<SoundMixer> _instance;

    osm::Manager* m_manager;
    std::shared_ptr<Resources> m_resources;

    SoundMixer();
    ~SoundMixer();

public:
    static bool Initialize(bool isReloadingEnabled);

    static void Terminate();

    static std::shared_ptr<SoundMixer>& GetInstance();

    /**
    @brief  音を読み込む
    @param  path    音源のファイルパス
    @param  isDecompressed  音源情報を解凍するか?
    @return 音源
    */
    std::shared_ptr<Sound> CreateSound(const char16_t* path, bool isDecompressed);

    /**
    @brief  音を再生する
    @param  sound   音源
    @return 音のID
    */
    int32_t Play(std::shared_ptr<Sound> sound);

    /**
    @brief  指定した音が再生中であるかを取得する
    @param  id  音のID
    @return IDに対応する音源が再生中であるか?
    */
    bool GetIsPlaying(int32_t id);

    /**
    @brief  再生中の音を全て停止する
    */
    void StopAll();

    /**
    @brief  指定した音の再生を停止する
    @param  id  音のID
    */
    void Stop(int32_t id);

    /**
    @brief  指定した音の再生を一時停止する
    @param  id  音のID
    */
    void Pause(int32_t id);

    /**
    @brief  指定した音の再生を再開する
    @param  id  音のID
    */
    void Resume(int32_t id);

    /**
    @brief  指定した音の再生位置を変更する
    @param  id  音のID
    @param  position    再生位置(秒)
    */
    void Seek(int32_t id, float position);

    /**
    @brief  指定した音の音量を変更する
    @param  id  音のID
    @param  volume  音量(0.0~1.0)
    */
    void SetVolume(int32_t id, float volume);

    /**
    @brief  指定した音をフェードインさせる
    @param  id  音のID
    @param  second  フェードインに使用する時間(秒)
    */
    void FadeIn(int32_t id, float second);

    /**
    @brief	指定した音をフェードアウトさせる
    @param	id	音のID
@param	second	フェードアウトに使用する時間(秒)
    */
    void FadeOut(int32_t id, float second);

    /**
    @brief	任意の音量に音量を一定時間かけて変更する
    @param	id		音のID
    @param	second	変更にかかる時間(秒)
    @param	targetedVolume	変更先の音量(0.0～1.0)
    @note
    この指定される音量はSetVolumeに指定される音量とは異なり、FadeIn、FadeOutに使用される音量と共通である。
    つまり、このメソッドはFadeIn、FadeOutの任意音量指定版と言える。
    */
    void Fade(int32_t id, float second, float targetedVolume);

    /**
    @brief	再生速度変更するかを取得する
    @param	id	音のID
    @return	再生速度変更するか?
    */
    bool GetIsPlaybackSpeedEnabled(int32_t id);

    /**
    @brief	再生速度変更するかを設定する
    @param	id	音のID
    @param	isPlaybackSpeedEnabled	再生速度変更するか?
    */
    void SetIsPlaybackSpeedEnabled(int32_t id, bool isPlaybackSpeedEnabled);

    /**
        @brief	再生速度を取得する
        @param	id	音のID
        @return	再生速度(比率)
        @note
        設定値は再生速度に比例する。1.0で等速。範囲は0.25から4.0
        音程は再生速度に比例して変化する。
        */
    float GetPlaybackSpeed(int32_t id);

    /**
    @brief	再生速度を設定する。
    @param	id	音のID
    @param	playbackSpeed	再生速度(比率)
    @note
    設定値は再生速度に比例する。1.0で等速。範囲は0.25から4.0
    音程は再生速度に比例して変化する。
    */
    void SetPlaybackSpeed(int32_t id, float playbackSpeed);

    /**
    @brief	パン位置を取得する。
    @param	id	音のID
    @return	パン位置, 0.0で中央, -1.0で左, 1.0で右
    */
    float GetPanningPosition(int32_t id);

    /**
    @brief	パン位置を設定する。
    @param	id	音のID
    @param	panningPosition	パン位置, 0.0で中央, -1.0で左, 1.0で右
    */
    void SetPanningPosition(int32_t id, float panningPosition);

    /**
    @brief	現在の再生位置を0～1で取得する
@param	id	音のID
    @return	再生位置
    */
    float GetPlaybackPercent(int32_t id);

    /**
    @brief  再生中の音のスペクトル情報を取得する
    @param  id  音のID
    @param  spectrums   音のスペクトル情報を格納するための配列
    @param  samplingRate    サンプリングレート, spectrums配列の要素数に等しい, 2の累乗(2,4,8,16,...)でなければならない
    @param  window  フーリエ変換に用いる窓関数
    */
    void GetSpectrumData(int32_t id, std::vector<float>& spectrums, int32_t samplingRate, osm::FFTWindow window);

#if !SWIG

    /**
    @brief	リロードする。
    @note   #Ignore
    */
    void Reload();

    osm::Manager* GetManager() { return m_manager; }

#endif
};

}  // namespace Altseed