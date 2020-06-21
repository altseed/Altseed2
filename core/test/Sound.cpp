#include <Sound/Sound.h>
#include <Sound/SoundMixer.h>
#include <gtest/gtest.h>

namespace asd = Altseed2;

TEST(Sound, SoundPlay) {
    char16_t s16[] = u"Sound Play";
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::Configuration::Create()));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);
    auto se = asd::Sound::Load(u"TestData/Sound/se1.wav", true);

    auto mixer = asd::SoundMixer::GetInstance();
    int id_bgm = mixer->Play(bgm);
    int id_se = mixer->Play(se);

    while (asd::Core::GetInstance()->DoEvent() && (mixer->GetIsPlaying(id_bgm) || mixer->GetIsPlaying(id_se))) {
    }

    asd::Core::Terminate();
}

TEST(Sound, SoundLoop) {
    char16_t s16[] = u"Sound Loop";
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::Configuration::Create()));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);

    auto mixer = asd::SoundMixer::GetInstance();
    int id_bgm = -1;

    if (bgm != nullptr) {
        EXPECT_FALSE(bgm->GetIsLoopingMode());
        bgm->SetIsLoopingMode(true);
        EXPECT_TRUE(bgm->GetIsLoopingMode());
        bgm->SetLoopStartingPoint(1.0);
        bgm->SetLoopEndPoint(2.5);

        id_bgm = mixer->Play(bgm);
    }

    while (asd::Core::GetInstance()->DoEvent() && mixer->GetIsPlaying(id_bgm)) {
    }

    asd::Core::Terminate();
}

TEST(Sound, SoundResume) {
    char16_t s16[] = u"Sound Resume";
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::Configuration::Create()));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);

    auto mixer = asd::SoundMixer::GetInstance();
    int id_bgm = -1;

    if (bgm != nullptr) id_bgm = mixer->Play(bgm);

    clock_t start = clock();
    int stage = 0;

    while (asd::Core::GetInstance()->DoEvent() && mixer->GetIsPlaying(id_bgm)) {
        double time = static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1000.0;

        if (stage == 0) {
            if (time > 1500) {
                mixer->Pause(id_bgm);
                ++stage;
            }
        }

        else if (stage == 1) {
            if (time > 2500) {
                mixer->Resume(id_bgm);
                ++stage;
            }
        }

        else if (stage == 2) {
            if (time > 3500) {
                mixer->Stop(id_bgm);
                ++stage;
            }
        }
    }

    asd::Core::Terminate();
}

TEST(Sound, SoundLength) {
    char16_t s16[] = u"Sound Length";
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::Configuration::Create()));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);
    auto se = asd::Sound::Load(u"TestData/Sound/se1.wav", true);

    auto mixer = asd::SoundMixer::GetInstance();
    int id_bgm = -1, id_se = -1;

    if (bgm != nullptr) {
        id_bgm = mixer->Play(bgm);
        id_se = mixer->Play(se);

        printf("Length of bgm : %f [sec]\n", bgm->GetLength());
        printf("Length of se  : %f [sec]\n", se->GetLength());
    }

    asd::Core::Terminate();
}

TEST(Sound, SpectrumAnalyze) {
    char16_t s16[] = u"Spectrum Analyze";
    EXPECT_TRUE(asd::Core::Initialize(s16, 640, 480, asd::Configuration::Create()));

    auto bgm = asd::Sound::Load(u"TestData/Sound/bgm1.ogg", false);

    auto spectrumData = asd::MakeAsdShared<asd::FloatArray>(8192);

    auto mixer = asd::SoundMixer::GetInstance();
    int id_bgm = -1;

    if (bgm != nullptr) id_bgm = mixer->Play(bgm);

    while (asd::Core::GetInstance()->DoEvent() && mixer->GetIsPlaying(id_bgm)) {
        mixer->GetSpectrum(id_bgm, spectrumData, asd::FFTWindow::Rectangular);
        for (int i = 0; i < 8192; ++i) {
            std::cout << "spactrumData[" << i << "] = " << spectrumData->GetVector()[i] << std::endl;
        }
    }

    asd::Core::Terminate();
}