import cbg
import ctypes
import sys

VoidPtr = cbg.Class('altseed', 'VoidPtr')

SeekOrigin = cbg.Enum('altseed', 'SeekOrigin')
with SeekOrigin as enum:
    enum.add('Begin')
    enum.add('Current')
    enum.add('End')

Bytes = cbg.Class('altseed', 'ByteBuffer')

ResourceType = cbg.Enum('altseed', 'ResourceType')
with ResourceType as enum:
    enum.add('StaticFile')
    enum.add('StreamFile')
    enum.add('Texture2D')
    enum.add('MAX')

ResourceContainer = cbg.Class('altseed', 'ResourceContainer')

Resources = cbg.Class('altseed', 'Resources')
with Resources as class_:
    with class_.add_func('Initialize') as func:
        func.is_static = True
        func.return_type = bool
    with class_.add_func('Terminate') as func:
        func.is_static = True
    with class_.add_func('GetInstance') as func:
        func.is_static = True
        func.return_type = Resources
    with class_.add_func('GetResourceContainer') as func:
        func.add_arg(ResourceType, 'type')
        func.return_type = ResourceContainer
    with class_.add_func('GetResourcesCount') as func:
        func.add_arg(ResourceType, 'type')
        func.return_type = int
    class_.add_func('Clear')
    class_.add_func('Reload')

BaseFileReader = cbg.Class('altseed', 'BaseFileReader')
with BaseFileReader as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(ctypes.c_wchar_p, 'path')
    with class_.add_func('GetPosition') as func:
        func.return_type = int
    with class_.add_func('GetFullPath') as func:
        func.return_type = ctypes.c_wchar_p
    with class_.add_func('GetSize') as func:
        func.return_type = int
    with class_.add_func('ReadBytes') as func:
        func.add_arg(Bytes, 'buffer')
        func.add_arg(int, 'count')
    with class_.add_func('ReadUInt32') as func:
        func.return_type = int
    with class_.add_func('ReadUInt64') as func:
        func.return_type = int
    with class_.add_func('ReadAllBytes') as func:
        func.add_arg(Bytes, 'buffer')
    with class_.add_func('Seek') as func:
        func.add_arg(int, 'offset')
        func.add_arg(SeekOrigin, 'origin')
    with class_.add_func('GetIsInPackage') as func:
        func.return_type = bool

StaticFile = cbg.Class('altseed', 'StaticFile')
with StaticFile as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(BaseFileReader, 'reader')
    with class_.add_func('GetBuffer') as func:
        func.return_type = Bytes
    with class_.add_func('GetPath') as func:
        func.return_type = ctypes.c_wchar_p
    with class_.add_func('GetData') as func:
        func.return_type = VoidPtr
    with class_.add_func('GetSize') as func:
        func.return_type = int
    with class_.add_func('GetIsInPackage') as func:
        func.return_type = bool
    with class_.add_func('Reload') as func:
        func.return_type = bool

StreamFile = cbg.Class('altseed', 'StreamFile')
with StreamFile as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(BaseFileReader, 'reader')
    with class_.add_func('GetSize') as func:
        func.return_type = int
    with class_.add_func('GetCurrentPosition') as func:
        func.return_type = int
    with class_.add_func('Read') as func:
        func.add_arg(int, 'size')
        func.return_type = int
    with class_.add_func('GetTempBuffer') as func:
        func.return_type = Bytes
    with class_.add_func('GetTempBufferSize') as func:
        func.return_type = int
    with class_.add_func('GetIsInPackage') as func:
        func.return_type = bool
    with class_.add_func('Reload') as func:
        func.return_type = bool

File = cbg.Class('altseed', 'File')
with File as class_:
    with class_.add_func('Initialize') as func:
        func.add_arg(Resources, 'resources')
        func.return_type = bool
    class_.add_func('Terminate')
    with class_.add_func('GetInstance') as func:
        func.return_type = File
    with class_.add_func('CreateStaticFile') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = StaticFile
    with class_.add_func('CreateStreamFile') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = StreamFile
    with class_.add_func('AddRootDirectory') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = bool
    with class_.add_func('AddRootPackageWithPassword') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.add_arg(ctypes.c_wchar_p, 'password')
        func.return_type = bool
    with class_.add_func('AddRootPackage') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = bool
    class_.add_func('ClearRootDirectories')
    with class_.add_func('Exists') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = bool
    with class_.add_func('Pack') as func:
        func.add_arg(ctypes.c_wchar_p, 'srcPath')
        func.add_arg(ctypes.c_wchar_p, 'dstPath')
        func.return_type = bool
    with class_.add_func('Pack') as func:
        func.add_arg(ctypes.c_wchar_p, 'srcPath')
        func.add_arg(ctypes.c_wchar_p, 'dstPath')
        func.add_arg(ctypes.c_wchar_p, 'password')
        func.return_type = bool

ZipPtr = cbg.Class('altseed', 'ZipPtr')
ZipFilePtr = cbg.Class('altseed', 'ZipFilePtr')
ZipStatPtr = cbg.Class('altseed', 'ZipStatPtr')

PackFile = cbg.Class('altseed', 'PackFile')
with PackFile as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(ZipPtr, 'zipPtr')
        ctor.add_arg(bool, 'isUsePassword')
    with class_.add_func('Load') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = ZipFilePtr
    with class_.add_func('Exists') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = bool
    with class_.add_func('GetZipStat') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = ZipStatPtr
    with class_.add_func('GetIsUsePassword') as func:
        func.return_type = bool

FileRoot = cbg.Class('altseed', 'FileRoot')
with FileRoot as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(ctypes.c_wchar_p, 'path')
    with class_.add_constructor() as ctor:
        ctor.add_arg(ctypes.c_wchar_p, 'path')
        ctor.add_arg(PackFile, 'packFile')
    with class_.add_func('GetPath') as func:
        func.return_type = ctypes.c_wchar_p
    with class_.add_func('GetPackFile') as func:
        func.return_type = PackFile
    with class_.add_func('IsPack') as func:
        func.return_type = bool

PackFileReader = cbg.Class('altseed', 'PackFileReader')
with PackFileReader as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(ZipFilePtr, 'zipFile')
        ctor.add_arg(ctypes.c_wchar_p, 'path')
        ctor.add_arg(ZipStatPtr, 'stat')
    with class_.add_func('GetSize') as func:
        func.return_type = int
    with class_.add_func('ReadBytes') as func:
        func.add_arg(Bytes, 'buffer')
        func.add_arg(int, 'count')
    with class_.add_func('Seek') as func:
        func.add_arg(int, 'offset')
        func.add_arg(SeekOrigin, 'origin')
    with class_.add_func('GetIsInPackage') as func:
        func.return_type = bool

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

Window = cbg.Class('altseed', 'Window')

Keyboard = cbg.Class('altseed', 'Keyboard')
with Keyboard as class_:
    with class_.add_func('Initialize') as func:
        func.add_arg(Window, 'window')
        func.return_type = bool
    class_.add_func('Terminate')
    with class_.add_func('GetInstance') as func:
        func.return_type = Keyboard
    class_.add_func('RefleshKeyStates')
    with class_.add_func('GetKeyState') as func:
        func.add_arg(Keys, 'key')
        func.return_type = ButtonState

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
    with class_.add_func('Initialize') as func:
        func.add_arg(Window, 'window')
        func.return_type = bool
    class_.add_func('Terminate')
    with class_.add_func('GetInstance') as func:
        func.return_type = Mouse
    class_.add_func('RefreshInputState')
    with class_.add_func('SetPosition') as func:
        func.add_arg(float, 'x')
        func.add_arg(float, 'y')
    with class_.add_func('GetPosition') as func:    # 参照引数を使った出力はサポートされない
        func.add_arg(float, 'x')
        func.add_arg(float, 'y')
    with class_.add_func('SetWheelCallback') as func:
        func.add_arg(VoidPtr, 'func')   # 関数ポインタの引数はサポートされない
    with class_.add_func('GetWheel') as func:
        func.return_type = float
    with class_.add_func('GetMouseButtonState') as func:
        func.add_arg(MouseButtons, 'button')
        func.return_type = ButtonState
    class_.add_property(CursorMode, 'CursorMode')

DeviceType = cbg.Enum('LLGI', 'DeviceType')

LlgiTexture = cbg.Class('LLGI', 'Texture')

Graphics = cbg.Class('altseed', 'Graphics')
with Graphics as class_:
    with class_.add_func('Initialize') as func:
        func.add_arg(DeviceType, 'deviceType')
        func.return_type = bool
        func.is_static = True
    with class_.add_func('GetInstance') as func:
        func.return_type = Graphics
        func.is_static = True
    with class_.add_func('Update') as func:
        func.return_type = bool
    with class_.add_func('Terminate') as func:
        func.is_static = True
    # Spriteフィールドはサポートされない。関数またはプロパティである必要がある。
    with class_.add_func('CreateDameyTexture') as func:
        func.add_arg(int, 'b')
        func.return_type = LlgiTexture

IntTuple = cbg.Class('altseed', 'IntTuple')

Texture2D = cbg.Class('altseed', 'Texture2D')
with Texture2D as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(Resources, 'resources')
        ctor.add_arg(Bytes, 'data')
        ctor.add_arg(int, 'width')
        ctor.add_arg(int, 'height')
    with class_.add_func('Reload') as func:
        func.return_type = bool
    with class_.add_func('GetSize') as func:
        func.return_type = IntTuple
    with class_.add_func('Load') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = Texture2D
        func.is_static = True

# サポートされない型
# u16string は const char16_t* として扱われることになる
# int64_t, int8_t などは int32_t として扱われることになる
# int8_t*, vector<int8_t> に対しては仮に Bytes クラスとおいている
# void* に対しては仮に VoidPtr クラスとおいている
# double; Mouse; floatとして扱われる
# double& 引数; Mouse
# std::function<void(double, double)>; Mouse
# フィールドはサポートされない; Graphics
# std::vector<std::shared_ptr<Sprite>>; Graphics
# LLGI::DeviceType; Graphics
# std::array<LLGI::Vec2F, 4>; Sprite
# LLGI::Vec2F; Sprite
# std::tuple<int32_t, int32_t>; Texture2D
# shared_ptrを使わずポインタで直接インスタンスを受け渡している場所

# define
define = cbg.Define()
define.classes.append(BaseFileReader)
define.classes.append(StreamFile)
define.classes.append(StaticFile)
define.classes.append(File)
define.classes.append(PackFile)
define.classes.append(FileRoot)
define.classes.append(PackFileReader)
define.classes.append(Bytes)
define.classes.append(Resources)
define.classes.append(ZipPtr)
define.classes.append(ZipFilePtr)
define.classes.append(ZipStatPtr)

define.enums.append(SeekOrigin)
define.enums.append(ResourceType)