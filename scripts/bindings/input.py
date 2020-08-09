from . import CppBindingGenerator as cbg
import ctypes

from .common import *
from .math import *

ButtonState = cbg.Enum('Altseed2', 'ButtonState')
with ButtonState as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'ボタンの押下状態を表します。')
    with enum.add('Free', 0) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'ボタンが押されていない状態')
    with enum.add('Push', 1) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'ボタンが押された瞬間の状態')
    with enum.add('Hold', 3) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'ボタンが押されている状態')
    with enum.add('Release', 2) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'ボタンが話された瞬間の状態')

Key = cbg.Enum('Altseed2', 'Key')
with Key as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'キーボードのキーの種類を表します。')
    with enum.add('Unknown') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '未知のキー')
    enum.add('Space')
    enum.add('Apostrophe')
    enum.add('Comma')
    enum.add('Minus')
    enum.add('Period')
    enum.add('Slash')
    with enum.add('Num0') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの0')
    with enum.add('Num1') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの1')
    with enum.add('Num2') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの2')
    with enum.add('Num3') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの3')
    with enum.add('Num4') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの4')
    with enum.add('Num5') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの5')
    with enum.add('Num6') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの6')
    with enum.add('Num7') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの7')
    with enum.add('Num8') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの8')
    with enum.add('Num9') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'テンキーの9')
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
    with enum.add('Right') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '矢印キー右')
    with enum.add('Left') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '矢印キー左')
    with enum.add('Down') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '矢印キー下')
    with enum.add('Up') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '矢印キー上')
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
    with enum.add('LeftShift') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左側のShiftキー')
    with enum.add('LeftControl') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左側のCtrlキー')
    with enum.add('LeftAlt') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左側のAltキー')
    with enum.add('LeftWin') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左側のWinキー')
    with enum.add('RightShift') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右側のShiftキー')
    with enum.add('RightControl') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右側のCtrlキー')
    with enum.add('RightAlt') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右側のAltキー')
    with enum.add('RightWin') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右側のWinキー')
    enum.add('Menu')
    enum.add('Last')

Cursor = cbg.Class('Altseed2', 'Cursor')
with Cursor as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'カーソルを表します。')
    class_.is_Sealed = True

    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add(
            'ja', '指定したpng画像を読み込んだ<see cref="Cursor"/>のインスタンスを生成します。')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むpng画像のパス')
            arg.nullable = False
        with func.add_arg(Vector2I, 'hot') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'カーソルのクリック判定座標を指定します。カーソル画像はここが中心となります。')

        func.is_static = True
        func.return_value.type_ = Cursor
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', '指定したpng画像を読み込んだ<see cref="Cursor"/>のインスタンス')

Keyboard = cbg.Class('Altseed2', 'Keyboard')
with Keyboard as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'キーボードを表します。')
    class_.is_Sealed = True

    # Initialize は Core 内部で呼び出されるので Engine には公開しない
    with class_.add_func('GetKeyState') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'キーの状態を取得します。')
        with func.add_arg(Key, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'キー')
        func.return_value.type_ = ButtonState
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'ボタンの押下状態')
        func.brief = cbg.Description()
        func.brief.add('ja', 'キーの状態を取得します。')
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.return_value.type_ = Keyboard
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_static = True
        func.is_public = False

MouseButton = cbg.Enum('Altseed2', 'MouseButton')
with MouseButton as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'マウスのボタンの種類を表します。')
    with enum.add('ButtonLeft', 0) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左ボタン')
    with enum.add('ButtonRight', 1) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '中央ボタン')
    with enum.add('ButtonMiddle', 2) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右ボタン')
    with enum.add('SubButton1', 3) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'サブボタン1')
    with enum.add('SubButton2', 4) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'サブボタン2')
    with enum.add('SubButton3', 5) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'サブボタン3')
    with enum.add('SubButton4', 6) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'サブボタン4')
    with enum.add('SubButton5', 7) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'サブボタン5')

CursorMode = cbg.Enum('Altseed2', 'CursorMode')
with CursorMode as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'カーソルの状態を表します。')
    with enum.add('Normal', 0x00034001) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '通常の状態')
    with enum.add('Hidden', 0x00034002) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '隠れている状態')
    with enum.add('Disable', 0x00034003) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '使用できない状態')

Mouse = cbg.Class('Altseed2', 'Mouse')
with Mouse as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'マウスを表します。')
    class_.is_Sealed = True

    # Initialize は Core 内部で呼び出されるので Engine には公開しない
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
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
        prop.brief.add('ja', 'カーソルのモードを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(float, 'Wheel') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'マウスホイールの回転量を取得します。')
        prop.has_getter = True
    with class_.add_func('GetMouseButtonState') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'マウスボタンの状態を取得します。')
        with func.add_arg(MouseButton, 'button') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を取得するマウスのボタン')
        func.return_value.type_ = ButtonState
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'マウスボタンの状態')
    with class_.add_func('SetCursorImage') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'カーソル画像をセットします。')
        with func.add_arg(Cursor, 'cursor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を取得するマウスのボタン')

JoystickType = cbg.Enum('Altseed2', 'JoystickType')
with JoystickType as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'ジョイスティックの種類を表します。')
    with enum.add('Other', 0) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '未知の種類のジョイスティック')
    
    with enum.add('DualShock3', 616) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'PlayStation DualShock3')
    
    with enum.add('DualShock4', 1476) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'PlayStation DualShock4')
    
    with enum.add('DualShock4Slim', 2508) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'PlayStation DualShock4Slim')

    with enum.add('XBOX360', 654) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'XBOX360のジョイスティック')

    with enum.add('JoyconL', 8198) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'NintendoSwitch 左のJon-Con')

    with enum.add('JoyconR', 8199) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'NintendoSwitch 右のJon-Con')

    with enum.add('ProController', 8201) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'NintendoSwitch ProController')

JoystickButton = cbg.Enum('Altseed2', 'JoystickButton')
with JoystickButton as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'ジョイスティックのボタンの種類を表します。')

    RightDownButton = 0
    RightRightButton = 1
    RightLeftButton = 2
    RightUpButton = 3

    with enum.add('RightDown', RightDownButton) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右側下ボタン')

    with enum.add('RightRight', RightRightButton) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右側右ボタン')

    with enum.add('RightLeft', RightLeftButton) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右側左ボタン')

    with enum.add('RightUp', RightUpButton) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右側上ボタン')

    with enum.add('LeftBumper', 4) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'Lボタン')

    with enum.add('RightBumper', 5) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'Rボタン')

    with enum.add('Back', 6) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '戻るボタン')

    with enum.add('Start', 7) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'スタートボタン')

    with enum.add('Guide', 8) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'ガイドボタン')

    with enum.add('LeftThumb', 9) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左スティック押し込み')

    with enum.add('RightThumb', 10) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右スティック押し込み')

    with enum.add('DPadUp', 11) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '十字キー上')

    with enum.add('DPadRight', 12) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '十字キー右')

    with enum.add('DPadDown', 13) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '十字キー下')

    with enum.add('DPadLeft', 14) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '十字キー左')


JoystickAxis = cbg.Enum('Altseed2', 'JoystickAxis')
with JoystickAxis as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'ジョイスティックの軸の種類を表します。')
    with enum.add('LeftX', 0) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左スティック横')

    with enum.add('LeftY', 1) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左スティック縦')

    with enum.add('RightX', 2) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右スティック横')

    with enum.add('RightY', 3) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右スティック縦')

    with enum.add('LeftTrigger', 4) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '左トリガー')

    with enum.add('RightTrigger', 5) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '右トリガー')


JoystickInfo = cbg.Class('Altseed2', 'JoystickInfo')
with JoystickInfo as class_:
    with class_.add_property(ctypes.c_wchar_p, 'Name') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(int, 'ButtonCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(int, 'AxisCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(bool, 'IsGamepad') as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', 'ジョイスティックがGamepadとして使えるかどうかを取得します。')
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(ctypes.c_wchar_p, 'GamepadName') as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', 'ジョイスティックがGamepadとして使える時、その名前を取得します。')
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(ctypes.c_wchar_p, 'GUID') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(int, 'Bustype') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(int, 'Vendor') as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '製造者IDを取得します。')
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(int, 'Product') as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '製品IDを取得します。')
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_property(int, 'Version') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.is_public = True

    with class_.add_func('IsJoystickType') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したジョイスティックの種類に合致するかどうかを取得します。')
        func.add_arg(JoystickType, 'type')
        func.return_value.type_ = bool


Joystick = cbg.Class('Altseed2', 'Joystick')
with Joystick as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ジョイスティックを表すクラス')
    class_.is_Sealed = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.return_value.type_ = Joystick
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_public = False
        func.is_static = True

    with class_.add_func('IsPresent') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したジョイスティックが存在しているかどうかを取得します。')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ジョイスティックのインデックス')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定したジョイスティックが存在したらtrue，存在していなかったらfalse')

    with class_.add_property(int, 'ConnectedJoystickCount') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '接続されているジョイスティックの数を取得します。')
        prop.has_getter = True
        prop.has_setter = False
        prop.is_public = True
        
    with class_.add_func('GetJoystickInfo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したジョイスティックの情報を取得します。')

        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ジョイスティックのインデックス')

        func.return_value.type_ = JoystickInfo

    with class_.add_func('GetButtonStateByIndex') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ボタンの状態をインデックスで取得します。')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するジョイスティックのインデックス')
        with func.add_arg(int, 'buttonIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を検索するボタンのインデックス')
        func.return_value.type_ = ButtonState
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'ボタンの状態')
        func.is_public = False
        func.onlyExtern = True

    with class_.add_func('GetButtonStateByType') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ボタンの状態を種類から取得します。')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するジョイスティックのインデックス')
        with func.add_arg(JoystickButton, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を検索するボタンの種類')
        func.return_value.type_ = ButtonState
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'ボタンの状態')
        func.is_public = False
        func.onlyExtern = True

    with class_.add_func('GetAxisStateByIndex') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '軸の状態をインデックスで取得します。')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するジョイスティックのインデックス')
        with func.add_arg(int, 'axisIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を検索する軸のインデックス')
        func.return_value.type_ = float
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '軸の状態')
        func.is_public = False
        func.onlyExtern = True

    with class_.add_func('GetAxisStateByType') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '軸の状態を軸の種類で取得します。')
        with func.add_arg(int, 'joystickIndex') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するジョイスティックのインデックス')
        with func.add_arg(JoystickAxis, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '状態を検索する軸の種類')
        func.return_value.type_ = float
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '軸の状態')
        func.is_public = False
        func.onlyExtern = True

    # with class_.add_func('Vibrate') as func:
    #     func.brief = cbg.Description()
    #     func.brief.add('ja', '指定したジョイスティックコントローラーを振動させます。')
    #     with func.add_arg(int, 'index') as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', 'ジョイスティックのインデックス')
    #     with func.add_arg(float, 'frequency') as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', '周波数')
    #     with func.add_arg(float, 'amplitude') as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', '振幅')
