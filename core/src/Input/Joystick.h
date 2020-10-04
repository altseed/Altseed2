#pragma once
#include <GLFW/glfw3.h>
// #include <hidapi.h>

#include <array>
#include <chrono>
#include <cmath>

#include "../Window/Window.h"
#include "ButtonState.h"
#include "HID.h"

namespace Altseed2 {

enum class JoystickType : int32_t {
    Other,
    DualShock3 = 616,
    DualShock4 = 1476,
    DualShock4Slim = 2508,
    XBOX360 = 654,
    JoyconL = 8198,
    JoyconR = 8199,
    ProController = 8201,
};

enum class JoystickButton : int32_t {
    RightDown = GLFW_GAMEPAD_BUTTON_A,
    RightRight = GLFW_GAMEPAD_BUTTON_B,
    RightLeft = GLFW_GAMEPAD_BUTTON_X,
    RightUp = GLFW_GAMEPAD_BUTTON_Y,
    LeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
    RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
    Back = GLFW_GAMEPAD_BUTTON_BACK,
    Start = GLFW_GAMEPAD_BUTTON_START,
    Guide = GLFW_GAMEPAD_BUTTON_GUIDE,
    LeftThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
    RightThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
    DPadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,
    DPadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
    DPadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
    DPadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
};

enum class JoystickAxis : int32_t {
    LeftX = GLFW_GAMEPAD_AXIS_LEFT_X,
    LeftY = GLFW_GAMEPAD_AXIS_LEFT_Y,
    RightX = GLFW_GAMEPAD_AXIS_RIGHT_X,
    RightY = GLFW_GAMEPAD_AXIS_RIGHT_Y,
    LeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
    RightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
};

class JoystickInfo : public BaseObject {
private:
    std::u16string name_;
    int32_t buttonCount_;
    int32_t axisCount_;

    bool isGamepad_;
    std::u16string gamepadName_;

    std::u16string guid_;
    int32_t bustype_;
    int32_t vendor_;
    int32_t product_;
    int32_t version_;

public:
    JoystickInfo(const std::u16string name, const int32_t buttonCount, const int32_t axisCount, const bool isGamepad, const std::u16string gamepadName, const char* guid);
    const char16_t* GetName() const { return name_.c_str(); }
    int32_t GetButtonCount() const { return buttonCount_; }
    int32_t GetAxisCount() const { return axisCount_; }

    bool GetIsGamepad() const { return isGamepad_; }
    const char16_t* GetGamepadName() const { return gamepadName_.c_str(); }

    const char16_t* GetGUID() const { return guid_.c_str(); }
    int32_t GetBustype() const { return bustype_; }
    int32_t GetVendor() const { return vendor_; }
    int32_t GetProduct() const { return product_; }
    int32_t GetVersion() const { return version_; }

    bool IsJoystickType(JoystickType type) const { return product_ == static_cast<int>(type); }
};

class Joystick : public BaseObject {
private:
    static const int MAX_AXES_NUM = 10;
    static const int MAX_BUTTONS_NUM = 30;
    static const int MAX_JOYSTICKS_NUM = 16;

    static const int MAX_GAMEPAD_BUTTONS_NUM = 15;
    static const int MAX_GAMEPAD_AXES_NUM = 6;

    static std::shared_ptr<Joystick> instance_;

    int32_t connectedJoystickCount_;

    // std::array<std::unique_ptr<hid_device>, MAX_JOYSTICKS_NUM> hidapiDevices_;

    std::array<std::shared_ptr<JoystickInfo>, MAX_JOYSTICKS_NUM> joystickInfo_;
    std::array<std::array<bool, MAX_BUTTONS_NUM>, MAX_JOYSTICKS_NUM> currentHit_;
    std::array<std::array<bool, MAX_BUTTONS_NUM>, MAX_JOYSTICKS_NUM> preHit_;
    std::array<std::array<float, MAX_AXES_NUM>, MAX_JOYSTICKS_NUM> currentAxis_;

    std::array<std::array<bool, MAX_GAMEPAD_BUTTONS_NUM>, MAX_JOYSTICKS_NUM> gamepadCurrentHit_;
    std::array<std::array<bool, MAX_GAMEPAD_BUTTONS_NUM>, MAX_JOYSTICKS_NUM> gamepadPreHit_;
    std::array<std::array<float, MAX_GAMEPAD_AXES_NUM>, MAX_JOYSTICKS_NUM> gamepadCurrentAxis_;

    std::unique_ptr<HID> hid_;

    std::u16string ToU16(const std::wstring& wstr) const;

public:

    Joystick();

    static bool Initialize();

    static void Terminate();

    static std::shared_ptr<Joystick>& GetInstance();

    void RefreshInputState();

    bool IsPresent(int32_t joystickIndex) const;
    int32_t GetConnectedJoystickCount() const;
    std::shared_ptr<JoystickInfo> GetJoystickInfo(int32_t joystickIndex) const;

    ButtonState GetButtonStateByIndex(int32_t joystickIndex, int32_t buttonIndex) const;
    ButtonState GetButtonStateByType(int32_t joystickIndex, JoystickButton type) const;

    float GetAxisStateByIndex(int32_t joystickIndex, int32_t axisIndex) const;
    float GetAxisStateByType(int32_t joystickIndex, JoystickAxis type) const;

    bool SetLight(int32_t joystickIndex, int32_t number);
    bool Vibrate(int32_t joystickIndex, float frequency, float amplitude);
};

}  // namespace Altseed2
