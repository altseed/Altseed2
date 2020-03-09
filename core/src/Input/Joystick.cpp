
#include "Joystick.h"

#include <algorithm>
#include <cstring>

#include "../Common/Miscs.h"

#define JOYCON_BUTTON_COUNT 15

#define JOYCON_L_PRODUCT_ID 8198
#define JOYCON_R_PRODUCT_ID 8199
#define DUALSHOCK4_PRODUCT_ID 0x0
#define XBOX360_PRODUCT_ID 0x0

#define JOYCON_L

namespace Altseed {

std::shared_ptr<Joystick> Joystick::instance_ = nullptr;

bool Joystick::Initialize() {
    instance_ = MakeAsdShared<Joystick>();
    instance_->types_.fill(JoystickType::Other);
    instance_->globalCount_ = 0;

    for (int32_t i = 0; i < MAX_JOYSTICKS_NUM; i++) {
        instance_->currentHit_[i].fill(false);
        instance_->preHit_[i].fill(false);
        //            currentAxis[i].fill(0);
    }

    return true;
};

void Joystick::Terminate() {
    for (int jind = 0; jind < MAX_JOYSTICKS_NUM; jind++) {
        if (!instance_->handler_[jind]) return;

        if (instance_->types_[jind] == JoystickType::JoyconL || instance_->types_[jind] == JoystickType::JoyconR) {
            uint8_t data[0x01];
            data[0] = 0;
            instance_->SendSubcommand(instance_->handler_[jind], 0x30, data, 1);

            data[0] = 0x01;
            instance_->SendSubcommand(instance_->handler_[jind], 0x48, data, 1);

            hid_close(instance_->handler_[jind]);
        }
    }

    instance_ = nullptr;
}

std::shared_ptr<Joystick>& Joystick::GetInstance() { return instance_; }

bool Joystick::IsPresent(int32_t joystickIndex) { return (bool)handler_[joystickIndex]; }

std::u16string Joystick::ToU16(const std::wstring& wstr) {
    if (sizeof(wchar_t) == 4) {
        std::u32string u32(wstr.cbegin(), wstr.cend());

        std::array<char16_t, 512> u16char;
        for (size_t i = 0; i < std::min(u32.size(), u16char.size()); ++i) {
            u16char[i] = (char16_t)u32[i];
        }

        if (u32.size() > 0) {
            u16char[std::min(u32.size(), u16char.size()) - 1] = 0;
            return std::u16string(u16char.data());
        }

        return std::u16string();
    } else {
        return std::u16string(wstr.cbegin(), wstr.cend());
    }
}

void Joystick::SendSubcommand(hid_device* dev, uint8_t command, uint8_t data[], int len) {
    uint8_t buf[0x40];
    memset(buf, 0x0, size_t(0x40));

    buf[0] = 1;  // 0x10 for rumble only
    buf[1] = globalCount_;  // Increment by 1 for each packet sent. It loops in 0x0 - 0xF range.

    if (globalCount_ == 0xf0) {
        globalCount_ = 0x00;
    } else {
        globalCount_++;
    }

    buf[10] = command;
    memcpy(buf + 11, data, len);

    hid_write(dev, buf, 0x40);
}

void Joystick::RefreshConnectedState() {
    // Get HID handler
    hid_device_info* device = hid_enumerate(0, 0);
    const char* path;
    int i = 0;

    while (device) {
        path = device->path;

        if (device->product_id == JOYCON_L_PRODUCT_ID || device->product_id == JOYCON_R_PRODUCT_ID ||
            device->product_id == DUALSHOCK4_PRODUCT_ID || device->product_id == XBOX360_PRODUCT_ID) {
            hid_device* dev = hid_open(device->vendor_id, device->product_id, device->serial_number);

            if (dev) hid_set_nonblocking(dev, 1);
            handler_[i] = dev;

            if (device->product_string != nullptr) names_[i] = ToU16(std::wstring(device->product_string));
            types_[i] = (JoystickType)device->product_id;

            if (types_[i] == JoystickType::JoyconL || types_[i] == JoystickType::JoyconR) {
                // enable vibration for joycon
                uint8_t data[0x01];
                data[0] = 0x01;
                this->SendSubcommand(dev, 0x48, data, 1);

                // send input report mode
                data[0] = 0x3F;
                this->SendSubcommand(dev, 0x03, data, 1);

                // send player light
                data[0] = (i + 1) % 4;
                this->SendSubcommand(dev, 0x30, data, 1);
            }
            i++;
        }
        device = device->next;
    }
    hid_free_enumeration(device);
};

//    NOTE: pushing in stick is handled as button
void Joystick::HandleJoyconInput(int index, unsigned char* buff, bool is_left) {
    if (*buff == 0x21) {
        // buttons
        int target_index = 3;
        if (is_left) {
            target_index = 5;
        }

        for (int i = 0; i <= 7; i++) {
            currentHit_[index][i] = buff[target_index] & (1 << i);
            currentHit_[index][i + 8] = buff[4] & (1 << i);
        }

    } else if (*buff == 0x3F) {
        // hundle buttons

        // convert 0x3F input report buttons status format to standard input report button status format.
        int to_standard_buttons[16] = {0, 2, 3, 1, 5, 4, 14, 15, 8, 9, 11, 10, 12, 13, 6, 7};

        for (int i = 0; i <= 7; i++) {
            currentHit_[index][to_standard_buttons[i]] = buff[1] & (1 << i);
            currentHit_[index][to_standard_buttons[i + 8]] = buff[2] & (1 << i);
        }

        // stick
        int axis_type_H = (int32_t)JoystickAxisType::RightH;
        int axis_type_V = (int32_t)JoystickAxisType::RightV;
        if (is_left) {
            axis_type_H = (int32_t)JoystickAxisType::LeftH;
            axis_type_V = (int32_t)JoystickAxisType::LeftV;
        }

        switch (buff[3]) {
                //                    Top
            case 0:
                currentAxis_[index][axis_type_H] = 0;
                currentAxis_[index][axis_type_V] = 1;
                break;
                //                    Top-right
            case 1:
                currentAxis_[index][axis_type_H] = 1;
                currentAxis_[index][axis_type_V] = 1;
                break;
                //                    Right
            case 2:
                currentAxis_[index][axis_type_H] = 1;
                currentAxis_[index][axis_type_V] = 0;
                break;
                //                    Bottom-right
            case 3:
                currentAxis_[index][axis_type_H] = 1;
                currentAxis_[index][axis_type_V] = -1;
                break;
                //                    Bottom
            case 4:
                currentAxis_[index][axis_type_H] = 0;
                currentAxis_[index][axis_type_V] = -1;
                break;
                //                    Bottom-Left
            case 5:
                currentAxis_[index][axis_type_H] = -1;
                currentAxis_[index][axis_type_V] = -1;
                break;
                //                    Left
            case 6:
                currentAxis_[index][axis_type_H] = -1;
                currentAxis_[index][axis_type_V] = 0;
                break;
                //                    Top-left
            case 7:
                currentAxis_[index][axis_type_H] = -1;
                currentAxis_[index][axis_type_V] = 1;
                break;

            default:
                currentAxis_[index][axis_type_H] = 0;
                currentAxis_[index][axis_type_V] = 0;
                break;
        }
    }
};

void Joystick::RefreshInputState() {
    preHit_ = currentHit_;

    for (int jind = 0; jind < MAX_JOYSTICKS_NUM; jind++) {
        if (!handler_[jind]) return;

        //            read input report
        uint8_t buff[0x40];
        memset(buff, 0x40, size_t(0x40));
        size_t size = 49;

        int ret = hid_read(handler_[jind], buff, size);
        if (!ret) {
            return;
        }

        if (types_[jind] == JoystickType::JoyconL) {
            HandleJoyconInput(jind, buff, true);
        } else if (types_[jind] == JoystickType::JoyconR) {
            HandleJoyconInput(jind, buff, false);
        }
    }
};

void Joystick::Vibrate(int32_t joystickIndex, float frequency, float amplitude) {
    if (types_[joystickIndex] == Altseed::JoystickType::JoyconL || types_[joystickIndex] == Altseed::JoystickType::JoyconR) {
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
        if (amp > 0.23f)
            encoded_hex_amp = (uint8_t)round(log2f(amp * 8.7f) * 32.f);
        else if (amp > 0.12f)
            encoded_hex_amp = (uint8_t)round(log2f(amp * 17.f) * 16.f);
        else {
            encoded_hex_amp = 0;
        }
        uint16_t hf_amp = encoded_hex_amp * 2;
        uint8_t lf_amp = encoded_hex_amp / 2 + 64;

        uint8_t byte[0x08];

        byte[0] = hf & 0xFF;
        byte[1] = hf_amp + ((hf >> 8) & 0xFF);

        byte[2] = lf + ((lf_amp >> 8) & 0xFF);
        byte[3] = lf_amp & 0xFF;

        for (int i = 4; i <= 7; i++) {
            byte[i] = byte[i - 4];
        }

        memcpy(buf + 2, byte, 8);
        hid_write(handler_[0], buf, sizeof(buf));
    }
};

ButtonState Joystick::GetButtonStateByIndex(int32_t joystickIndex, int32_t buttonIndex) const {
    if (buttonIndex < 0) return ButtonState::Free;

    if (currentHit_[joystickIndex][buttonIndex] && preHit_[joystickIndex][buttonIndex])
        return ButtonState::Hold;
    else if (!currentHit_[joystickIndex][buttonIndex] && preHit_[joystickIndex][buttonIndex])
        return ButtonState::Release;
    else if (currentHit_[joystickIndex][buttonIndex] && !preHit_[joystickIndex][buttonIndex])
        return ButtonState::Push;
    else
        return ButtonState::Free;
};

ButtonState Joystick::GetButtonStateByType(int32_t joystickIndex, JoystickButtonType type) const {
    auto jtype = GetJoystickType(joystickIndex);

    if (jtype == JoystickType::Other) return ButtonState::Free;

    if (jtype == JoystickType::JoyconL) {
        std::array<int, (int32_t)JoystickButtonType::Max> maps;
        maps.fill(-1);

        maps[(int32_t)JoystickButtonType::LeftDown] = 0;
        maps[(int32_t)JoystickButtonType::LeftUp] = 1;
        maps[(int32_t)JoystickButtonType::LeftRight] = 2;
        maps[(int32_t)JoystickButtonType::LeftLeft] = 3;

        maps[(int32_t)JoystickButtonType::R3] = 4;
        maps[(int32_t)JoystickButtonType::L3] = 5;

        maps[(int32_t)JoystickButtonType::L1] = 6;
        maps[(int32_t)JoystickButtonType::L2] = 7;

        maps[(int32_t)JoystickButtonType::Select] = 8;
        maps[(int32_t)JoystickButtonType::Start] = 9;
        maps[(int32_t)JoystickButtonType::RightPush] = 10;
        maps[(int32_t)JoystickButtonType::LeftPush] = 11;

        maps[(int32_t)JoystickButtonType::Home] = 12;
        maps[(int32_t)JoystickButtonType::Capture] = 13;

        return GetButtonStateByIndex(joystickIndex, maps[(int32_t)type]);
    } else if (jtype == JoystickType::JoyconR) {
        std::array<int, (int32_t)JoystickButtonType::Max> maps;
        maps.fill(-1);

        maps[(int32_t)JoystickButtonType::RightDown] = 0;
        maps[(int32_t)JoystickButtonType::RightUp] = 1;
        maps[(int32_t)JoystickButtonType::RightRight] = 2;
        maps[(int32_t)JoystickButtonType::RightLeft] = 3;

        maps[(int32_t)JoystickButtonType::R3] = 4;
        maps[(int32_t)JoystickButtonType::L3] = 5;

        maps[(int32_t)JoystickButtonType::R1] = 6;
        maps[(int32_t)JoystickButtonType::R2] = 7;

        maps[(int32_t)JoystickButtonType::Select] = 8;
        maps[(int32_t)JoystickButtonType::Start] = 9;
        maps[(int32_t)JoystickButtonType::RightPush] = 10;
        maps[(int32_t)JoystickButtonType::LeftPush] = 11;

        maps[(int32_t)JoystickButtonType::Home] = 12;
        maps[(int32_t)JoystickButtonType::Capture] = 13;

        return GetButtonStateByIndex(joystickIndex, maps[(int32_t)type]);
    }

    return ButtonState::Hold;
};

float Joystick::GetAxisStateByIndex(int32_t joystickIndex, int32_t axisIndex) const {
    if (axisIndex < 0) return 0;

    return currentAxis_[joystickIndex][axisIndex];
};

float Joystick::GetAxisStateByType(int32_t joystickIndex, JoystickAxisType type) const {
    auto jtype = GetJoystickType(joystickIndex);
    if (jtype == JoystickType::Other) return 0;

    if (jtype == JoystickType::JoyconL || jtype == JoystickType::JoyconR) {
        return GetAxisStateByIndex(joystickIndex, (int32_t)type);
    }

    return 0.0f;
};

JoystickType Joystick::GetJoystickType(int32_t index) const { return types_[index]; };

const char16_t* Joystick::GetJoystickName(int32_t index) const { return names_[index].c_str(); }

}  // namespace Altseed
