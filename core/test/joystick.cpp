#include <Core.h>
#include <Input/Joystick.h>
#include <gtest/gtest.h>
#include <hidapi.h>
#include <cmath>
#include <chrono>

uint8_t global_count = 0x00;

TEST(Joystick, Initialize) {
    
    char16_t s16[] = u"test";
    
    EXPECT_TRUE(Altseed::Core::Initialize(s16, 640, 480, Altseed::CoreOption()));

//    Altseed::JoystickManager::GetInstance()->PrintDevicesInfo();
//    temp();
    Altseed::Joystick *joystick = new Altseed::Joystick();
    joystick->Initialize(Altseed::JoystickType::JoyconL);
    for (int i=0;i<10;i++) {
        printf("name: %ls", joystick->GetJoystickName(i));
    }
    
    
    std::chrono::system_clock::time_point  start, end; // 型は auto で可
    start = std::chrono::system_clock::now(); // 計測開始時間
    // 処理
    end = std::chrono::system_clock::now();  // 計測終了時間
    joystick->SetVibration(0, 462.457855f, 462.457855f, 0.981378f, 0.981378f, 1000);
    
//    joystick->SetVibration(0, 600.0f, 200.0f, 0.8f, 0.8f, 3000);
    
//    float pre_h = 0;
//    float pre_v = 0;
//
    while(std::chrono::duration_cast<std::chrono::seconds>(end - start).count() <= 5.0f)
    {
        joystick->RefreshVibrateState();

        joystick->RefreshInputState();
//        float h = joystick->GetAxisState(0, Altseed::JoystickAxisType::LeftH);
//        float v = joystick->GetAxisState(0, Altseed::JoystickAxisType::LeftV);
//
//        if (pre_h == h && pre_v == v) {
//
//        } else {
//            printf("\nh: %f\n", h);
//            printf("v: %f\n", v);
//        }
//
//        pre_h = h;
//        pre_v = v;

        end = std::chrono::system_clock::now();  // 計測終了時間


    }

    
    Altseed::Core::Terminate();
}


