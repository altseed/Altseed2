#pragma once

#include <stdio.h>
#include <array>
#include <hidapi.h>
#include <cmath>
#include <chrono>

#include "ButtonState.h"
#include "../Window/Window.h"


namespace altseed {
    
    enum class JoystickType : int32_t
    {
        Other,
        PS4 = 8200,
        XBOX360 = 8199,
        JoyconL = 8198,
        JoyconR = 8197,
    };
    
    enum class JoystickButtonType : int32_t
    {
        Start,    ///Joycon plus
        Select,    ///Joycon minus
        
        Home,
        Capture,
        
        LeftUp,
        LeftDown,
        LeftLeft,
        LeftRight,
        LeftPush,
        
        RightUp,    ///< PSx Triangle
        RightRight,    ///< PSx Circle
        RightLeft,    ///< PSx Square
        RightDown,    ///< PSx Cross
        RightPush,
        
        L1,
        R1,
        L2,    //Joycon ZL
        R2,    //Joycon ZR
        L3,    //Joycon SL
        R3,    //Joycon SR
        
        LeftStart,    ///< XBOX360 Start, PS4 Options
        RightStart,    ///< XBOX360 Select, PS4 TouchPad
        
        Max,
    };
    
    enum class JoystickAxisType : int32_t
    {
        LeftH,
        LeftV,
        RightH,
        RightV,
        L2,
        R2,
        
        Max,
    };
    
    

    struct VibrateData {
        float high_frequency;
        float low_frequency;
        float high_amplitude;
        float low_amplitude;
        int life_time;
        bool isSended;
        std::chrono::system_clock::time_point pre_time;
    };

    class Joystick {
    private:
        static const int MAX_AXES_NUM = 10;
        static const int MAX_BUTTONS_NUM = 30;
        static const int MAX_JOYSTICKS_NUM = 16;
        
        Window*        window = nullptr;

//        hid_write ç”¨
        uint8_t globalCount;
        
        std::array<JoystickType, MAX_JOYSTICKS_NUM>        types;
        std::array<wchar_t*, MAX_JOYSTICKS_NUM> names;

        std::array<std::array<bool,MAX_BUTTONS_NUM>, MAX_JOYSTICKS_NUM> currentHit;
        std::array<std::array<bool,MAX_BUTTONS_NUM>, MAX_JOYSTICKS_NUM> preHit;
        std::array<std::array<float,MAX_AXES_NUM>, static_cast<int>(JoystickAxisType::Max)> currentAxis;
        
        void SendSubcommand(hid_device *dev, uint8_t command, uint8_t data[], int len);
        void HandleJoyconInput(int index, unsigned char *buff);
        
//     for vibration only
        std::array<hid_device*, MAX_JOYSTICKS_NUM> handler;
        std::array<VibrateData, MAX_JOYSTICKS_NUM> vibrateStates;

        
    public:
        
        bool Initialize(JoystickType type);
        
        void Terminate();
        
        void RefreshInputState();
        
        void RefreshConnectedState();
        
        bool IsPresent(int32_t joystickIndex);

        ButtonState GetButtonState(int32_t joystickIndex, int32_t buttonIndex) const;
        ButtonState GetButtonState(int32_t joystickIndex, JoystickButtonType type) const;
        
        JoystickType GetJoystickType(int32_t index) const;
        
        float GetAxisState(int32_t joystickIndex, int32_t axisIndex) const;
        float GetAxisState(int32_t joystickIndex, JoystickAxisType type) const;
        
        wchar_t * GetJoystickName(int16_t index) const;
        
        
//    for vibration only
        
        void RefreshVibrateState();
        
        void SetVibration(int16_t index, float high_freq, float low_freq, float high_amp, float low_amp, int life_time);
    

    };

}
