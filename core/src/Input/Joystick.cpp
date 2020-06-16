
#include "Joystick.h"

#include <algorithm>
#include <cstring>

#include "../Common/Miscs.h"
#include "../Logger/Log.h"
#include "JoystickMapping.h"

namespace Altseed {
JoystickInfo::JoystickInfo(const std::u16string name, const int32_t buttonCount, const int32_t axisCount, const char* guid)
    : name_(name), buttonCount_(buttonCount), axisCount_(axisCount) {
    guid_ = utf8_to_utf16(std::string(guid));
    unsigned int bustype1, bustype2;
    unsigned int vendor1, vendor2;
    unsigned int product1, product2;
    unsigned int version1, version2;
    sscanf(guid, "%02x%02x0000%02x%02x0000%02x%02x0000%02x%02x0000", &bustype1, &bustype2, &vendor1, &vendor2, &product1, &product2, &version1, &version2);
    bustype_ = (bustype2 << 8) | bustype1;
    vendor_ = (vendor2 << 8) | vendor1;
    product_ = (product2 << 8) | product1;
    version_ = (version2 << 8) | version1;
}

bool JoystickInfo::GetIsAvailableButtonMapping() const {
    return ButtonMapping.find(product_) != ButtonMapping.end();
}

bool JoystickInfo::GetIsAvailableAxisMapping() const {
    return AxisMapping.find(product_) != AxisMapping.end();
}

std::shared_ptr<Joystick> Joystick::instance_ = nullptr;

Joystick::Joystick() : connectedJoystickCount_(0) {
    // hidapiDevices_.fill(nullptr);
    joystickInfo_.fill(nullptr);
    for (int32_t i = 0; i < MAX_JOYSTICKS_NUM; i++) {
        currentHit_[i].fill(false);
        preHit_[i].fill(false);
        currentAxis_[i].fill(0.0);
    }
}

bool Joystick::Initialize() {
    instance_ = MakeAsdShared<Joystick>();
    instance_->RefreshInputState();

    return true;
};

void Joystick::Terminate() {
    instance_ = nullptr;
}

std::shared_ptr<Joystick>& Joystick::GetInstance() { return instance_; }

std::u16string Joystick::ToU16(const std::wstring& wstr) const {
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

void Joystick::RefreshInputState() {
    preHit_ = currentHit_;

    for (int jind = 0; jind < MAX_JOYSTICKS_NUM; jind++) {
        auto isPresent = glfwJoystickPresent(jind) == GLFW_TRUE;

        // Joystickの接続が外れたフレーム
        if (!isPresent) {
            // if(hidapiDevices_[jind] != nullptr) {
            //     hidapiDevices_[jind] = nullptr;
            // }

            if (joystickInfo_[jind] != nullptr) {
                connectedJoystickCount_--;
                joystickInfo_[jind] = nullptr;
            }

            continue;
        }

        int32_t buttonsCount = 0;
        auto btns = glfwGetJoystickButtons(jind, &buttonsCount);
        for (int i = 0; i < buttonsCount; ++i) {
            currentHit_[jind][i] = (bool)btns[i];
        }

        int32_t axesCount = 0;
        auto ax = glfwGetJoystickAxes(jind, &axesCount);
        for (int i = 0; i < axesCount; ++i) {
            currentAxis_[jind][i] = ax[i];
        }

        // Joystickが接続されたフレーム
        if (joystickInfo_[jind] == nullptr) {
            auto name = glfwGetJoystickName(jind);
            auto guid = glfwGetJoystickGUID(jind);
            joystickInfo_[jind] = MakeAsdShared<JoystickInfo>(utf8_to_utf16(std::string(name)), buttonsCount, axesCount, guid);
            connectedJoystickCount_++;

            // VendorId, ProductIdをもとにhid_device*を取得してunique_ptrに変換する。
            // 同じJoystickが接続されている場合にそれらをどうやって区別しよう？
        }

        // 特定のジョイスティックに対する補正
        auto info = joystickInfo_[jind];
        if (info->IsJoystickType(JoystickType::XBOX360)) {
            currentHit_[jind][14] = currentAxis_[jind][4] > 0.8;
            currentHit_[jind][15] = currentAxis_[jind][5] > 0.8;
        }
    }
};

bool Joystick::IsPresent(int32_t joystickIndex) const {
    return (0 <= joystickIndex) && (joystickIndex < MAX_JOYSTICKS_NUM) && joystickInfo_[joystickIndex] != nullptr;
}

int32_t Joystick::GetConnectedJoystickCount() const {
    return connectedJoystickCount_;
}

std::shared_ptr<JoystickInfo> Joystick::GetJoystickInfo(int32_t joystickIndex) const {
    if (joystickIndex < 0 || MAX_JOYSTICKS_NUM <= joystickIndex) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetJoystickInfo: joystickIndex '{0}' is out of range.", joystickIndex);
        return nullptr;
    }

    return joystickInfo_[joystickIndex];
}

ButtonState Joystick::GetButtonStateByIndex(int32_t joystickIndex, int32_t buttonIndex) const {
    if (!IsPresent(joystickIndex)) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetButtonStateByIndex: Joystick is not present at {0}", joystickIndex);
        return ButtonState::Free;
    }

    auto buttonCount = joystickInfo_[joystickIndex]->GetButtonCount();
    if (buttonIndex < 0 || buttonCount <= buttonIndex) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetButtonStateByIndex: 'buttonIndex: {0}' is out of range, ButtonCount is", buttonIndex, buttonCount);
        return ButtonState::Free;
    }

    auto current = currentHit_[joystickIndex][buttonIndex];
    auto pre = preHit_[joystickIndex][buttonIndex];

    if (current && pre) return ButtonState::Hold;
    if (!current && pre) return ButtonState::Release;
    if (current && !pre) return ButtonState::Push;
    return ButtonState::Free;
};

ButtonState Joystick::GetButtonStateByType(int32_t joystickIndex, JoystickButtonType type) const {
    if (!IsPresent(joystickIndex)) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetButtonStateByType: Joystick is not present at {0}", joystickIndex);
        return ButtonState::Free;
    }

    auto info = joystickInfo_[joystickIndex];

    auto productId = info->GetProduct();

    auto mapping = ButtonMapping.find(productId);

    if (mapping == ButtonMapping.end()) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetButtonStateByType: ButtonMapping is not found for joyscitk(index:{0}, name:{1}) ", joystickIndex, utf16_to_utf8(std::u16string(info->GetName())));
        return ButtonState::Free;
    }

    auto buttonIndex = mapping->second.find(type);

    if (buttonIndex == mapping->second.end()) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetButtonStateByType: Mapping of ButtonType '{0}' is not found for joyscitk(index:{1}, name:{2}) ", static_cast<int32_t>(type), joystickIndex, utf16_to_utf8(std::u16string(info->GetName())));
        return ButtonState::Free;
    }

    return GetButtonStateByIndex(joystickIndex, buttonIndex->second);
};

float Joystick::GetAxisStateByIndex(int32_t joystickIndex, int32_t axisIndex) const {
    if (!IsPresent(joystickIndex)) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetAxisStateByIndex: Joystick is not present at {0}", joystickIndex);
        return 0.0f;
    }

    auto axisCount = joystickInfo_[joystickIndex]->GetAxisCount();
    if (axisIndex < 0 || axisCount <= axisIndex) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetAxisStateByIndex: 'axisIndex: {0}' is out of range, ButtonCount is", axisIndex, axisCount);
        return 0.0f;
    }

    return currentAxis_[joystickIndex][axisIndex];
};

float Joystick::GetAxisStateByType(int32_t joystickIndex, JoystickAxisType type) const {
    if (!IsPresent(joystickIndex)) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetAxisStateByType: Joystick is not present at {0}", joystickIndex);
        return 0.0f;
    }

    auto info = joystickInfo_[joystickIndex];

    auto productId = info->GetProduct();

    auto mapping = AxisMapping.find(productId);

    if (mapping == AxisMapping.end()) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetAxisStateByType: AxisMapping is not found for joyscitk(index:{0}, name:{1}) ", joystickIndex, utf16_to_utf8(std::u16string(info->GetName())));
        return 0.0f;
    }

    auto axisIndex = mapping->second.find(type);

    if (axisIndex == mapping->second.end()) {
        Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::GetAxisStateByType: Mapping of AxisType '{0}' is not found for joyscitk(index:{1}, name:{2}) ", static_cast<int32_t>(type), joystickIndex, utf16_to_utf8(std::u16string(info->GetName())));
        return 0.0f;
    }

    return GetAxisStateByIndex(joystickIndex, axisIndex->second);
};

// void Joystick::Vibrate(int32_t joystickIndex, float frequency, float amplitude) {
//     Log::GetInstance()->Warn(LogCategory::Core, u"Joystick::Vibrate is not supported yet");
// }

}  // namespace Altseed
