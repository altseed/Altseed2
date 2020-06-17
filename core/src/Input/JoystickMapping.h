#pragma once
#include <map>

#include "Joystick.h"

namespace Altseed {

// DualShock4
static const std::map<JoystickButtonType, int32_t> DualShock4ButtonMapping{
        {JoystickButtonType::RightLeft, 0},  // Square
        {JoystickButtonType::RightDown, 1},  // Cross
        {JoystickButtonType::RightRight, 2},  // Circle
        {JoystickButtonType::RightUp, 3},  // Triangle

        {JoystickButtonType::L1, 4},
        {JoystickButtonType::R1, 5},
        {JoystickButtonType::L2, 6},
        {JoystickButtonType::R2, 7},

        {JoystickButtonType::LeftPush, 10},
        {JoystickButtonType::RightPush, 11},

        {JoystickButtonType::LeftUp, 14},
        {JoystickButtonType::LeftRight, 15},
        {JoystickButtonType::LeftDown, 16},
        {JoystickButtonType::LeftLeft, 17},

        {JoystickButtonType::Capture, 8},  // SHARE
        {JoystickButtonType::RightStart, 9},  // Options
        {JoystickButtonType::Home, 12},  // Home
        {JoystickButtonType::LeftStart, 13},  // TouchPad
};

static const std::map<JoystickAxisType, int32_t> DualShock4AxisMapping{
        {JoystickAxisType::LeftH, 0},
        {JoystickAxisType::LeftV, 1},
        {JoystickAxisType::RightH, 2},
        {JoystickAxisType::RightV, 5},

        {JoystickAxisType::L2, 3},
        {JoystickAxisType::R2, 4},
};

// XBOX360
static const std::map<JoystickButtonType, int32_t> XBOX360ButtonMapping{
        {JoystickButtonType::RightLeft, 2},
        {JoystickButtonType::RightDown, 0},
        {JoystickButtonType::RightRight, 1},
        {JoystickButtonType::RightUp, 3},

        {JoystickButtonType::L1, 4},
        {JoystickButtonType::R1, 5},
        {JoystickButtonType::L2, 14},
        {JoystickButtonType::R2, 15},

        {JoystickButtonType::LeftPush, 8},
        {JoystickButtonType::RightPush, 9},

        {JoystickButtonType::LeftUp, 10},
        {JoystickButtonType::LeftRight, 11},
        {JoystickButtonType::LeftDown, 12},
        {JoystickButtonType::LeftLeft, 13},

        {JoystickButtonType::LeftStart, 6},
        {JoystickButtonType::RightStart, 7},
        // {JoystickButtonType::Capture, },
        // {JoystickButtonType::Home, },
};

static const std::map<JoystickAxisType, int32_t> XBOX360AxisMapping{
        {JoystickAxisType::LeftH, 0},
        {JoystickAxisType::LeftV, 1},
        {JoystickAxisType::RightH, 2},
        {JoystickAxisType::RightV, 3},

        {JoystickAxisType::L2, 4},
        {JoystickAxisType::R2, 5},
};

// JoyconR
static const std::map<JoystickButtonType, int32_t> JoyconRButtonMapping{
        {JoystickButtonType::RightLeft, 2},
        {JoystickButtonType::RightDown, 0},
        {JoystickButtonType::RightRight, 1},
        {JoystickButtonType::RightUp, 3},

        {JoystickButtonType::L1, 4},  // SL
        {JoystickButtonType::R1, 5},  // SR

        {JoystickButtonType::R2, 14},  // R
        {JoystickButtonType::R3, 15},  // ZR

        {JoystickButtonType::LeftPush, 11},  // stick

        {JoystickButtonType::LeftUp, 16},
        {JoystickButtonType::LeftRight, 17},
        {JoystickButtonType::LeftDown, 18},
        {JoystickButtonType::LeftLeft, 19},

        {JoystickButtonType::RightStart, 9},
        {JoystickButtonType::Home, 12},
};

// JoyconL
static const std::map<JoystickButtonType, int32_t> JoyconLButtonMapping{
        {JoystickButtonType::RightLeft, 2},
        {JoystickButtonType::RightDown, 0},
        {JoystickButtonType::RightRight, 1},
        {JoystickButtonType::RightUp, 3},

        {JoystickButtonType::L1, 4},  // SL
        {JoystickButtonType::R1, 5},  // SR

        {JoystickButtonType::L2, 14},  // L
        {JoystickButtonType::L3, 15},  // ZL

        {JoystickButtonType::RightPush, 10},  // stick

        {JoystickButtonType::LeftUp, 16},
        {JoystickButtonType::LeftRight, 17},
        {JoystickButtonType::LeftDown, 18},
        {JoystickButtonType::LeftLeft, 19},

        {JoystickButtonType::LeftStart, 8},
        {JoystickButtonType::Capture, 13},
};

// ProController
static const std::map<JoystickButtonType, int32_t> ProControllerButtonMapping{
        {JoystickButtonType::RightLeft, 2},
        {JoystickButtonType::RightDown, 0},
        {JoystickButtonType::RightRight, 1},
        {JoystickButtonType::RightUp, 3},

        {JoystickButtonType::L1, 4},  // SL
        {JoystickButtonType::R1, 5},  // SR

        {JoystickButtonType::L2, 6},  // ZL
        {JoystickButtonType::R2, 7},  // ZR

        {JoystickButtonType::LeftPush, 11},
        {JoystickButtonType::RightPush, 10},

        {JoystickButtonType::LeftUp, 16},
        {JoystickButtonType::LeftRight, 17},
        {JoystickButtonType::LeftDown, 18},
        {JoystickButtonType::LeftLeft, 19},

        {JoystickButtonType::LeftStart, 8},
        {JoystickButtonType::RightStart, 9},
        {JoystickButtonType::Home, 12},
        {JoystickButtonType::Capture, 12},
};

static const std::map<JoystickAxisType, int32_t> ProControllerAxisMapping{
        {JoystickAxisType::LeftH, 0},
        {JoystickAxisType::LeftV, 1},
        {JoystickAxisType::RightH, 2},
        {JoystickAxisType::RightV, 3},
};

static const std::map<JoystickButtonType, int32_t> pseudo;

static const std::map<int32_t, const std::map<JoystickButtonType, int32_t>> ButtonMapping{
        {static_cast<int32_t>(JoystickType::DualShock4), DualShock4ButtonMapping},
        {static_cast<int32_t>(JoystickType::XBOX360), XBOX360ButtonMapping},
        {static_cast<int32_t>(JoystickType::JoyconR), JoyconRButtonMapping},
        {static_cast<int32_t>(JoystickType::JoyconL), JoyconLButtonMapping},
        {static_cast<int32_t>(JoystickType::ProController), ProControllerButtonMapping},
};

static const std::map<int32_t, const std::map<JoystickAxisType, int32_t>> AxisMapping{
        {static_cast<int32_t>(JoystickType::DualShock4), DualShock4AxisMapping},
        {static_cast<int32_t>(JoystickType::XBOX360), XBOX360AxisMapping},
        {static_cast<int32_t>(JoystickType::ProController), ProControllerAxisMapping},
};
};  // namespace Altseed