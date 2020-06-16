
#include "Joystick.h"

#include <algorithm>
#include <cstring>

#include "../Common/Miscs.h"
#include "../Logger/Log.h"


namespace Altseed {

JoystickInfo::JoystickInfo(const std::u16string name, const int32_t buttonCount, const int32_t axisCount, const char* guid)
    : name_(name), buttonCount_(buttonCount), axisCount_(axisCount)
{
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

std::shared_ptr<Joystick> Joystick::instance_ = nullptr;

Joystick::Joystick() {
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

        if (!isPresent) {
            joystickInfo_[jind] = nullptr;
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

        if (joystickInfo_[jind] == nullptr) {
            auto name = glfwGetJoystickName(jind);
            auto guid = utf8_to_utf16(std::string(glfwGetJoystickGUID(jind)));
            joystickInfo_[jind] = MakeAsdShared<JoystickInfo>(utf8_to_utf16(std::string(name)), buttonsCount, axesCount, guid);
        }

        // auto jtype = GetJoystickType(jind);

        // if (jtype == JoystickType::XBOX360) {
        //     currentHit[jind][14] = currentAxis_[jind][4] > 0.8;
        //     currentHit[jind][15] = currentAxis_[jind][5] > 0.8;
        // }
    }
};

bool Joystick::IsPresent(int32_t joystickIndex) const {
    return (0 <= joystickIndex) && (joystickIndex < MAX_JOYSTICKS_NUM) && joystickInfo_[joystickIndex] != nullptr;
}

std::shared_ptr<JoystickInfo> Joystick::GetJoystickInfo(int32_t index) const {
    if (index < 0 || MAX_JOYSTICKS_NUM <= index) {
        Log::GetInstance()->Error(LogCategory::Core, u"Joystick::GetJoystickInfo: Joystick index '{0}' is out of range.", index);
        return nullptr;
    }

    return joystickInfo_[index];
}

ButtonState Joystick::GetButtonStateByIndex(int32_t joystickIndex, int32_t buttonIndex) const {
    if (!IsPresent(joystickIndex)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Joystick::GetButtonStateByIndex: Joystick is not present at {0}", joystickIndex);
        return ButtonState::Free;
    }

    auto buttonCount = joystickInfo_[joystickIndex]->GetButtonCount();
    if (buttonIndex < 0 || buttonCount <= buttonIndex) {
        Log::GetInstance()->Error(LogCategory::Core, u"Joystick::GetButtonStateByIndex: 'buttonIndex: {0}' is out of range, ButtonCount is", buttonIndex, buttonCount);
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
        Log::GetInstance()->Error(LogCategory::Core, u"Joystick::GetButtonStateByType: Joystick is not present at {0}", joystickIndex);
        return ButtonState::Free;
    }

    // TODO
    return GetButtonStateByIndex(joystickIndex, -1);
};

float Joystick::GetAxisStateByIndex(int32_t joystickIndex, int32_t axisIndex) const {
    if (!IsPresent(joystickIndex)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Joystick::GetAxisStateByIndex: Joystick is not present at {0}", joystickIndex);
        return 0.0f;
    }

    auto axisCount = joystickInfo_[joystickIndex]->GetAxisCount();
    if (axisIndex < 0 || axisCount <= axisIndex) {
        Log::GetInstance()->Error(LogCategory::Core, u"Joystick::GetAxisStateByIndex: 'axisIndex: {0}' is out of range, ButtonCount is", axisIndex, axisCount);
        return 0.0f;
    }

    return currentAxis_[joystickIndex][axisIndex];
};

float Joystick::GetAxisStateByType(int32_t joystickIndex, JoystickAxisType type) const {
    if (!IsPresent(joystickIndex)) {
        Log::GetInstance()->Error(LogCategory::Core, u"Joystick::GetAxisStateByType: Joystick is not present at {0}", joystickIndex);
        return 0.0f;
    }

    // TODO
    return GetAxisStateByIndex(joystickIndex, -1);
};

}  // namespace Altseed
