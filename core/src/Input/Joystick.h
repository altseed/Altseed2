#pragma once
#include <GLFW/glfw3.h>
// #include <hidapi.h>

#include <optional>
#include <array>
#include <chrono>
#include <cmath>

#include "../Window/Window.h"
#include "ButtonState.h"

namespace Altseed {

enum class JoystickType : int32_t {
    Other,
    DualShock3 = 616,
    DualShock4 = 1476,
    DualShock4Slim = 2508,
    XBOX360 = 654,
    JoyconL = 8198,
    JoyconR = 8199,
};

enum class JoystickButtonType : int32_t {
    Start,  /// Joycon plus
    Select,  /// Joycon minus

    Home,
    Capture,

    LeftUp,
    LeftDown,
    LeftLeft,
    LeftRight,
    LeftPush,

    RightUp,  ///< PSx Triangle
    RightRight,  ///< PSx Circle
    RightLeft,  ///< PSx Square
    RightDown,  ///< PSx Cross
    RightPush,

    L1,
    R1,
    L2,  // Joycon ZL
    R2,  // Joycon ZR
    L3,  // Joycon SL
    R3,  // Joycon SR

    LeftStart,  ///< XBOX360 Start, PS4 Options
    RightStart,  ///< XBOX360 Select, PS4 TouchPad

    Max,
};

enum class JoystickAxisType : int32_t {
    LeftH,
    LeftV,
    RightH,
    RightV,
    L2,
    R2,

    Max,
};

class JoystickInfo : public BaseObject {
private:
    std::u16string name_;
    int32_t buttonCount_;
    int32_t axisCount_;
    std::u16string guid_;
    int32_t bustype_;
    int32_t vendor_;
    int32_t product_;
    int32_t version_;
public:
    JoystickInfo(const std::u16string name, const int32_t buttonCount, const int32_t axisCount, const char* guid);
    const char16_t* GetName() const { return name_.c_str(); }
    int32_t GetButtonCount() const { return buttonCount_; }
    int32_t GetAxisCount() const { return axisCount_; }
    const char16_t* GetGUID() const { return guid_.c_str(); }
    int32_t GetBustype() const { return bustype_; }
    int32_t GetVendor() const { return vendor_; }
    int32_t GetProduct() const { return product_; }
    int32_t GetVersion() const { return version_; }
};

class Joystick : public BaseObject {
private:
    static const int MAX_AXES_NUM = 10;
    static const int MAX_BUTTONS_NUM = 30;
    static const int MAX_JOYSTICKS_NUM = 16;

    static std::shared_ptr<Joystick> instance_;

    std::array<std::shared_ptr<JoystickInfo>, MAX_BUTTONS_NUM> joystickInfo_;
    std::array<std::array<bool, MAX_BUTTONS_NUM>, MAX_JOYSTICKS_NUM> currentHit_;
    std::array<std::array<bool, MAX_BUTTONS_NUM>, MAX_JOYSTICKS_NUM> preHit_;
    std::array<std::array<float, MAX_AXES_NUM>, MAX_JOYSTICKS_NUM> currentAxis_;

    std::u16string ToU16(const std::wstring& wstr) const;


public:
    Joystick();

    static bool Initialize();

    static void Terminate();

    static std::shared_ptr<Joystick>& GetInstance();

    void RefreshInputState();

    bool IsPresent(int32_t joystickIndex) const;
    std::shared_ptr<JoystickInfo> GetJoystickInfo(int32_t joystickIndex) const;

    ButtonState GetButtonStateByIndex(int32_t joystickIndex, int32_t buttonIndex) const;
    ButtonState GetButtonStateByType(int32_t joystickIndex, JoystickButtonType type) const;

    float GetAxisStateByIndex(int32_t joystickIndex, int32_t axisIndex) const;
    float GetAxisStateByType(int32_t joystickIndex, JoystickAxisType type) const;

    // void Vibrate(int32_t joystickIndex, float frequency, float amplitude);
};

}  // namespace Altseed
