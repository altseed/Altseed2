#pragma once
#include <cfloat>

#include "../Common/Array.h"
#include "../Graphics/Graphics.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector4F.h"

class ImguiPlatform;

namespace Altseed2 {

class Graphics;

enum class ToolGlyphRange : int32_t {
    Default,
    // キリル文字
    Cyrillic,
    Japanese,
    ChineseFull,
    ChineseSimplifiedCommon,
    Korean,
    Thai,
};

enum class ToolUsage {
    Overwrapped,
    Main,
};
enum class ToolWindowFlags : int32_t {
    None = 0,
    NoTitleBar = 1 << 0,
    NoResize = 1 << 1,
    NoMove = 1 << 2,
    NoScrollbar = 1 << 3,
    NoScrollWithMouse = 1 << 4,
    NoCollapse = 1 << 5,
    AlwaysAutoResize = 1 << 6,
    NoBackground = 1 << 7,
    NoSavedSettings = 1 << 8,
    NoMouseInputs = 1 << 9,
    MenuBar = 1 << 10,
    HorizontalScrollbar = 1 << 11,
    NoFocusOnAppearing = 1 << 12,
    NoBringToFrontOnFocus = 1 << 13,
    AlwaysVerticalScrollbar = 1 << 14,
    AlwaysHorizontalScrollbar = 1 << 15,
    AlwaysUseWindowPadding = 1 << 16,
    NoNavInputs = 1 << 18,
    NoNavFocus = 1 << 19,
    UnsavedDocument = 1 << 20,
    NoDocking = 1 << 21,
    NoNav = NoNavInputs | NoNavFocus,
    NoDecoration = NoTitleBar | NoResize | NoScrollbar | NoCollapse,
    NoInputs = NoMouseInputs | NoNavInputs | NoNavFocus,
    NavFlattened = 1 << 23,
    ChildWindow = 1 << 24,
    Tooltip = 1 << 25,
    Popup = 1 << 26,
    Modal = 1 << 27,
    ChildMenu = 1 << 28,
    DockNodeHost = 1 << 29,
};

enum class ToolInputTextFlags : int32_t {
    None = 0,
    CharsDecimal = 1 << 0,
    CharsHexadecimal = 1 << 1,
    CharsUppercase = 1 << 2,
    CharsNoBlank = 1 << 3,
    AutoSelectAll = 1 << 4,
    EnterReturnsTrue = 1 << 5,
    CallbackCompletion = 1 << 6,
    CallbackHistory = 1 << 7,
    CallbackAlways = 1 << 8,
    CallbackCharFilter = 1 << 9,
    AllowTabInput = 1 << 10,
    CtrlEnterForNewLine = 1 << 11,
    NoHorizontalScroll = 1 << 12,
    AlwaysInsertMode = 1 << 13,
    ReadOnly = 1 << 14,
    Password = 1 << 15,
    NoUndoRedo = 1 << 16,
    CharsScientific = 1 << 17,
    CallbackResize = 1 << 18,
    CallbackEdit = 1 << 19,
    Multiline = 1 << 20,
    NoMarkEdited = 1 << 21,
};

enum class ToolTreeNodeFlags : int32_t {
    None = 0,
    Selected = 1 << 0,
    Framed = 1 << 1,
    AllowItemOverlap = 1 << 2,
    NoTreePushOnOpen = 1 << 3,
    NoAutoOpenOnLog = 1 << 4,
    DefaultOpen = 1 << 5,
    OpenOnDoubleClick = 1 << 6,
    OpenOnArrow = 1 << 7,
    Leaf = 1 << 8,
    Bullet = 1 << 9,
    FramePadding = 1 << 10,
    SpanAvailWidth = 1 << 11,
    SpanFullWidth = 1 << 12,
    NavLeftJumpsBackHere = 1 << 13,
    CollapsingHeader = Framed | NoTreePushOnOpen | NoAutoOpenOnLog,
};

enum class ToolPopupFlags : int32_t {
    None = 0,
    MouseButtonLeft = 0,
    MouseButtonRight = 1,
    MouseButtonMiddle = 2,
    NoOpenOverExistingPopup = 1 << 5,
    NoOpenOverItems = 1 << 6,
    AnyPopupId = 1 << 7,
    AnyPopupLevel = 1 << 8,
    AnyPopup = AnyPopupId | AnyPopupLevel,
};

enum class ToolSelectableFlags : int32_t {
    None = 0,
    DontClosePopups = 1 << 0,
    SpanAllColumns = 1 << 1,
    AllowDoubleClick = 1 << 2,
    Disabled = 1 << 3,
    AllowItemOverlap = 1 << 4,
};

enum class ToolComboFlags : int32_t {
    None = 0,
    PopupAlignLeft = 1 << 0,
    HeightSmall = 1 << 1,
    HeightRegular = 1 << 2,
    HeightLarge = 1 << 3,
    HeightLargest = 1 << 4,
    NoArrowButton = 1 << 5,
    NoPreview = 1 << 6,
};

enum class ToolTabBarFlags : int32_t {
    None = 0,
    Reorderable = 1 << 0,
    AutoSelectNewTabs = 1 << 1,
    TabListPopupButton = 1 << 2,
    NoCloseWithMiddleMouseButton = 1 << 3,
    NoTabListScrollingButtons = 1 << 4,
    NoTooltip = 1 << 5,
    FittingPolicyResizeDown = 1 << 6,
    FittingPolicyScroll = 1 << 7,
};

enum class ToolTabItemFlags : int32_t {
    None = 0,
    UnsavedDocument = 1 << 0,
    SetSelected = 1 << 1,
    NoCloseWithMiddleMouseButton = 1 << 2,
    NoPushId = 1 << 3,
    NoTooltip = 1 << 4,
    NoReorder = 1 << 5,
    Leading = 1 << 6,
    Trailing = 1 << 7,
};

enum class ToolFocusedFlags : int32_t {
    None = 0,
    ChildWindows = 1 << 0,
    RootWindow = 1 << 1,
    AnyWindow = 1 << 2,
    RootAndChildWindows = RootWindow | ChildWindows,
};

enum class ToolHoveredFlags : int32_t {
    None = 0,
    ChildWindows = 1 << 0,
    RootWindow = 1 << 1,
    AnyWindow = 1 << 2,
    AllowWhenBlockedByPopup = 1 << 3,
    AllowWhenBlockedByActiveItem = 1 << 5,
    AllowWhenOverlapped = 1 << 6,
    AllowWhenDisabled = 1 << 7,
    RectOnly = AllowWhenBlockedByPopup | AllowWhenBlockedByActiveItem | AllowWhenOverlapped,
    RootAndChildWindows = RootWindow | ChildWindows,
};

enum class ToolDockNodeFlags : int32_t {
    None = 0,
    KeepAliveOnly = 1 << 0,
    NoDockingInCentralNode = 1 << 2,
    PassthruCentralNode = 1 << 3,
    NoSplit = 1 << 4,
    NoResize = 1 << 5,
    AutoHideTabBar = 1 << 6,
};

enum class ToolDragDropFlags : int32_t {
    None = 0,
    SourceNoPreviewTooltip = 1 << 0,
    SourceNoDisableHover = 1 << 1,
    SourceNoHoldToOpenOthers = 1 << 2,
    SourceAllowNullID = 1 << 3,
    SourceExtern = 1 << 4,
    SourceAutoExpirePayload = 1 << 5,
    AcceptBeforeDelivery = 1 << 10,
    AcceptNoDrawDefaultRect = 1 << 11,
    AcceptNoPreviewTooltip = 1 << 12,
    AcceptPeekOnly = AcceptBeforeDelivery | AcceptNoDrawDefaultRect,
};

enum class ToolDataType : int32_t {
    S8,
    U8,
    S16,
    U16,
    S32,
    U32,
    S64,
    U64,
    Float,
    Double,
    COUNT,
};

enum class ToolDir : int32_t {
    None = - 1,
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3,
    COUNT,
};

enum class ToolKey : int32_t {
    Tab,
    LeftArrow,
    RightArrow,
    UpArrow,
    DownArrow,
    PageUp,
    PageDown,
    Home,
    End,
    Insert,
    Delete,
    Backspace,
    Space,
    Enter,
    Escape,
    KeyPadEnter,
    A,
    C,
    V,
    X,
    Y,
    Z,
    COUNT,
};

enum class ToolKeyModFlags : int32_t {
    None = 0,
    Ctrl = 1 << 0,
    Shift = 1 << 1,
    Alt = 1 << 2,
    Super = 1 << 3,
};

enum class ToolNavInput : int32_t {
    Activate,
    Cancel,
    Input,
    Menu,
    DpadLeft,
    DpadRight,
    DpadUp,
    DpadDown,
    LStickLeft,
    LStickRight,
    LStickUp,
    LStickDown,
    FocusPrev,
    FocusNext,
    TweakSlow,
    TweakFast,
    COUNT,
};

enum class ToolConfigFlags : int32_t {
    None = 0,
    NavEnableKeyboard = 1 << 0,
    NavEnableGamepad = 1 << 1,
    NavEnableSetMousePos = 1 << 2,
    NavNoCaptureKeyboard = 1 << 3,
    NoMouse = 1 << 4,
    NoMouseCursorChange = 1 << 5,
    DockingEnable = 1 << 6,
    ViewportsEnable = 1 << 10,
    DpiEnableScaleViewports = 1 << 14,
    DpiEnableScaleFonts = 1 << 15,
    IsSRGB = 1 << 20,
    IsTouchScreen = 1 << 21,
};

enum class ToolBackendFlags : int32_t {
    None = 0,
    HasGamepad = 1 << 0,
    HasMouseCursors = 1 << 1,
    HasSetMousePos = 1 << 2,
    RendererHasVtxOffset = 1 << 3,
    PlatformHasViewports = 1 << 10,
    HasMouseHoveredViewport = 1 << 11,
    RendererHasViewports = 1 << 12,
};

enum class ToolCol : int32_t {
    Text,
    TextDisabled,
    WindowBg,
    ChildBg,
    PopupBg,
    Border,
    BorderShadow,
    FrameBg,
    FrameBgHovered,
    FrameBgActive,
    TitleBg,
    TitleBgActive,
    TitleBgCollapsed,
    MenuBarBg,
    ScrollbarBg,
    ScrollbarGrab,
    ScrollbarGrabHovered,
    ScrollbarGrabActive,
    CheckMark,
    SliderGrab,
    SliderGrabActive,
    Button,
    ButtonHovered,
    ButtonActive,
    Header,
    HeaderHovered,
    HeaderActive,
    Separator,
    SeparatorHovered,
    SeparatorActive,
    ResizeGrip,
    ResizeGripHovered,
    ResizeGripActive,
    Tab,
    TabHovered,
    TabActive,
    TabUnfocused,
    TabUnfocusedActive,
    DockingPreview,
    DockingEmptyBg,
    PlotLines,
    PlotLinesHovered,
    PlotHistogram,
    PlotHistogramHovered,
    TextSelectedBg,
    DragDropTarget,
    NavHighlight,
    NavWindowingHighlight,
    NavWindowingDimBg,
    ModalWindowDimBg,
    COUNT,
};

enum class ToolStyleVar : int32_t {
    Alpha,
    WindowPadding,
    WindowRounding,
    WindowBorderSize,
    WindowMinSize,
    WindowTitleAlign,
    ChildRounding,
    ChildBorderSize,
    PopupRounding,
    PopupBorderSize,
    FramePadding,
    FrameRounding,
    FrameBorderSize,
    ItemSpacing,
    ItemInnerSpacing,
    IndentSpacing,
    ScrollbarSize,
    ScrollbarRounding,
    GrabMinSize,
    GrabRounding,
    TabRounding,
    ButtonTextAlign,
    SelectableTextAlign,
    COUNT,
};

enum class ToolButtonFlags : int32_t {
    None = 0,
    MouseButtonLeft = 1 << 0,
    MouseButtonRight = 1 << 1,
    MouseButtonMiddle = 1 << 2,
};

enum class ToolColorEditFlags : int32_t {
    None = 0,
    NoAlpha = 1 << 1,
    NoPicker = 1 << 2,
    NoOptions = 1 << 3,
    NoSmallPreview = 1 << 4,
    NoInputs = 1 << 5,
    NoTooltip = 1 << 6,
    NoLabel = 1 << 7,
    NoSidePreview = 1 << 8,
    NoDragDrop = 1 << 9,
    NoBorder = 1 << 10,
    AlphaBar = 1 << 16,
    AlphaPreview = 1 << 17,
    AlphaPreviewHalf = 1 << 18,
    HDR = 1 << 19,
    DisplayRGB = 1 << 20,
    DisplayHSV = 1 << 21,
    DisplayHex = 1 << 22,
    Uint8 = 1 << 23,
    Float = 1 << 24,
    PickerHueBar = 1 << 25,
    PickerHueWheel = 1 << 26,
    InputRGB = 1 << 27,
    InputHSV = 1 << 28,
    OptionsDefault = Uint8 | DisplayRGB | InputRGB | PickerHueBar,
    DisplayMask = DisplayRGB | DisplayHSV | DisplayHex,
    DataTypeMask = Uint8 | Float,
    PickerMask = PickerHueWheel | PickerHueBar,
    InputMask = InputRGB | InputHSV,
};

enum class ToolSliderFlags : int32_t {
    None = 0,
    AlwaysClamp = 1 << 4,
    Logarithmic = 1 << 5,
    NoRoundToFormat = 1 << 6,
    NoInput = 1 << 7,
};

enum class ToolMouseButton : int32_t {
    Left = 0,
    Right = 1,
    Middle = 2,
    COUNT = 5,
};

enum class ToolMouseCursor : int32_t {
    None = - 1,
    Arrow = 0,
    TextInput,
    ResizeAll,
    ResizeNS,
    ResizeEW,
    ResizeNESW,
    ResizeNWSE,
    Hand,
    NotAllowed,
    COUNT,
};

enum class ToolCond : int32_t {
    None = 0,
    Always = 1 << 0,
    Once = 1 << 1,
    FirstUseEver = 1 << 2,
    Appearing = 1 << 3,
};

enum class ToolDrawCornerFlags : int32_t {
    None = 0,
    TopLeft = 1 << 0,
    TopRight = 1 << 1,
    BotLeft = 1 << 2,
    BotRight = 1 << 3,
    Top = TopLeft | TopRight,
    Bot = BotLeft | BotRight,
    Left = TopLeft | BotLeft,
    Right = TopRight | BotRight,
    All = 0xF,
};

enum class ToolDrawListFlags : int32_t {
    None = 0,
    AntiAliasedLines = 1 << 0,
    AntiAliasedLinesUseTex = 1 << 1,
    AntiAliasedFill = 1 << 2,
    AllowVtxOffset = 1 << 3,
};

enum class ToolFontAtlasFlags : int32_t {
    None = 0,
    NoPowerOfTwoHeight = 1 << 0,
    NoMouseCursors = 1 << 1,
    NoBakedLines = 1 << 2,
};

enum class ToolViewportFlags : int32_t {
    None = 0,
    NoDecoration = 1 << 0,
    NoTaskBarIcon = 1 << 1,
    NoFocusOnAppearing = 1 << 2,
    NoFocusOnClick = 1 << 3,
    NoInputs = 1 << 4,
    NoRendererClear = 1 << 5,
    TopMost = 1 << 6,
    Minimized = 1 << 7,
    NoAutoMerge = 1 << 8,
    CanHostOtherWindows = 1 << 9,
};

class Tool : public BaseObject {
private:
    static std::shared_ptr<Tool> instance_;
    std::shared_ptr<ImguiPlatform> platform_;

    //! to hold graphics device
    std::shared_ptr<Graphics> graphics_;

    ToolUsage toolUsageMode_ = ToolUsage::Overwrapped;

    std::mutex terminatingMtx_;

    std::string iniFilename_;

    void Dispose();

public:
    static std::shared_ptr<Tool>& GetInstance();

#if !USE_CBG

    static bool Initialize(std::shared_ptr<Graphics> graphics, const char16_t* iniFilename);

    static void Terminate();

    Tool(std::shared_ptr<Graphics> graphics, const char16_t* iniFilename);

    virtual ~Tool();

    void OnTerminating() override;
#endif

    ToolUsage GetToolUsage() const;

    void SetToolUsage(ToolUsage toolUsage);

    void NewFrame();

    void Render();

    bool AddFontFromFileTTF(const char16_t* path, float sizePixels, ToolGlyphRange ranges);

    bool ListBox(const char16_t* label, int32_t* current, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items = -1);

    const char16_t* InputText(const char16_t* label, const char16_t* input, int32_t max_length, ToolInputTextFlags flags = ToolInputTextFlags::None);

    const char16_t* InputTextWithHint(
            const char16_t* label,
            const char16_t* hint,
            const char16_t* input,
            int32_t max_length,
            ToolInputTextFlags flags = ToolInputTextFlags::None);

    const char16_t* InputTextMultiline(
            const char16_t* label, const char16_t* input, int32_t max_length, Vector2F size, ToolInputTextFlags flags = ToolInputTextFlags::None);

    bool ColorEdit3(const char16_t* label, Color* color, ToolColorEditFlags flags = ToolColorEditFlags::None);

    bool ColorEdit4(const char16_t* label, Color* color, ToolColorEditFlags flags = ToolColorEditFlags::None);

    void Image(
            std::shared_ptr<TextureBase> texture,
            Vector2F size,
            Vector2F uv0 = Vector2F(0, 0),
            Vector2F uv1 = Vector2F(1, 1),
            Color tint_col = Color(255, 255, 255, 255),
            Color border_col = Color(0, 0, 0, 0));

    bool ImageButton(
            std::shared_ptr<TextureBase> texture,
            Vector2F size,
            Vector2F uv0 = Vector2F(0, 0),
            Vector2F uv1 = Vector2F(1, 1),
            int32_t frame_padding = -1,
            Color bg_col = Color(0, 0, 0, 0),
            Color tint_col = Color(255, 255, 255, 255));

    bool Combo(
            const char16_t* label, int32_t* current_item, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items = -1);

    bool ColorButton(const char16_t* desc_id, Color* col, ToolColorEditFlags flags = ToolColorEditFlags::None, Vector2F size = Vector2F(0, 0));

    void PlotLines(
            const char16_t* label,
            std::shared_ptr<FloatArray> values,
            int32_t values_count,
            int32_t values_offset = 0,
            const char16_t* overlay_text = NULL,
            float scale_min = FLT_MAX,
            float scale_max = FLT_MAX,
            Vector2F graph_size = Vector2F(0, 0),
            int32_t stride = sizeof(float));

    void PlotHistogram(
            const char16_t* label,
            std::shared_ptr<FloatArray> values,
            int32_t values_count,
            int32_t values_offset = 0,
            const char16_t* overlay_text = NULL,
            float scale_min = FLT_MAX,
            float scale_max = FLT_MAX,
            Vector2F graph_size = Vector2F(0, 0),
            int32_t stride = sizeof(float));

    float GetTime();

    int32_t GetMainViewportID();

    Vector2F GetMainViewportPos();

    Vector2F GetMainViewportSize();

    Vector2F GetMainViewportWorkPos();
    
    Vector2F GetMainViewportWorkSize();

    void DockSpace(int32_t id, Vector2F size, ToolDockNodeFlags flags);

    bool BeginDockHost(const char16_t* label, Vector2F offset);

    void ShowDemoWindowNoCloseButton();

    void ShowAboutWindowNoCloseButton();

    void ShowMetricsWindowNoCloseButton();

    bool Begin(const char16_t* name, ToolWindowFlags flags = (ToolWindowFlags)0);

    bool BeginPopupModal(const char16_t* name, ToolWindowFlags flags = (ToolWindowFlags)0);

    bool BeginTabItem(const char16_t* label, ToolTabItemFlags flags = (ToolTabItemFlags)0);

    const char16_t* OpenDialog(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* OpenDialogMultiple(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* SaveDialog(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* PickFolder(const char16_t* defaultPath);

    bool SetDragDropPayload(const char16_t* type, std::shared_ptr<Int8Array> data, ToolCond cond);

    bool AcceptDragDropPayload(const char16_t* type, ToolDragDropFlags dragDropFlags, std::shared_ptr<Int8Array> result);
    // ImGuiContext *(ImFontAtlas *) CreateContext

    // void (ImGuiContext *) DestroyContext

    // ImGuiContext *() GetCurrentContext

    // void (ImGuiContext *) SetCurrentContext

    // ImGuiIO &() GetIO

    // ImGuiStyle &() GetStyle

    // ImDrawData *() GetDrawData

    void ShowDemoWindow(bool* p_open = NULL);

    void ShowAboutWindow(bool* p_open = NULL);

    void ShowMetricsWindow(bool* p_open = NULL);

    // void (ImGuiStyle *) ShowStyleEditor

    bool ShowStyleSelector(const char16_t* label);

    void ShowFontSelector(const char16_t* label);

    void ShowUserGuide();

    const char16_t* GetVersion();

    // void (ImGuiStyle *) StyleColorsDark

    // void (ImGuiStyle *) StyleColorsClassic

    // void (ImGuiStyle *) StyleColorsLight

    bool Begin(const char16_t* name, bool* p_open = NULL, ToolWindowFlags flags = (ToolWindowFlags)0);

    void End();

    bool BeginChild(const char16_t* str_id, Vector2F size = Vector2F ( 0 , 0 ), bool border = false, ToolWindowFlags flags = (ToolWindowFlags)0);

    bool BeginChild(uint32_t id, Vector2F size = Vector2F ( 0 , 0 ), bool border = false, ToolWindowFlags flags = (ToolWindowFlags)0);

    void EndChild();

    bool IsWindowAppearing();

    bool IsWindowCollapsed();

    bool IsWindowFocused(ToolFocusedFlags flags = (ToolFocusedFlags)0);

    bool IsWindowHovered(ToolHoveredFlags flags = (ToolHoveredFlags)0);

    // ImDrawList *() GetWindowDrawList

    float GetWindowDpiScale();

    // ImGuiViewport *() GetWindowViewport

    Vector2F GetWindowPos();

    Vector2F GetWindowSize();

    float GetWindowWidth();

    float GetWindowHeight();

    void SetNextWindowPos(Vector2F pos, ToolCond cond = (ToolCond)0, Vector2F pivot = Vector2F ( 0 , 0 ));

    void SetNextWindowSize(Vector2F size, ToolCond cond = (ToolCond)0);

    // void (const ImVec2 &, const ImVec2 &, ImGuiSizeCallback, void *) SetNextWindowSizeConstraints

    void SetNextWindowContentSize(Vector2F size);

    void SetNextWindowCollapsed(bool collapsed, ToolCond cond = (ToolCond)0);

    void SetNextWindowFocus();

    void SetNextWindowBgAlpha(float alpha);

    void SetNextWindowViewport(uint32_t viewport_id);

    void SetWindowPos(Vector2F pos, ToolCond cond = (ToolCond)0);

    void SetWindowSize(Vector2F size, ToolCond cond = (ToolCond)0);

    void SetWindowCollapsed(bool collapsed, ToolCond cond = (ToolCond)0);

    void SetWindowFocus();

    void SetWindowFontScale(float scale);

    void SetWindowPos(const char16_t* name, Vector2F pos, ToolCond cond = (ToolCond)0);

    void SetWindowSize(const char16_t* name, Vector2F size, ToolCond cond = (ToolCond)0);

    void SetWindowCollapsed(const char16_t* name, bool collapsed, ToolCond cond = (ToolCond)0);

    void SetWindowFocus(const char16_t* name);

    Vector2F GetContentRegionMax();

    Vector2F GetContentRegionAvail();

    Vector2F GetWindowContentRegionMin();

    Vector2F GetWindowContentRegionMax();

    float GetWindowContentRegionWidth();

    float GetScrollX();

    float GetScrollY();

    float GetScrollMaxX();

    float GetScrollMaxY();

    void SetScrollX(float scroll_x);

    void SetScrollY(float scroll_y);

    void SetScrollHereX(float center_x_ratio = 0.5f);

    void SetScrollHereY(float center_y_ratio = 0.5f);

    void SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);

    void SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);

    // void (ImFont *) PushFont

    void PopFont();

    void PushStyleColor(ToolCol idx, uint32_t col);

    void PushStyleColor(ToolCol idx, Vector4F col);

    void PopStyleColor(int32_t count = 1);

    void PushStyleVar(ToolStyleVar idx, float val);

    void PushStyleVar(ToolStyleVar idx, Vector2F val);

    void PopStyleVar(int32_t count = 1);

    // const ImVec4 &(ImGuiCol) GetStyleColorVec4

    // ImFont *() GetFont

    float GetFontSize();

    Vector2F GetFontTexUvWhitePixel();

    uint32_t GetColorU32(ToolCol idx, float alpha_mul = 1.0f);

    uint32_t GetColorU32(Vector4F col);

    uint32_t GetColorU32(uint32_t col);

    void PushItemWidth(float item_width);

    void PopItemWidth();

    void SetNextItemWidth(float item_width);

    float CalcItemWidth();

    void PushTextWrapPos(float wrap_local_pos_x = 0.0f);

    void PopTextWrapPos();

    void PushAllowKeyboardFocus(bool allow_keyboard_focus);

    void PopAllowKeyboardFocus();

    void PushButtonRepeat(bool repeat);

    void PopButtonRepeat();

    void Separator();

    void SameLine(float offset_from_start_x = 0.0f, float spacing = - 1.0f);

    void NewLine();

    void Spacing();

    void Dummy(Vector2F size);

    void Indent(float indent_w = 0.0f);

    void Unindent(float indent_w = 0.0f);

    void BeginGroup();

    void EndGroup();

    Vector2F GetCursorPos();

    float GetCursorPosX();

    float GetCursorPosY();

    void SetCursorPos(Vector2F local_pos);

    void SetCursorPosX(float local_x);

    void SetCursorPosY(float local_y);

    Vector2F GetCursorStartPos();

    Vector2F GetCursorScreenPos();

    void SetCursorScreenPos(Vector2F pos);

    void AlignTextToFramePadding();

    float GetTextLineHeight();

    float GetTextLineHeightWithSpacing();

    float GetFrameHeight();

    float GetFrameHeightWithSpacing();

    void PushID(const char16_t* str_id);

    void PushID(const char16_t* str_id_begin, const char16_t* str_id_end);

    // void (const void *) PushID

    void PushID(int32_t int_id);

    void PopID();

    uint32_t GetID(const char16_t* str_id);

    uint32_t GetID(const char16_t* str_id_begin, const char16_t* str_id_end);

    // ImGuiID (const void *) GetID

    void TextUnformatted(const char16_t* text, const char16_t* text_end = NULL);

    void Text(const char16_t* fmt);

    // void (const char *, __va_list_tag *) TextV

    void TextColored(Vector4F col, const char16_t* fmt);

    // void (const ImVec4 &, const char *, __va_list_tag *) TextColoredV

    void TextDisabled(const char16_t* fmt);

    // void (const char *, __va_list_tag *) TextDisabledV

    void TextWrapped(const char16_t* fmt);

    // void (const char *, __va_list_tag *) TextWrappedV

    void LabelText(const char16_t* label, const char16_t* fmt);

    // void (const char *, const char *, __va_list_tag *) LabelTextV

    void BulletText(const char16_t* fmt);

    // void (const char *, __va_list_tag *) BulletTextV

    bool Button(const char16_t* label, Vector2F size = Vector2F ( 0 , 0 ));

    bool SmallButton(const char16_t* label);

    bool InvisibleButton(const char16_t* str_id, Vector2F size, ToolButtonFlags flags = (ToolButtonFlags)0);

    bool ArrowButton(const char16_t* str_id, ToolDir dir);

    // void (ImTextureID, const ImVec2 &, const ImVec2 &, const ImVec2 &, const ImVec4 &, const ImVec4 &) Image

    // bool (ImTextureID, const ImVec2 &, const ImVec2 &, const ImVec2 &, int, const ImVec4 &, const ImVec4 &) ImageButton

    bool Checkbox(const char16_t* label, bool* v);

    // bool (const char *, unsigned int *, unsigned int) CheckboxFlags

    bool RadioButton(const char16_t* label, bool active);

    bool RadioButton(const char16_t* label, int32_t* v, int32_t v_button);

    void ProgressBar(float fraction, Vector2F size_arg = Vector2F ( - 1 , 0 ), const char16_t* overlay = NULL);

    void Bullet();

    bool BeginCombo(const char16_t* label, const char16_t* preview_value, ToolComboFlags flags = (ToolComboFlags)0);

    void EndCombo();

    bool DragFloat(const char16_t* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragFloat2(const char16_t* label, std::shared_ptr<FloatArray> v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragFloat3(const char16_t* label, std::shared_ptr<FloatArray> v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragFloat4(const char16_t* label, std::shared_ptr<FloatArray> v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragFloatRange2(const char16_t* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char16_t* format = u"%.3f", const char16_t* format_max = NULL, ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragInt(const char16_t* label, int32_t* v, float v_speed = 1.0f, int32_t v_min = 0, int32_t v_max = 0, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragInt2(const char16_t* label, std::shared_ptr<Int32Array> v, float v_speed = 1.0f, int32_t v_min = 0, int32_t v_max = 0, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragInt3(const char16_t* label, std::shared_ptr<Int32Array> v, float v_speed = 1.0f, int32_t v_min = 0, int32_t v_max = 0, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragInt4(const char16_t* label, std::shared_ptr<Int32Array> v, float v_speed = 1.0f, int32_t v_min = 0, int32_t v_max = 0, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool DragIntRange2(const char16_t* label, int32_t* v_current_min, int32_t* v_current_max, float v_speed = 1.0f, int32_t v_min = 0, int32_t v_max = 0, const char16_t* format = u"%d", const char16_t* format_max = NULL, ToolSliderFlags flags = (ToolSliderFlags)0);

    // bool (const char *, ImGuiDataType, void *, float, const void *, const void *, const char *, ImGuiSliderFlags) DragScalar

    // bool (const char *, ImGuiDataType, void *, int, float, const void *, const void *, const char *, ImGuiSliderFlags) DragScalarN

    bool SliderFloat(const char16_t* label, float* v, float v_min, float v_max, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool SliderFloat2(const char16_t* label, std::shared_ptr<FloatArray> v, float v_min, float v_max, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool SliderFloat3(const char16_t* label, std::shared_ptr<FloatArray> v, float v_min, float v_max, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool SliderFloat4(const char16_t* label, std::shared_ptr<FloatArray> v, float v_min, float v_max, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool SliderAngle(const char16_t* label, float* v_rad, float v_degrees_min = - 360.0f, float v_degrees_max = + 360.0f, const char16_t* format = u"%.0f deg", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool SliderInt(const char16_t* label, int32_t* v, int32_t v_min, int32_t v_max, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool SliderInt2(const char16_t* label, std::shared_ptr<Int32Array> v, int32_t v_min, int32_t v_max, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool SliderInt3(const char16_t* label, std::shared_ptr<Int32Array> v, int32_t v_min, int32_t v_max, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool SliderInt4(const char16_t* label, std::shared_ptr<Int32Array> v, int32_t v_min, int32_t v_max, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    // bool (const char *, ImGuiDataType, void *, const void *, const void *, const char *, ImGuiSliderFlags) SliderScalar

    // bool (const char *, ImGuiDataType, void *, int, const void *, const void *, const char *, ImGuiSliderFlags) SliderScalarN

    bool VSliderFloat(const char16_t* label, Vector2F size, float* v, float v_min, float v_max, const char16_t* format = u"%.3f", ToolSliderFlags flags = (ToolSliderFlags)0);

    bool VSliderInt(const char16_t* label, Vector2F size, int32_t* v, int32_t v_min, int32_t v_max, const char16_t* format = u"%d", ToolSliderFlags flags = (ToolSliderFlags)0);

    // bool (const char *, const ImVec2 &, ImGuiDataType, void *, const void *, const void *, const char *, ImGuiSliderFlags) VSliderScalar

    // bool (const char *, char *, size_t, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputText

    // bool (const char *, char *, size_t, const ImVec2 &, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputTextMultiline

    // bool (const char *, const char *, char *, size_t, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputTextWithHint

    bool InputFloat(const char16_t* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char16_t* format = u"%.3f", ToolInputTextFlags flags = (ToolInputTextFlags)0);

    bool InputFloat2(const char16_t* label, std::shared_ptr<FloatArray> v, const char16_t* format = u"%.3f", ToolInputTextFlags flags = (ToolInputTextFlags)0);

    bool InputFloat3(const char16_t* label, std::shared_ptr<FloatArray> v, const char16_t* format = u"%.3f", ToolInputTextFlags flags = (ToolInputTextFlags)0);

    bool InputFloat4(const char16_t* label, std::shared_ptr<FloatArray> v, const char16_t* format = u"%.3f", ToolInputTextFlags flags = (ToolInputTextFlags)0);

    bool InputInt(const char16_t* label, int32_t* v, int32_t step = 1, int32_t step_fast = 100, ToolInputTextFlags flags = (ToolInputTextFlags)0);

    bool InputInt2(const char16_t* label, std::shared_ptr<Int32Array> v, ToolInputTextFlags flags = (ToolInputTextFlags)0);

    bool InputInt3(const char16_t* label, std::shared_ptr<Int32Array> v, ToolInputTextFlags flags = (ToolInputTextFlags)0);

    bool InputInt4(const char16_t* label, std::shared_ptr<Int32Array> v, ToolInputTextFlags flags = (ToolInputTextFlags)0);

    // bool (const char *, double *, double, double, const char *, ImGuiInputTextFlags) InputDouble

    // bool (const char *, ImGuiDataType, void *, const void *, const void *, const char *, ImGuiInputTextFlags) InputScalar

    // bool (const char *, ImGuiDataType, void *, int, const void *, const void *, const char *, ImGuiInputTextFlags) InputScalarN

    bool ColorEdit3(const char16_t* label, std::shared_ptr<FloatArray> col, ToolColorEditFlags flags = (ToolColorEditFlags)0);

    bool ColorEdit4(const char16_t* label, std::shared_ptr<FloatArray> col, ToolColorEditFlags flags = (ToolColorEditFlags)0);

    bool ColorPicker3(const char16_t* label, std::shared_ptr<FloatArray> col, ToolColorEditFlags flags = (ToolColorEditFlags)0);

    bool ColorPicker4(const char16_t* label, std::shared_ptr<FloatArray> col, ToolColorEditFlags flags = (ToolColorEditFlags)0, float* ref_col = NULL);

    // bool (const char *, const ImVec4 &, ImGuiColorEditFlags, ImVec2) ColorButton

    void SetColorEditOptions(ToolColorEditFlags flags);

    bool TreeNode(const char16_t* label);

    bool TreeNode(const char16_t* str_id, const char16_t* fmt);

    // bool (const void *, const char *, ...) TreeNode

    // bool (const char *, const char *, __va_list_tag *) TreeNodeV

    // bool (const void *, const char *, __va_list_tag *) TreeNodeV

    bool TreeNodeEx(const char16_t* label, ToolTreeNodeFlags flags = (ToolTreeNodeFlags)0);

    bool TreeNodeEx(const char16_t* str_id, ToolTreeNodeFlags flags, const char16_t* fmt);

    // bool (const void *, ImGuiTreeNodeFlags, const char *, ...) TreeNodeEx

    // bool (const char *, ImGuiTreeNodeFlags, const char *, __va_list_tag *) TreeNodeExV

    // bool (const void *, ImGuiTreeNodeFlags, const char *, __va_list_tag *) TreeNodeExV

    void TreePush(const char16_t* str_id);

    // void (const void *) TreePush

    void TreePop();

    float GetTreeNodeToLabelSpacing();

    bool CollapsingHeader(const char16_t* label, ToolTreeNodeFlags flags = (ToolTreeNodeFlags)0);

    bool CollapsingHeader(const char16_t* label, bool* p_open, ToolTreeNodeFlags flags = (ToolTreeNodeFlags)0);

    void SetNextItemOpen(bool is_open, ToolCond cond = (ToolCond)0);

    bool Selectable(const char16_t* label, bool selected = false, ToolSelectableFlags flags = (ToolSelectableFlags)0, Vector2F size = Vector2F ( 0 , 0 ));

    bool Selectable(const char16_t* label, bool* p_selected, ToolSelectableFlags flags = (ToolSelectableFlags)0, Vector2F size = Vector2F ( 0 , 0 ));

    // bool (const char *, int *, const char *const *, int, int) ListBox

    // bool (const char *, int *, bool (*)(void *, int, const char **), void *, int, int) ListBox

    bool ListBoxHeader(const char16_t* label, Vector2F size = Vector2F ( 0 , 0 ));

    bool ListBoxHeader(const char16_t* label, int32_t items_count, int32_t height_in_items = - 1);

    void ListBoxFooter();

    // void (const char *, const float *, int, int, const char *, float, float, ImVec2, int) PlotLines

    // void (const char *, float (*)(void *, int), void *, int, int, const char *, float, float, ImVec2) PlotLines

    // void (const char *, const float *, int, int, const char *, float, float, ImVec2, int) PlotHistogram

    // void (const char *, float (*)(void *, int), void *, int, int, const char *, float, float, ImVec2) PlotHistogram

    void Value(const char16_t* prefix, bool b);

    void Value(const char16_t* prefix, int32_t v);

    // void (const char *, unsigned int) Value

    void Value(const char16_t* prefix, float v, const char16_t* float_format = NULL);

    bool BeginMenuBar();

    void EndMenuBar();

    bool BeginMainMenuBar();

    void EndMainMenuBar();

    bool BeginMenu(const char16_t* label, bool enabled = true);

    void EndMenu();

    bool MenuItem(const char16_t* label, const char16_t* shortcut = NULL, bool selected = false, bool enabled = true);

    bool MenuItem(const char16_t* label, const char16_t* shortcut, bool* p_selected, bool enabled = true);

    void BeginTooltip();

    void EndTooltip();

    void SetTooltip(const char16_t* fmt);

    // void (const char *, __va_list_tag *) SetTooltipV

    bool BeginPopup(const char16_t* str_id, ToolWindowFlags flags = (ToolWindowFlags)0);

    bool BeginPopupModal(const char16_t* name, bool* p_open = NULL, ToolWindowFlags flags = (ToolWindowFlags)0);

    void EndPopup();

    void OpenPopup(const char16_t* str_id, ToolPopupFlags popup_flags = (ToolPopupFlags)0);

    void OpenPopupOnItemClick(const char16_t* str_id = NULL, ToolPopupFlags popup_flags = (ToolPopupFlags)1);

    void CloseCurrentPopup();

    bool BeginPopupContextItem(const char16_t* str_id = NULL, ToolPopupFlags popup_flags = (ToolPopupFlags)1);

    bool BeginPopupContextWindow(const char16_t* str_id = NULL, ToolPopupFlags popup_flags = (ToolPopupFlags)1);

    bool BeginPopupContextVoid(const char16_t* str_id = NULL, ToolPopupFlags popup_flags = (ToolPopupFlags)1);

    bool IsPopupOpen(const char16_t* str_id, ToolPopupFlags flags = (ToolPopupFlags)0);

    void Columns(int32_t count = 1, const char16_t* id = NULL, bool border = true);

    void NextColumn();

    int32_t GetColumnIndex();

    float GetColumnWidth(int32_t column_index = - 1);

    void SetColumnWidth(int32_t column_index, float width);

    float GetColumnOffset(int32_t column_index = - 1);

    void SetColumnOffset(int32_t column_index, float offset_x);

    int32_t GetColumnsCount();

    bool BeginTabBar(const char16_t* str_id, ToolTabBarFlags flags = (ToolTabBarFlags)0);

    void EndTabBar();

    bool BeginTabItem(const char16_t* label, bool* p_open = NULL, ToolTabItemFlags flags = (ToolTabItemFlags)0);

    void EndTabItem();

    bool TabItemButton(const char16_t* label, ToolTabItemFlags flags = (ToolTabItemFlags)0);

    void SetTabItemClosed(const char16_t* tab_or_docked_window_label);

    // void (ImGuiID, const ImVec2 &, ImGuiDockNodeFlags, const ImGuiWindowClass *) DockSpace

    // ImGuiID (ImGuiViewport *, ImGuiDockNodeFlags, const ImGuiWindowClass *) DockSpaceOverViewport

    void SetNextWindowDockID(uint32_t dock_id, ToolCond cond = (ToolCond)0);

    // void (const ImGuiWindowClass *) SetNextWindowClass

    uint32_t GetWindowDockID();

    bool IsWindowDocked();

    void LogToTTY(int32_t auto_open_depth = - 1);

    void LogToFile(int32_t auto_open_depth = - 1, const char16_t* filename = NULL);

    void LogToClipboard(int32_t auto_open_depth = - 1);

    void LogFinish();

    void LogButtons();

    void LogText(const char16_t* fmt);

    bool BeginDragDropSource(ToolDragDropFlags flags = (ToolDragDropFlags)0);

    // bool (const char *, const void *, size_t, ImGuiCond) SetDragDropPayload

    void EndDragDropSource();

    bool BeginDragDropTarget();

    // const ImGuiPayload *(const char *, ImGuiDragDropFlags) AcceptDragDropPayload

    void EndDragDropTarget();

    // const ImGuiPayload *() GetDragDropPayload

    void PushClipRect(Vector2F clip_rect_min, Vector2F clip_rect_max, bool intersect_with_current_clip_rect);

    void PopClipRect();

    void SetItemDefaultFocus();

    void SetKeyboardFocusHere(int32_t offset = 0);

    bool IsItemHovered(ToolHoveredFlags flags = (ToolHoveredFlags)0);

    bool IsItemActive();

    bool IsItemFocused();

    bool IsItemClicked(ToolMouseButton mouse_button = (ToolMouseButton)0);

    bool IsItemVisible();

    bool IsItemEdited();

    bool IsItemActivated();

    bool IsItemDeactivated();

    bool IsItemDeactivatedAfterEdit();

    bool IsItemToggledOpen();

    bool IsAnyItemHovered();

    bool IsAnyItemActive();

    bool IsAnyItemFocused();

    Vector2F GetItemRectMin();

    Vector2F GetItemRectMax();

    Vector2F GetItemRectSize();

    void SetItemAllowOverlap();

    bool IsRectVisible(Vector2F size);

    bool IsRectVisible(Vector2F rect_min, Vector2F rect_max);

    // double () GetTime

    int32_t GetFrameCount();

    // ImDrawList *() GetBackgroundDrawList

    // ImDrawList *() GetForegroundDrawList

    // ImDrawList *(ImGuiViewport *) GetBackgroundDrawList

    // ImDrawList *(ImGuiViewport *) GetForegroundDrawList

    // ImDrawListSharedData *() GetDrawListSharedData

    const char16_t* GetStyleColorName(ToolCol idx);

    // void (ImGuiStorage *) SetStateStorage

    // ImGuiStorage *() GetStateStorage

    void CalcListClipping(int32_t items_count, float items_height, int32_t* out_items_display_start, int32_t* out_items_display_end);

    bool BeginChildFrame(uint32_t id, Vector2F size, ToolWindowFlags flags = (ToolWindowFlags)0);

    void EndChildFrame();

    Vector2F CalcTextSize(const char16_t* text, const char16_t* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = - 1.0f);

    Vector4F ColorConvertU32ToFloat4(uint32_t in);

    uint32_t ColorConvertFloat4ToU32(Vector4F in);

    // void (float, float, float, float &, float &, float &) ColorConvertRGBtoHSV

    // void (float, float, float, float &, float &, float &) ColorConvertHSVtoRGB

    int32_t GetKeyIndex(ToolKey imgui_key);

    bool IsKeyDown(int32_t user_key_index);

    bool IsKeyPressed(int32_t user_key_index, bool repeat = true);

    bool IsKeyReleased(int32_t user_key_index);

    int32_t GetKeyPressedAmount(int32_t key_index, float repeat_delay, float rate);

    void CaptureKeyboardFromApp(bool want_capture_keyboard_value = true);

    bool IsMouseDown(ToolMouseButton button);

    bool IsMouseClicked(ToolMouseButton button, bool repeat = false);

    bool IsMouseReleased(ToolMouseButton button);

    bool IsMouseDoubleClicked(ToolMouseButton button);

    bool IsMouseHoveringRect(Vector2F r_min, Vector2F r_max, bool clip = true);

    // bool (const ImVec2 *) IsMousePosValid

    bool IsAnyMouseDown();

    Vector2F GetMousePos();

    Vector2F GetMousePosOnOpeningCurrentPopup();

    bool IsMouseDragging(ToolMouseButton button, float lock_threshold = - 1.0f);

    Vector2F GetMouseDragDelta(ToolMouseButton button = (ToolMouseButton)0, float lock_threshold = - 1.0f);

    void ResetMouseDragDelta(ToolMouseButton button = (ToolMouseButton)0);

    // ImGuiMouseCursor () GetMouseCursor

    void SetMouseCursor(ToolMouseCursor cursor_type);

    void CaptureMouseFromApp(bool want_capture_mouse_value = true);

    const char16_t* GetClipboardText();

    void SetClipboardText(const char16_t* text);

    void LoadIniSettingsFromDisk(const char16_t* ini_filename);

    // void (const char *, size_t) LoadIniSettingsFromMemory

    void SaveIniSettingsToDisk(const char16_t* ini_filename);

    // const char *(size_t *) SaveIniSettingsToMemory

    // bool (const char *, size_t, size_t, size_t, size_t, size_t, size_t) DebugCheckVersionAndDataLayout

    // void (void *(*)(size_t, void *), void (*)(void *, void *), void *) SetAllocatorFunctions

    // void *(size_t) MemAlloc

    // void (void *) MemFree

    // ImGuiPlatformIO &() GetPlatformIO

    // ImGuiViewport *() GetMainViewport

    void UpdatePlatformWindows();

    // void (void *, void *) RenderPlatformWindowsDefault

    void DestroyPlatformWindows();

    // ImGuiViewport *(ImGuiID) FindViewportByID

    // ImGuiViewport *(void *) FindViewportByPlatformHandle

};

}