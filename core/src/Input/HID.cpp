#include "HID.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cstring>

#include "../Logger/Log.h"

namespace Altseed2 {

static const uint16_t VendorNintendo = 1406;
static const uint16_t ProductJoyconL = 8198;
static const uint16_t ProductJoyconR = 8199;

bool HID::Initialize() {
    if (initialized_) {
        return false;
    }

    if (hid_init() != 0) {
        return false;
    }

    initialized_ = true;
    return true;
}

HID::~HID() {
    if (initialized_) {
        hid_exit();
    }
}

void HID::SendSubcommand(hid_device* handler, uint8_t command, uint8_t data[], int32_t len) {
    RETURN_IF_NULL(handler, );

    std::array<uint8_t, 0x40> buf;
    buf.fill(0);

    buf[0] = 1;  // 0x10 for rumble only
    buf[1] = globalCount_;  // Increment by 1 for each packet sent. It loops in 0x0 - 0xF range.

    if (globalCount_ == 0xf0) {
        globalCount_ = 0x00;
    } else {
        globalCount_++;
    }

    buf[10] = command;
    memcpy(buf.data() + 11, data, len);

    hid_write(handler, buf.data(), 0x40);
}

std::vector<HID::DeviceProperty> HID::Enumerate() {
    std::vector<HID::DeviceProperty> devices;

    auto firstDevice = hid_enumerate(0, 0);
    auto device = firstDevice;

    while (device) {
        HID::DeviceProperty prop;
        prop.Path = device->path;
        prop.ProductID = device->product_id;
        prop.VendorID = device->vendor_id;

        if (device->product_string != nullptr) {
            prop.ProductString = device->product_string;
        }

        if (device->manufacturer_string != nullptr) {
            prop.ManifactureString = device->manufacturer_string;
        }

        if (device->serial_number != nullptr) {
            prop.SerialNumber = device->serial_number;
        }

        if (prop.VendorID == VendorNintendo) {
            if (prop.ProductID == ProductJoyconL || prop.ProductID == ProductJoyconR) {
                prop.Handler = hid_open(device->vendor_id, device->product_id, device->serial_number);

                if (prop.Handler != nullptr) {
                    hid_set_nonblocking(prop.Handler, 1);

                    // enable vibration for joycon
                    uint8_t data[1];
                    data[0] = 0x01;
                    SendSubcommand(prop.Handler, 0x48, data, 1);

                    // send player light
                    data[0] = 0b1111;
                    SendSubcommand(prop.Handler, 0x30, data, 1);
                }
            }
        }

        devices.emplace_back(std::move(prop));
        device = device->next;
    }
    hid_free_enumeration(firstDevice);

    return devices;
}

std::vector<HID::DeviceProperty> HID::GetPairDevices(std::vector<HID::DeviceProperty> properties) {
    std::vector<HID::DeviceProperty> devices;

    if (properties.size() == 0) {
        return devices;
    }

    auto hid = Enumerate();

    size_t propIndex = 0;

    devices.resize(properties.size());

    for (size_t i = 0; i < hid.size(); i++) {
        if (properties[propIndex].SerialNumber != L"" && properties[propIndex].SerialNumber == hid[i].SerialNumber) {
            devices[propIndex] = std::move(hid[i]);
            propIndex++;
            if (propIndex >= properties.size()) {
                break;
            }

            continue;
        } else if (properties[propIndex].ProductString != L"" && properties[propIndex].ProductString == hid[i].ProductString) {
            devices[propIndex] = std::move(hid[i]);
            propIndex++;
            if (propIndex >= properties.size()) {
                break;
            }

            continue;
        }
    }

    return devices;
}

void HID::TerminateDevices() {
    for (const auto& prop : pairs_) {
        if (prop.Handler != nullptr) {
            if (prop.VendorID == VendorNintendo) {
                if (prop.ProductID == ProductJoyconL || prop.ProductID == ProductJoyconR) {
                    uint8_t data[1];

                    // set light
                    data[0] = 0b1111;
                    this->SendSubcommand(prop.Handler, 0x30, data, 1);

                    // vibration
                    data[0] = 0x01;
                    this->SendSubcommand(prop.Handler, 0x48, data, 1);
                }
            }

            hid_close(prop.Handler);
        }
    }
}

void HID::Refresh(int32_t connectedJoystickCount) {
    TerminateDevices();

    std::vector<HID::DeviceProperty> props;
    props.resize(connectedJoystickCount);

    for (int32_t i = 0; i < connectedJoystickCount; i++) {
#if defined(_WIN32)
        props[i].ProductString = glfwJoystickGetProductName(i);
#elif defined(__APPLE__)
        props[i].SerialNumber = glfwJoystickGetSerialNumberStr(i);
#endif
    }

    pairs_ = GetPairDevices(props);
}

bool HID::SetLight(int32_t joystickIndex, int32_t number) {
    if (joystickIndex < 0 || pairs_.size() <= joystickIndex) {
        Log::GetInstance()->Error(LogCategory::Core, u"HID::SetLight: index is out of range");
        return false;
    }

    const DeviceProperty& prop = pairs_.at(joystickIndex);
    if (prop.Handler == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"HID::SetLight: Device is not valid");
        return false;
    }

    if (prop.VendorID == VendorNintendo) {
        if (prop.ProductID == ProductJoyconL || prop.ProductID == ProductJoyconR) {
            uint8_t data[1];
            // send player light
            data[0] = 0b1111 & number;
            SendSubcommand(prop.Handler, 0x30, data, 1);
            return true;
        }
    }

    Log::GetInstance()->Error(LogCategory::Core, u"HID::Vibarte: Device type is not supported");
    return false;
}

bool HID::Vibrate(int32_t joystickIndex, float frequency, float amplitude) {
    if (joystickIndex < 0 || pairs_.size() <= joystickIndex) {
        Log::GetInstance()->Error(LogCategory::Core, u"HID::Vibarte: index is out of range");
        return false;
    }

    const DeviceProperty& prop = pairs_.at(joystickIndex);
    if (prop.Handler == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"HID::Vibarte: Device is not valid");
        return false;
    }

    if (prop.VendorID == VendorNintendo) {
        if (prop.ProductID == ProductJoyconL || prop.ProductID == ProductJoyconR) {
            VibrateJoycon(prop.Handler, frequency, amplitude);
            return true;
        }
    }

    Log::GetInstance()->Error(LogCategory::Core, u"HID::Vibarte: Device type is not supported");
    return false;
}

void HID::VibrateJoycon(hid_device* handler, float frequency, float amplitude) {
    RETURN_IF_NULL(handler, );

    uint8_t buf[0x40];
    memset(buf, 0x0, size_t(0x40));
    buf[0] = 0x10;
    buf[1] = 0x01;

    float freq = std::clamp(frequency, 40.0f, 1252.0f);
    float amp = std::clamp(amplitude, 0.0f, 1.0f);

    uint8_t encoded_hex_freq = (uint8_t)round(log2((double)freq / 10.0) * 32.0);

    uint16_t hf = (encoded_hex_freq - 0x60) * 4;
    uint8_t lf = encoded_hex_freq - 0x40;

    uint8_t encoded_hex_amp = 0;

    if (amp > 0.23f) {
        encoded_hex_amp = (uint8_t)round(log2f(amp * 8.7f) * 32.f);
    } else if (amp > 0.12f) {
        encoded_hex_amp = (uint8_t)round(log2f(amp * 17.f) * 16.f);
    } else {
        encoded_hex_amp = 0;
    }

    uint16_t hf_amp = encoded_hex_amp * 2;
    uint8_t lf_amp = encoded_hex_amp / 2 + 64;

    uint8_t byte[0x08];

    byte[0] = hf & 0xFF;
    byte[1] = hf_amp + ((hf >> 8) & 0xFF);

    byte[2] = lf + ((lf_amp >> 8) & 0xFF);
    byte[3] = lf_amp & 0xFF;

    for (int32_t i = 4; i <= 7; i++) {
        byte[i] = byte[i - 4];
    }

    memcpy(buf + 2, byte, 8);

    hid_write(handler, buf, sizeof(buf));
}

}  // namespace Altseed2