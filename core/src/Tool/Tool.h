#pragma once

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

    void TextColored(const Vector4F color, const char16_t* text);

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

    bool Combo(const char16_t* label, int* current, const char* items[], size_t count);

    bool ListBox(const char16_t* label, int* current, const char* items[], size_t count);

    bool Selectable(const char16_t* label, bool* selected, ToolSelectable flags = ToolSelectable::None);

    bool InputText(const char16_t* label, char* buf, size_t buf_size, ToolInputText flags = ToolInputText::None);

    bool InputTextWithHint(
            const char16_t* label, const char16_t* hint, char* buf, size_t buf_size, ToolInputText flags = ToolInputText::None);

    bool InputTextMultiline(const char16_t* label, char* buf, size_t buf_size, Vector2F size, ToolInputText flags = ToolInputText::None);

    bool InputInt(const char16_t* label, int* v);

    bool InputInt2(const char16_t* label, int* array);

    bool InputInt3(const char16_t* label, int* array);

    bool InputInt4(const char16_t* label, int* array);

    bool InputFloat(const char16_t* label, float* v);

    bool InputFloat2(const char16_t* label, float* array);

    bool InputFloat3(const char16_t* label, float* array);

    bool InputFloat4(const char16_t* label, float* array);

    bool SliderInt(const char16_t* label, int* v, float speed, int v_min, int v_max);

    bool SliderInt2(const char16_t* label, int* array, float speed, int v_min, int v_max);

    bool SliderInt3(const char16_t* label, int* array, float speed, int v_min, int v_max);

    bool SliderInt4(const char16_t* label, int* array, float speed, int v_min, int v_max);

    bool SliderFloat(const char16_t* label, float* v, float speed, float v_min, float v_max);

    bool SliderFloat2(const char16_t* label, float* array, float speed, float v_min, float v_max);

    bool SliderFloat3(const char16_t* label, float* array, float speed, float v_min, float v_max);

    bool SliderFloat4(const char16_t* label, float* array, float speed, float v_min, float v_max);

    bool SliderAngle(const char16_t* label, float* angle);

    bool VSliderInt(const char16_t* label, Vector2F size, int* v, float v_min, float v_max);

    bool VSliderFloat(const char16_t* label, Vector2F size, float* v, float v_min, float v_max);

    bool DragInt(const char16_t* label, int* v, float speed, int v_min, int v_max);

    bool DragFloat(const char16_t* label, float* v, float speed, float v_min, float v_max);

    bool DragIntRange2(const char16_t* label, int* current_min, int* current_max, float speed, int v_min, int v_max);

    bool DragFloatRange2(const char16_t* label, float* current_min, float* current_max, float speed, float v_min, float v_max);

    bool ColorEdit3(const char16_t* label, float* color, ToolColorEdit flags = ToolColorEdit::None);

    bool ColorEdit4(const char16_t* label, float* color, ToolColorEdit flags = ToolColorEdit::None);

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

    void SetNextItemWidth(int width);

    void PushItemWidth(float width);
    
    void PopItemWidth();

    void PushButtonRepeat(bool repeat);

    void PopButtonRepeat();

    void Columns(int count, bool border);

    void NextColumn();

    void PushID(int id);

    void PopID();

    bool IsItemActive();

    bool IsItemHovered();

    void SetScrollHere();

    void SetScrollHereX();

    void SetScrollHereY();

    float GetTextLineHeight();

    float GetFontSize();

    Vector2F GetWindowSize();

    void SetWindowSize(Vector2F size);

    bool IsMousePosValid();

    bool IsMouseDragging();

    bool IsMouseDoubleClicked(int id);

    Vector2F GetMouseDragDelta(int button);

    void ResetMouseDragDelta(int button);

    void SetNextWindowContentSize(Vector2F size);

    void SetNextWindowPos(Vector2F pos, ToolCond cond = ToolCond::None);

    void SetNextWindowSize(Vector2F size, ToolCond cond = ToolCond::None);
};

}  // namespace Altseed