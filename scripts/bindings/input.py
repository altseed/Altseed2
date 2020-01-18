from . import CppBindingGenerator as cbg
import ctypes

from .common import *

ButtonState = cbg.Enum('altseed', 'ButtonState')
with ButtonState as enum:
    enum.add('Free', 0)
    enum.add('Push', 1)
    enum.add('Hold', 3)
    enum.add('Release', 2)

Keys = cbg.Enum('altseed', 'Keys')
with Keys as enum:
    enum.add('Unknown')
    enum.add('Space')
    enum.add('Apostrophe')
    enum.add('Comma')
    enum.add('Minus')
    enum.add('Period')
    enum.add('Slash')
    enum.add('Num0')
    enum.add('Num1')
    enum.add('Num2')
    enum.add('Num3')
    enum.add('Num4')
    enum.add('Num5')
    enum.add('Num6')
    enum.add('Num7')
    enum.add('Num8')
    enum.add('Num9')
    enum.add('Semicolon')
    enum.add('Equal')
    enum.add('A')
    enum.add('B')
    enum.add('C')
    enum.add('D')
    enum.add('E')
    enum.add('F')
    enum.add('G')
    enum.add('H')
    enum.add('I')
    enum.add('J')
    enum.add('K')
    enum.add('L')
    enum.add('M')
    enum.add('N')
    enum.add('O')
    enum.add('P')
    enum.add('Q')
    enum.add('R')
    enum.add('S')
    enum.add('T')
    enum.add('U')
    enum.add('V')
    enum.add('W')
    enum.add('X')
    enum.add('Y')
    enum.add('Z')
    enum.add('LeftBracket')
    enum.add('Backslash')
    enum.add('RightBracket')
    enum.add('GraveAccent')
    enum.add('World1')
    enum.add('World2')
    enum.add('Escape')
    enum.add('Enter')
    enum.add('Tab')
    enum.add('Backspace')
    enum.add('Insert')
    enum.add('Delete')
    enum.add('Right')
    enum.add('Left')
    enum.add('Down')
    enum.add('Up')
    enum.add('PageUp')
    enum.add('PageDown')
    enum.add('Home')
    enum.add('End')
    enum.add('CapsLock')
    enum.add('ScrollLock')
    enum.add('NumLock')
    enum.add('PrintScreen')
    enum.add('Pause')
    enum.add('F1')
    enum.add('F2')
    enum.add('F3')
    enum.add('F4')
    enum.add('F5')
    enum.add('F6')
    enum.add('F7')
    enum.add('F8')
    enum.add('F9')
    enum.add('F10')
    enum.add('F11')
    enum.add('F12')
    enum.add('F13')
    enum.add('F14')
    enum.add('F15')
    enum.add('F16')
    enum.add('F17')
    enum.add('F18')
    enum.add('F19')
    enum.add('F20')
    enum.add('F21')
    enum.add('F22')
    enum.add('F23')
    enum.add('F24')
    enum.add('F25')
    enum.add('Keypad0')
    enum.add('Keypad1')
    enum.add('Keypad2')
    enum.add('Keypad3')
    enum.add('Keypad4')
    enum.add('Keypad5')
    enum.add('Keypad6')
    enum.add('Keypad7')
    enum.add('Keypad8')
    enum.add('Keypad9')
    enum.add('KeypadDecimal')
    enum.add('KeypadDivide')
    enum.add('KeypadMultiply')
    enum.add('KeypadSubstract')
    enum.add('KeypadAdd')
    enum.add('KeypadEnter')
    enum.add('KeypadEqual')
    enum.add('LeftShift')
    enum.add('LeftControl')
    enum.add('LeftAlt')
    enum.add('LeftWin')
    enum.add('RightShift')
    enum.add('RightControl')
    enum.add('RightAlt')
    enum.add('RightWin')
    enum.add('Menu')
    enum.add('Last')
    enum.add('MAX')

Keyboard = cbg.Class('altseed', 'Keyboard')
with Keyboard as class_:
    # Initialize は Core 内部で呼び出されるので Engine には公開しない
    with class_.add_func('GetKeyState') as func:
        func.add_arg(Keys, 'key')
        func.return_value.type_ = ButtonState
    with class_.add_func('GetInstance') as func:
        func.return_value.type_ = Keyboard
        func.is_static = True

MouseButtons = cbg.Enum('altseed', 'MouseButtons')
with MouseButtons as enum:
    enum.add('ButtonLeft', 0)
    enum.add('ButtonRight', 1)
    enum.add('ButtonMiddle', 2)
    enum.add('SubButton1', 3)
    enum.add('SubButton2', 4)
    enum.add('SubButton3', 5)
    enum.add('SubButton4', 6)
    enum.add('SubButton5', 7)

CursorMode = cbg.Enum('altseed', 'CursorMode')
with CursorMode as enum:
    enum.add('Normal', 0x00034001)
    enum.add('Hidden', 0x00034002)
    enum.add('Disable', 0x00034003)

Mouse = cbg.Class('altseed', 'Mouse')
with Mouse as class_:
    # Initialize は Core 内部で呼び出されるので Engine には公開しない
    with class_.add_func('GetInstance') as func:
        func.return_value.type_ = Mouse
    class_.add_func('RefreshInputState')
    with class_.add_func('SetPosition') as func:
        func.add_arg(Vector2DF, 'vec')
    with class_.add_func('GetPosition') as func:
        func.return_value.type_ = Vector2DF
    with class_.add_func('GetWheel') as func:
        func.return_value.type_ = float
    with class_.add_func('GetMouseButtonState') as func:
        func.add_arg(MouseButtons, 'button')
        func.return_type = ButtonState
    with class_.add_property(CursorMode, 'CursorMode') as prop:
        prop.has_getter = True
        prop.has_setter = True

JoystickType = cbg.Enum('altseed', 'JoystickType')
with JoystickType as enum:
    enum.add('Other', 0)
    enum.add('PS4', 8200)
    enum.add('XBOX360', 8199)
    enum.add('JoyconL', 8198)
    enum.add('JoyconR', 8197)

JoystickButtonType = cbg.Enum('altseed', 'JoystickButtonType')
with JoystickButtonType as enum:
    enum.add('Start')
    enum.add('Select')
    enum.add('Home')
    enum.add('Release')
    enum.add('Capture')
    enum.add('LeftUp')
    enum.add('LeftDown')
    enum.add('LeftLeft')
    enum.add('LeftRight')
    enum.add('LeftPush')
    enum.add('RightUp')
    enum.add('RightRight')
    enum.add('RightLeft')
    enum.add('RightDown')
    enum.add('RightPush')
    enum.add('L1')
    enum.add('R1')
    enum.add('L2')
    enum.add('R2')
    enum.add('L3')
    enum.add('R3')
    enum.add('LeftStart')
    enum.add('RightStart')
    enum.add('Max')

JoystickAxisType = cbg.Enum('altseed', 'JoystickAxisType')
with JoystickAxisType as enum:
    enum.add('Start')
    enum.add('LeftH')
    enum.add('LeftV')
    enum.add('RightH')
    enum.add('RightV')
    enum.add('L2')
    enum.add('R2')
    enum.add('Max')

Joystick = cbg.Class('altseed', 'Joystick')
with Joystick as class_:
    # Core 内部で呼び出されるので Initialize は Engineに公開しない
    with class_.add_func('IsPresent') as func:
        func.add_arg(int, 'joystickIndex')
        func.return_type = bool
    class_.add_func('RefreshInputState')
    class_.add_func('RefreshConnectedState')
    with class_.add_func('GetButtonStateByIndex') as func:
        func.add_arg(int, 'joystickIndex')
        func.add_arg(int, 'buttonIndex')
        func.return_value.type_ = ButtonState
    with class_.add_func('GetButtonStateByType') as func:
        func.add_arg(int, 'joystickIndex')
        func.add_arg(JoystickButtonType, 'type')
        func.return_value.type_ = ButtonState
    with class_.add_func('GetJoystickType') as func:
        func.add_arg(int, 'index')
        func.return_value.type_ = JoystickType
    with class_.add_func('GetAxisStateByIndex') as func:
        func.add_arg(int, 'joystickIndex')
        func.add_arg(int, 'axisIndex')
        func.return_value.type_ = float
    with class_.add_func('GetAxisStateByType') as func:
        func.add_arg(int, 'joystickIndex')
        func.add_arg(JoystickAxisType, 'type')
        func.return_value.type_ = float
    with class_.add_func('GetJoystickName') as func:
        func.add_arg(int, 'index')
        func.return_value.type_ = ctypes.c_wchar_p
    class_.add_func('RefreshVibrateState')
    with class_.add_func('SetVibration') as func:
        func.add_arg(int, 'index')
        func.add_arg(float, 'high_freq')
        func.add_arg(float, 'low_freq')
        func.add_arg(float, 'high_amp')
        func.add_arg(float, 'low_amp')
        func.add_arg(int, 'life_time')

