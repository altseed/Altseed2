#pragma once
#include <cfloat>

#include "../Common/Array.h"
#include "../Graphics/Graphics.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector4F.h"

class ImguiPlatform;

namespace Altseed {

class Graphics;

enum class ToolDir : int32_t {
    None = -1,
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3,
};

enum class ToolCond : int32_t {
    None = 0,
    Always = 1 << 0,
    Once = 1 << 1,
    FirstUseEver = 1 << 2,
    Appearing = 1 << 3,
};

enum class ToolTreeNode : int32_t {
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
    CollapsingHeader = Framed | NoTreePushOnOpen | NoAutoOpenOnLog
};

enum class ToolInputText : int32_t {
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
};

enum class ToolColorEdit : int32_t {
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
};

enum class ToolSelectable {
    None = 0,
    DontClosePopups = 1 << 0,
    SpanAllColumns = 1 << 1,
    AllowDoubleClick = 1 << 2,
    Disabled = 1 << 3,
    AllowItemOverlap = 1 << 4,
};

enum class ToolWindow : int32_t {
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
    NoNav = NoNavInputs | NoNavFocus,
    NoDecoration = NoTitleBar | NoResize | NoScrollbar | NoCollapse,
    NoInputs = NoMouseInputs | NoNavInputs | NoNavFocus,
};

enum class ToolTabBar : int32_t {
    None = 0,
    Reorderable = 1 << 0,
    AutoSelectNewTabs = 1 << 1,
    TabListPopupButton = 1 << 2,
    NoCloseWithMiddleMouseButton = 1 << 3,
    NoTabListScrollingButtons = 1 << 4,
    NoTooltip = 1 << 5,
    FittingPolicyResizeDown = 1 << 6,
    FittingPolicyScroll = 1 << 7,
    FittingPolicyMask = FittingPolicyResizeDown | FittingPolicyScroll,
    FittingPolicyDefault = FittingPolicyResizeDown,
};

enum class ToolGlyphRanges : int32_t {
    Default,
    // キリル文字
    Cyrillic,
    Japanese,
    ChineseFull,
    ChineseSimplifiedCommon,
    Korean,
    Thai,
};

enum class ToolFocused : int32_t {
    None = 0,
    ChildWindows = 1 << 0,
    RootWindow = 1 << 1,
    AnyWindow = 1 << 2,
    RootAndChildWindows = RootWindow | ChildWindows
};

enum class ToolColor : int32_t {
    Text,
    TextDisabled,
    WindowBg,  // Background of normal windows
    ChildBg,  // Background of child windows
    PopupBg,  // Background of popups, menus, tooltips windows
    Border,
    BorderShadow,
    FrameBg,  // Background of checkbox, radio button, plot, slider, text input
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
    Header,  // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
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
    PlotLines,
    PlotLinesHovered,
    PlotHistogram,
    PlotHistogramHovered,
    TextSelectedBg,
    DragDropTarget,
    NavHighlight,  // Gamepad/keyboard: current highlighted item
    NavWindowingHighlight,  // Highlight window when using CTRL+TAB
    NavWindowingDimBg,  // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    ModalWindowDimBg,  // Darken/colorize entire screen behind a modal window, when one is active
    COUNT
};

enum class ToolStyleVar : int32_t {
    // Enum name --------------------- // Member in ImGuiStyle structure (see ImGuiStyle for descriptions)
    Alpha,  // float     Alpha
    WindowPadding,  // ImVec2    WindowPadding
    WindowRounding,  // float     WindowRounding
    WindowBorderSize,  // float     WindowBorderSize
    WindowMinSize,  // ImVec2    WindowMinSize
    WindowTitleAlign,  // ImVec2    WindowTitleAlign
    ChildRounding,  // float     ChildRounding
    ChildBorderSize,  // float     ChildBorderSize
    PopupRounding,  // float     PopupRounding
    PopupBorderSize,  // float     PopupBorderSize
    FramePadding,  // ImVec2    FramePadding
    FrameRounding,  // float     FrameRounding
    FrameBorderSize,  // float     FrameBorderSize
    ItemSpacing,  // ImVec2    ItemSpacing
    ItemInnerSpacing,  // ImVec2    ItemInnerSpacing
    IndentSpacing,  // float     IndentSpacing
    ScrollbarSize,  // float     ScrollbarSize
    ScrollbarRounding,  // float     ScrollbarRounding
    GrabMinSize,  // float     GrabMinSize
    GrabRounding,  // float     GrabRounding
    TabRounding,  // float     TabRounding
    ButtonTextAlign,  // ImVec2    ButtonTextAlign
    SelectableTextAlign,  // ImVec2    SelectableTextAlign
    COUNT
};

enum class ToolCombo : int32_t {
    None = 0,
    PopupAlignLeft = 1 << 0,  // Align the popup toward the left by default
    HeightSmall = 1 << 1,  // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use
                           // SetNextWindowSizeConstraints() prior to calling BeginCombo()
    HeightRegular = 1 << 2,  // Max ~8 items visible (default)
    HeightLarge = 1 << 3,  // Max ~20 items visible
    HeightLargest = 1 << 4,  // As many fitting items as possible
    NoArrowButton = 1 << 5,  // Display on the preview box without the square arrow button
    NoPreview = 1 << 6,  // Display only a square arrow button
    HeightMask_ = HeightSmall | HeightRegular | HeightLarge | HeightLargest
};

enum class ToolHovered : int32_t {
    None = 0,  // Return true if directly over the item/window, not obstructed by another window, not obstructed by an
               // active popup or modal blocking inputs under them.
    ChildWindows = 1 << 0,  // IsWindowHovered() only: Return true if any children of the window is hovered
    RootWindow = 1 << 1,  // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    AnyWindow = 1 << 2,  // IsWindowHovered() only: Return true if any window is hovered
    AllowWhenBlockedByPopup = 1 << 3,  // Return true even if a popup window is normally blocking access to this item/window
    // AllowWhenBlockedByModal     = 1 << 4,   // Return true even if a modal popup window is normally blocking access to
    // this item/window. FIXME-TODO: Unavailable yet.
    AllowWhenBlockedByActiveItem =
            1 << 5,  // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    AllowWhenOverlapped = 1 << 6,  // Return true even if the position is overlapped by another window
    AllowWhenDisabled = 1 << 7,  // Return true even if the item is disabled
    RectOnly = AllowWhenBlockedByPopup | AllowWhenBlockedByActiveItem | AllowWhenOverlapped,
    RootAndChildWindows = RootWindow | ChildWindows
};

class Tool : public BaseObject {
private:
    static std::shared_ptr<Tool> instance_;
    std::shared_ptr<ImguiPlatform> platform_;

public:
    static std::shared_ptr<Tool>& GetInstance();

    static bool Initialize(std::shared_ptr<Graphics> graphics);

    static void Terminate();

    Tool(std::shared_ptr<Graphics> graphics);

    virtual ~Tool();

    void NewFrame();

    void Render();

    bool AddFontFromFileTTF(const char16_t* path, float sizePixels, ToolGlyphRanges ranges);

    bool Begin(const char16_t* name, ToolWindow flags = ToolWindow::None);

    void End();

    void Dummy(Vector2F size);

    void Text(const char16_t* text);

    void TextUnformatted(const char16_t* text);

    void TextWrapped(const char16_t* text);

    void TextColored(const Color color, const char16_t* text);

    void TextDisabled(const char16_t* text);

    void BulletText(const char16_t* text);

    void LabelText(const char16_t* label, const char16_t* text);

    bool CollapsingHeader(const char16_t* label, ToolTreeNode flags = ToolTreeNode::None);

    bool TreeNode(const char16_t* label);

    bool TreeNodeEx(const char16_t* label, ToolTreeNode flags = ToolTreeNode::None);

    void TreePop();

    void SetNextItemOpen(bool is_open, ToolCond cond = ToolCond::None);

    bool Button(const char16_t* label, const Vector2F size);

    bool CheckBox(const char16_t* label, bool* is_open);

    bool RadioButton(const char16_t* label, bool active);

    bool ArrowButton(const char16_t* id, ToolDir dir);

    bool InvisibleButton(const char16_t* label, Vector2F size);

    bool ListBox(const char16_t* label, int32_t* current, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items = -1);

    bool Selectable(const char16_t* label, bool* selected, ToolSelectable flags = ToolSelectable::None);

    const char16_t* InputText(const char16_t* label, const char16_t* input, int32_t max_length, ToolInputText flags = ToolInputText::None);

    const char16_t* InputTextWithHint(
            const char16_t* label,
            const char16_t* hint,
            const char16_t* input,
            int32_t max_length,
            ToolInputText flags = ToolInputText::None);

    const char16_t* InputTextMultiline(
            const char16_t* label, const char16_t* input, int32_t max_length, Vector2F size, ToolInputText flags = ToolInputText::None);

    bool InputInt(const char16_t* label, int32_t* v);

    bool InputInt2(const char16_t* label, std::shared_ptr<Int32Array> array);

    bool InputInt3(const char16_t* label, std::shared_ptr<Int32Array> array);

    bool InputInt4(const char16_t* label, std::shared_ptr<Int32Array> array);

    bool InputFloat(const char16_t* label, float* v);

    bool InputFloat2(const char16_t* label, std::shared_ptr<FloatArray> array);

    bool InputFloat3(const char16_t* label, std::shared_ptr<FloatArray> array);

    bool InputFloat4(const char16_t* label, std::shared_ptr<FloatArray> array);

    bool SliderInt(const char16_t* label, int32_t* v, float speed, int32_t v_min, int32_t v_max);

    bool SliderInt2(const char16_t* label, std::shared_ptr<Int32Array> array, float speed, int32_t v_min, int32_t v_max);

    bool SliderInt3(const char16_t* label, std::shared_ptr<Int32Array> array, float speed, int32_t v_min, int32_t v_max);

    bool SliderInt4(const char16_t* label, std::shared_ptr<Int32Array> array, float speed, int32_t v_min, int32_t v_max);

    bool SliderFloat(const char16_t* label, float* v, float speed, float v_min, float v_max);

    bool SliderFloat2(const char16_t* label, std::shared_ptr<FloatArray> array, float speed, float v_min, float v_max);

    bool SliderFloat3(const char16_t* label, std::shared_ptr<FloatArray> array, float speed, float v_min, float v_max);

    bool SliderFloat4(const char16_t* label, std::shared_ptr<FloatArray> array, float speed, float v_min, float v_max);

    bool SliderAngle(const char16_t* label, float* angle);

    bool VSliderInt(const char16_t* label, Vector2F size, int32_t* v, float v_min, float v_max);

    bool VSliderFloat(const char16_t* label, Vector2F size, float* v, float v_min, float v_max);

    bool DragInt(const char16_t* label, int32_t* v, float speed, int32_t v_min, int32_t v_max);

    bool DragFloat(const char16_t* label, float* v, float speed, float v_min, float v_max);

    bool DragIntRange2(const char16_t* label, int32_t* current_min, int32_t* current_max, float speed, int32_t v_min, int32_t v_max);

    bool DragFloatRange2(const char16_t* label, float* current_min, float* current_max, float speed, float v_min, float v_max);

    bool ColorEdit3(const char16_t* label, Color* color, ToolColorEdit flags = ToolColorEdit::None);

    bool ColorEdit4(const char16_t* label, Color* color, ToolColorEdit flags = ToolColorEdit::None);

    void OpenPopup(const char16_t* label);

    bool BeginPopup(const char16_t* label);

    bool BeginPopupModal(const char16_t* label);

    void EndPopup();

    bool BeginChild(const char16_t* label, Vector2F size, bool border, ToolWindow flags = ToolWindow::None);

    void EndChild();

    bool BeginMenuBar();

    void EndMenuBar();

    bool BeginMenu(const char16_t* label, bool enabled);

    void EndMenu();

    bool MenuItem(const char16_t* label, const char16_t* shortcut, bool selected, bool enabled);

    bool BeginTabBar(const char16_t* label, ToolTabBar flags = ToolTabBar::None);

    void EndTabBar();

    bool BeginTabItem(const char16_t* label);

    void EndTabItem();

    void Indent();

    void Unindent();

    void Separator();

    void SetTooltip(const char16_t* text);

    void BeginTooltip();

    void EndTooltip();

    void NewLine();

    void SameLine();

    void PushTextWrapPos(float wrap_local_pos_x);

    void PopTextWrapPos();

    void PushItemWidth(float width);

    void PopItemWidth();

    void PushButtonRepeat(bool repeat);

    void PopButtonRepeat();

    void Columns(int32_t count, bool border);

    void NextColumn();

    void PushID(int32_t id);

    void PopID();

    bool IsItemActive();

    bool IsItemHovered();

    void SetScrollHere();

    float GetTextLineHeight();

    float GetFontSize();

    Vector2F GetWindowSize();

    void SetWindowSize(Vector2F size);

    bool IsMousePosValid();

    bool IsMouseDragging();

    bool IsMouseDoubleClicked(int32_t id);

    Vector2F GetMouseDragDelta(int32_t button);

    void ResetMouseDragDelta(int32_t button);

    void SetNextWindowContentSize(Vector2F size);

    void SetNextWindowPos(Vector2F pos, ToolCond cond = ToolCond::None);

    void SetNextWindowSize(Vector2F size, ToolCond cond = ToolCond::None);

    bool IsWindowAppearing();

    bool IsWindowCollapsed();

    bool IsWindowFocused(ToolFocused flags = ToolFocused::None);

    bool IsWindowHovered(ToolFocused flags = ToolFocused::None);

    Vector2F GetWindowPos();

    void SetNextWindowCollapsed(bool collapsed, ToolCond cond = ToolCond::None);

    void SetNextWindowFocus();

    void SetNextWindowBgAlpha(float alpha);

    void SetWindowPosWithCond(Vector2F pos, ToolCond cond = ToolCond::None);

    void SetWindowSizeWithCond(Vector2F size, ToolCond cond = ToolCond::None);

    void SetWindowCollapsedWithCond(bool collapsed, ToolCond cond = ToolCond::None);

    void SetWindowFocus();

    void SetWindowFontScale(float scale);

    void SetWindowPosByName(const char16_t* name, Vector2F pos, ToolCond cond = ToolCond::None);

    void SetWindowSizeByName(const char16_t* name, Vector2F size, ToolCond cond = ToolCond::None);

    void SetWindowCollapsedByName(const char16_t* name, bool collapsed, ToolCond cond = ToolCond::None);

    void SetWindowFocusByName(const char16_t* name);

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

    void PushStyleColor(ToolColor idx, Color col);

    void PopStyleColor(int32_t count = 1);

    void PushStyleVarFloat(ToolStyleVar idx, float val);

    void PushStyleVarVector2F(ToolStyleVar idx, Vector2F val);

    void PopStyleVar(int32_t count = 1);

    Color GetStyleColor(ToolColor idx);

    Vector2F GetFontTexUvWhitePixel();

    void SetNextItemWidth(float item_width);

    float CalcItemWidth();

    void PushAllowKeyboardFocus(bool allow_keyboard_focus);

    void PopAllowKeyboardFocus();

    void Spacing();

    void BeginGroup();

    void EndGroup();

    Vector2F GetCursorPos();

    void SetCursorPos(Vector2F local_pos);

    Vector2F GetCursorStartPos();

    Vector2F GetCursorScreenPos();

    void AlignTextToFramePadding();

    float GetTextLineHeightWithSpacing();

    float GetFrameHeight();

    float GetFrameHeightWithSpacing();

    bool SmallButton(const char16_t* label);

    void Image(
            std::shared_ptr<Texture2D> texture,
            Vector2F size,
            Vector2F uv0 = Vector2F(0, 0),
            Vector2F uv1 = Vector2F(1, 1),
            Color tint_col = Color(1, 1, 1, 1),
            Color border_col = Color(0, 0, 0, 0));

    bool ImageButton(
            std::shared_ptr<Texture2D> texture,
            Vector2F size,
            Vector2F uv0 = Vector2F(0, 0),
            Vector2F uv1 = Vector2F(1, 1),
            int32_t frame_padding = -1,
            Color bg_col = Color(0, 0, 0, 0),
            Color tint_col = Color(1, 1, 1, 1));

    bool Checkbox(const char16_t* label, bool* v);

    bool CheckboxFlags(const char16_t* label, unsigned int* flags, unsigned int flags_value);

    void ProgressBar(float fraction, Vector2F size_arg = Vector2F(-1, 0), const char16_t* overlay = NULL);

    void Bullet();

    bool BeginCombo(const char16_t* label, const char16_t* preview_value, ToolCombo flags = ToolCombo::None);

    void EndCombo();

    bool Combo(
            const char16_t* label, int32_t* current_item, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items = -1);

    bool ColorButton(const char16_t* desc_id, Color* col, ToolColorEdit flags = ToolColorEdit::None, Vector2F size = Vector2F(0, 0));

    void SetColorEditOptions(ToolColorEdit flags);

    float GetTreeNodeToLabelSpacing();

    bool ListBoxHeader(const char16_t* label, Vector2F size = Vector2F(0, 0));

    void ListBoxFooter();

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

    void ValueBool(const char16_t* prefix, bool b);

    void ValueInt(const char16_t* prefix, int32_t v);

    void ValueFloat(const char16_t* prefix, float v, const char16_t* float_format = NULL);

    bool BeginMainMenuBar();

    void EndMainMenuBar();

    bool BeginPopupContextItem(const char16_t* str_id = NULL, int32_t mouse_button = 1);

    bool BeginPopupContextWindow(const char16_t* str_id = NULL, int32_t mouse_button = 1, bool also_over_items = true);

    bool BeginPopupContextVoid(const char16_t* str_id = NULL, int32_t mouse_button = 1);

    bool BeginPopupModalEx(const char16_t* name, bool* p_open = NULL, ToolWindow flags = ToolWindow::None);

    bool OpenPopupOnItemClick(const char16_t* str_id = NULL, int32_t mouse_button = 1);

    bool IsPopupOpen(const char16_t* str_id);

    void CloseCurrentPopup();

    int32_t GetColumnIndex();

    float GetColumnWidth(int32_t column_index = -1);

    void SetColumnWidth(int32_t column_index, float width);

    float GetColumnOffset(int32_t column_index = -1);

    void SetColumnOffset(int32_t column_index, float offset_x);

    int32_t GetColumnsCount();

    void SetTabItemClosed(const char16_t* tab_or_docked_window_label);

    void PushClipRect(Vector2F clip_rect_min, Vector2F clip_rect_max, bool intersect_with_current_clip_rect);

    void PopClipRect();

    void SetItemDefaultFocus();

    void SetKeyboardFocusHere(int32_t offset = 0);

    bool IsItemHoveredWithFlags(ToolHovered flags = ToolHovered::None);

    bool IsItemFocused();

    bool IsItemClicked(int32_t mouse_button = 0);

    bool IsItemVisible();

    bool IsItemEdited();

    bool IsItemActivated();

    bool IsItemDeactivated();

    bool IsItemDeactivatedAfterEdit();

    bool IsAnyItemHovered();

    bool IsAnyItemActive();

    bool IsAnyItemFocused();

    Vector2F GetItemRectMin();

    Vector2F GetItemRectMax();

    Vector2F GetItemRectSize();

    void SetItemAllowOverlap();

    bool IsRectVisible(Vector2F size);

    bool IsRectVisibleVector2F2(Vector2F rect_min, Vector2F rect_max);

    float GetTime();

    const char16_t* GetClipboardText();

    void SetClipboardText(const char16_t* text);

    void LoadIniSettingsFromDisk(const char16_t* ini_filename);

    void SaveIniSettingsToDisk(const char16_t* ini_filename);

    const char16_t* OpenDialog(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* OpenDialogMultiple(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* SaveDialog(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* PickFolder(const char16_t* defaultPath);
};

}  // namespace Altseed