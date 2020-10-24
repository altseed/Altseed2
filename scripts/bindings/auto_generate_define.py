from . import CppBindingGenerator as cbg
from .define import *
import ctypes
import sys

ShaderStageType = cbg.Enum('Altseed2', 'ShaderStageType')
with ShaderStageType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
define.enums.append(ShaderStageType)

ResourceType = cbg.Enum('Altseed2', 'ResourceType')
with ResourceType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('StaticFile', 0)
    enum_.add('StreamFile', 1)
    enum_.add('Texture2D', 2)
    enum_.add('Font', 3)
    enum_.add('Sound', 4)
    enum_.add('MAX', 5)
define.enums.append(ResourceType)

TextureWrapMode = cbg.Enum('Altseed2', 'TextureWrapMode')
with TextureWrapMode as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Clamp', 0)
    enum_.add('Repeat', 1)
define.enums.append(TextureWrapMode)

TextureFilterType = cbg.Enum('Altseed2', 'TextureFilterType')
with TextureFilterType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Nearest', 0)
    enum_.add('Linear', 1)
define.enums.append(TextureFilterType)

TextureFormatType = cbg.Enum('Altseed2', 'TextureFormatType')
with TextureFormatType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('R8G8B8A8_UNORM', 0)
    enum_.add('R16G16B16A16_FLOAT', 1)
    enum_.add('R32G32B32A32_FLOAT', 2)
    enum_.add('R8G8B8A8_UNORM_SRGB', 3)
    enum_.add('R16G16_FLOAT', 4)
    enum_.add('R8_UNORM', 5)
    enum_.add('D32', 12)
    enum_.add('D32S8', 13)
    enum_.add('D24S8', 14)
define.enums.append(TextureFormatType)

BlendEquationType = cbg.Enum('Altseed2', 'BlendEquationType')
with BlendEquationType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Add', 0)
    enum_.add('Sub', 1)
    enum_.add('ReverseSub', 2)
    enum_.add('Min', 3)
    enum_.add('Max', 4)
define.enums.append(BlendEquationType)

BlendFuncType = cbg.Enum('Altseed2', 'BlendFuncType')
with BlendFuncType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Zero', 0)
    enum_.add('One', 1)
    enum_.add('SrcColor', 2)
    enum_.add('OneMinusSrcColor', 3)
    enum_.add('SrcAlpha', 4)
    enum_.add('OneMinusSrcAlpha', 5)
    enum_.add('DstAlpha', 6)
    enum_.add('OneMinusDstAlpha', 7)
    enum_.add('DstColor', 8)
    enum_.add('OneMinusDstColor', 9)
define.enums.append(BlendFuncType)

GraphicsDeviceType = cbg.Enum('Altseed2', 'GraphicsDeviceType')
with GraphicsDeviceType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Default', 0)
    enum_.add('DirectX12', 1)
    enum_.add('Metal', 2)
    enum_.add('Vulkan', 3)
define.enums.append(GraphicsDeviceType)

CoreModules = cbg.Enum('Altseed2', 'CoreModules')
with CoreModules as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('Window', 1)
    enum_.add('File', 1 << 1)
    enum_.add('Keyboard', 1 << 2)
    enum_.add('Mouse', 1 << 3)
    enum_.add('Joystick', 1 << 4)
    enum_.add('Graphics', 1 << 5)
    enum_.add('Tool', 1 << 6)
    enum_.add('RequireGraphics', (1 << 5) | (1 << 6))
    enum_.add('RequireWindow', (1) | (1 << 2) | (1 << 3) | (1 << 4) | ((1 << 5) | (1 << 6)))
    enum_.add('Sound', 1 << 7)
    enum_.add('Default', (1) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 4) | (1 << 5) | (1 << 7))
    enum_.add('RequireFile', (1 << 1) | (1 << 7) | ((1 << 5) | (1 << 6)))
define.enums.append(CoreModules)

FramerateMode = cbg.Enum('Altseed2', 'FramerateMode')
with FramerateMode as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Variable', 0)
    enum_.add('Constant', 1)
define.enums.append(FramerateMode)

BuiltinShaderType = cbg.Enum('Altseed2', 'BuiltinShaderType')
with BuiltinShaderType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('SpriteUnlitVS', 0)
    enum_.add('SpriteUnlitPS', 1)
    enum_.add('FontUnlitPS', 2)
define.enums.append(BuiltinShaderType)

RenderTargetCareType = cbg.Enum('Altseed2', 'RenderTargetCareType')
with RenderTargetCareType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('DontCare', 0)
    enum_.add('Clear', 1)
define.enums.append(RenderTargetCareType)

WritingDirection = cbg.Enum('Altseed2', 'WritingDirection')
with WritingDirection as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Vertical', 0)
    enum_.add('Horizontal', 1)
define.enums.append(WritingDirection)

FrameEventType = cbg.Enum('Altseed2', 'FrameEventType')
with FrameEventType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Clear', 0)
    enum_.add('SetRenderTarget', 1)
    enum_.add('SetRenderTargetWithRealScreen', 2)
    enum_.add('BeginRenderPass', 3)
    enum_.add('EndRenderPass', 4)
    enum_.add('EndFrame', 5)
    enum_.add('Render', 6)
    enum_.add('Draw', 7)
    enum_.add('Uniform', 8)
    enum_.add('Texture', 9)
    enum_.add('SetVertexBuffer', 10)
    enum_.add('SetIndexBuffer', 11)
define.enums.append(FrameEventType)

FrameEventUniformType = cbg.Enum('Altseed2', 'FrameEventUniformType')
with FrameEventUniformType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Vector', 0)
    enum_.add('Matrix', 1)
define.enums.append(FrameEventUniformType)

ButtonState = cbg.Enum('Altseed2', 'ButtonState')
with ButtonState as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Free', 0b00)
    enum_.add('Push', 0b01)
    enum_.add('Release', 0b10)
    enum_.add('Hold', 0b11)
define.enums.append(ButtonState)

JoystickType = cbg.Enum('Altseed2', 'JoystickType')
with JoystickType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Other', 0)
    enum_.add('DualShock3', 616)
    enum_.add('XBOX360', 654)
    enum_.add('DualShock4', 1476)
    enum_.add('DualShock4Slim', 2508)
    enum_.add('JoyconL', 8198)
    enum_.add('JoyconR', 8199)
    enum_.add('ProController', 8201)
define.enums.append(JoystickType)

JoystickButton = cbg.Enum('Altseed2', 'JoystickButton')
with JoystickButton as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('RightDown', 0)
    enum_.add('RightRight', 1)
    enum_.add('RightLeft', 2)
    enum_.add('RightUp', 3)
    enum_.add('LeftBumper', 4)
    enum_.add('RightBumper', 5)
    enum_.add('Back', 6)
    enum_.add('Start', 7)
    enum_.add('Guide', 8)
    enum_.add('LeftThumb', 9)
    enum_.add('RightThumb', 10)
    enum_.add('DPadUp', 11)
    enum_.add('DPadRight', 12)
    enum_.add('DPadDown', 13)
    enum_.add('DPadLeft', 14)
define.enums.append(JoystickButton)

JoystickAxis = cbg.Enum('Altseed2', 'JoystickAxis')
with JoystickAxis as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('LeftX', 0)
    enum_.add('LeftY', 1)
    enum_.add('RightX', 2)
    enum_.add('RightY', 3)
    enum_.add('LeftTrigger', 4)
    enum_.add('RightTrigger', 5)
define.enums.append(JoystickAxis)

Key = cbg.Enum('Altseed2', 'Key')
with Key as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Unknown', 0)
    enum_.add('Space', 1)
    enum_.add('Apostrophe', 2)
    enum_.add('Comma', 3)
    enum_.add('Minus', 4)
    enum_.add('Period', 5)
    enum_.add('Slash', 6)
    enum_.add('Num0', 7)
    enum_.add('Num1', 8)
    enum_.add('Num2', 9)
    enum_.add('Num3', 10)
    enum_.add('Num4', 11)
    enum_.add('Num5', 12)
    enum_.add('Num6', 13)
    enum_.add('Num7', 14)
    enum_.add('Num8', 15)
    enum_.add('Num9', 16)
    enum_.add('Semicolon', 17)
    enum_.add('Equal', 18)
    enum_.add('A', 19)
    enum_.add('B', 20)
    enum_.add('C', 21)
    enum_.add('D', 22)
    enum_.add('E', 23)
    enum_.add('F', 24)
    enum_.add('G', 25)
    enum_.add('H', 26)
    enum_.add('I', 27)
    enum_.add('J', 28)
    enum_.add('K', 29)
    enum_.add('L', 30)
    enum_.add('M', 31)
    enum_.add('N', 32)
    enum_.add('O', 33)
    enum_.add('P', 34)
    enum_.add('Q', 35)
    enum_.add('R', 36)
    enum_.add('S', 37)
    enum_.add('T', 38)
    enum_.add('U', 39)
    enum_.add('V', 40)
    enum_.add('W', 41)
    enum_.add('X', 42)
    enum_.add('Y', 43)
    enum_.add('Z', 44)
    enum_.add('LeftBracket', 45)
    enum_.add('Backslash', 46)
    enum_.add('RightBracket', 47)
    enum_.add('GraveAccent', 48)
    enum_.add('World1', 49)
    enum_.add('World2', 50)
    enum_.add('Escape', 51)
    enum_.add('Enter', 52)
    enum_.add('Tab', 53)
    enum_.add('Backspace', 54)
    enum_.add('Insert', 55)
    enum_.add('Delete', 56)
    enum_.add('Right', 57)
    enum_.add('Left', 58)
    enum_.add('Down', 59)
    enum_.add('Up', 60)
    enum_.add('PageUp', 61)
    enum_.add('PageDown', 62)
    enum_.add('Home', 63)
    enum_.add('End', 64)
    enum_.add('CapsLock', 65)
    enum_.add('ScrollLock', 66)
    enum_.add('NumLock', 67)
    enum_.add('PrintScreen', 68)
    enum_.add('Pause', 69)
    enum_.add('F1', 70)
    enum_.add('F2', 71)
    enum_.add('F3', 72)
    enum_.add('F4', 73)
    enum_.add('F5', 74)
    enum_.add('F6', 75)
    enum_.add('F7', 76)
    enum_.add('F8', 77)
    enum_.add('F9', 78)
    enum_.add('F10', 79)
    enum_.add('F11', 80)
    enum_.add('F12', 81)
    enum_.add('F13', 82)
    enum_.add('F14', 83)
    enum_.add('F15', 84)
    enum_.add('F16', 85)
    enum_.add('F17', 86)
    enum_.add('F18', 87)
    enum_.add('F19', 88)
    enum_.add('F20', 89)
    enum_.add('F21', 90)
    enum_.add('F22', 91)
    enum_.add('F23', 92)
    enum_.add('F24', 93)
    enum_.add('F25', 94)
    enum_.add('Keypad0', 95)
    enum_.add('Keypad1', 96)
    enum_.add('Keypad2', 97)
    enum_.add('Keypad3', 98)
    enum_.add('Keypad4', 99)
    enum_.add('Keypad5', 100)
    enum_.add('Keypad6', 101)
    enum_.add('Keypad7', 102)
    enum_.add('Keypad8', 103)
    enum_.add('Keypad9', 104)
    enum_.add('KeypadDecimal', 105)
    enum_.add('KeypadDivide', 106)
    enum_.add('KeypadMultiply', 107)
    enum_.add('KeypadSubstract', 108)
    enum_.add('KeypadAdd', 109)
    enum_.add('KeypadEnter', 110)
    enum_.add('KeypadEqual', 111)
    enum_.add('LeftShift', 112)
    enum_.add('LeftControl', 113)
    enum_.add('LeftAlt', 114)
    enum_.add('LeftWin', 115)
    enum_.add('RightShift', 116)
    enum_.add('RightControl', 117)
    enum_.add('RightAlt', 118)
    enum_.add('RightWin', 119)
    enum_.add('Menu', 120)
    enum_.add('Last', 121)
    enum_.add('MAX', 122)
define.enums.append(Key)

MouseButton = cbg.Enum('Altseed2', 'MouseButton')
with MouseButton as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('ButtonLeft', 0)
    enum_.add('ButtonRight', 1)
    enum_.add('ButtonMiddle', 2)
    enum_.add('SubButton1', 3)
    enum_.add('SubButton2', 4)
    enum_.add('SubButton3', 5)
    enum_.add('SubButton4', 6)
    enum_.add('SubButton5', 7)
define.enums.append(MouseButton)

CursorMode = cbg.Enum('Altseed2', 'CursorMode')
with CursorMode as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Normal', 0x00034001)
    enum_.add('Hidden', 0x00034002)
    enum_.add('Disable', 0x00034003)
define.enums.append(CursorMode)

LogLevel = cbg.Enum('Altseed2', 'LogLevel')
with LogLevel as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Trace', 0)
    enum_.add('Debug', 1)
    enum_.add('Info', 2)
    enum_.add('Warn', 3)
    enum_.add('Error', 4)
    enum_.add('Critical', 5)
    enum_.add('Off', 6)
define.enums.append(LogLevel)

LogCategory = cbg.Enum('Altseed2', 'LogCategory')
with LogCategory as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Core', 0)
    enum_.add('Graphics', 1)
    enum_.add('Engine', 2)
    enum_.add('User', 3)
define.enums.append(LogCategory)

EasingType = cbg.Enum('Altseed2', 'EasingType')
with EasingType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Linear', 0)
    enum_.add('InSine', 1)
    enum_.add('OutSine', 2)
    enum_.add('InOutSine', 3)
    enum_.add('InQuad', 4)
    enum_.add('OutQuad', 5)
    enum_.add('InOutQuad', 6)
    enum_.add('InCubic', 7)
    enum_.add('OutCubic', 8)
    enum_.add('InOutCubic', 9)
    enum_.add('InQuart', 10)
    enum_.add('OutQuart', 11)
    enum_.add('InOutQuart', 12)
    enum_.add('InQuint', 13)
    enum_.add('OutQuint', 14)
    enum_.add('InOutQuint', 15)
    enum_.add('InExpo', 16)
    enum_.add('OutExpo', 17)
    enum_.add('InOutExpo', 18)
    enum_.add('InCirc', 19)
    enum_.add('OutCirc', 20)
    enum_.add('InOutCirc', 21)
    enum_.add('InBack', 22)
    enum_.add('OutBack', 23)
    enum_.add('InOutBack', 24)
    enum_.add('InElastic', 25)
    enum_.add('OutElastic', 26)
    enum_.add('InOutElastic', 27)
    enum_.add('InBounce', 28)
    enum_.add('OutBounce', 29)
    enum_.add('InOutBounce', 30)
define.enums.append(EasingType)

ToolGlyphRange = cbg.Enum('Altseed2', 'ToolGlyphRange')
with ToolGlyphRange as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Default', 0)
    enum_.add('Cyrillic', 1)
    enum_.add('Japanese', 2)
    enum_.add('ChineseFull', 3)
    enum_.add('ChineseSimplifiedCommon', 4)
    enum_.add('Korean', 5)
    enum_.add('Thai', 6)
define.enums.append(ToolGlyphRange)

ToolUsage = cbg.Enum('Altseed2', 'ToolUsage')
with ToolUsage as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Overwrapped', 0)
    enum_.add('Main', 1)
define.enums.append(ToolUsage)

ToolWindowFlags = cbg.Enum('Altseed2', 'ToolWindowFlags')
with ToolWindowFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('NoTitleBar', 1 << 0)
    enum_.add('NoResize', 1 << 1)
    enum_.add('NoMove', 1 << 2)
    enum_.add('NoScrollbar', 1 << 3)
    enum_.add('NoScrollWithMouse', 1 << 4)
    enum_.add('NoCollapse', 1 << 5)
    enum_.add('NoDecoration', (1 << 0) | (1 << 1) | (1 << 3) | (1 << 5))
    enum_.add('AlwaysAutoResize', 1 << 6)
    enum_.add('NoBackground', 1 << 7)
    enum_.add('NoSavedSettings', 1 << 8)
    enum_.add('NoMouseInputs', 1 << 9)
    enum_.add('MenuBar', 1 << 10)
    enum_.add('HorizontalScrollbar', 1 << 11)
    enum_.add('NoFocusOnAppearing', 1 << 12)
    enum_.add('NoBringToFrontOnFocus', 1 << 13)
    enum_.add('AlwaysVerticalScrollbar', 1 << 14)
    enum_.add('AlwaysHorizontalScrollbar', 1 << 15)
    enum_.add('AlwaysUseWindowPadding', 1 << 16)
    enum_.add('NoNavInputs', 1 << 18)
    enum_.add('NoNavFocus', 1 << 19)
    enum_.add('NoNav', (1 << 18) | (1 << 19))
    enum_.add('NoInputs', (1 << 9) | (1 << 18) | (1 << 19))
    enum_.add('UnsavedDocument', 1 << 20)
    enum_.add('NavFlattened', 1 << 23)
    enum_.add('ChildWindow', 1 << 24)
    enum_.add('Tooltip', 1 << 25)
    enum_.add('Popup', 1 << 26)
    enum_.add('Modal', 1 << 27)
    enum_.add('ChildMenu', 1 << 28)
define.enums.append(ToolWindowFlags)

ToolInputTextFlags = cbg.Enum('Altseed2', 'ToolInputTextFlags')
with ToolInputTextFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('CharsDecimal', 1 << 0)
    enum_.add('CharsHexadecimal', 1 << 1)
    enum_.add('CharsUppercase', 1 << 2)
    enum_.add('CharsNoBlank', 1 << 3)
    enum_.add('AutoSelectAll', 1 << 4)
    enum_.add('EnterReturnsTrue', 1 << 5)
    enum_.add('CallbackCompletion', 1 << 6)
    enum_.add('CallbackHistory', 1 << 7)
    enum_.add('CallbackAlways', 1 << 8)
    enum_.add('CallbackCharFilter', 1 << 9)
    enum_.add('AllowTabInput', 1 << 10)
    enum_.add('CtrlEnterForNewLine', 1 << 11)
    enum_.add('NoHorizontalScroll', 1 << 12)
    enum_.add('AlwaysInsertMode', 1 << 13)
    enum_.add('ReadOnly', 1 << 14)
    enum_.add('Password', 1 << 15)
    enum_.add('NoUndoRedo', 1 << 16)
    enum_.add('CharsScientific', 1 << 17)
    enum_.add('CallbackResize', 1 << 18)
    enum_.add('Multiline', 1 << 20)
    enum_.add('NoMarkEdited', 1 << 21)
define.enums.append(ToolInputTextFlags)

ToolTreeNodeFlags = cbg.Enum('Altseed2', 'ToolTreeNodeFlags')
with ToolTreeNodeFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('Selected', 1 << 0)
    enum_.add('Framed', 1 << 1)
    enum_.add('AllowItemOverlap', 1 << 2)
    enum_.add('NoTreePushOnOpen', 1 << 3)
    enum_.add('NoAutoOpenOnLog', 1 << 4)
    enum_.add('CollapsingHeader', (1 << 1) | (1 << 3) | (1 << 4))
    enum_.add('DefaultOpen', 1 << 5)
    enum_.add('OpenOnDoubleClick', 1 << 6)
    enum_.add('OpenOnArrow', 1 << 7)
    enum_.add('Leaf', 1 << 8)
    enum_.add('Bullet', 1 << 9)
    enum_.add('FramePadding', 1 << 10)
    enum_.add('SpanAvailWidth', 1 << 11)
    enum_.add('SpanFullWidth', 1 << 12)
    enum_.add('NavLeftJumpsBackHere', 1 << 13)
define.enums.append(ToolTreeNodeFlags)

ToolSelectableFlags = cbg.Enum('Altseed2', 'ToolSelectableFlags')
with ToolSelectableFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('DontClosePopups', 1 << 0)
    enum_.add('SpanAllColumns', 1 << 1)
    enum_.add('AllowDoubleClick', 1 << 2)
    enum_.add('Disabled', 1 << 3)
    enum_.add('AllowItemOverlap', 1 << 4)
define.enums.append(ToolSelectableFlags)

ToolComboFlags = cbg.Enum('Altseed2', 'ToolComboFlags')
with ToolComboFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('PopupAlignLeft', 1 << 0)
    enum_.add('HeightSmall', 1 << 1)
    enum_.add('HeightRegular', 1 << 2)
    enum_.add('HeightLarge', 1 << 3)
    enum_.add('HeightLargest', 1 << 4)
    enum_.add('NoArrowButton', 1 << 5)
    enum_.add('NoPreview', 1 << 6)
define.enums.append(ToolComboFlags)

ToolTabBarFlags = cbg.Enum('Altseed2', 'ToolTabBarFlags')
with ToolTabBarFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('Reorderable', 1 << 0)
    enum_.add('AutoSelectNewTabs', 1 << 1)
    enum_.add('TabListPopupButton', 1 << 2)
    enum_.add('NoCloseWithMiddleMouseButton', 1 << 3)
    enum_.add('NoTabListScrollingButtons', 1 << 4)
    enum_.add('NoTooltip', 1 << 5)
    enum_.add('FittingPolicyResizeDown', 1 << 6)
    enum_.add('FittingPolicyScroll', 1 << 7)
define.enums.append(ToolTabBarFlags)

ToolTabItemFlags = cbg.Enum('Altseed2', 'ToolTabItemFlags')
with ToolTabItemFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('UnsavedDocument', 1 << 0)
    enum_.add('SetSelected', 1 << 1)
    enum_.add('NoCloseWithMiddleMouseButton', 1 << 2)
    enum_.add('NoPushId', 1 << 3)
define.enums.append(ToolTabItemFlags)

ToolFocusedFlags = cbg.Enum('Altseed2', 'ToolFocusedFlags')
with ToolFocusedFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('ChildWindows', 1 << 0)
    enum_.add('RootWindow', 1 << 1)
    enum_.add('RootAndChildWindows', (1 << 1) | (1 << 0))
    enum_.add('AnyWindow', 1 << 2)
define.enums.append(ToolFocusedFlags)

ToolHoveredFlags = cbg.Enum('Altseed2', 'ToolHoveredFlags')
with ToolHoveredFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('ChildWindows', 1 << 0)
    enum_.add('RootWindow', 1 << 1)
    enum_.add('RootAndChildWindows', (1 << 1) | (1 << 0))
    enum_.add('AnyWindow', 1 << 2)
    enum_.add('AllowWhenBlockedByPopup', 1 << 3)
    enum_.add('AllowWhenBlockedByActiveItem', 1 << 5)
    enum_.add('AllowWhenOverlapped', 1 << 6)
    enum_.add('RectOnly', (1 << 3) | (1 << 5) | (1 << 6))
    enum_.add('AllowWhenDisabled', 1 << 7)
define.enums.append(ToolHoveredFlags)

ToolDragDropFlags = cbg.Enum('Altseed2', 'ToolDragDropFlags')
with ToolDragDropFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('SourceNoPreviewTooltip', 1 << 0)
    enum_.add('SourceNoDisableHover', 1 << 1)
    enum_.add('SourceNoHoldToOpenOthers', 1 << 2)
    enum_.add('SourceAllowNullID', 1 << 3)
    enum_.add('SourceExtern', 1 << 4)
    enum_.add('SourceAutoExpirePayload', 1 << 5)
    enum_.add('AcceptBeforeDelivery', 1 << 10)
    enum_.add('AcceptNoDrawDefaultRect', 1 << 11)
    enum_.add('AcceptPeekOnly', (1 << 10) | (1 << 11))
    enum_.add('AcceptNoPreviewTooltip', 1 << 12)
define.enums.append(ToolDragDropFlags)

ToolDataType = cbg.Enum('Altseed2', 'ToolDataType')
with ToolDataType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('S8', 0)
    enum_.add('U8', 1)
    enum_.add('S16', 2)
    enum_.add('U16', 3)
    enum_.add('S32', 4)
    enum_.add('U32', 5)
    enum_.add('S64', 6)
    enum_.add('U64', 7)
    enum_.add('Float', 8)
    enum_.add('Double', 9)
    enum_.add('COUNT', 10)
define.enums.append(ToolDataType)

ToolDir = cbg.Enum('Altseed2', 'ToolDir')
with ToolDir as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', - 1)
    enum_.add('Left', 0)
    enum_.add('Right', 1)
    enum_.add('Up', 2)
    enum_.add('Down', 3)
    enum_.add('COUNT', 5)
define.enums.append(ToolDir)

ToolKey = cbg.Enum('Altseed2', 'ToolKey')
with ToolKey as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Tab', 0)
    enum_.add('LeftArrow', 1)
    enum_.add('RightArrow', 2)
    enum_.add('UpArrow', 3)
    enum_.add('DownArrow', 4)
    enum_.add('PageUp', 5)
    enum_.add('PageDown', 6)
    enum_.add('Home', 7)
    enum_.add('End', 8)
    enum_.add('Insert', 9)
    enum_.add('Delete', 10)
    enum_.add('Backspace', 11)
    enum_.add('Space', 12)
    enum_.add('Enter', 13)
    enum_.add('Escape', 14)
    enum_.add('KeyPadEnter', 15)
    enum_.add('A', 16)
    enum_.add('C', 17)
    enum_.add('V', 18)
    enum_.add('X', 19)
    enum_.add('Y', 20)
    enum_.add('Z', 21)
    enum_.add('COUNT', 22)
define.enums.append(ToolKey)

ToolKeyModFlags = cbg.Enum('Altseed2', 'ToolKeyModFlags')
with ToolKeyModFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('Ctrl', 1 << 0)
    enum_.add('Shift', 1 << 1)
    enum_.add('Alt', 1 << 2)
    enum_.add('Super', 1 << 3)
define.enums.append(ToolKeyModFlags)

ToolNavInput = cbg.Enum('Altseed2', 'ToolNavInput')
with ToolNavInput as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Activate', 0)
    enum_.add('Cancel', 1)
    enum_.add('Input', 2)
    enum_.add('Menu', 3)
    enum_.add('DpadLeft', 4)
    enum_.add('DpadRight', 5)
    enum_.add('DpadUp', 6)
    enum_.add('DpadDown', 7)
    enum_.add('LStickLeft', 8)
    enum_.add('LStickRight', 9)
    enum_.add('LStickUp', 10)
    enum_.add('LStickDown', 11)
    enum_.add('FocusPrev', 12)
    enum_.add('FocusNext', 13)
    enum_.add('TweakSlow', 14)
    enum_.add('TweakFast', 15)
    enum_.add('COUNT', 16)
define.enums.append(ToolNavInput)

ToolConfigFlags = cbg.Enum('Altseed2', 'ToolConfigFlags')
with ToolConfigFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('NavEnableKeyboard', 1 << 0)
    enum_.add('NavEnableGamepad', 1 << 1)
    enum_.add('NavEnableSetMousePos', 1 << 2)
    enum_.add('NavNoCaptureKeyboard', 1 << 3)
    enum_.add('NoMouse', 1 << 4)
    enum_.add('NoMouseCursorChange', 1 << 5)
    enum_.add('IsSRGB', 1 << 20)
    enum_.add('IsTouchScreen', 1 << 21)
define.enums.append(ToolConfigFlags)

ToolBackendFlags = cbg.Enum('Altseed2', 'ToolBackendFlags')
with ToolBackendFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('HasGamepad', 1 << 0)
    enum_.add('HasMouseCursors', 1 << 1)
    enum_.add('HasSetMousePos', 1 << 2)
    enum_.add('RendererHasVtxOffset', 1 << 3)
define.enums.append(ToolBackendFlags)

ToolCol = cbg.Enum('Altseed2', 'ToolCol')
with ToolCol as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Text', 0)
    enum_.add('TextDisabled', 1)
    enum_.add('WindowBg', 2)
    enum_.add('ChildBg', 3)
    enum_.add('PopupBg', 4)
    enum_.add('Border', 5)
    enum_.add('BorderShadow', 6)
    enum_.add('FrameBg', 7)
    enum_.add('FrameBgHovered', 8)
    enum_.add('FrameBgActive', 9)
    enum_.add('TitleBg', 10)
    enum_.add('TitleBgActive', 11)
    enum_.add('TitleBgCollapsed', 12)
    enum_.add('MenuBarBg', 13)
    enum_.add('ScrollbarBg', 14)
    enum_.add('ScrollbarGrab', 15)
    enum_.add('ScrollbarGrabHovered', 16)
    enum_.add('ScrollbarGrabActive', 17)
    enum_.add('CheckMark', 18)
    enum_.add('SliderGrab', 19)
    enum_.add('SliderGrabActive', 20)
    enum_.add('Button', 21)
    enum_.add('ButtonHovered', 22)
    enum_.add('ButtonActive', 23)
    enum_.add('Header', 24)
    enum_.add('HeaderHovered', 25)
    enum_.add('HeaderActive', 26)
    enum_.add('Separator', 27)
    enum_.add('SeparatorHovered', 28)
    enum_.add('SeparatorActive', 29)
    enum_.add('ResizeGrip', 30)
    enum_.add('ResizeGripHovered', 31)
    enum_.add('ResizeGripActive', 32)
    enum_.add('Tab', 33)
    enum_.add('TabHovered', 34)
    enum_.add('TabActive', 35)
    enum_.add('TabUnfocused', 36)
    enum_.add('TabUnfocusedActive', 37)
    enum_.add('PlotLines', 38)
    enum_.add('PlotLinesHovered', 39)
    enum_.add('PlotHistogram', 40)
    enum_.add('PlotHistogramHovered', 41)
    enum_.add('TextSelectedBg', 42)
    enum_.add('DragDropTarget', 43)
    enum_.add('NavHighlight', 44)
    enum_.add('NavWindowingHighlight', 45)
    enum_.add('NavWindowingDimBg', 46)
    enum_.add('ModalWindowDimBg', 47)
    enum_.add('COUNT', 48)
define.enums.append(ToolCol)

ToolStyleVar = cbg.Enum('Altseed2', 'ToolStyleVar')
with ToolStyleVar as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Alpha', 0)
    enum_.add('WindowPadding', 1)
    enum_.add('WindowRounding', 2)
    enum_.add('WindowBorderSize', 3)
    enum_.add('WindowMinSize', 4)
    enum_.add('WindowTitleAlign', 5)
    enum_.add('ChildRounding', 6)
    enum_.add('ChildBorderSize', 7)
    enum_.add('PopupRounding', 8)
    enum_.add('PopupBorderSize', 9)
    enum_.add('FramePadding', 10)
    enum_.add('FrameRounding', 11)
    enum_.add('FrameBorderSize', 12)
    enum_.add('ItemSpacing', 13)
    enum_.add('ItemInnerSpacing', 14)
    enum_.add('IndentSpacing', 15)
    enum_.add('ScrollbarSize', 16)
    enum_.add('ScrollbarRounding', 17)
    enum_.add('GrabMinSize', 18)
    enum_.add('GrabRounding', 19)
    enum_.add('TabRounding', 20)
    enum_.add('ButtonTextAlign', 21)
    enum_.add('SelectableTextAlign', 22)
    enum_.add('COUNT', 23)
define.enums.append(ToolStyleVar)

ToolColorEditFlags = cbg.Enum('Altseed2', 'ToolColorEditFlags')
with ToolColorEditFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('NoAlpha', 1 << 1)
    enum_.add('NoPicker', 1 << 2)
    enum_.add('NoOptions', 1 << 3)
    enum_.add('NoSmallPreview', 1 << 4)
    enum_.add('NoInputs', 1 << 5)
    enum_.add('NoTooltip', 1 << 6)
    enum_.add('NoLabel', 1 << 7)
    enum_.add('NoSidePreview', 1 << 8)
    enum_.add('NoDragDrop', 1 << 9)
    enum_.add('NoBorder', 1 << 10)
    enum_.add('AlphaBar', 1 << 16)
    enum_.add('AlphaPreview', 1 << 17)
    enum_.add('AlphaPreviewHalf', 1 << 18)
    enum_.add('HDR', 1 << 19)
    enum_.add('DisplayRGB', 1 << 20)
    enum_.add('DisplayHSV', 1 << 21)
    enum_.add('DisplayHex', 1 << 22)
    enum_.add('DisplayMask', (1 << 20) | (1 << 21) | (1 << 22))
    enum_.add('Uint8', 1 << 23)
    enum_.add('Float', 1 << 24)
    enum_.add('DataTypeMask', (1 << 23) | (1 << 24))
    enum_.add('PickerHueBar', 1 << 25)
    enum_.add('PickerHueWheel', 1 << 26)
    enum_.add('PickerMask', (1 << 26) | (1 << 25))
    enum_.add('InputRGB', 1 << 27)
    enum_.add('OptionsDefault', (1 << 23) | (1 << 20) | (1 << 27) | (1 << 25))
    enum_.add('InputHSV', 1 << 28)
    enum_.add('InputMask', (1 << 27) | (1 << 28))
define.enums.append(ToolColorEditFlags)

ToolMouseButton = cbg.Enum('Altseed2', 'ToolMouseButton')
with ToolMouseButton as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Left', 0)
    enum_.add('Right', 1)
    enum_.add('Middle', 2)
    enum_.add('COUNT', 5)
define.enums.append(ToolMouseButton)

ToolMouseCursor = cbg.Enum('Altseed2', 'ToolMouseCursor')
with ToolMouseCursor as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', - 1)
    enum_.add('Arrow', 0)
    enum_.add('TextInput', 2)
    enum_.add('ResizeAll', 3)
    enum_.add('ResizeNS', 4)
    enum_.add('ResizeEW', 5)
    enum_.add('ResizeNESW', 6)
    enum_.add('ResizeNWSE', 7)
    enum_.add('Hand', 8)
    enum_.add('NotAllowed', 9)
    enum_.add('COUNT', 10)
define.enums.append(ToolMouseCursor)

ToolCond = cbg.Enum('Altseed2', 'ToolCond')
with ToolCond as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Always', 1 << 0)
    enum_.add('Once', 1 << 1)
    enum_.add('FirstUseEver', 1 << 2)
    enum_.add('Appearing', 1 << 3)
define.enums.append(ToolCond)

ToolDrawCornerFlags = cbg.Enum('Altseed2', 'ToolDrawCornerFlags')
with ToolDrawCornerFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('TopLeft', 1 << 0)
    enum_.add('TopRight', 1 << 1)
    enum_.add('Top', (1 << 0) | (1 << 1))
    enum_.add('BotLeft', 1 << 2)
    enum_.add('Left', (1 << 0) | (1 << 2))
    enum_.add('BotRight', 1 << 3)
    enum_.add('Right', (1 << 1) | (1 << 3))
    enum_.add('Bot', (1 << 2) | (1 << 3))
    enum_.add('All', 0xF)
define.enums.append(ToolDrawCornerFlags)

ToolDrawListFlags = cbg.Enum('Altseed2', 'ToolDrawListFlags')
with ToolDrawListFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('AntiAliasedLines', 1 << 0)
    enum_.add('AntiAliasedFill', 1 << 1)
    enum_.add('AllowVtxOffset', 1 << 2)
define.enums.append(ToolDrawListFlags)

ToolFontAtlasFlags = cbg.Enum('Altseed2', 'ToolFontAtlasFlags')
with ToolFontAtlasFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('NoPowerOfTwoHeight', 1 << 0)
    enum_.add('NoMouseCursors', 1 << 1)
define.enums.append(ToolFontAtlasFlags)

Window = cbg.Class('Altseed2', 'Window')
ShaderCompileResult = cbg.Class('Altseed2', 'ShaderCompileResult')
Shader = cbg.Class('Altseed2', 'Shader')
Resources = cbg.Class('Altseed2', 'Resources')
TextureBase = cbg.Class('Altseed2', 'TextureBase')
MaterialPropertyBlock = cbg.Class('Altseed2', 'MaterialPropertyBlock')
MaterialPropertyBlockCollection = cbg.Class('Altseed2', 'MaterialPropertyBlockCollection')
Material = cbg.Class('Altseed2', 'Material')
Texture2D = cbg.Class('Altseed2', 'Texture2D')
Sprite = cbg.Class('Altseed2', 'Sprite')
Camera = cbg.Class('Altseed2', 'Camera')
BuiltinShader = cbg.Class('Altseed2', 'BuiltinShader')
CommandList = cbg.Class('Altseed2', 'CommandList')
Graphics = cbg.Class('Altseed2', 'Graphics')
Configuration = cbg.Class('Altseed2', 'Configuration')
FPS = cbg.Class('Altseed2', 'FPS')
Core = cbg.Class('Altseed2', 'Core')
File = cbg.Class('Altseed2', 'File')
StaticFile = cbg.Class('Altseed2', 'StaticFile')
RenderTexture = cbg.Class('Altseed2', 'RenderTexture')
Glyph = cbg.Class('Altseed2', 'Glyph')
Font = cbg.Class('Altseed2', 'Font')
FrameEvent = cbg.Class('Altseed2', 'FrameEvent')
FrameEventSetRenderTarget = cbg.Class('Altseed2', 'FrameEventSetRenderTarget')
FrameEventSetRenderTargetWithRealScreen = cbg.Class('Altseed2', 'FrameEventSetRenderTargetWithRealScreen')
FrameEventDraw = cbg.Class('Altseed2', 'FrameEventDraw')
FrameEventRender = cbg.Class('Altseed2', 'FrameEventRender')
FrameEventSetVertexBuffer = cbg.Class('Altseed2', 'FrameEventSetVertexBuffer')
FrameEventSetIndexBuffer = cbg.Class('Altseed2', 'FrameEventSetIndexBuffer')
FrameEventUniform = cbg.Class('Altseed2', 'FrameEventUniform')
FrameEventTexture = cbg.Class('Altseed2', 'FrameEventTexture')
FrameDebugger = cbg.Class('Altseed2', 'FrameDebugger')
ImageFont = cbg.Class('Altseed2', 'ImageFont')
CullingSystem = cbg.Class('Altseed2', 'CullingSystem')
Rendered = cbg.Class('Altseed2', 'Rendered')
RenderedCamera = cbg.Class('Altseed2', 'RenderedCamera')
RenderedSprite = cbg.Class('Altseed2', 'RenderedSprite')
RenderedText = cbg.Class('Altseed2', 'RenderedText')
RenderedPolygon = cbg.Class('Altseed2', 'RenderedPolygon')
Renderer = cbg.Class('Altseed2', 'Renderer')
ShaderCompiler = cbg.Class('Altseed2', 'ShaderCompiler')
StreamFile = cbg.Class('Altseed2', 'StreamFile')
Cursor = cbg.Class('Altseed2', 'Cursor')
JoystickInfo = cbg.Class('Altseed2', 'JoystickInfo')
Joystick = cbg.Class('Altseed2', 'Joystick')
Keyboard = cbg.Class('Altseed2', 'Keyboard')
Mouse = cbg.Class('Altseed2', 'Mouse')
Log = cbg.Class('Altseed2', 'Log')
Easing = cbg.Class('Altseed2', 'Easing')
Collider = cbg.Class('Altseed2', 'Collider')
RectangleCollider = cbg.Class('Altseed2', 'RectangleCollider')
PolygonCollider = cbg.Class('Altseed2', 'PolygonCollider')
CircleCollider = cbg.Class('Altseed2', 'CircleCollider')
Sound = cbg.Class('Altseed2', 'Sound')
SoundMixer = cbg.Class('Altseed2', 'SoundMixer')
Tool = cbg.Class('Altseed2', 'Tool')

with Window as class_:
    with class_.add_func('DoEvent') as func_:
        func_.return_value.type_ = bool

    with class_.add_property(ctypes.c_wchar_p, 'Title') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(Vector2I, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
define.classes.append(Window)

with Resources as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('GetResourcesCount') as func_:
        func_.return_value.type_ = int
        func_.add_arg(ResourceType, 'type')

    with class_.add_func('Clear') as func_:
        pass

    with class_.add_func('Reload') as func_:
        pass

    with class_.add_property(Resources, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(Resources)

with MaterialPropertyBlock as class_:
    with class_.add_func('GetVector4F') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(Vector4F, 'value')

    with class_.add_func('SetVector4F') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(Vector4F, 'value')

    with class_.add_func('GetMatrix44F') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(Matrix44F, 'value')

    with class_.add_func('SetMatrix44F') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(Matrix44F, 'value')

    with class_.add_func('GetTexture') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(TextureBase, 'value')

    with class_.add_func('SetTexture') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(TextureBase, 'value')

define.classes.append(MaterialPropertyBlock)

with MaterialPropertyBlockCollection as class_:
    with class_.add_func('Add') as func_:
        func_.add_arg(MaterialPropertyBlock, 'block')

    with class_.add_func('Clear') as func_:
        pass

    with class_.add_func('GetVector4F') as func_:
        func_.return_value.type_ = Vector4F
        func_.add_arg(ctypes.c_wchar_p, 'key')

    with class_.add_func('GetMatrix44F') as func_:
        func_.return_value.type_ = Matrix44F
        func_.add_arg(ctypes.c_wchar_p, 'key')

    with class_.add_func('GetTexture') as func_:
        func_.return_value.type_ = TextureBase
        func_.add_arg(ctypes.c_wchar_p, 'key')

define.classes.append(MaterialPropertyBlockCollection)

with Material as class_:
    with class_.add_func('Create') as func_:
        func_.return_value.type_ = Material

    with class_.add_func('GetVector4F') as func_:
        func_.return_value.type_ = Vector4F
        func_.add_arg(ctypes.c_wchar_p, 'key')

    with class_.add_func('SetVector4F') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(Vector4F, 'value')

    with class_.add_func('GetMatrix44F') as func_:
        func_.return_value.type_ = Matrix44F
        func_.add_arg(ctypes.c_wchar_p, 'key')

    with class_.add_func('SetMatrix44F') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(Matrix44F, 'value')

    with class_.add_func('GetTexture') as func_:
        func_.return_value.type_ = TextureBase
        func_.add_arg(ctypes.c_wchar_p, 'key')

    with class_.add_func('SetTexture') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'key')
        func_.add_arg(TextureBase, 'value')

    with class_.add_func('GetShader') as func_:
        func_.return_value.type_ = Shader
        func_.add_arg(ShaderStageType, 'shaderStage')

    with class_.add_property(int, 'BlendFuncs') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(Shader, 'Shader') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(AlphaBlend, 'AlphaBlend') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(MaterialPropertyBlock, 'PropertyBlock') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'PipelineState') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(Material)

with Texture2D as class_:
    with class_.add_func('Reload') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('Load') as func_:
        func_.return_value.type_ = Texture2D
        func_.add_arg(ctypes.c_wchar_p, 'path')

    with class_.add_property(ctypes.c_wchar_p, 'Path') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(Texture2D)

with Configuration as class_:
    with class_.add_func('Create') as func_:
        func_.return_value.type_ = Configuration

    with class_.add_property(bool, 'IsFullscreen') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(bool, 'IsResizable') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(GraphicsDeviceType, 'DeviceType') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(bool, 'WaitVSync') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(CoreModules, 'EnabledCoreModules') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(bool, 'ConsoleLoggingEnabled') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(bool, 'FileLoggingEnabled') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(ctypes.c_wchar_p, 'LogFileName') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
define.classes.append(Configuration)

with FPS as class_:
    with class_.add_func('Update') as func_:
        pass

    with class_.add_property(float, 'DeltaSecond') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'CurrentFPS') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'TargetFPS') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Target') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(FramerateMode, 'FramerateMode') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
define.classes.append(FPS)

with Core as class_:
    with class_.add_func('PrintAllBaseObjectName') as func_:
        pass

    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'width')
        func_.add_arg(int, 'height')

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('DoEvent') as func_:
        func_.return_value.type_ = bool

    with class_.add_property(int, 'BaseObjectCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Core, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'DeltaSecond') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'CurrentFPS') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'TargetFPS') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(FramerateMode, 'FramerateMode') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
define.classes.append(Core)

with StaticFile as class_:
    with class_.add_func('Create') as func_:
        func_.return_value.type_ = StaticFile
        func_.add_arg(ctypes.c_wchar_p, 'path')

    with class_.add_func('Reload') as func_:
        func_.return_value.type_ = bool

    with class_.add_property(Int8Array, 'Buffer') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'Path') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(bool, 'IsInPackage') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(StaticFile)

with Glyph as class_:
    with class_.add_property(Vector2I, 'TextureSize') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'TextureIndex') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2I, 'Position') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2I, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2I, 'Offset') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'GlyphWidth') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(Glyph)

with Font as class_:
    with class_.add_func('GetGlyph') as func_:
        func_.return_value.type_ = Glyph
        func_.add_arg(int, 'character')

    with class_.add_func('GetFontTexture') as func_:
        func_.return_value.type_ = Texture2D
        func_.add_arg(int, 'index')

    with class_.add_func('GetKerning') as func_:
        func_.return_value.type_ = int
        func_.add_arg(int, 'c1')
        func_.add_arg(int, 'c2')

    with class_.add_func('LoadDynamicFont') as func_:
        func_.return_value.type_ = Font
        func_.add_arg(ctypes.c_wchar_p, 'path')
        func_.add_arg(int, 'size')

    with class_.add_func('LoadStaticFont') as func_:
        func_.return_value.type_ = Font
        func_.add_arg(ctypes.c_wchar_p, 'path')

    with class_.add_func('CreateImageFont') as func_:
        func_.return_value.type_ = Font
        func_.add_arg(Font, 'baseFont')

    with class_.add_func('GenerateFontFile') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'dynamicFontPath')
        func_.add_arg(ctypes.c_wchar_p, 'staticFontPath')
        func_.add_arg(int, 'size')
        func_.add_arg(ctypes.c_wchar_p, 'characters')

    with class_.add_func('AddImageGlyph') as func_:
        func_.add_arg(int, 'character')
        func_.add_arg(Texture2D, 'texture')

    with class_.add_func('GetImageGlyph') as func_:
        func_.return_value.type_ = Texture2D
        func_.add_arg(int, 'character')

    with class_.add_func('Reload') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('AddFontTexture') as func_:
        pass

    with class_.add_func('AddGlyph') as func_:
        func_.add_arg(int, 'character')

    with class_.add_property(int, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Ascent') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Descent') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'LineGap') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(bool, 'IsStaticFont') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'ActualSize') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'PixelDistScale') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'ActualScale') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'Scale') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'Path') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(Font)

with FrameDebugger as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('Start') as func_:
        pass

    with class_.add_func('End') as func_:
        pass

    with class_.add_func('DumpToLog') as func_:
        pass

    with class_.add_func('Clear') as func_:
        pass

    with class_.add_func('SetRenderTargetWithRealScreen') as func_:
        pass

    with class_.add_func('BeginRenderPass') as func_:
        pass

    with class_.add_func('EndRenderPass') as func_:
        pass

    with class_.add_func('EndFrame') as func_:
        pass

# std::u16string
    """
    with class_.add_func('Render') as func_:
        func_.add_arg(int, 'indexCount')

    """

    with class_.add_func('SetVertexBuffer') as func_:
        func_.add_arg(int, 'stride')
        func_.add_arg(int, 'offset')

# std::u16string
    """
    with class_.add_func('Uniform') as func_:
        func_.add_arg(ShaderStageType, 'stageType')

    """

# std::u16string
    """
    with class_.add_func('Texture') as func_:
        func_.add_arg(ShaderStageType, 'stageType')

    """

    with class_.add_property(FrameDebugger, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(RenderTexture, 'RenderTarget') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(int, 'IndexBuffer') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    # class_.add_property(std::u16string, 'DebuggingRenderTargetFileNameAndMoveNext')
    with class_.add_property(bool, 'IsEnabled') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(FrameDebugger)

with ImageFont as class_:
    with class_.add_func('GetGlyph') as func_:
        func_.return_value.type_ = Glyph
        func_.add_arg(int, 'character')

    with class_.add_func('GetFontTexture') as func_:
        func_.return_value.type_ = Texture2D
        func_.add_arg(int, 'index')

    with class_.add_func('GetKerning') as func_:
        func_.return_value.type_ = int
        func_.add_arg(int, 'c1')
        func_.add_arg(int, 'c2')

    with class_.add_func('AddImageGlyph') as func_:
        func_.add_arg(int, 'character')
        func_.add_arg(Texture2D, 'texture')

    with class_.add_func('GetImageGlyph') as func_:
        func_.return_value.type_ = Texture2D
        func_.add_arg(int, 'character')

    with class_.add_property(int, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Ascent') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Descent') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'LineGap') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(bool, 'IsStaticFont') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'ActualSize') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'PixelDistScale') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'ActualScale') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'Scale') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(ImageFont)

with CullingSystem as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('Register') as func_:
        func_.add_arg(Rendered, 'rendered')

    with class_.add_func('UpdateAABB') as func_:
        pass

    with class_.add_func('Cull') as func_:
        func_.add_arg(RectF, 'rect')

    with class_.add_func('Unregister') as func_:
        func_.add_arg(Rendered, 'rendered')

    with class_.add_func('QueryCallback') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'id')

    with class_.add_property(CullingSystem, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'DrawingRenderedCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Int32Array, 'DrawingRenderedIds') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(CullingSystem)

with Renderer as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Window, 'window')
        func_.add_arg(Graphics, 'graphics')
        func_.add_arg(CullingSystem, 'cullingSystem')

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('DrawPolygon') as func_:
        func_.add_arg(RenderedPolygon, 'text')

    with class_.add_func('DrawSprite') as func_:
        func_.add_arg(RenderedSprite, 'sprite')

    with class_.add_func('DrawText') as func_:
        func_.add_arg(RenderedText, 'text')

    with class_.add_func('Render') as func_:
        pass

    with class_.add_func('ResetCamera') as func_:
        pass

    with class_.add_property(Renderer, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(RenderedCamera, 'Camera') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
define.classes.append(Renderer)

with ShaderCompiler as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Graphics, 'graphics')
        func_.add_arg(File, 'file')

    with class_.add_func('Terminate') as func_:
        pass

# char *
    """
    with class_.add_func('Compile') as func_:
        func_.return_value.type_ = ShaderCompileResult

    """

    with class_.add_property(ShaderCompiler, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(ShaderCompiler)

with StreamFile as class_:
    with class_.add_func('Create') as func_:
        func_.return_value.type_ = StreamFile
        func_.add_arg(ctypes.c_wchar_p, 'path')

    with class_.add_func('Read') as func_:
        func_.return_value.type_ = int
        func_.add_arg(int, 'size')

    with class_.add_func('Reload') as func_:
        func_.return_value.type_ = bool

    with class_.add_property(int, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'CurrentPosition') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Int8Array, 'TempBuffer') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'TempBufferSize') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(bool, 'IsInPackage') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'Path') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(StreamFile)

with Cursor as class_:
# void *
    """
    with class_.add_func('LoadPNGImage') as func_:
        func_.return_value.type_ = bool

    """

    with class_.add_func('Create') as func_:
        func_.return_value.type_ = Cursor
        func_.add_arg(ctypes.c_wchar_p, 'path')
        func_.add_arg(Vector2I, 'hot')

define.classes.append(Cursor)

with JoystickInfo as class_:
    with class_.add_func('IsJoystickType') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(JoystickType, 'type')

    with class_.add_property(ctypes.c_wchar_p, 'Name') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'ButtonCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'AxisCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(bool, 'IsGamepad') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'GamepadName') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'GUID') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Bustype') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Vendor') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Product') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'Version') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(JoystickInfo)

with Joystick as class_:
# std::u16string
    """
    with class_.add_func('ToU16') as func_:

    """

    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('RefreshInputState') as func_:
        pass

    with class_.add_func('IsPresent') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'joystickIndex')

    with class_.add_func('GetJoystickInfo') as func_:
        func_.return_value.type_ = JoystickInfo
        func_.add_arg(int, 'joystickIndex')

    with class_.add_func('GetButtonStateByIndex') as func_:
        func_.return_value.type_ = ButtonState
        func_.add_arg(int, 'joystickIndex')
        func_.add_arg(int, 'buttonIndex')

    with class_.add_func('GetButtonStateByType') as func_:
        func_.return_value.type_ = ButtonState
        func_.add_arg(int, 'joystickIndex')
        func_.add_arg(JoystickButton, 'type')

    with class_.add_func('GetAxisStateByIndex') as func_:
        func_.return_value.type_ = float
        func_.add_arg(int, 'joystickIndex')
        func_.add_arg(int, 'axisIndex')

    with class_.add_func('GetAxisStateByType') as func_:
        func_.return_value.type_ = float
        func_.add_arg(int, 'joystickIndex')
        func_.add_arg(JoystickAxis, 'type')

    with class_.add_property(Joystick, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'ConnectedJoystickCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(Joystick)

with Keyboard as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Window, 'window')

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('RefleshKeyStates') as func_:
        pass

    with class_.add_func('GetKeyState') as func_:
        func_.return_value.type_ = ButtonState
        func_.add_arg(Key, 'key')

    with class_.add_property(Keyboard, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(Keyboard)

with Mouse as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Window, 'window')

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('RefreshInputState') as func_:
        pass

    with class_.add_func('GetMouseButtonState') as func_:
        func_.return_value.type_ = ButtonState
        func_.add_arg(MouseButton, 'button')

    with class_.add_property(Mouse, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'Position') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(float, 'Wheel') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(CursorMode, 'CursorMode') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(Cursor, 'CursorImage') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
define.classes.append(Mouse)

with Log as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(bool, 'enabledConsoleLogging')
        func_.add_arg(bool, 'enabledFileLogging')
        func_.add_arg(int, 'filename')

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('SetLevel') as func_:
        func_.add_arg(LogCategory, 'category')
        func_.add_arg(LogLevel, 'level')

    with class_.add_property(Log, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(Log)

with Easing as class_:
    with class_.add_func('GetEasing') as func_:
        func_.return_value.type_ = float
        func_.add_arg(EasingType, 'easing')
        func_.add_arg(float, 't')

    with class_.add_func('Release') as func_:
        func_.return_value.type_ = int

define.classes.append(Easing)

with Collider as class_:
    with class_.add_func('GetIsCollidedWith_') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Collider, 'collider')

    with class_.add_func('GetIsCollidedWith') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Collider, 'collider')

    with class_.add_property(Vector2F, 'Position') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    # class_.add_property(double, 'Rotation')
    with class_.add_property(Matrix44F, 'Transform') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
define.classes.append(Collider)

with RectangleCollider as class_:
    with class_.add_func('GetIsCollidedWith_') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Collider, 'shape')

    with class_.add_func('Create') as func_:
        func_.return_value.type_ = RectangleCollider

    with class_.add_property(Vector2F, 'Size') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(Vector2F, 'CenterPosition') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
define.classes.append(RectangleCollider)

with PolygonCollider as class_:
    with class_.add_func('GetIsCollidedWith_') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Collider, 'collider')

    with class_.add_func('Create') as func_:
        func_.return_value.type_ = PolygonCollider

    with class_.add_property(Vector2FArray, 'Vertexes') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
define.classes.append(PolygonCollider)

with CircleCollider as class_:
    with class_.add_func('GetIsCollidedWith_') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Collider, 'shape')

    with class_.add_func('Create') as func_:
        func_.return_value.type_ = CircleCollider

    # class_.add_property(double, 'Radius')
define.classes.append(CircleCollider)

with SoundMixer as class_:
    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(bool, 'isReloadingEnabled')

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('Play') as func_:
        func_.return_value.type_ = int
        func_.add_arg(Sound, 'sound')

    with class_.add_func('GetIsPlaying') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'id')

    with class_.add_func('StopAll') as func_:
        pass

    with class_.add_func('Stop') as func_:
        func_.add_arg(int, 'id')

    with class_.add_func('Pause') as func_:
        func_.add_arg(int, 'id')

    with class_.add_func('Resume') as func_:
        func_.add_arg(int, 'id')

    with class_.add_func('SetVolume') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'volume')

    with class_.add_func('FadeIn') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'second')

    with class_.add_func('FadeOut') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'second')

    with class_.add_func('Fade') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'second')
        func_.add_arg(float, 'targetedVolume')

    with class_.add_func('GetIsPlaybackSpeedEnabled') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'id')

    with class_.add_func('SetIsPlaybackSpeedEnabled') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(bool, 'isPlaybackSpeedEnabled')

    with class_.add_func('GetPlaybackSpeed') as func_:
        func_.return_value.type_ = float
        func_.add_arg(int, 'id')

    with class_.add_func('SetPlaybackSpeed') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'playbackSpeed')

    with class_.add_func('GetPanningPosition') as func_:
        func_.return_value.type_ = float
        func_.add_arg(int, 'id')

    with class_.add_func('SetPanningPosition') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'panningPosition')

    with class_.add_func('GetPlaybackPosition') as func_:
        func_.return_value.type_ = float
        func_.add_arg(int, 'id')

    with class_.add_func('SetPlaybackPosition') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'position')

    with class_.add_func('GetSpectrum') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(FloatArray, 'spectrums')
        func_.add_arg(int, 'window')

    with class_.add_func('Reload') as func_:
        pass

    with class_.add_property(SoundMixer, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
define.classes.append(SoundMixer)

with Tool as class_:
    with class_.add_func('Dispose') as func_:
        pass

    with class_.add_func('Initialize') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Graphics, 'graphics')

    with class_.add_func('Terminate') as func_:
        pass

    with class_.add_func('OnTerminating') as func_:
        pass

    with class_.add_func('NewFrame') as func_:
        pass

    with class_.add_func('Render') as func_:
        pass

    with class_.add_func('AddFontFromFileTTF') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'path')
        func_.add_arg(float, 'sizePixels')
        func_.add_arg(ToolGlyphRange, 'ranges')

    with class_.add_func('ListBox') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(int, 'current')
        func_.add_arg(ctypes.c_wchar_p, 'items_separated_by_tabs')
        func_.add_arg(int, 'popup_max_height_in_items')

    with class_.add_func('InputText') as func_:
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'input')
        func_.add_arg(int, 'max_length')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputTextWithHint') as func_:
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'hint')
        func_.add_arg(ctypes.c_wchar_p, 'input')
        func_.add_arg(int, 'max_length')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputTextMultiline') as func_:
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'input')
        func_.add_arg(int, 'max_length')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('ColorEdit3') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'col')
        func_.add_arg(ToolColorEditFlags, 'flags')

    with class_.add_func('ColorEdit4') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'col')
        func_.add_arg(ToolColorEditFlags, 'flags')

    with class_.add_func('Image') as func_:
        func_.add_arg(TextureBase, 'texture')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(Vector2F, 'uv0')
        func_.add_arg(Vector2F, 'uv1')
        func_.add_arg(Color, 'tint_col')
        func_.add_arg(Color, 'border_col')

    with class_.add_func('ImageButton') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(TextureBase, 'texture')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(Vector2F, 'uv0')
        func_.add_arg(Vector2F, 'uv1')
        func_.add_arg(int, 'frame_padding')
        func_.add_arg(Color, 'bg_col')
        func_.add_arg(Color, 'tint_col')

    with class_.add_func('Combo') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(int, 'current_item')
        func_.add_arg(ctypes.c_wchar_p, 'items_separated_by_tabs')
        func_.add_arg(int, 'popup_max_height_in_items')

# Color *
    """
    with class_.add_func('ColorButton') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'desc_id')

    """

    with class_.add_func('PlotLines') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'values')
        func_.add_arg(int, 'values_count')
        func_.add_arg(int, 'values_offset')
        func_.add_arg(ctypes.c_wchar_p, 'overlay_text')
        func_.add_arg(float, 'scale_min')
        func_.add_arg(float, 'scale_max')
        func_.add_arg(Vector2F, 'graph_size')
        func_.add_arg(int, 'stride')

    with class_.add_func('PlotHistogram') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'values')
        func_.add_arg(int, 'values_count')
        func_.add_arg(int, 'values_offset')
        func_.add_arg(ctypes.c_wchar_p, 'overlay_text')
        func_.add_arg(float, 'scale_min')
        func_.add_arg(float, 'scale_max')
        func_.add_arg(Vector2F, 'graph_size')
        func_.add_arg(int, 'stride')

    with class_.add_func('OpenDialog') as func_:
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.add_arg(ctypes.c_wchar_p, 'filter')
        func_.add_arg(ctypes.c_wchar_p, 'defaultPath')

    with class_.add_func('OpenDialogMultiple') as func_:
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.add_arg(ctypes.c_wchar_p, 'filter')
        func_.add_arg(ctypes.c_wchar_p, 'defaultPath')

    with class_.add_func('SaveDialog') as func_:
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.add_arg(ctypes.c_wchar_p, 'filter')
        func_.add_arg(ctypes.c_wchar_p, 'defaultPath')

    with class_.add_func('PickFolder') as func_:
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.add_arg(ctypes.c_wchar_p, 'defaultPath')

    with class_.add_func('ShowDemoWindow') as func_:
        func_.add_arg(bool, 'p_open')

    with class_.add_func('ShowAboutWindow') as func_:
        func_.add_arg(bool, 'p_open')

    with class_.add_func('ShowMetricsWindow') as func_:
        func_.add_arg(bool, 'p_open')

    with class_.add_func('ShowStyleSelector') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')

    with class_.add_func('ShowFontSelector') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'label')

    with class_.add_func('ShowUserGuide') as func_:
        pass

    with class_.add_func('Begin') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'name')
        func_.add_arg(bool, 'p_open')
        func_.add_arg(ToolWindowFlags, 'flags')

    with class_.add_func('End') as func_:
        pass

    with class_.add_func('BeginChild') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'id')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(bool, 'border')
        func_.add_arg(ToolWindowFlags, 'flags')

    with class_.add_func('EndChild') as func_:
        pass

    with class_.add_func('IsWindowAppearing') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsWindowCollapsed') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsWindowFocused') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolFocusedFlags, 'flags')

    with class_.add_func('IsWindowHovered') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolHoveredFlags, 'flags')

    with class_.add_func('SetNextWindowPos') as func_:
        func_.add_arg(Vector2F, 'pos')
        func_.add_arg(ToolCond, 'cond')
        func_.add_arg(Vector2F, 'pivot')

    with class_.add_func('SetNextWindowSize') as func_:
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(ToolCond, 'cond')

    with class_.add_func('SetNextWindowCollapsed') as func_:
        func_.add_arg(bool, 'collapsed')
        func_.add_arg(ToolCond, 'cond')

    with class_.add_func('SetNextWindowFocus') as func_:
        pass

    with class_.add_func('SetWindowPos') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'name')
        func_.add_arg(Vector2F, 'pos')
        func_.add_arg(ToolCond, 'cond')

    with class_.add_func('SetWindowSize') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'name')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(ToolCond, 'cond')

    with class_.add_func('SetWindowCollapsed') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'name')
        func_.add_arg(bool, 'collapsed')
        func_.add_arg(ToolCond, 'cond')

    with class_.add_func('SetWindowFocus') as func_:
        pass

    with class_.add_func('SetScrollFromPosX') as func_:
        func_.add_arg(float, 'local_x')
        func_.add_arg(float, 'center_x_ratio')

    with class_.add_func('SetScrollFromPosY') as func_:
        func_.add_arg(float, 'local_y')
        func_.add_arg(float, 'center_y_ratio')

    with class_.add_func('PopFont') as func_:
        pass

    with class_.add_func('PushStyleColor') as func_:
        func_.add_arg(ToolCol, 'idx')
        func_.add_arg(Vector4F, 'col')

    with class_.add_func('PopStyleColor') as func_:
        func_.add_arg(int, 'count')

    with class_.add_func('PushStyleVar') as func_:
        func_.add_arg(ToolStyleVar, 'idx')
        func_.add_arg(Vector2F, 'val')

    with class_.add_func('PopStyleVar') as func_:
        func_.add_arg(int, 'count')

    with class_.add_func('GetColorU32') as func_:
        func_.return_value.type_ = int
        func_.add_arg(int, 'col')

    with class_.add_func('PushItemWidth') as func_:
        func_.add_arg(float, 'item_width')

    with class_.add_func('PopItemWidth') as func_:
        pass

    with class_.add_func('CalcItemWidth') as func_:
        func_.return_value.type_ = float

    with class_.add_func('PushTextWrapPos') as func_:
        func_.add_arg(float, 'wrap_local_pos_x')

    with class_.add_func('PopTextWrapPos') as func_:
        pass

    with class_.add_func('PushAllowKeyboardFocus') as func_:
        func_.add_arg(bool, 'allow_keyboard_focus')

    with class_.add_func('PopAllowKeyboardFocus') as func_:
        pass

    with class_.add_func('PushButtonRepeat') as func_:
        func_.add_arg(bool, 'repeat')

    with class_.add_func('PopButtonRepeat') as func_:
        pass

    with class_.add_func('Separator') as func_:
        pass

    with class_.add_func('SameLine') as func_:
        func_.add_arg(float, 'offset_from_start_x')
        func_.add_arg(float, 'spacing')

    with class_.add_func('NewLine') as func_:
        pass

    with class_.add_func('Spacing') as func_:
        pass

    with class_.add_func('Dummy') as func_:
        func_.add_arg(Vector2F, 'size')

    with class_.add_func('Indent') as func_:
        func_.add_arg(float, 'indent_w')

    with class_.add_func('Unindent') as func_:
        func_.add_arg(float, 'indent_w')

    with class_.add_func('BeginGroup') as func_:
        pass

    with class_.add_func('EndGroup') as func_:
        pass

    with class_.add_func('AlignTextToFramePadding') as func_:
        pass

    with class_.add_func('PushID') as func_:
        func_.add_arg(int, 'int_id')

    with class_.add_func('PopID') as func_:
        pass

    with class_.add_func('GetID') as func_:
        func_.return_value.type_ = int
        func_.add_arg(ctypes.c_wchar_p, 'str_id_begin')
        func_.add_arg(ctypes.c_wchar_p, 'str_id_end')

    with class_.add_func('TextUnformatted') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'text')
        func_.add_arg(ctypes.c_wchar_p, 'text_end')

    with class_.add_func('Text') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('TextV') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('TextColored') as func_:
        func_.add_arg(Vector4F, 'col')
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('TextColoredV') as func_:
        func_.add_arg(Vector4F, 'col')
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('TextDisabled') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('TextDisabledV') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('TextWrapped') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('TextWrappedV') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('LabelText') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('LabelTextV') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('BulletText') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('BulletTextV') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('Button') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Vector2F, 'size')

    with class_.add_func('SmallButton') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')

    with class_.add_func('InvisibleButton') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(Vector2F, 'size')

    with class_.add_func('ArrowButton') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolDir, 'dir')

    with class_.add_func('Checkbox') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(bool, 'v')

    with class_.add_func('RadioButton') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(int, 'v')
        func_.add_arg(int, 'v_button')

    with class_.add_func('ProgressBar') as func_:
        func_.add_arg(float, 'fraction')
        func_.add_arg(Vector2F, 'size_arg')
        func_.add_arg(ctypes.c_wchar_p, 'overlay')

    with class_.add_func('Bullet') as func_:
        pass

    with class_.add_func('BeginCombo') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'preview_value')
        func_.add_arg(ToolComboFlags, 'flags')

    with class_.add_func('EndCombo') as func_:
        pass

    with class_.add_func('DragFloat') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(float, 'v')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('DragFloat2') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('DragFloat3') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('DragFloat4') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('DragFloatRange2') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(float, 'v_current_min')
        func_.add_arg(float, 'v_current_max')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(ctypes.c_wchar_p, 'format_max')
        func_.add_arg(float, 'power')

    with class_.add_func('DragInt') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(int, 'v')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('DragInt2') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('DragInt3') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('DragInt4') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('DragIntRange2') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(int, 'v_current_min')
        func_.add_arg(int, 'v_current_max')
        func_.add_arg(float, 'v_speed')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(ctypes.c_wchar_p, 'format_max')

    with class_.add_func('SliderFloat') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(float, 'v')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('SliderFloat2') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('SliderFloat3') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('SliderFloat4') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('SliderAngle') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(float, 'v_rad')
        func_.add_arg(float, 'v_degrees_min')
        func_.add_arg(float, 'v_degrees_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('SliderInt') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(int, 'v')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('SliderInt2') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('SliderInt3') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('SliderInt4') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('VSliderFloat') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(float, 'v')
        func_.add_arg(float, 'v_min')
        func_.add_arg(float, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(float, 'power')

    with class_.add_func('VSliderInt') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(int, 'v')
        func_.add_arg(int, 'v_min')
        func_.add_arg(int, 'v_max')
        func_.add_arg(ctypes.c_wchar_p, 'format')

    with class_.add_func('InputFloat') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(float, 'v')
        func_.add_arg(float, 'step')
        func_.add_arg(float, 'step_fast')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputFloat2') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputFloat3') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputFloat4') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'v')
        func_.add_arg(ctypes.c_wchar_p, 'format')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputInt') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(int, 'v')
        func_.add_arg(int, 'step')
        func_.add_arg(int, 'step_fast')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputInt2') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputInt3') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('InputInt4') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(Int32Array, 'v')
        func_.add_arg(ToolInputTextFlags, 'flags')

    with class_.add_func('ColorPicker3') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'col')
        func_.add_arg(ToolColorEditFlags, 'flags')

    with class_.add_func('ColorPicker4') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'col')
        func_.add_arg(ToolColorEditFlags, 'flags')
        func_.add_arg(float, 'ref_col')

    with class_.add_func('TreeNode') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('TreeNodeV') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('TreeNodeEx') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolTreeNodeFlags, 'flags')
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('TreeNodeExV') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolTreeNodeFlags, 'flags')
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('TreePush') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'str_id')

    with class_.add_func('TreePop') as func_:
        pass

    with class_.add_func('CollapsingHeader') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(bool, 'p_open')
        func_.add_arg(ToolTreeNodeFlags, 'flags')

    with class_.add_func('SetNextItemOpen') as func_:
        func_.add_arg(bool, 'is_open')
        func_.add_arg(ToolCond, 'cond')

    with class_.add_func('Selectable') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(bool, 'p_selected')
        func_.add_arg(ToolSelectableFlags, 'flags')
        func_.add_arg(Vector2F, 'size')

    with class_.add_func('ListBoxHeader') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(int, 'items_count')
        func_.add_arg(int, 'height_in_items')

    with class_.add_func('ListBoxFooter') as func_:
        pass

    with class_.add_func('Value') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'prefix')
        func_.add_arg(float, 'v')
        func_.add_arg(ctypes.c_wchar_p, 'float_format')

    with class_.add_func('BeginMenuBar') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('EndMenuBar') as func_:
        pass

    with class_.add_func('BeginMainMenuBar') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('EndMainMenuBar') as func_:
        pass

    with class_.add_func('BeginMenu') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(bool, 'enabled')

    with class_.add_func('EndMenu') as func_:
        pass

    with class_.add_func('MenuItem') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(ctypes.c_wchar_p, 'shortcut')
        func_.add_arg(bool, 'p_selected')
        func_.add_arg(bool, 'enabled')

    with class_.add_func('BeginTooltip') as func_:
        pass

    with class_.add_func('EndTooltip') as func_:
        pass

    with class_.add_func('SetTooltipV') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')
        func_.add_arg(int, 'args')

    with class_.add_func('OpenPopup') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'str_id')

    with class_.add_func('BeginPopup') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolWindowFlags, 'flags')

    with class_.add_func('BeginPopupContextItem') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolMouseButton, 'mouse_button')

    with class_.add_func('BeginPopupContextWindow') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolMouseButton, 'mouse_button')
        func_.add_arg(bool, 'also_over_items')

    with class_.add_func('BeginPopupContextVoid') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolMouseButton, 'mouse_button')

    with class_.add_func('BeginPopupModal') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'name')
        func_.add_arg(bool, 'p_open')
        func_.add_arg(ToolWindowFlags, 'flags')

    with class_.add_func('EndPopup') as func_:
        pass

    with class_.add_func('OpenPopupOnItemClick') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolMouseButton, 'mouse_button')

    with class_.add_func('IsPopupOpen') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')

    with class_.add_func('CloseCurrentPopup') as func_:
        pass

    with class_.add_func('Columns') as func_:
        func_.add_arg(int, 'count')
        func_.add_arg(ctypes.c_wchar_p, 'id')
        func_.add_arg(bool, 'border')

    with class_.add_func('NextColumn') as func_:
        pass

    with class_.add_func('GetColumnWidth') as func_:
        func_.return_value.type_ = float
        func_.add_arg(int, 'column_index')

    with class_.add_func('SetColumnWidth') as func_:
        func_.add_arg(int, 'column_index')
        func_.add_arg(float, 'width')

    with class_.add_func('GetColumnOffset') as func_:
        func_.return_value.type_ = float
        func_.add_arg(int, 'column_index')

    with class_.add_func('SetColumnOffset') as func_:
        func_.add_arg(int, 'column_index')
        func_.add_arg(float, 'offset_x')

    with class_.add_func('BeginTabBar') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'str_id')
        func_.add_arg(ToolTabBarFlags, 'flags')

    with class_.add_func('EndTabBar') as func_:
        pass

    with class_.add_func('BeginTabItem') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(bool, 'p_open')
        func_.add_arg(ToolTabItemFlags, 'flags')

    with class_.add_func('EndTabItem') as func_:
        pass

    with class_.add_func('LogToTTY') as func_:
        func_.add_arg(int, 'auto_open_depth')

    with class_.add_func('LogToFile') as func_:
        func_.add_arg(int, 'auto_open_depth')
        func_.add_arg(ctypes.c_wchar_p, 'filename')

    with class_.add_func('LogToClipboard') as func_:
        func_.add_arg(int, 'auto_open_depth')

    with class_.add_func('LogFinish') as func_:
        pass

    with class_.add_func('LogButtons') as func_:
        pass

    with class_.add_func('LogText') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'fmt')

    with class_.add_func('BeginDragDropSource') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolDragDropFlags, 'flags')

    with class_.add_func('EndDragDropSource') as func_:
        pass

    with class_.add_func('BeginDragDropTarget') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('EndDragDropTarget') as func_:
        pass

    with class_.add_func('PushClipRect') as func_:
        func_.add_arg(Vector2F, 'clip_rect_min')
        func_.add_arg(Vector2F, 'clip_rect_max')
        func_.add_arg(bool, 'intersect_with_current_clip_rect')

    with class_.add_func('PopClipRect') as func_:
        pass

    with class_.add_func('SetItemDefaultFocus') as func_:
        pass

    with class_.add_func('IsItemHovered') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolHoveredFlags, 'flags')

    with class_.add_func('IsItemActive') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsItemFocused') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsItemClicked') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolMouseButton, 'mouse_button')

    with class_.add_func('IsItemVisible') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsItemEdited') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsItemActivated') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsItemDeactivated') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsItemDeactivatedAfterEdit') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsItemToggledOpen') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsAnyItemHovered') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsAnyItemActive') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsAnyItemFocused') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('SetItemAllowOverlap') as func_:
        pass

    with class_.add_func('IsRectVisible') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Vector2F, 'rect_min')
        func_.add_arg(Vector2F, 'rect_max')

    with class_.add_func('GetStyleColorName') as func_:
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.add_arg(ToolCol, 'idx')

    with class_.add_func('CalcListClipping') as func_:
        func_.add_arg(int, 'items_count')
        func_.add_arg(float, 'items_height')
        func_.add_arg(int, 'out_items_display_start')
        func_.add_arg(int, 'out_items_display_end')

    with class_.add_func('BeginChildFrame') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'id')
        func_.add_arg(Vector2F, 'size')
        func_.add_arg(ToolWindowFlags, 'flags')

    with class_.add_func('EndChildFrame') as func_:
        pass

    with class_.add_func('CalcTextSize') as func_:
        func_.return_value.type_ = Vector2F
        func_.add_arg(ctypes.c_wchar_p, 'text')
        func_.add_arg(ctypes.c_wchar_p, 'text_end')
        func_.add_arg(bool, 'hide_text_after_double_hash')
        func_.add_arg(float, 'wrap_width')

    with class_.add_func('ColorConvertU32ToFloat4') as func_:
        func_.return_value.type_ = Vector4F
        func_.add_arg(int, 'in')

    with class_.add_func('ColorConvertFloat4ToU32') as func_:
        func_.return_value.type_ = int
        func_.add_arg(Vector4F, 'in')

    with class_.add_func('GetKeyIndex') as func_:
        func_.return_value.type_ = int
        func_.add_arg(ToolKey, 'imgui_key')

    with class_.add_func('IsKeyDown') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'user_key_index')

    with class_.add_func('IsKeyPressed') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'user_key_index')
        func_.add_arg(bool, 'repeat')

    with class_.add_func('IsKeyReleased') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(int, 'user_key_index')

    with class_.add_func('GetKeyPressedAmount') as func_:
        func_.return_value.type_ = int
        func_.add_arg(int, 'key_index')
        func_.add_arg(float, 'repeat_delay')
        func_.add_arg(float, 'rate')

    with class_.add_func('CaptureKeyboardFromApp') as func_:
        func_.add_arg(bool, 'want_capture_keyboard_value')

    with class_.add_func('IsMouseDown') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolMouseButton, 'button')

    with class_.add_func('IsMouseClicked') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolMouseButton, 'button')
        func_.add_arg(bool, 'repeat')

    with class_.add_func('IsMouseReleased') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolMouseButton, 'button')

    with class_.add_func('IsMouseDoubleClicked') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolMouseButton, 'button')

    with class_.add_func('IsMouseHoveringRect') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(Vector2F, 'r_min')
        func_.add_arg(Vector2F, 'r_max')
        func_.add_arg(bool, 'clip')

    with class_.add_func('IsAnyMouseDown') as func_:
        func_.return_value.type_ = bool

    with class_.add_func('IsMouseDragging') as func_:
        func_.return_value.type_ = bool
        func_.add_arg(ToolMouseButton, 'button')
        func_.add_arg(float, 'lock_threshold')

    with class_.add_func('GetMouseDragDelta') as func_:
        func_.return_value.type_ = Vector2F
        func_.add_arg(ToolMouseButton, 'button')
        func_.add_arg(float, 'lock_threshold')

    with class_.add_func('ResetMouseDragDelta') as func_:
        func_.add_arg(ToolMouseButton, 'button')

    with class_.add_func('CaptureMouseFromApp') as func_:
        func_.add_arg(bool, 'want_capture_mouse_value')

    with class_.add_func('LoadIniSettingsFromDisk') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'ini_filename')

    with class_.add_func('SaveIniSettingsToDisk') as func_:
        func_.add_arg(ctypes.c_wchar_p, 'ini_filename')

    with class_.add_property(Tool, 'Instance') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ToolUsage, 'ToolUsage') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(float, 'Time') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'Version') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'WindowPos') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'WindowSize') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'WindowWidth') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'WindowHeight') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'NextWindowContentSize') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(float, 'NextWindowBgAlpha') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(float, 'WindowFontScale') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(ctypes.c_wchar_p, 'WindowFocus') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(Vector2F, 'ContentRegionMax') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'ContentRegionAvail') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'WindowContentRegionMin') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'WindowContentRegionMax') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'WindowContentRegionWidth') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'ScrollX') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(float, 'ScrollY') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(float, 'ScrollMaxX') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'ScrollMaxY') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'ScrollHereX') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(float, 'ScrollHereY') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(float, 'FontSize') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'FontTexUvWhitePixel') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'NextItemWidth') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(Vector2F, 'CursorPos') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(float, 'CursorPosX') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(float, 'CursorPosY') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(Vector2F, 'CursorStartPos') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'CursorScreenPos') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
    with class_.add_property(float, 'TextLineHeight') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'TextLineHeightWithSpacing') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'FrameHeight') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(float, 'FrameHeightWithSpacing') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ToolColorEditFlags, 'ColorEditOptions') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(float, 'TreeNodeToLabelSpacing') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'Tooltip') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(int, 'ColumnIndex') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'ColumnsCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'TabItemClosed') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(int, 'KeyboardFocusHere') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(Vector2F, 'ItemRectMin') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'ItemRectMax') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'ItemRectSize') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(int, 'FrameCount') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'MousePos') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(Vector2F, 'MousePosOnOpeningCurrentPopup') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ToolMouseCursor, 'MouseCursor') as prop_:
        prop_.has_getter = False
        prop_.has_setter = True
    with class_.add_property(ctypes.c_wchar_p, 'ClipboardText') as prop_:
        prop_.has_getter = True
        prop_.has_setter = True
define.classes.append(Tool)

