from . import CppBindingGenerator as cbg
import ctypes

from .common import *

ButtonState = cbg.Enum('Altseed', 'ButtonState')
with ButtonState as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'ボタンの押下状態を表します。')
    enum.add('Free', 0)
    enum.add('Push', 1)
    enum.add('Hold', 3)
    enum.add('Release', 2)

Keys = cbg.Enum('Altseed', 'Keys')
with Keys as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'キーボードのキーの種類を表す')
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

Keyboard = cbg.Class('Altseed', 'Keyboard')
with Keyboard as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'キーボードを表します。')
    # Initialize は Core 内部で呼び出されるので Engine には公開しない
    with class_.add_func('GetKeyState') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'キーの状態を取得する')
        with func.add_arg(Keys, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'キー')
        func.return_value.type_ = ButtonState
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'ボタンの押下状態')
        func.brief = cbg.Description()
        func.brief.add('ja', 'キーの状態を取得します。')
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得する')
        func.return_value.type_ = Keyboard
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_static = True
        func.is_public = False

MouseButtons = cbg.Enum('Altseed', 'MouseButtons')
with MouseButtons as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'マウスのボタンの種類を表す')
    enum.add('ButtonLeft', 0)
    enum.add('ButtonRight', 1)
    enum.add('ButtonMiddle', 2)
    enum.add('SubButton1', 3)
    enum.add('SubButton2', 4)
    enum.add('SubButton3', 5)
    enum.add('SubButton4', 6)
    enum.add('SubButton5', 7)

CursorMode = cbg.Enum('Altseed', 'CursorMode')
with CursorMode as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'カーソルの状態を表す')
    enum.add('Normal', 0x00034001)
    enum.add('Hidden', 0x00034002)
    enum.add('Disable', 0x00034003)

Mouse = cbg.Class('Altseed', 'Mouse')
with Mouse as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'マウスを表します。')
    # Initialize は Core 内部で呼び出されるので Engine には公開しない
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得する')
        func.return_value.type_ = Mouse
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_public = False
        func.is_static = True
    with class_.add_property(Vector2F, 'Position') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'マウスカーソルの座標を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(CursorMode, 'CursorMode') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'カーソルのモードを取得または設定する')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_func('GetWheel') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'マウスホイールの回転量を取得します。')
        func.return_value.type_ = float
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'マウスカーソルの回転量')
    with class_.add_func('GetMouseButtonState') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'マウスボタンの状態を取得します。')
        with func.add_arg(MouseButtons, 'button') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を取得するマウスのボタン')
        func.return_value.type_ = ButtonState
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'マウスボタンの状態')

JoystickType = cbg.Enum('Altseed', 'JoystickType')
with JoystickType as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'ジョイスティックの種類を表す')
    enum.add('Other', 0)
    enum.add('PS4', 8200)
    enum.add('XBOX360', 8199)
    enum.add('JoyconL', 8198)
    enum.add('JoyconR', 8197)

JoystickButtonType = cbg.Enum('Altseed', 'JoystickButtonType')
with JoystickButtonType as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'ジョイスティックのボタンの種類を表す')
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

JoystickAxisType = cbg.Enum('Altseed', 'JoystickAxisType')
with JoystickAxisType as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'ジョイスティックの軸の種類を表す')
    enum.add('Start')
    enum.add('LeftH')
    enum.add('LeftV')
    enum.add('RightH')
    enum.add('RightV')
    enum.add('L2')
    enum.add('R2')
    enum.add('Max')

Joystick = cbg.Class('Altseed', 'Joystick')
with Joystick as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ジョイスティックを表すクラス')
    # Core 内部で呼び出されるので Initialize は Engineに公開しない
    with class_.add_func('IsPresent') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したジョイスティックが親であるかどうかを取得する')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ジョイスティックのインデックス')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定したジョイスティックが親であったらtrue，それ以外でfalse')
    with class_.add_func('RefreshInputState') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インプットの状態をリセットする')
    with class_.add_func('RefreshConnectedState') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '接続の状態をリセットする')
    with class_.add_func('GetButtonStateByIndex') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ボタンの状態をインデックスで取得する')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するジョイスティックのインデックス')
        with func.add_arg(int, 'buttonIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を検索するボタンのインデックス')
        func.return_value.type_ = ButtonState
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定インデックスのボタンの状態')
    with class_.add_func('GetButtonStateByType') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ボタンの状態を種類から取得する')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するジョイスティックのインデックス')
        with func.add_arg(JoystickButtonType, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を検索するボタンの種類')
        func.return_value.type_ = ButtonState
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定種類のボタンの状態')
    with class_.add_func('GetJoystickType') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定インデックスのジョイスティックの種類を取得する')
        with func.add_arg(int, 'index') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '種類を取得するジョイスティックのインデックス')
        func.return_value.type_ = JoystickType
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定インデックスのジョイスティックの種類')
    with class_.add_func('GetAxisStateByIndex') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '軸の状態をインデックスで取得する')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するジョイスティックのインデックス')
        with func.add_arg(int, 'axisIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を検索する軸のインデックス')
        func.return_value.type_ = float
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定インデックスの軸の状態')
    with class_.add_func('GetAxisStateByType') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '軸の状態を軸の種類で取得する')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するジョイスティックのインデックス')
        with func.add_arg(JoystickAxisType, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を検索する軸の種類')
        func.return_value.type_ = float
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定種類の軸の状態')
    with class_.add_func('GetJoystickName') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ジョイスティックの名前を取得する')
        with func.add_arg(int, 'index') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '名前を検索するジョイスティックのインデックス')
        func.return_value.type_ = ctypes.c_wchar_p
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定したインデックスのジョイスティックの名前')
    with class_.add_func('RefreshVibrateState') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '振動の状態をリセットする')
    with class_.add_func('SetVibration') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '振動を設定する')
        with func.add_arg(int, 'index') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ジョイスティックのインデックス')
        with func.add_arg(float, 'high_freq') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(float, 'low_freq') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(float, 'high_amp') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(float, 'low_amp') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(int, 'life_time') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')

