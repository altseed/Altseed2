#pragma once
#include <hidapi.h>

#include <array>
#include <chrono>
#include <cmath>

#include "../Window/Window.h"
#include "ButtonState.h"

namespace Altseed2 {

class HID {
private:
    struct DeviceProperty {
        std::string Path;
        std::wstring ProductString;
        std::wstring ManifactureString;
        uint16_t ProductID;
        uint16_t VendorID;
        std::wstring SerialNumber;
        hid_device* Handler;
    };

    uint8_t globalCount_;

    bool initialized_ = false;
    std::vector<DeviceProperty> pairs_;

    std::vector<DeviceProperty> Enumerate();
    std::vector<DeviceProperty> GetPairDevices(std::vector<DeviceProperty> properties);
    void SendSubcommand(hid_device* handler, uint8_t command, uint8_t data[], int len);

    void VibrateJoycon(hid_device* handler, float frequency, float amplitude);

public:
    ~HID();
    bool Initialize();
    void TerminateDevices();
    void Refresh(int connectedJoystickCount);

    bool Vibrate(int joystickIndex, float frequency, float amplitude);
};

}  // namespace Altseed2