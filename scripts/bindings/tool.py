from . import CppBindingGenerator as cbg
import ctypes
from .math import Vector2F, Vector4F
from .common import *
from .graphics import *

ToolUsage = cbg.Enum('Altseed2', 'ToolUsage')
with ToolUsage as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'ツール機能の使用方法(描画位置)')

    with enum_.add('Overwrapped', 0) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '画面の上に表示')
    with enum_.add('Main', 1) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '画面を表示せずにツールのみ表示')

ToolGlyphRange = cbg.Enum('Altseed2', 'ToolGlyphRange')
with ToolGlyphRange as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('en', 'Don\'t bit operation')
    enum_.brief.add('ja', 'ツール機能を使ってフォントを読み込む際の範囲を指定します。ビット演算は行わないでください。')

    enum_.add('Default')

    with enum_.add('Cyrillic') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'キリル文字')

    with enum_.add('Japanese') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '日本語')
    with enum_.add('ChineseFull') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '繁体字中国語')
    with enum_.add('ChineseSimplifiedCommon') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '簡体字中国語')
    with enum_.add('Korean') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '韓国語')
    with enum_.add('Thai') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'タイ語')

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
    enum_.add('UnsavedDocument', 1 << 20)
    enum_.add('NoNav', (1 << 18) | (1 << 19))
    enum_.add('NoDecoration', (1 << 0) | (1 << 1) | (1 << 3) | (1 << 5))
    enum_.add('NoInputs', (1 << 9) | (1 << 18) | (1 << 19))
    enum_.add('NavFlattened', 1 << 23)
    enum_.add('ChildWindow', 1 << 24)
    enum_.add('Tooltip', 1 << 25)
    enum_.add('Popup', 1 << 26)
    enum_.add('Modal', 1 << 27)
    enum_.add('ChildMenu', 1 << 28)

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
    enum_.add('DefaultOpen', 1 << 5)
    enum_.add('OpenOnDoubleClick', 1 << 6)
    enum_.add('OpenOnArrow', 1 << 7)
    enum_.add('Leaf', 1 << 8)
    enum_.add('Bullet', 1 << 9)
    enum_.add('FramePadding', 1 << 10)
    enum_.add('SpanAvailWidth', 1 << 11)
    enum_.add('SpanFullWidth', 1 << 12)
    enum_.add('NavLeftJumpsBackHere', 1 << 13)
    enum_.add('CollapsingHeader', (1 << 1) | (1 << 3) | (1 << 4))

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

ToolFocusedFlags = cbg.Enum('Altseed2', 'ToolFocusedFlags')
with ToolFocusedFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('ChildWindows', 1 << 0)
    enum_.add('RootWindow', 1 << 1)
    enum_.add('AnyWindow', 1 << 2)
    enum_.add('RootAndChildWindows', (1 << 1) | (1 << 0))

ToolHoveredFlags = cbg.Enum('Altseed2', 'ToolHoveredFlags')
with ToolHoveredFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('ChildWindows', 1 << 0)
    enum_.add('RootWindow', 1 << 1)
    enum_.add('AnyWindow', 1 << 2)
    enum_.add('AllowWhenBlockedByPopup', 1 << 3)
    enum_.add('AllowWhenBlockedByActiveItem', 1 << 5)
    enum_.add('AllowWhenOverlapped', 1 << 6)
    enum_.add('AllowWhenDisabled', 1 << 7)
    enum_.add('RectOnly', (1 << 3) | (1 << 5) | (1 << 6))
    enum_.add('RootAndChildWindows', (1 << 1) | (1 << 0))

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
    enum_.add('AcceptNoPreviewTooltip', 1 << 12)
    enum_.add('AcceptPeekOnly', (1 << 10) | (1 << 11))

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
    enum_.add('Uint8', 1 << 23)
    enum_.add('Float', 1 << 24)
    enum_.add('PickerHueBar', 1 << 25)
    enum_.add('PickerHueWheel', 1 << 26)
    enum_.add('InputRGB', 1 << 27)
    enum_.add('InputHSV', 1 << 28)
    enum_.add('OptionsDefault', (1 << 23) | (1 << 20) | (1 << 27) | (1 << 25))
    enum_.add('DisplayMask', (1 << 20) | (1 << 21) | (1 << 22))
    enum_.add('DataTypeMask', (1 << 23) | (1 << 24))
    enum_.add('PickerMask', (1 << 26) | (1 << 25))
    enum_.add('InputMask', (1 << 27) | (1 << 28))

ToolMouseButton = cbg.Enum('Altseed2', 'ToolMouseButton')
with ToolMouseButton as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Left', 0)
    enum_.add('Right', 1)
    enum_.add('Middle', 2)
    enum_.add('COUNT', 5)

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

ToolCond = cbg.Enum('Altseed2', 'ToolCond')
with ToolCond as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('Always', 1 << 0)
    enum_.add('Once', 1 << 1)
    enum_.add('FirstUseEver', 1 << 2)
    enum_.add('Appearing', 1 << 3)

ToolDrawCornerFlags = cbg.Enum('Altseed2', 'ToolDrawCornerFlags')
with ToolDrawCornerFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('TopLeft', 1 << 0)
    enum_.add('TopRight', 1 << 1)
    enum_.add('BotLeft', 1 << 2)
    enum_.add('BotRight', 1 << 3)
    enum_.add('Top', (1 << 0) | (1 << 1))
    enum_.add('Bot', (1 << 2) | (1 << 3))
    enum_.add('Left', (1 << 0) | (1 << 2))
    enum_.add('Right', (1 << 1) | (1 << 3))
    enum_.add('All', 0xF)

ToolDrawListFlags = cbg.Enum('Altseed2', 'ToolDrawListFlags')
with ToolDrawListFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('AntiAliasedLines', 1 << 0)
    enum_.add('AntiAliasedFill', 1 << 1)
    enum_.add('AllowVtxOffset', 1 << 2)

ToolFontAtlasFlags = cbg.Enum('Altseed2', 'ToolFontAtlasFlags')
with ToolFontAtlasFlags as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
    enum_.add('None', 0)
    enum_.add('NoPowerOfTwoHeight', 1 << 0)
    enum_.add('NoMouseCursors', 1 << 1)

Tool = cbg.Class('Altseed2', 'Tool')
with Tool as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'imguiのツール処理を行うクラス')
    class_.is_Sealed = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.is_static = True
        func.is_public = False
        func.return_value.type_ = Tool

    with class_.add_property(ToolUsage, 'ToolUsage') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'ツールの使用方法を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True

    with class_.add_func('AddFontFromFileTTF') as func_:
        func_.brief = cbg.Description()
        func_.brief.add(
            'en', 'Load font from path. Packed files are not supported.')
        func_.brief.add('ja', 'パスからフォントを読み込みます。パックされたファイルは非対応です。')
        func_.add_arg(ctypes.c_wchar_p, 'path')
        func_.add_arg(float, 'sizePixels')
        func_.add_arg(ToolGlyphRange, 'ranges')
        func_.return_value.type_ = bool

    with class_.add_func('ListBox') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'リストボックスを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(int, 'current') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '選択中のアイテムのインデックス -1で選択無し')
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ctypes.c_wchar_p, 'items') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'タブ文字を用いて分割したアイテム')
        with func_.add_arg(int, 'popupMaxHeightInItems') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '一度に表示されるアイテムの個数')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', 'アイテムがクリックされたらtrue，それ以外でfalse')

    with class_.add_func('InputText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'テキストを入力するボックスを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'input') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '入力するテキスト')
            arg.nullable = False
        with func_.add_arg(int, 'maxLength') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '処理するテキストの最大長')
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力されたテキスト')

    with class_.add_func('InputTextWithHint') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'ヒント付きのテキスト入力ボックスを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'hint') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インプットされている文字列長が0の時に表示されるヒント')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'input') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '入力するテキスト')
            arg.nullable = False
        with func_.add_arg(int, 'maxLength') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '処理するテキストの最大長')
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力されたテキスト')

    with class_.add_func('InputTextMultiline') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '複数行のテキストが入力可能なボックスを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'input') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '入力するテキスト')
            arg.nullable = False
        with func_.add_arg(int, 'maxLength') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '処理するテキストの最大長')
        with func_.add_arg(Vector2F, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'サイズ')
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力されたテキスト')

    with class_.add_func('ColorEdit3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '色を入力するツールを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(Color, 'color') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '扱う色')
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力が決定されたらtrue，それ以外でfalse')

    with class_.add_func('ColorEdit4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '色を入力するツールを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(Color, 'color') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '扱う色')
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力が決定されたらtrue，それ以外でfalse')

    with class_.add_func('Image') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '画像表示ボックスを生成します。')
        with func_.add_arg(TextureBase, 'texture') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '表示するテクスチャ')
        with func_.add_arg(Vector2F, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'サイズ')
        with func_.add_arg(Vector2F, 'uv0') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャのUV値(0~1)')
        with func_.add_arg(Vector2F, 'uv1') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャのUV値(0~1)')
        with func_.add_arg(Color, 'tintColor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャの色')
        with func_.add_arg(Color, 'borderColor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '縁の色')

    with class_.add_func('ImageButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'ボタンとして機能する画像表示ボックスを生成します。')
        with func_.add_arg(TextureBase, 'texture') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '表示するテクスチャ')
        with func_.add_arg(Vector2F, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'サイズ')
        with func_.add_arg(Vector2F, 'uv0') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャのUV値(0~1)')
        with func_.add_arg(Vector2F, 'uv1') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャのUV値(0~1)')
        with func_.add_arg(int, 'framePadding') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '縁の太さ')
        with func_.add_arg(Color, 'tintColor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャの色')
        with func_.add_arg(Color, 'borderColor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '縁の色')
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', 'クリックされたらtrue，それ以外でfalse')
        func_.return_value.type_ = bool

    with class_.add_func('PlotLines') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'values')
        func_.add_arg(int, 'valuesCount')
        func_.add_arg(int, 'valuesOffset')
        func_.add_arg(ctypes.c_wchar_p, 'overlayText')
        func_.add_arg(float, 'scaleMin')
        func_.add_arg(float, 'scaleMax')
        func_.add_arg(Vector2F, 'graphSize')
        func_.add_arg(int, 'stride')
        func_.is_public = False

    with class_.add_func('PlotHistogram') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'values')
        func_.add_arg(int, 'valuesCount')
        func_.add_arg(int, 'valuesOffset')
        func_.add_arg(ctypes.c_wchar_p, 'overlayText')
        func_.add_arg(float, 'scaleMin')
        func_.add_arg(float, 'scaleMax')
        func_.add_arg(Vector2F, 'graphSize')
        func_.add_arg(int, 'stride')
        func_.is_public = False

    with class_.add_func('GetTime') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float

    with class_.add_func('OpenDialog') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '1つの開くファイルを選択するダイアログを開きます。')
        with func_.add_arg(ctypes.c_wchar_p, 'filter') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルの拡張子のフィルタ')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'defaultPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ファイルダイアログの初期位置のパス')
            arg.nullable = False
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '読み込むファイルのパス')

    with class_.add_func('OpenDialogMultiple') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '複数の開くファイルを選択するダイアログを開きます。')
        with func_.add_arg(ctypes.c_wchar_p, 'filter') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルの拡張子のフィルタ')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'defaultPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ファイルダイアログの初期位置のパス')
            arg.nullable = False
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '読み込むファイルのパス')

    with class_.add_func('SaveDialog') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '保存するファイルを選択するダイアログを開きます。')
        with func_.add_arg(ctypes.c_wchar_p, 'filter') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '保存するファイルの拡張子のフィルタ')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'defaultPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ファイルダイアログの初期位置のパス')
            arg.nullable = False
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '保存するファイルのパス')

    with class_.add_func('PickFolder') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'フォルダを選択するダイアログを開きます。')
        with func_.add_arg(ctypes.c_wchar_p, 'defaultPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ファイルダイアログの初期位置のパス')
            arg.nullable = False
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '選択するフォルダのパス')

    # ImGuiContext *(ImFontAtlas *) CreateContext

    # void (ImGuiContext *) DestroyContext

    # ImGuiContext *() GetCurrentContext

    # void (ImGuiContext *) SetCurrentContext

    # ImGuiIO &() GetIO

    # ImGuiStyle &() GetStyle

    # ImDrawData *() GetDrawData


    with class_.add_func('ShowDemoWindow') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'p_open') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref


    with class_.add_func('ShowAboutWindow') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'p_open') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref


    with class_.add_func('ShowMetricsWindow') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'p_open') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref

    # void (ImGuiStyle *) ShowStyleEditor


    with class_.add_func('ShowStyleSelector') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ShowFontSelector') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass


    with class_.add_func('ShowUserGuide') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('GetVersion') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # void (ImGuiStyle *) StyleColorsDark

    # void (ImGuiStyle *) StyleColorsClassic

    # void (ImGuiStyle *) StyleColorsLight


    with class_.add_func('Begin') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'name') as arg:
            pass
        with func_.add_arg(bool, 'p_open') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolWindowFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('End') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('BeginChild') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        with func_.add_arg(bool, 'border') as arg:
            pass
        with func_.add_arg(ToolWindowFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('BeginChild') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'id') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        with func_.add_arg(bool, 'border') as arg:
            pass
        with func_.add_arg(ToolWindowFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndChild') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('IsWindowAppearing') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsWindowCollapsed') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsWindowFocused') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolFocusedFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsWindowHovered') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolHoveredFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # ImDrawList *() GetWindowDrawList


    with class_.add_func('GetWindowPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetWindowSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetWindowWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetWindowHeight') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetNextWindowPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'pos') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass
        with func_.add_arg(Vector2F, 'pivot') as arg:
            pass


    with class_.add_func('SetNextWindowSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass

    # void (const ImVec2 &, const ImVec2 &, ImGuiSizeCallback, void *) SetNextWindowSizeConstraints


    with class_.add_func('SetNextWindowContentSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'size') as arg:
            pass


    with class_.add_func('SetNextWindowCollapsed') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'collapsed') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass


    with class_.add_func('SetNextWindowFocus') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('SetNextWindowBgAlpha') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'alpha') as arg:
            pass


    with class_.add_func('SetWindowPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'pos') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass


    with class_.add_func('SetWindowSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass


    with class_.add_func('SetWindowCollapsed') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'collapsed') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass


    with class_.add_func('SetWindowFocus') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('SetWindowFontScale') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'scale') as arg:
            pass


    with class_.add_func('SetWindowPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'name') as arg:
            pass
        with func_.add_arg(Vector2F, 'pos') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass


    with class_.add_func('SetWindowSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'name') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass


    with class_.add_func('SetWindowCollapsed') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'name') as arg:
            pass
        with func_.add_arg(bool, 'collapsed') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass


    with class_.add_func('SetWindowFocus') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'name') as arg:
            pass


    with class_.add_func('GetContentRegionMax') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetContentRegionAvail') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetWindowContentRegionMin') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetWindowContentRegionMax') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetWindowContentRegionWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetScrollX') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetScrollY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetScrollMaxX') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetScrollMaxY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetScrollX') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'scroll_x') as arg:
            pass


    with class_.add_func('SetScrollY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'scroll_y') as arg:
            pass


    with class_.add_func('SetScrollHereX') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'center_x_ratio') as arg:
            pass


    with class_.add_func('SetScrollHereY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'center_y_ratio') as arg:
            pass


    with class_.add_func('SetScrollFromPosX') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'local_x') as arg:
            pass
        with func_.add_arg(float, 'center_x_ratio') as arg:
            pass


    with class_.add_func('SetScrollFromPosY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'local_y') as arg:
            pass
        with func_.add_arg(float, 'center_y_ratio') as arg:
            pass

    # void (ImFont *) PushFont


    with class_.add_func('PopFont') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('PushStyleColor') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolCol, 'idx') as arg:
            pass
        with func_.add_arg(int, 'col') as arg:
            pass


    with class_.add_func('PushStyleColor') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolCol, 'idx') as arg:
            pass
        with func_.add_arg(Vector4F, 'col') as arg:
            pass


    with class_.add_func('PopStyleColor') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'count') as arg:
            pass


    with class_.add_func('PushStyleVar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolStyleVar, 'idx') as arg:
            pass
        with func_.add_arg(float, 'val') as arg:
            pass


    with class_.add_func('PushStyleVar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolStyleVar, 'idx') as arg:
            pass
        with func_.add_arg(Vector2F, 'val') as arg:
            pass


    with class_.add_func('PopStyleVar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'count') as arg:
            pass

    # const ImVec4 &(ImGuiCol) GetStyleColorVec4

    # ImFont *() GetFont


    with class_.add_func('GetFontSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetFontTexUvWhitePixel') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetColorU32') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolCol, 'idx') as arg:
            pass
        with func_.add_arg(float, 'alpha_mul') as arg:
            pass
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetColorU32') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector4F, 'col') as arg:
            pass
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetColorU32') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'col') as arg:
            pass
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('PushItemWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'item_width') as arg:
            pass


    with class_.add_func('PopItemWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('SetNextItemWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'item_width') as arg:
            pass


    with class_.add_func('CalcItemWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('PushTextWrapPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'wrap_local_pos_x') as arg:
            pass


    with class_.add_func('PopTextWrapPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('PushAllowKeyboardFocus') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'allow_keyboard_focus') as arg:
            pass


    with class_.add_func('PopAllowKeyboardFocus') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('PushButtonRepeat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'repeat') as arg:
            pass


    with class_.add_func('PopButtonRepeat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('Separator') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('SameLine') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'offset_from_start_x') as arg:
            pass
        with func_.add_arg(float, 'spacing') as arg:
            pass


    with class_.add_func('NewLine') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('Spacing') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('Dummy') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'size') as arg:
            pass


    with class_.add_func('Indent') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'indent_w') as arg:
            pass


    with class_.add_func('Unindent') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'indent_w') as arg:
            pass


    with class_.add_func('BeginGroup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('EndGroup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('GetCursorPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetCursorPosX') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetCursorPosY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetCursorPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'local_pos') as arg:
            pass


    with class_.add_func('SetCursorPosX') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'local_x') as arg:
            pass


    with class_.add_func('SetCursorPosY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'local_y') as arg:
            pass


    with class_.add_func('GetCursorStartPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetCursorScreenPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetCursorScreenPos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'pos') as arg:
            pass


    with class_.add_func('AlignTextToFramePadding') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('GetTextLineHeight') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetTextLineHeightWithSpacing') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetFrameHeight') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetFrameHeightWithSpacing') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('PushID') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass


    with class_.add_func('PushID') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id_begin') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'str_id_end') as arg:
            pass

    # void (const void *) PushID


    with class_.add_func('PushID') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'int_id') as arg:
            pass


    with class_.add_func('PopID') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('GetID') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetID') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id_begin') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'str_id_end') as arg:
            pass
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # ImGuiID (const void *) GetID


    with class_.add_func('TextUnformatted') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'text') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'text_end') as arg:
            pass


    with class_.add_func('Text') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass


    with class_.add_func('TextV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass


    with class_.add_func('TextColored') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector4F, 'col') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass


    with class_.add_func('TextColoredV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector4F, 'col') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass


    with class_.add_func('TextDisabled') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass


    with class_.add_func('TextDisabledV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass


    with class_.add_func('TextWrapped') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass


    with class_.add_func('TextWrappedV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass


    with class_.add_func('LabelText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass


    with class_.add_func('LabelTextV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass


    with class_.add_func('BulletText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass


    with class_.add_func('BulletTextV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass


    with class_.add_func('Button') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SmallButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('InvisibleButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ArrowButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolDir, 'dir') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # void (ImTextureID, const ImVec2 &, const ImVec2 &, const ImVec2 &, const ImVec4 &, const ImVec4 &) Image

    # bool (ImTextureID, const ImVec2 &, const ImVec2 &, const ImVec2 &, int, const ImVec4 &, const ImVec4 &) ImageButton


    with class_.add_func('Checkbox') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(bool, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const char *, unsigned int *, unsigned int) CheckboxFlags


    with class_.add_func('RadioButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(bool, 'active') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('RadioButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(int, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(int, 'v_button') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ProgressBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(float, 'fraction') as arg:
            pass
        with func_.add_arg(Vector2F, 'size_arg') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'overlay') as arg:
            pass


    with class_.add_func('Bullet') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('BeginCombo') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'preview_value') as arg:
            pass
        with func_.add_arg(ToolComboFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndCombo') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('DragFloat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(float, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragFloat2') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragFloat3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragFloat4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragFloatRange2') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(float, 'v_current_min') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'v_current_max') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format_max') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragInt') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(int, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragInt2') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragInt3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragInt4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('DragIntRange2') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(int, 'v_current_min') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(int, 'v_current_max') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'v_speed') as arg:
            pass
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format_max') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const char *, ImGuiDataType, void *, float, const void *, const void *, const char *, float) DragScalar

    # bool (const char *, ImGuiDataType, void *, int, float, const void *, const void *, const char *, float) DragScalarN


    with class_.add_func('SliderFloat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(float, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SliderFloat2') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SliderFloat3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SliderFloat4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SliderAngle') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(float, 'v_rad') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'v_degrees_min') as arg:
            pass
        with func_.add_arg(float, 'v_degrees_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SliderInt') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(int, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SliderInt2') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SliderInt3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SliderInt4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const char *, ImGuiDataType, void *, const void *, const void *, const char *, float) SliderScalar

    # bool (const char *, ImGuiDataType, void *, int, const void *, const void *, const char *, float) SliderScalarN


    with class_.add_func('VSliderFloat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        with func_.add_arg(float, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'v_min') as arg:
            pass
        with func_.add_arg(float, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(float, 'power') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('VSliderInt') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        with func_.add_arg(int, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(int, 'v_min') as arg:
            pass
        with func_.add_arg(int, 'v_max') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const char *, const ImVec2 &, ImGuiDataType, void *, const void *, const void *, const char *, float) VSliderScalar

    # bool (const char *, char *, size_t, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputText

    # bool (const char *, char *, size_t, const ImVec2 &, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputTextMultiline

    # bool (const char *, const char *, char *, size_t, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputTextWithHint


    with class_.add_func('InputFloat') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(float, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(float, 'step') as arg:
            pass
        with func_.add_arg(float, 'step_fast') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('InputFloat2') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('InputFloat3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('InputFloat4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'v') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'format') as arg:
            pass
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('InputInt') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(int, 'v') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(int, 'step') as arg:
            pass
        with func_.add_arg(int, 'step_fast') as arg:
            pass
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('InputInt2') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('InputInt3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('InputInt4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Int32Array, 'v') as arg:
            pass
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const char *, double *, double, double, const char *, ImGuiInputTextFlags) InputDouble

    # bool (const char *, ImGuiDataType, void *, const void *, const void *, const char *, ImGuiInputTextFlags) InputScalar

    # bool (const char *, ImGuiDataType, void *, int, const void *, const void *, const char *, ImGuiInputTextFlags) InputScalarN


    with class_.add_func('ColorEdit3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'col') as arg:
            pass
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ColorEdit4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'col') as arg:
            pass
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ColorPicker3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'col') as arg:
            pass
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ColorPicker4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(FloatArray, 'col') as arg:
            pass
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            pass
        with func_.add_arg(float, 'ref_col') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const char *, const ImVec4 &, ImGuiColorEditFlags, ImVec2) ColorButton


    with class_.add_func('SetColorEditOptions') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            pass


    with class_.add_func('TreeNode') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('TreeNode') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const void *, const char *, ...) TreeNode


    with class_.add_func('TreeNodeV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const void *, const char *, int) TreeNodeV


    with class_.add_func('TreeNodeEx') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(ToolTreeNodeFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('TreeNodeEx') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolTreeNodeFlags, 'flags') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const void *, ImGuiTreeNodeFlags, const char *, ...) TreeNodeEx


    with class_.add_func('TreeNodeExV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolTreeNodeFlags, 'flags') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const void *, ImGuiTreeNodeFlags, const char *, int) TreeNodeExV


    with class_.add_func('TreePush') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass

    # void (const void *) TreePush


    with class_.add_func('TreePop') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('GetTreeNodeToLabelSpacing') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('CollapsingHeader') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(ToolTreeNodeFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('CollapsingHeader') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(bool, 'p_open') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolTreeNodeFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetNextItemOpen') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'is_open') as arg:
            pass
        with func_.add_arg(ToolCond, 'cond') as arg:
            pass


    with class_.add_func('Selectable') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(bool, 'selected') as arg:
            pass
        with func_.add_arg(ToolSelectableFlags, 'flags') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('Selectable') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(bool, 'p_selected') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolSelectableFlags, 'flags') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const char *, int *, const char *const *, int, int) ListBox

    # bool (const char *, int *, bool (*)(void *, int, const char **), void *, int, int) ListBox


    with class_.add_func('ListBoxHeader') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ListBoxHeader') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(int, 'items_count') as arg:
            pass
        with func_.add_arg(int, 'height_in_items') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ListBoxFooter') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    # void (const char *, const float *, int, int, const char *, float, float, ImVec2, int) PlotLines

    # void (const char *, float (*)(void *, int), void *, int, int, const char *, float, float, ImVec2) PlotLines

    # void (const char *, const float *, int, int, const char *, float, float, ImVec2, int) PlotHistogram

    # void (const char *, float (*)(void *, int), void *, int, int, const char *, float, float, ImVec2) PlotHistogram


    with class_.add_func('Value') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'prefix') as arg:
            pass
        with func_.add_arg(bool, 'b') as arg:
            pass


    with class_.add_func('Value') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'prefix') as arg:
            pass
        with func_.add_arg(int, 'v') as arg:
            pass

    # void (const char *, unsigned int) Value


    with class_.add_func('Value') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'prefix') as arg:
            pass
        with func_.add_arg(float, 'v') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'float_format') as arg:
            pass


    with class_.add_func('BeginMenuBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndMenuBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('BeginMainMenuBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndMainMenuBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('BeginMenu') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(bool, 'enabled') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndMenu') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('MenuItem') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'shortcut') as arg:
            pass
        with func_.add_arg(bool, 'selected') as arg:
            pass
        with func_.add_arg(bool, 'enabled') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('MenuItem') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'shortcut') as arg:
            pass
        with func_.add_arg(bool, 'p_selected') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(bool, 'enabled') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('BeginTooltip') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('EndTooltip') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('SetTooltip') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass


    with class_.add_func('SetTooltipV') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass
        with func_.add_arg(int, 'args') as arg:
            pass


    with class_.add_func('OpenPopup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass


    with class_.add_func('BeginPopup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolWindowFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('BeginPopupContextItem') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolMouseButton, 'mouse_button') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('BeginPopupContextWindow') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolMouseButton, 'mouse_button') as arg:
            pass
        with func_.add_arg(bool, 'also_over_items') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('BeginPopupContextVoid') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolMouseButton, 'mouse_button') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('BeginPopupModal') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'name') as arg:
            pass
        with func_.add_arg(bool, 'p_open') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolWindowFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndPopup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('OpenPopupOnItemClick') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolMouseButton, 'mouse_button') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsPopupOpen') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('CloseCurrentPopup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('Columns') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'count') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'id') as arg:
            pass
        with func_.add_arg(bool, 'border') as arg:
            pass


    with class_.add_func('NextColumn') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('GetColumnIndex') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetColumnWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'column_index') as arg:
            pass
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetColumnWidth') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'column_index') as arg:
            pass
        with func_.add_arg(float, 'width') as arg:
            pass


    with class_.add_func('GetColumnOffset') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'column_index') as arg:
            pass
        func_.return_value.type_ = float
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetColumnOffset') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'column_index') as arg:
            pass
        with func_.add_arg(float, 'offset_x') as arg:
            pass


    with class_.add_func('GetColumnsCount') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('BeginTabBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'str_id') as arg:
            pass
        with func_.add_arg(ToolTabBarFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndTabBar') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('BeginTabItem') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            pass
        with func_.add_arg(bool, 'p_open') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolTabItemFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndTabItem') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('SetTabItemClosed') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'tab_or_docked_window_label') as arg:
            pass


    with class_.add_func('LogToTTY') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'auto_open_depth') as arg:
            pass


    with class_.add_func('LogToFile') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'auto_open_depth') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'filename') as arg:
            pass


    with class_.add_func('LogToClipboard') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'auto_open_depth') as arg:
            pass


    with class_.add_func('LogFinish') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('LogButtons') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('LogText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'fmt') as arg:
            pass


    with class_.add_func('BeginDragDropSource') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolDragDropFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const char *, const void *, size_t, ImGuiCond) SetDragDropPayload


    with class_.add_func('EndDragDropSource') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('BeginDragDropTarget') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # const ImGuiPayload *(const char *, ImGuiDragDropFlags) AcceptDragDropPayload


    with class_.add_func('EndDragDropTarget') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')

    # const ImGuiPayload *() GetDragDropPayload


    with class_.add_func('PushClipRect') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'clip_rect_min') as arg:
            pass
        with func_.add_arg(Vector2F, 'clip_rect_max') as arg:
            pass
        with func_.add_arg(bool, 'intersect_with_current_clip_rect') as arg:
            pass


    with class_.add_func('PopClipRect') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('SetItemDefaultFocus') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('SetKeyboardFocusHere') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'offset') as arg:
            pass


    with class_.add_func('IsItemHovered') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolHoveredFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemActive') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemFocused') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemClicked') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseButton, 'mouse_button') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemVisible') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemEdited') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemActivated') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemDeactivated') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemDeactivatedAfterEdit') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsItemToggledOpen') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsAnyItemHovered') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsAnyItemActive') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsAnyItemFocused') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetItemRectMin') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetItemRectMax') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetItemRectSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetItemAllowOverlap') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('IsRectVisible') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsRectVisible') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'rect_min') as arg:
            pass
        with func_.add_arg(Vector2F, 'rect_max') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # double () GetTime


    with class_.add_func('GetFrameCount') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # ImDrawList *() GetBackgroundDrawList

    # ImDrawList *() GetForegroundDrawList

    # ImDrawListSharedData *() GetDrawListSharedData


    with class_.add_func('GetStyleColorName') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolCol, 'idx') as arg:
            pass
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # void (ImGuiStorage *) SetStateStorage

    # ImGuiStorage *() GetStateStorage


    with class_.add_func('CalcListClipping') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'items_count') as arg:
            pass
        with func_.add_arg(float, 'items_height') as arg:
            pass
        with func_.add_arg(int, 'out_items_display_start') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(int, 'out_items_display_end') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref


    with class_.add_func('BeginChildFrame') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'id') as arg:
            pass
        with func_.add_arg(Vector2F, 'size') as arg:
            pass
        with func_.add_arg(ToolWindowFlags, 'flags') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('EndChildFrame') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')


    with class_.add_func('CalcTextSize') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'text') as arg:
            pass
        with func_.add_arg(ctypes.c_wchar_p, 'text_end') as arg:
            pass
        with func_.add_arg(bool, 'hide_text_after_double_hash') as arg:
            pass
        with func_.add_arg(float, 'wrap_width') as arg:
            pass
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ColorConvertU32ToFloat4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'in') as arg:
            pass
        func_.return_value.type_ = Vector4F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ColorConvertFloat4ToU32') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector4F, 'in') as arg:
            pass
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # void (float, float, float, float &, float &, float &) ColorConvertRGBtoHSV

    # void (float, float, float, float &, float &, float &) ColorConvertHSVtoRGB


    with class_.add_func('GetKeyIndex') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolKey, 'imgui_key') as arg:
            pass
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsKeyDown') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'user_key_index') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsKeyPressed') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'user_key_index') as arg:
            pass
        with func_.add_arg(bool, 'repeat') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsKeyReleased') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'user_key_index') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetKeyPressedAmount') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(int, 'key_index') as arg:
            pass
        with func_.add_arg(float, 'repeat_delay') as arg:
            pass
        with func_.add_arg(float, 'rate') as arg:
            pass
        func_.return_value.type_ = int
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('CaptureKeyboardFromApp') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'want_capture_keyboard_value') as arg:
            pass


    with class_.add_func('IsMouseDown') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseButton, 'button') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsMouseClicked') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseButton, 'button') as arg:
            pass
        with func_.add_arg(bool, 'repeat') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsMouseReleased') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseButton, 'button') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsMouseDoubleClicked') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseButton, 'button') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsMouseHoveringRect') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(Vector2F, 'r_min') as arg:
            pass
        with func_.add_arg(Vector2F, 'r_max') as arg:
            pass
        with func_.add_arg(bool, 'clip') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')

    # bool (const ImVec2 *) IsMousePosValid


    with class_.add_func('IsAnyMouseDown') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetMousePos') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetMousePosOnOpeningCurrentPopup') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('IsMouseDragging') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseButton, 'button') as arg:
            pass
        with func_.add_arg(float, 'lock_threshold') as arg:
            pass
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('GetMouseDragDelta') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseButton, 'button') as arg:
            pass
        with func_.add_arg(float, 'lock_threshold') as arg:
            pass
        func_.return_value.type_ = Vector2F
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('ResetMouseDragDelta') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseButton, 'button') as arg:
            pass

    # ImGuiMouseCursor () GetMouseCursor


    with class_.add_func('SetMouseCursor') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ToolMouseCursor, 'cursor_type') as arg:
            pass


    with class_.add_func('CaptureMouseFromApp') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(bool, 'want_capture_mouse_value') as arg:
            pass


    with class_.add_func('GetClipboardText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')


    with class_.add_func('SetClipboardText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'text') as arg:
            pass


    with class_.add_func('LoadIniSettingsFromDisk') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'ini_filename') as arg:
            pass

    # void (const char *, size_t) LoadIniSettingsFromMemory


    with class_.add_func('SaveIniSettingsToDisk') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        with func_.add_arg(ctypes.c_wchar_p, 'ini_filename') as arg:
            pass

    # const char *(size_t *) SaveIniSettingsToMemory

    # bool (const char *, size_t, size_t, size_t, size_t, size_t, size_t) DebugCheckVersionAndDataLayout

    # void (void *(*)(size_t, void *), void (*)(void *, void *), void *) SetAllocatorFunctions

    # void *(size_t) MemAlloc

    # void (void *) MemFree

