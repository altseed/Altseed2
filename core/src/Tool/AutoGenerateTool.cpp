#include "Tool.h"

#include <nfd.h>

#include "../Common/StringHelper.h"
#include "Platform/ImGuiPlatform.h"
#ifdef _WIN32
#include "Platform/ImGuiPlatformDX12.h"
#elif __APPLE__
#include "Platform/ImGuiPlatformMetal.h"
#endif

#ifdef ENABLE_VULKAN
#include "Platform/ImGuiPlatformVulkan.h"
#endif

#include <imgui_impl_glfw.h>

#include "../Graphics/CommandList.h"
#include "../Graphics/Graphics.h"
#include "../IO/File.h"
#include "../IO/StaticFile.h"
#include "../Logger/Log.h"
#include "../Math/Vector4F.h"
#include "../System/SynchronizationContext.h"

namespace Altseed2 {

static std::u16string returnStr;

inline ImVec2 toImVec2(const Vector2F& v) { return ImVec2(v.X, v.Y); }

inline ImVec4 toImVec4(const Vector4F& v) { return ImVec4(v.X, v.Y, v.Z, v.W); }

inline ImVec4 toImVec4(const Color& v) { return ImVec4(v.R / 255.0f, v.G / 255.0f, v.B / 255.0f, v.A / 255.0f); }

inline Vector2F toVector2F(const ImVec2& v) { return Vector2F(v.x, v.y); }

inline Vector4F toVector4F(const ImVec4& v) { return Vector4F(v.x, v.y, v.z, v.w); }

inline Color toColor(const ImVec4& v) { return Color(v.x * 255, v.y * 255, v.z * 255, v.w * 255); }
// ImGuiContext *(ImFontAtlas *) CreateContext

// void (ImGuiContext *) DestroyContext

// ImGuiContext *() GetCurrentContext

// void (ImGuiContext *) SetCurrentContext

// ImGuiIO &() GetIO

// ImGuiStyle &() GetStyle

// ImDrawData *() GetDrawData

void Tool::ShowDemoWindow(bool* p_open) {
    ImGui::ShowDemoWindow(p_open);
}

void Tool::ShowAboutWindow(bool* p_open) {
    ImGui::ShowAboutWindow(p_open);
}

void Tool::ShowMetricsWindow(bool* p_open) {
    ImGui::ShowMetricsWindow(p_open);
}

// void (ImGuiStyle *) ShowStyleEditor

bool Tool::ShowStyleSelector(const char16_t* label) {
    return ImGui::ShowStyleSelector(utf16_to_utf8(label).c_str());
}

void Tool::ShowFontSelector(const char16_t* label) {
    ImGui::ShowFontSelector(utf16_to_utf8(label).c_str());
}

void Tool::ShowUserGuide() {
    ImGui::ShowUserGuide();
}

const char16_t* Tool::GetVersion() {
    returnStr = utf8_to_utf16(ImGui::GetVersion());
    return returnStr.c_str();
}

// void (ImGuiStyle *) StyleColorsDark

// void (ImGuiStyle *) StyleColorsClassic

// void (ImGuiStyle *) StyleColorsLight

bool Tool::Begin(const char16_t* name, bool* p_open, ToolWindowFlags flags) {
    return ImGui::Begin(utf16_to_utf8(name).c_str(), p_open, (ImGuiWindowFlags)flags);
}

void Tool::End() {
    ImGui::End();
}

bool Tool::BeginChild(const char16_t* str_id, Vector2F size, bool border, ToolWindowFlags flags) {
    return ImGui::BeginChild(utf16_to_utf8(str_id).c_str(), toImVec2(size), border, (ImGuiWindowFlags)flags);
}

bool Tool::BeginChild(uint32_t id, Vector2F size, bool border, ToolWindowFlags flags) {
    return ImGui::BeginChild(id, toImVec2(size), border, (ImGuiWindowFlags)flags);
}

void Tool::EndChild() {
    ImGui::EndChild();
}

bool Tool::IsWindowAppearing() {
    return ImGui::IsWindowAppearing();
}

bool Tool::IsWindowCollapsed() {
    return ImGui::IsWindowCollapsed();
}

bool Tool::IsWindowFocused(ToolFocusedFlags flags) {
    return ImGui::IsWindowFocused((ImGuiFocusedFlags)flags);
}

bool Tool::IsWindowHovered(ToolHoveredFlags flags) {
    return ImGui::IsWindowHovered((ImGuiHoveredFlags)flags);
}

// ImDrawList *() GetWindowDrawList

float Tool::GetWindowDpiScale() {
    return ImGui::GetWindowDpiScale();
}

// ImGuiViewport *() GetWindowViewport

Vector2F Tool::GetWindowPos() {
    return toVector2F(ImGui::GetWindowPos());
}

Vector2F Tool::GetWindowSize() {
    return toVector2F(ImGui::GetWindowSize());
}

float Tool::GetWindowWidth() {
    return ImGui::GetWindowWidth();
}

float Tool::GetWindowHeight() {
    return ImGui::GetWindowHeight();
}

void Tool::SetNextWindowPos(Vector2F pos, ToolCond cond, Vector2F pivot) {
    ImGui::SetNextWindowPos(toImVec2(pos), (ImGuiCond)cond, toImVec2(pivot));
}

void Tool::SetNextWindowSize(Vector2F size, ToolCond cond) {
    ImGui::SetNextWindowSize(toImVec2(size), (ImGuiCond)cond);
}

// void (const ImVec2 &, const ImVec2 &, ImGuiSizeCallback, void *) SetNextWindowSizeConstraints

void Tool::SetNextWindowContentSize(Vector2F size) {
    ImGui::SetNextWindowContentSize(toImVec2(size));
}

void Tool::SetNextWindowCollapsed(bool collapsed, ToolCond cond) {
    ImGui::SetNextWindowCollapsed(collapsed, (ImGuiCond)cond);
}

void Tool::SetNextWindowFocus() {
    ImGui::SetNextWindowFocus();
}

void Tool::SetNextWindowBgAlpha(float alpha) {
    ImGui::SetNextWindowBgAlpha(alpha);
}

void Tool::SetNextWindowViewport(uint32_t viewport_id) {
    ImGui::SetNextWindowViewport(viewport_id);
}

void Tool::SetWindowPos(Vector2F pos, ToolCond cond) {
    ImGui::SetWindowPos(toImVec2(pos), (ImGuiCond)cond);
}

void Tool::SetWindowSize(Vector2F size, ToolCond cond) {
    ImGui::SetWindowSize(toImVec2(size), (ImGuiCond)cond);
}

void Tool::SetWindowCollapsed(bool collapsed, ToolCond cond) {
    ImGui::SetWindowCollapsed(collapsed, (ImGuiCond)cond);
}

void Tool::SetWindowFocus() {
    ImGui::SetWindowFocus();
}

void Tool::SetWindowFontScale(float scale) {
    ImGui::SetWindowFontScale(scale);
}

void Tool::SetWindowPos(const char16_t* name, Vector2F pos, ToolCond cond) {
    ImGui::SetWindowPos(utf16_to_utf8(name).c_str(), toImVec2(pos), (ImGuiCond)cond);
}

void Tool::SetWindowSize(const char16_t* name, Vector2F size, ToolCond cond) {
    ImGui::SetWindowSize(utf16_to_utf8(name).c_str(), toImVec2(size), (ImGuiCond)cond);
}

void Tool::SetWindowCollapsed(const char16_t* name, bool collapsed, ToolCond cond) {
    ImGui::SetWindowCollapsed(utf16_to_utf8(name).c_str(), collapsed, (ImGuiCond)cond);
}

void Tool::SetWindowFocus(const char16_t* name) {
    ImGui::SetWindowFocus(utf16_to_utf8(name).c_str());
}

Vector2F Tool::GetContentRegionMax() {
    return toVector2F(ImGui::GetContentRegionMax());
}

Vector2F Tool::GetContentRegionAvail() {
    return toVector2F(ImGui::GetContentRegionAvail());
}

Vector2F Tool::GetWindowContentRegionMin() {
    return toVector2F(ImGui::GetWindowContentRegionMin());
}

Vector2F Tool::GetWindowContentRegionMax() {
    return toVector2F(ImGui::GetWindowContentRegionMax());
}

float Tool::GetWindowContentRegionWidth() {
    return ImGui::GetWindowContentRegionWidth();
}

float Tool::GetScrollX() {
    return ImGui::GetScrollX();
}

float Tool::GetScrollY() {
    return ImGui::GetScrollY();
}

float Tool::GetScrollMaxX() {
    return ImGui::GetScrollMaxX();
}

float Tool::GetScrollMaxY() {
    return ImGui::GetScrollMaxY();
}

void Tool::SetScrollX(float scroll_x) {
    ImGui::SetScrollX(scroll_x);
}

void Tool::SetScrollY(float scroll_y) {
    ImGui::SetScrollY(scroll_y);
}

void Tool::SetScrollHereX(float center_x_ratio) {
    ImGui::SetScrollHereX(center_x_ratio);
}

void Tool::SetScrollHereY(float center_y_ratio) {
    ImGui::SetScrollHereY(center_y_ratio);
}

void Tool::SetScrollFromPosX(float local_x, float center_x_ratio) {
    ImGui::SetScrollFromPosX(local_x, center_x_ratio);
}

void Tool::SetScrollFromPosY(float local_y, float center_y_ratio) {
    ImGui::SetScrollFromPosY(local_y, center_y_ratio);
}

// void (ImFont *) PushFont

void Tool::PopFont() {
    ImGui::PopFont();
}

void Tool::PushStyleColor(ToolCol idx, uint32_t col) {
    ImGui::PushStyleColor((ImGuiCol)idx, col);
}

void Tool::PushStyleColor(ToolCol idx, Vector4F col) {
    ImGui::PushStyleColor((ImGuiCol)idx, toImVec4(col));
}

void Tool::PopStyleColor(int32_t count) {
    ImGui::PopStyleColor(count);
}

void Tool::PushStyleVar(ToolStyleVar idx, float val) {
    ImGui::PushStyleVar((ImGuiStyleVar)idx, val);
}

void Tool::PushStyleVar(ToolStyleVar idx, Vector2F val) {
    ImGui::PushStyleVar((ImGuiStyleVar)idx, toImVec2(val));
}

void Tool::PopStyleVar(int32_t count) {
    ImGui::PopStyleVar(count);
}

// const ImVec4 &(ImGuiCol) GetStyleColorVec4

// ImFont *() GetFont

float Tool::GetFontSize() {
    return ImGui::GetFontSize();
}

Vector2F Tool::GetFontTexUvWhitePixel() {
    return toVector2F(ImGui::GetFontTexUvWhitePixel());
}

uint32_t Tool::GetColorU32(ToolCol idx, float alpha_mul) {
    return ImGui::GetColorU32((ImGuiCol)idx, alpha_mul);
}

uint32_t Tool::GetColorU32(Vector4F col) {
    return ImGui::GetColorU32(toImVec4(col));
}

uint32_t Tool::GetColorU32(uint32_t col) {
    return ImGui::GetColorU32(col);
}

void Tool::PushItemWidth(float item_width) {
    ImGui::PushItemWidth(item_width);
}

void Tool::PopItemWidth() {
    ImGui::PopItemWidth();
}

void Tool::SetNextItemWidth(float item_width) {
    ImGui::SetNextItemWidth(item_width);
}

float Tool::CalcItemWidth() {
    return ImGui::CalcItemWidth();
}

void Tool::PushTextWrapPos(float wrap_local_pos_x) {
    ImGui::PushTextWrapPos(wrap_local_pos_x);
}

void Tool::PopTextWrapPos() {
    ImGui::PopTextWrapPos();
}

void Tool::PushAllowKeyboardFocus(bool allow_keyboard_focus) {
    ImGui::PushAllowKeyboardFocus(allow_keyboard_focus);
}

void Tool::PopAllowKeyboardFocus() {
    ImGui::PopAllowKeyboardFocus();
}

void Tool::PushButtonRepeat(bool repeat) {
    ImGui::PushButtonRepeat(repeat);
}

void Tool::PopButtonRepeat() {
    ImGui::PopButtonRepeat();
}

void Tool::Separator() {
    ImGui::Separator();
}

void Tool::SameLine(float offset_from_start_x, float spacing) {
    ImGui::SameLine(offset_from_start_x, spacing);
}

void Tool::NewLine() {
    ImGui::NewLine();
}

void Tool::Spacing() {
    ImGui::Spacing();
}

void Tool::Dummy(Vector2F size) {
    ImGui::Dummy(toImVec2(size));
}

void Tool::Indent(float indent_w) {
    ImGui::Indent(indent_w);
}

void Tool::Unindent(float indent_w) {
    ImGui::Unindent(indent_w);
}

void Tool::BeginGroup() {
    ImGui::BeginGroup();
}

void Tool::EndGroup() {
    ImGui::EndGroup();
}

Vector2F Tool::GetCursorPos() {
    return toVector2F(ImGui::GetCursorPos());
}

float Tool::GetCursorPosX() {
    return ImGui::GetCursorPosX();
}

float Tool::GetCursorPosY() {
    return ImGui::GetCursorPosY();
}

void Tool::SetCursorPos(Vector2F local_pos) {
    ImGui::SetCursorPos(toImVec2(local_pos));
}

void Tool::SetCursorPosX(float local_x) {
    ImGui::SetCursorPosX(local_x);
}

void Tool::SetCursorPosY(float local_y) {
    ImGui::SetCursorPosY(local_y);
}

Vector2F Tool::GetCursorStartPos() {
    return toVector2F(ImGui::GetCursorStartPos());
}

Vector2F Tool::GetCursorScreenPos() {
    return toVector2F(ImGui::GetCursorScreenPos());
}

void Tool::SetCursorScreenPos(Vector2F pos) {
    ImGui::SetCursorScreenPos(toImVec2(pos));
}

void Tool::AlignTextToFramePadding() {
    ImGui::AlignTextToFramePadding();
}

float Tool::GetTextLineHeight() {
    return ImGui::GetTextLineHeight();
}

float Tool::GetTextLineHeightWithSpacing() {
    return ImGui::GetTextLineHeightWithSpacing();
}

float Tool::GetFrameHeight() {
    return ImGui::GetFrameHeight();
}

float Tool::GetFrameHeightWithSpacing() {
    return ImGui::GetFrameHeightWithSpacing();
}

void Tool::PushID(const char16_t* str_id) {
    ImGui::PushID(utf16_to_utf8(str_id).c_str());
}

void Tool::PushID(const char16_t* str_id_begin, const char16_t* str_id_end) {
    ImGui::PushID(utf16_to_utf8(str_id_begin).c_str(), utf16_to_utf8(str_id_end).c_str());
}

// void (const void *) PushID

void Tool::PushID(int32_t int_id) {
    ImGui::PushID(int_id);
}

void Tool::PopID() {
    ImGui::PopID();
}

uint32_t Tool::GetID(const char16_t* str_id) {
    return ImGui::GetID(utf16_to_utf8(str_id).c_str());
}

uint32_t Tool::GetID(const char16_t* str_id_begin, const char16_t* str_id_end) {
    return ImGui::GetID(utf16_to_utf8(str_id_begin).c_str(), utf16_to_utf8(str_id_end).c_str());
}

// ImGuiID (const void *) GetID

void Tool::TextUnformatted(const char16_t* text, const char16_t* text_end) {
    ImGui::TextUnformatted(utf16_to_utf8(text).c_str(), text_end != nullptr ? utf16_to_utf8(text_end).c_str() : nullptr);
}

void Tool::Text(const char16_t* fmt) {
    ImGui::Text(utf16_to_utf8(fmt).c_str());
}

// void (const char *, __va_list_tag *) TextV

void Tool::TextColored(Vector4F col, const char16_t* fmt) {
    ImGui::TextColored(toImVec4(col), utf16_to_utf8(fmt).c_str());
}

// void (const ImVec4 &, const char *, __va_list_tag *) TextColoredV

void Tool::TextDisabled(const char16_t* fmt) {
    ImGui::TextDisabled(utf16_to_utf8(fmt).c_str());
}

// void (const char *, __va_list_tag *) TextDisabledV

void Tool::TextWrapped(const char16_t* fmt) {
    ImGui::TextWrapped(utf16_to_utf8(fmt).c_str());
}

// void (const char *, __va_list_tag *) TextWrappedV

void Tool::LabelText(const char16_t* label, const char16_t* fmt) {
    ImGui::LabelText(utf16_to_utf8(label).c_str(), utf16_to_utf8(fmt).c_str());
}

// void (const char *, const char *, __va_list_tag *) LabelTextV

void Tool::BulletText(const char16_t* fmt) {
    ImGui::BulletText(utf16_to_utf8(fmt).c_str());
}

// void (const char *, __va_list_tag *) BulletTextV

bool Tool::Button(const char16_t* label, Vector2F size) {
    return ImGui::Button(utf16_to_utf8(label).c_str(), toImVec2(size));
}

bool Tool::SmallButton(const char16_t* label) {
    return ImGui::SmallButton(utf16_to_utf8(label).c_str());
}

bool Tool::InvisibleButton(const char16_t* str_id, Vector2F size, ToolButtonFlags flags) {
    return ImGui::InvisibleButton(utf16_to_utf8(str_id).c_str(), toImVec2(size), (ImGuiButtonFlags)flags);
}

bool Tool::ArrowButton(const char16_t* str_id, ToolDir dir) {
    return ImGui::ArrowButton(utf16_to_utf8(str_id).c_str(), (ImGuiDir)dir);
}

// void (ImTextureID, const ImVec2 &, const ImVec2 &, const ImVec2 &, const ImVec4 &, const ImVec4 &) Image

// bool (ImTextureID, const ImVec2 &, const ImVec2 &, const ImVec2 &, int, const ImVec4 &, const ImVec4 &) ImageButton

bool Tool::Checkbox(const char16_t* label, bool* v) {
    return ImGui::Checkbox(utf16_to_utf8(label).c_str(), v);
}

// bool (const char *, unsigned int *, unsigned int) CheckboxFlags

bool Tool::RadioButton(const char16_t* label, bool active) {
    return ImGui::RadioButton(utf16_to_utf8(label).c_str(), active);
}

bool Tool::RadioButton(const char16_t* label, int32_t* v, int32_t v_button) {
    return ImGui::RadioButton(utf16_to_utf8(label).c_str(), v, v_button);
}

void Tool::ProgressBar(float fraction, Vector2F size_arg, const char16_t* overlay) {
    ImGui::ProgressBar(fraction, toImVec2(size_arg), overlay != nullptr ? utf16_to_utf8(overlay).c_str() : nullptr);
}

void Tool::Bullet() {
    ImGui::Bullet();
}

bool Tool::BeginCombo(const char16_t* label, const char16_t* preview_value, ToolComboFlags flags) {
    return ImGui::BeginCombo(utf16_to_utf8(label).c_str(), utf16_to_utf8(preview_value).c_str(), (ImGuiComboFlags)flags);
}

void Tool::EndCombo() {
    ImGui::EndCombo();
}

bool Tool::DragFloat(const char16_t* label, float* v, float v_speed, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    return ImGui::DragFloat(utf16_to_utf8(label).c_str(), v, v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::DragFloat2(const char16_t* label, std::shared_ptr<FloatArray> v, float v_speed, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::DragFloat2(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::DragFloat3(const char16_t* label, std::shared_ptr<FloatArray> v, float v_speed, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::DragFloat3(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::DragFloat4(const char16_t* label, std::shared_ptr<FloatArray> v, float v_speed, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::DragFloat4(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::DragFloatRange2(const char16_t* label, float* v_current_min, float* v_current_max, float v_speed, float v_min, float v_max, const char16_t* format, const char16_t* format_max, ToolSliderFlags flags) {
    return ImGui::DragFloatRange2(utf16_to_utf8(label).c_str(), v_current_min, v_current_max, v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), format_max != nullptr ? utf16_to_utf8(format_max).c_str() : nullptr, (ImGuiSliderFlags)flags);
}

bool Tool::DragInt(const char16_t* label, int32_t* v, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    return ImGui::DragInt(utf16_to_utf8(label).c_str(), v, v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::DragInt2(const char16_t* label, std::shared_ptr<Int32Array> v, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::DragInt2(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::DragInt3(const char16_t* label, std::shared_ptr<Int32Array> v, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::DragInt3(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::DragInt4(const char16_t* label, std::shared_ptr<Int32Array> v, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::DragInt4(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::DragIntRange2(const char16_t* label, int32_t* v_current_min, int32_t* v_current_max, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, const char16_t* format_max, ToolSliderFlags flags) {
    return ImGui::DragIntRange2(utf16_to_utf8(label).c_str(), v_current_min, v_current_max, v_speed, v_min, v_max, utf16_to_utf8(format).c_str(), format_max != nullptr ? utf16_to_utf8(format_max).c_str() : nullptr, (ImGuiSliderFlags)flags);
}

// bool (const char *, ImGuiDataType, void *, float, const void *, const void *, const char *, ImGuiSliderFlags) DragScalar

// bool (const char *, ImGuiDataType, void *, int, float, const void *, const void *, const char *, ImGuiSliderFlags) DragScalarN

bool Tool::SliderFloat(const char16_t* label, float* v, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    return ImGui::SliderFloat(utf16_to_utf8(label).c_str(), v, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::SliderFloat2(const char16_t* label, std::shared_ptr<FloatArray> v, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::SliderFloat2(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::SliderFloat3(const char16_t* label, std::shared_ptr<FloatArray> v, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::SliderFloat3(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::SliderFloat4(const char16_t* label, std::shared_ptr<FloatArray> v, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::SliderFloat4(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::SliderAngle(const char16_t* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char16_t* format, ToolSliderFlags flags) {
    return ImGui::SliderAngle(utf16_to_utf8(label).c_str(), v_rad, v_degrees_min, v_degrees_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::SliderInt(const char16_t* label, int32_t* v, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    return ImGui::SliderInt(utf16_to_utf8(label).c_str(), v, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::SliderInt2(const char16_t* label, std::shared_ptr<Int32Array> v, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::SliderInt2(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::SliderInt3(const char16_t* label, std::shared_ptr<Int32Array> v, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::SliderInt3(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::SliderInt4(const char16_t* label, std::shared_ptr<Int32Array> v, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::SliderInt4(utf16_to_utf8(label).c_str(), &v->GetVector()[0], v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

// bool (const char *, ImGuiDataType, void *, const void *, const void *, const char *, ImGuiSliderFlags) SliderScalar

// bool (const char *, ImGuiDataType, void *, int, const void *, const void *, const char *, ImGuiSliderFlags) SliderScalarN

bool Tool::VSliderFloat(const char16_t* label, Vector2F size, float* v, float v_min, float v_max, const char16_t* format, ToolSliderFlags flags) {
    return ImGui::VSliderFloat(utf16_to_utf8(label).c_str(), toImVec2(size), v, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

bool Tool::VSliderInt(const char16_t* label, Vector2F size, int32_t* v, int32_t v_min, int32_t v_max, const char16_t* format, ToolSliderFlags flags) {
    return ImGui::VSliderInt(utf16_to_utf8(label).c_str(), toImVec2(size), v, v_min, v_max, utf16_to_utf8(format).c_str(), (ImGuiSliderFlags)flags);
}

// bool (const char *, const ImVec2 &, ImGuiDataType, void *, const void *, const void *, const char *, ImGuiSliderFlags) VSliderScalar

// bool (const char *, char *, size_t, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputText

// bool (const char *, char *, size_t, const ImVec2 &, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputTextMultiline

// bool (const char *, const char *, char *, size_t, ImGuiInputTextFlags, ImGuiInputTextCallback, void *) InputTextWithHint

bool Tool::InputFloat(const char16_t* label, float* v, float step, float step_fast, const char16_t* format, ToolInputTextFlags flags) {
    return ImGui::InputFloat(utf16_to_utf8(label).c_str(), v, step, step_fast, utf16_to_utf8(format).c_str(), (ImGuiInputTextFlags)flags);
}

bool Tool::InputFloat2(const char16_t* label, std::shared_ptr<FloatArray> v, const char16_t* format, ToolInputTextFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::InputFloat2(utf16_to_utf8(label).c_str(), &v->GetVector()[0], utf16_to_utf8(format).c_str(), (ImGuiInputTextFlags)flags);
}

bool Tool::InputFloat3(const char16_t* label, std::shared_ptr<FloatArray> v, const char16_t* format, ToolInputTextFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::InputFloat3(utf16_to_utf8(label).c_str(), &v->GetVector()[0], utf16_to_utf8(format).c_str(), (ImGuiInputTextFlags)flags);
}

bool Tool::InputFloat4(const char16_t* label, std::shared_ptr<FloatArray> v, const char16_t* format, ToolInputTextFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::InputFloat4(utf16_to_utf8(label).c_str(), &v->GetVector()[0], utf16_to_utf8(format).c_str(), (ImGuiInputTextFlags)flags);
}

bool Tool::InputInt(const char16_t* label, int32_t* v, int32_t step, int32_t step_fast, ToolInputTextFlags flags) {
    return ImGui::InputInt(utf16_to_utf8(label).c_str(), v, step, step_fast, (ImGuiInputTextFlags)flags);
}

bool Tool::InputInt2(const char16_t* label, std::shared_ptr<Int32Array> v, ToolInputTextFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::InputInt2(utf16_to_utf8(label).c_str(), &v->GetVector()[0], (ImGuiInputTextFlags)flags);
}

bool Tool::InputInt3(const char16_t* label, std::shared_ptr<Int32Array> v, ToolInputTextFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::InputInt3(utf16_to_utf8(label).c_str(), &v->GetVector()[0], (ImGuiInputTextFlags)flags);
}

bool Tool::InputInt4(const char16_t* label, std::shared_ptr<Int32Array> v, ToolInputTextFlags flags) {
    RETURN_IF_NULL(v, false);
    return ImGui::InputInt4(utf16_to_utf8(label).c_str(), &v->GetVector()[0], (ImGuiInputTextFlags)flags);
}

// bool (const char *, double *, double, double, const char *, ImGuiInputTextFlags) InputDouble

// bool (const char *, ImGuiDataType, void *, const void *, const void *, const char *, ImGuiInputTextFlags) InputScalar

// bool (const char *, ImGuiDataType, void *, int, const void *, const void *, const char *, ImGuiInputTextFlags) InputScalarN

bool Tool::ColorEdit3(const char16_t* label, std::shared_ptr<FloatArray> col, ToolColorEditFlags flags) {
    RETURN_IF_NULL(col, false);
    return ImGui::ColorEdit3(utf16_to_utf8(label).c_str(), &col->GetVector()[0], (ImGuiColorEditFlags)flags);
}

bool Tool::ColorEdit4(const char16_t* label, std::shared_ptr<FloatArray> col, ToolColorEditFlags flags) {
    RETURN_IF_NULL(col, false);
    return ImGui::ColorEdit4(utf16_to_utf8(label).c_str(), &col->GetVector()[0], (ImGuiColorEditFlags)flags);
}

bool Tool::ColorPicker3(const char16_t* label, std::shared_ptr<FloatArray> col, ToolColorEditFlags flags) {
    RETURN_IF_NULL(col, false);
    return ImGui::ColorPicker3(utf16_to_utf8(label).c_str(), &col->GetVector()[0], (ImGuiColorEditFlags)flags);
}

bool Tool::ColorPicker4(const char16_t* label, std::shared_ptr<FloatArray> col, ToolColorEditFlags flags, float* ref_col) {
    RETURN_IF_NULL(col, false);
    return ImGui::ColorPicker4(utf16_to_utf8(label).c_str(), &col->GetVector()[0], (ImGuiColorEditFlags)flags, ref_col);
}

// bool (const char *, const ImVec4 &, ImGuiColorEditFlags, ImVec2) ColorButton

void Tool::SetColorEditOptions(ToolColorEditFlags flags) {
    ImGui::SetColorEditOptions((ImGuiColorEditFlags)flags);
}

bool Tool::TreeNode(const char16_t* label) {
    return ImGui::TreeNode(utf16_to_utf8(label).c_str());
}

bool Tool::TreeNode(const char16_t* str_id, const char16_t* fmt) {
    return ImGui::TreeNode(utf16_to_utf8(str_id).c_str(), utf16_to_utf8(fmt).c_str());
}

// bool (const void *, const char *, ...) TreeNode

// bool (const char *, const char *, __va_list_tag *) TreeNodeV

// bool (const void *, const char *, __va_list_tag *) TreeNodeV

bool Tool::TreeNodeEx(const char16_t* label, ToolTreeNodeFlags flags) {
    return ImGui::TreeNodeEx(utf16_to_utf8(label).c_str(), (ImGuiTreeNodeFlags)flags);
}

bool Tool::TreeNodeEx(const char16_t* str_id, ToolTreeNodeFlags flags, const char16_t* fmt) {
    return ImGui::TreeNodeEx(utf16_to_utf8(str_id).c_str(), (ImGuiTreeNodeFlags)flags, utf16_to_utf8(fmt).c_str());
}

// bool (const void *, ImGuiTreeNodeFlags, const char *, ...) TreeNodeEx

// bool (const char *, ImGuiTreeNodeFlags, const char *, __va_list_tag *) TreeNodeExV

// bool (const void *, ImGuiTreeNodeFlags, const char *, __va_list_tag *) TreeNodeExV

void Tool::TreePush(const char16_t* str_id) {
    ImGui::TreePush(utf16_to_utf8(str_id).c_str());
}

// void (const void *) TreePush

void Tool::TreePop() {
    ImGui::TreePop();
}

float Tool::GetTreeNodeToLabelSpacing() {
    return ImGui::GetTreeNodeToLabelSpacing();
}

bool Tool::CollapsingHeader(const char16_t* label, ToolTreeNodeFlags flags) {
    return ImGui::CollapsingHeader(utf16_to_utf8(label).c_str(), (ImGuiTreeNodeFlags)flags);
}

bool Tool::CollapsingHeader(const char16_t* label, bool* p_open, ToolTreeNodeFlags flags) {
    return ImGui::CollapsingHeader(utf16_to_utf8(label).c_str(), p_open, (ImGuiTreeNodeFlags)flags);
}

void Tool::SetNextItemOpen(bool is_open, ToolCond cond) {
    ImGui::SetNextItemOpen(is_open, (ImGuiCond)cond);
}

bool Tool::Selectable(const char16_t* label, bool selected, ToolSelectableFlags flags, Vector2F size) {
    return ImGui::Selectable(utf16_to_utf8(label).c_str(), selected, (ImGuiSelectableFlags)flags, toImVec2(size));
}

bool Tool::Selectable(const char16_t* label, bool* p_selected, ToolSelectableFlags flags, Vector2F size) {
    return ImGui::Selectable(utf16_to_utf8(label).c_str(), p_selected, (ImGuiSelectableFlags)flags, toImVec2(size));
}

// bool (const char *, int *, const char *const *, int, int) ListBox

// bool (const char *, int *, bool (*)(void *, int, const char **), void *, int, int) ListBox

bool Tool::ListBoxHeader(const char16_t* label, Vector2F size) {
    return ImGui::ListBoxHeader(utf16_to_utf8(label).c_str(), toImVec2(size));
}

bool Tool::ListBoxHeader(const char16_t* label, int32_t items_count, int32_t height_in_items) {
    return ImGui::ListBoxHeader(utf16_to_utf8(label).c_str(), items_count, height_in_items);
}

void Tool::ListBoxFooter() {
    ImGui::ListBoxFooter();
}

// void (const char *, const float *, int, int, const char *, float, float, ImVec2, int) PlotLines

// void (const char *, float (*)(void *, int), void *, int, int, const char *, float, float, ImVec2) PlotLines

// void (const char *, const float *, int, int, const char *, float, float, ImVec2, int) PlotHistogram

// void (const char *, float (*)(void *, int), void *, int, int, const char *, float, float, ImVec2) PlotHistogram

void Tool::Value(const char16_t* prefix, bool b) {
    ImGui::Value(utf16_to_utf8(prefix).c_str(), b);
}

void Tool::Value(const char16_t* prefix, int32_t v) {
    ImGui::Value(utf16_to_utf8(prefix).c_str(), v);
}

// void (const char *, unsigned int) Value

void Tool::Value(const char16_t* prefix, float v, const char16_t* float_format) {
    ImGui::Value(utf16_to_utf8(prefix).c_str(), v, float_format != nullptr ? utf16_to_utf8(float_format).c_str() : nullptr);
}

bool Tool::BeginMenuBar() {
    return ImGui::BeginMenuBar();
}

void Tool::EndMenuBar() {
    ImGui::EndMenuBar();
}

bool Tool::BeginMainMenuBar() {
    return ImGui::BeginMainMenuBar();
}

void Tool::EndMainMenuBar() {
    ImGui::EndMainMenuBar();
}

bool Tool::BeginMenu(const char16_t* label, bool enabled) {
    return ImGui::BeginMenu(utf16_to_utf8(label).c_str(), enabled);
}

void Tool::EndMenu() {
    ImGui::EndMenu();
}

bool Tool::MenuItem(const char16_t* label, const char16_t* shortcut, bool selected, bool enabled) {
    return ImGui::MenuItem(utf16_to_utf8(label).c_str(), shortcut != nullptr ? utf16_to_utf8(shortcut).c_str() : nullptr, selected, enabled);
}

bool Tool::MenuItem(const char16_t* label, const char16_t* shortcut, bool* p_selected, bool enabled) {
    return ImGui::MenuItem(utf16_to_utf8(label).c_str(), utf16_to_utf8(shortcut).c_str(), p_selected, enabled);
}

void Tool::BeginTooltip() {
    ImGui::BeginTooltip();
}

void Tool::EndTooltip() {
    ImGui::EndTooltip();
}

void Tool::SetTooltip(const char16_t* fmt) {
    ImGui::SetTooltip(utf16_to_utf8(fmt).c_str());
}

// void (const char *, __va_list_tag *) SetTooltipV

bool Tool::BeginPopup(const char16_t* str_id, ToolWindowFlags flags) {
    return ImGui::BeginPopup(utf16_to_utf8(str_id).c_str(), (ImGuiWindowFlags)flags);
}

bool Tool::BeginPopupModal(const char16_t* name, bool* p_open, ToolWindowFlags flags) {
    return ImGui::BeginPopupModal(utf16_to_utf8(name).c_str(), p_open, (ImGuiWindowFlags)flags);
}

void Tool::EndPopup() {
    ImGui::EndPopup();
}

void Tool::OpenPopup(const char16_t* str_id, ToolPopupFlags popup_flags) {
    ImGui::OpenPopup(utf16_to_utf8(str_id).c_str(), (ImGuiPopupFlags)popup_flags);
}

void Tool::OpenPopupOnItemClick(const char16_t* str_id, ToolPopupFlags popup_flags) {
    ImGui::OpenPopupOnItemClick(str_id != nullptr ? utf16_to_utf8(str_id).c_str() : nullptr, (ImGuiPopupFlags)popup_flags);
}

void Tool::CloseCurrentPopup() {
    ImGui::CloseCurrentPopup();
}

bool Tool::BeginPopupContextItem(const char16_t* str_id, ToolPopupFlags popup_flags) {
    return ImGui::BeginPopupContextItem(str_id != nullptr ? utf16_to_utf8(str_id).c_str() : nullptr, (ImGuiPopupFlags)popup_flags);
}

bool Tool::BeginPopupContextWindow(const char16_t* str_id, ToolPopupFlags popup_flags) {
    return ImGui::BeginPopupContextWindow(str_id != nullptr ? utf16_to_utf8(str_id).c_str() : nullptr, (ImGuiPopupFlags)popup_flags);
}

bool Tool::BeginPopupContextVoid(const char16_t* str_id, ToolPopupFlags popup_flags) {
    return ImGui::BeginPopupContextVoid(str_id != nullptr ? utf16_to_utf8(str_id).c_str() : nullptr, (ImGuiPopupFlags)popup_flags);
}

bool Tool::IsPopupOpen(const char16_t* str_id, ToolPopupFlags flags) {
    return ImGui::IsPopupOpen(utf16_to_utf8(str_id).c_str(), (ImGuiPopupFlags)flags);
}

void Tool::Columns(int32_t count, const char16_t* id, bool border) {
    ImGui::Columns(count, id != nullptr ? utf16_to_utf8(id).c_str() : nullptr, border);
}

void Tool::NextColumn() {
    ImGui::NextColumn();
}

int32_t Tool::GetColumnIndex() {
    return ImGui::GetColumnIndex();
}

float Tool::GetColumnWidth(int32_t column_index) {
    return ImGui::GetColumnWidth(column_index);
}

void Tool::SetColumnWidth(int32_t column_index, float width) {
    ImGui::SetColumnWidth(column_index, width);
}

float Tool::GetColumnOffset(int32_t column_index) {
    return ImGui::GetColumnOffset(column_index);
}

void Tool::SetColumnOffset(int32_t column_index, float offset_x) {
    ImGui::SetColumnOffset(column_index, offset_x);
}

int32_t Tool::GetColumnsCount() {
    return ImGui::GetColumnsCount();
}

bool Tool::BeginTabBar(const char16_t* str_id, ToolTabBarFlags flags) {
    return ImGui::BeginTabBar(utf16_to_utf8(str_id).c_str(), (ImGuiTabBarFlags)flags);
}

void Tool::EndTabBar() {
    ImGui::EndTabBar();
}

bool Tool::BeginTabItem(const char16_t* label, bool* p_open, ToolTabItemFlags flags) {
    return ImGui::BeginTabItem(utf16_to_utf8(label).c_str(), p_open, (ImGuiTabItemFlags)flags);
}

void Tool::EndTabItem() {
    ImGui::EndTabItem();
}

bool Tool::TabItemButton(const char16_t* label, ToolTabItemFlags flags) {
    return ImGui::TabItemButton(utf16_to_utf8(label).c_str(), (ImGuiTabItemFlags)flags);
}

void Tool::SetTabItemClosed(const char16_t* tab_or_docked_window_label) {
    ImGui::SetTabItemClosed(utf16_to_utf8(tab_or_docked_window_label).c_str());
}

// void (ImGuiID, const ImVec2 &, ImGuiDockNodeFlags, const ImGuiWindowClass *) DockSpace

// ImGuiID (ImGuiViewport *, ImGuiDockNodeFlags, const ImGuiWindowClass *) DockSpaceOverViewport

void Tool::SetNextWindowDockID(uint32_t dock_id, ToolCond cond) {
    ImGui::SetNextWindowDockID(dock_id, (ImGuiCond)cond);
}

// void (const ImGuiWindowClass *) SetNextWindowClass

uint32_t Tool::GetWindowDockID() {
    return ImGui::GetWindowDockID();
}

bool Tool::IsWindowDocked() {
    return ImGui::IsWindowDocked();
}

void Tool::LogToTTY(int32_t auto_open_depth) {
    ImGui::LogToTTY(auto_open_depth);
}

void Tool::LogToFile(int32_t auto_open_depth, const char16_t* filename) {
    ImGui::LogToFile(auto_open_depth, filename != nullptr ? utf16_to_utf8(filename).c_str() : nullptr);
}

void Tool::LogToClipboard(int32_t auto_open_depth) {
    ImGui::LogToClipboard(auto_open_depth);
}

void Tool::LogFinish() {
    ImGui::LogFinish();
}

void Tool::LogButtons() {
    ImGui::LogButtons();
}

void Tool::LogText(const char16_t* fmt) {
    ImGui::LogText(utf16_to_utf8(fmt).c_str());
}

bool Tool::BeginDragDropSource(ToolDragDropFlags flags) {
    return ImGui::BeginDragDropSource((ImGuiDragDropFlags)flags);
}

// bool (const char *, const void *, size_t, ImGuiCond) SetDragDropPayload

void Tool::EndDragDropSource() {
    ImGui::EndDragDropSource();
}

bool Tool::BeginDragDropTarget() {
    return ImGui::BeginDragDropTarget();
}

// const ImGuiPayload *(const char *, ImGuiDragDropFlags) AcceptDragDropPayload

void Tool::EndDragDropTarget() {
    ImGui::EndDragDropTarget();
}

// const ImGuiPayload *() GetDragDropPayload

void Tool::PushClipRect(Vector2F clip_rect_min, Vector2F clip_rect_max, bool intersect_with_current_clip_rect) {
    ImGui::PushClipRect(toImVec2(clip_rect_min), toImVec2(clip_rect_max), intersect_with_current_clip_rect);
}

void Tool::PopClipRect() {
    ImGui::PopClipRect();
}

void Tool::SetItemDefaultFocus() {
    ImGui::SetItemDefaultFocus();
}

void Tool::SetKeyboardFocusHere(int32_t offset) {
    ImGui::SetKeyboardFocusHere(offset);
}

bool Tool::IsItemHovered(ToolHoveredFlags flags) {
    return ImGui::IsItemHovered((ImGuiHoveredFlags)flags);
}

bool Tool::IsItemActive() {
    return ImGui::IsItemActive();
}

bool Tool::IsItemFocused() {
    return ImGui::IsItemFocused();
}

bool Tool::IsItemClicked(ToolMouseButton mouse_button) {
    return ImGui::IsItemClicked((ImGuiMouseButton)mouse_button);
}

bool Tool::IsItemVisible() {
    return ImGui::IsItemVisible();
}

bool Tool::IsItemEdited() {
    return ImGui::IsItemEdited();
}

bool Tool::IsItemActivated() {
    return ImGui::IsItemActivated();
}

bool Tool::IsItemDeactivated() {
    return ImGui::IsItemDeactivated();
}

bool Tool::IsItemDeactivatedAfterEdit() {
    return ImGui::IsItemDeactivatedAfterEdit();
}

bool Tool::IsItemToggledOpen() {
    return ImGui::IsItemToggledOpen();
}

bool Tool::IsAnyItemHovered() {
    return ImGui::IsAnyItemHovered();
}

bool Tool::IsAnyItemActive() {
    return ImGui::IsAnyItemActive();
}

bool Tool::IsAnyItemFocused() {
    return ImGui::IsAnyItemFocused();
}

Vector2F Tool::GetItemRectMin() {
    return toVector2F(ImGui::GetItemRectMin());
}

Vector2F Tool::GetItemRectMax() {
    return toVector2F(ImGui::GetItemRectMax());
}

Vector2F Tool::GetItemRectSize() {
    return toVector2F(ImGui::GetItemRectSize());
}

void Tool::SetItemAllowOverlap() {
    ImGui::SetItemAllowOverlap();
}

bool Tool::IsRectVisible(Vector2F size) {
    return ImGui::IsRectVisible(toImVec2(size));
}

bool Tool::IsRectVisible(Vector2F rect_min, Vector2F rect_max) {
    return ImGui::IsRectVisible(toImVec2(rect_min), toImVec2(rect_max));
}

// double () GetTime

int32_t Tool::GetFrameCount() {
    return ImGui::GetFrameCount();
}

// ImDrawList *() GetBackgroundDrawList

// ImDrawList *() GetForegroundDrawList

// ImDrawList *(ImGuiViewport *) GetBackgroundDrawList

// ImDrawList *(ImGuiViewport *) GetForegroundDrawList

// ImDrawListSharedData *() GetDrawListSharedData

const char16_t* Tool::GetStyleColorName(ToolCol idx) {
    returnStr = utf8_to_utf16(ImGui::GetStyleColorName((ImGuiCol)idx));
    return returnStr.c_str();
}

// void (ImGuiStorage *) SetStateStorage

// ImGuiStorage *() GetStateStorage

void Tool::CalcListClipping(int32_t items_count, float items_height, int32_t* out_items_display_start, int32_t* out_items_display_end) {
    ImGui::CalcListClipping(items_count, items_height, out_items_display_start, out_items_display_end);
}

bool Tool::BeginChildFrame(uint32_t id, Vector2F size, ToolWindowFlags flags) {
    return ImGui::BeginChildFrame(id, toImVec2(size), (ImGuiWindowFlags)flags);
}

void Tool::EndChildFrame() {
    ImGui::EndChildFrame();
}

Vector2F Tool::CalcTextSize(const char16_t* text, const char16_t* text_end, bool hide_text_after_double_hash, float wrap_width) {
    return toVector2F(ImGui::CalcTextSize(utf16_to_utf8(text).c_str(), text_end != nullptr ? utf16_to_utf8(text_end).c_str() : nullptr, hide_text_after_double_hash, wrap_width));
}

Vector4F Tool::ColorConvertU32ToFloat4(uint32_t in) {
    return toVector4F(ImGui::ColorConvertU32ToFloat4(in));
}

uint32_t Tool::ColorConvertFloat4ToU32(Vector4F in) {
    return ImGui::ColorConvertFloat4ToU32(toImVec4(in));
}

// void (float, float, float, float &, float &, float &) ColorConvertRGBtoHSV

// void (float, float, float, float &, float &, float &) ColorConvertHSVtoRGB

int32_t Tool::GetKeyIndex(ToolKey imgui_key) {
    return ImGui::GetKeyIndex((ImGuiKey)imgui_key);
}

bool Tool::IsKeyDown(int32_t user_key_index) {
    return ImGui::IsKeyDown(user_key_index);
}

bool Tool::IsKeyPressed(int32_t user_key_index, bool repeat) {
    return ImGui::IsKeyPressed(user_key_index, repeat);
}

bool Tool::IsKeyReleased(int32_t user_key_index) {
    return ImGui::IsKeyReleased(user_key_index);
}

int32_t Tool::GetKeyPressedAmount(int32_t key_index, float repeat_delay, float rate) {
    return ImGui::GetKeyPressedAmount(key_index, repeat_delay, rate);
}

void Tool::CaptureKeyboardFromApp(bool want_capture_keyboard_value) {
    ImGui::CaptureKeyboardFromApp(want_capture_keyboard_value);
}

bool Tool::IsMouseDown(ToolMouseButton button) {
    return ImGui::IsMouseDown((ImGuiMouseButton)button);
}

bool Tool::IsMouseClicked(ToolMouseButton button, bool repeat) {
    return ImGui::IsMouseClicked((ImGuiMouseButton)button, repeat);
}

bool Tool::IsMouseReleased(ToolMouseButton button) {
    return ImGui::IsMouseReleased((ImGuiMouseButton)button);
}

bool Tool::IsMouseDoubleClicked(ToolMouseButton button) {
    return ImGui::IsMouseDoubleClicked((ImGuiMouseButton)button);
}

bool Tool::IsMouseHoveringRect(Vector2F r_min, Vector2F r_max, bool clip) {
    return ImGui::IsMouseHoveringRect(toImVec2(r_min), toImVec2(r_max), clip);
}

// bool (const ImVec2 *) IsMousePosValid

bool Tool::IsAnyMouseDown() {
    return ImGui::IsAnyMouseDown();
}

Vector2F Tool::GetMousePos() {
    return toVector2F(ImGui::GetMousePos());
}

Vector2F Tool::GetMousePosOnOpeningCurrentPopup() {
    return toVector2F(ImGui::GetMousePosOnOpeningCurrentPopup());
}

bool Tool::IsMouseDragging(ToolMouseButton button, float lock_threshold) {
    return ImGui::IsMouseDragging((ImGuiMouseButton)button, lock_threshold);
}

Vector2F Tool::GetMouseDragDelta(ToolMouseButton button, float lock_threshold) {
    return toVector2F(ImGui::GetMouseDragDelta((ImGuiMouseButton)button, lock_threshold));
}

void Tool::ResetMouseDragDelta(ToolMouseButton button) {
    ImGui::ResetMouseDragDelta((ImGuiMouseButton)button);
}

// ImGuiMouseCursor () GetMouseCursor

void Tool::SetMouseCursor(ToolMouseCursor cursor_type) {
    ImGui::SetMouseCursor((ImGuiMouseCursor)cursor_type);
}

void Tool::CaptureMouseFromApp(bool want_capture_mouse_value) {
    ImGui::CaptureMouseFromApp(want_capture_mouse_value);
}

const char16_t* Tool::GetClipboardText() {
    returnStr = utf8_to_utf16(ImGui::GetClipboardText());
    return returnStr.c_str();
}

void Tool::SetClipboardText(const char16_t* text) {
    ImGui::SetClipboardText(utf16_to_utf8(text).c_str());
}

void Tool::LoadIniSettingsFromDisk(const char16_t* ini_filename) {
    ImGui::LoadIniSettingsFromDisk(utf16_to_utf8(ini_filename).c_str());
}

// void (const char *, size_t) LoadIniSettingsFromMemory

void Tool::SaveIniSettingsToDisk(const char16_t* ini_filename) {
    ImGui::SaveIniSettingsToDisk(utf16_to_utf8(ini_filename).c_str());
}

// const char *(size_t *) SaveIniSettingsToMemory

// bool (const char *, size_t, size_t, size_t, size_t, size_t, size_t) DebugCheckVersionAndDataLayout

// void (void *(*)(size_t, void *), void (*)(void *, void *), void *) SetAllocatorFunctions

// void *(size_t) MemAlloc

// void (void *) MemFree

// ImGuiPlatformIO &() GetPlatformIO

// ImGuiViewport *() GetMainViewport

void Tool::UpdatePlatformWindows() {
    ImGui::UpdatePlatformWindows();
}

// void (void *, void *) RenderPlatformWindowsDefault

void Tool::DestroyPlatformWindows() {
    ImGui::DestroyPlatformWindows();
}

// ImGuiViewport *(ImGuiID) FindViewportByID

// ImGuiViewport *(void *) FindViewportByPlatformHandle

}  // namespace Altseed2