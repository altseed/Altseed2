#include <Sound/Sound.h>
#include <Sound/SoundMixer.h>
#include <gtest/gtest.h>

#include "TestHelper.h"

namespace asd = Altseed2;

TEST(Sound, SoundPlay) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Sound);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(asd::Core::Initialize(u"Sound Play", 640, 480, config));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);
    EXPECT_TRUE(bgm != nullptr);
    auto se = asd::Sound::Load(u"TestData/Sound/se1.wav", true);
    EXPECT_TRUE(se != nullptr);

    auto mixer = asd::SoundMixer::GetInstance();
    int id_bgm = mixer->Play(bgm);
    EXPECT_TRUE(id_bgm != -1);
    int id_se = mixer->Play(se);
    EXPECT_TRUE(id_se != -1);

    clock_t start = clock();

    while (asd::Core::GetInstance()->DoEvent() && (mixer->GetIsPlaying(id_bgm) || mixer->GetIsPlaying(id_se))) {
        double time = (clock() - start) * 0.01;

        if (time > 1500) mixer->Stop(id_bgm);
    }

    asd::Core::Terminate();
}

TEST(Sound, SoundLoop) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Sound);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(asd::Core::Initialize(u"Sound Loop", 640, 480, config));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);
    EXPECT_TRUE(bgm != nullptr);

    auto mixer = asd::SoundMixer::GetInstance();

    EXPECT_FALSE(bgm->GetIsLoopingMode());
    bgm->SetIsLoopingMode(true);
    EXPECT_TRUE(bgm->GetIsLoopingMode());
    bgm->SetLoopStartingPoint(1.0);
    bgm->SetLoopEndPoint(2.5);

    int id_bgm = mixer->Play(bgm);
    EXPECT_TRUE(id_bgm != -1);

    clock_t start = clock();

    while (asd::Core::GetInstance()->DoEvent() && mixer->GetIsPlaying(id_bgm)) {
        double time = (clock() - start) / CLOCKS_PER_SEC;

        if (time > 5) mixer->Stop(id_bgm);
    }

    asd::Core::Terminate();
}

TEST(Sound, SoundResume) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Sound);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(asd::Core::Initialize(u"SOund Resume", 640, 480, config));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);
    EXPECT_TRUE(bgm != nullptr);

    auto mixer = asd::SoundMixer::GetInstance();

    int id_bgm = mixer->Play(bgm);
    EXPECT_TRUE(id_bgm != -1);

    clock_t start = clock();
    int stage = 0;

    while (asd::Core::GetInstance()->DoEvent() && mixer->GetIsPlaying(id_bgm)) {
        double time = (clock() - start) * 0.01;

        if (stage == 0) {
            if (time > 750) {
                mixer->Pause(id_bgm);
                ++stage;
            }
        }

        else if (stage == 1) {
            if (time > 1500) {
                mixer->Resume(id_bgm);
                ++stage;
            }
        }

        else if (stage == 2) {
            if (time > 2250) {
                mixer->Stop(id_bgm);
                ++stage;
            }
        }
    }

    asd::Core::Terminate();
}

TEST(Sound, SoundLength) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Sound);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(asd::Core::Initialize(u"Sound Length", 640, 480, config));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);
    EXPECT_TRUE(bgm != nullptr);
    auto se = asd::Sound::Load(u"TestData/Sound/se1.wav", true);
    EXPECT_TRUE(se != nullptr);

    auto mixer = asd::SoundMixer::GetInstance();

    int id_bgm = mixer->Play(bgm);
    EXPECT_TRUE(id_bgm != -1);
    int id_se = mixer->Play(se);
    EXPECT_TRUE(id_se != -1);

    printf("Length of bgm : %f [sec]\n", bgm->GetLength());
    printf("Length of se  : %f [sec]\n", se->GetLength());

    asd::Core::Terminate();
}

TEST(Sound, SpectrumAnalyze) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::Sound);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(asd::Core::Initialize(u"Spectrum Analyze", 640, 480, config));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);
    EXPECT_TRUE(bgm != nullptr);

    auto spectrumData = asd::MakeAsdShared<asd::FloatArray>(8192);

    auto mixer = asd::SoundMixer::GetInstance();

    int id_bgm = mixer->Play(bgm);
    EXPECT_TRUE(id_bgm != -1);

    clock_t start = clock();

    while (asd::Core::GetInstance()->DoEvent() && mixer->GetIsPlaying(id_bgm)) {
        double time = (clock() - start) * 0.01;

        if (time > 1500) mixer->Stop(id_bgm);

        mixer->GetSpectrum(id_bgm, spectrumData, asd::FFTWindow::Rectangular);
        for (int i = 0; i < 8192; ++i) {
            std::cout << "spactrumData[" << i << "] = " << spectrumData->GetVector()[i] << std::endl;
        }
    }

    asd::Core::Terminate();
}