#include "Tool.h"
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

namespace Altseed {

std::shared_ptr<Tool> Tool::instance_;

std::shared_ptr<Tool>& Tool::GetInstance() { return instance_; }

bool Tool::Initialize(std::shared_ptr<Graphics> graphics) {
    instance_ = MakeAsdShared<Tool>(graphics);
    return true;
}

void Tool::Terminate() { instance_ = nullptr; }

Tool::Tool(std::shared_ptr<Graphics> graphics) {
    auto g = graphics->GetGraphicsLLGI();
    auto p = graphics->GetLLGIPlatform();
    auto w = graphics->GetLLGIWindow();

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForVulkan(w->GetGlfwWindow(), true);

    LLGI::DeviceType deviceType = LLGI::DeviceType::Default;
#ifdef ENABLE_VULKAN
    deviceType = LLGI::DeviceType::Vulkan;
#endif

#ifdef ENABLE_VULKAN
    platform_ = std::make_shared<ImguiPlatformVulkan>(g, p);
#elif defined(_WIN32)
    platform_ = std::make_shared<ImguiPlatformDX12>(g);
#elif defined(__APPLE__)
    platform_ = std::make_shared<ImguiPlatformMetal>(g);
#endif
}

Tool::~Tool() {
    platform_.reset();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Tool::NewFrame() {
    platform_->NewFrame(Graphics::GetInstance()->GetCommandList()->GetCurrentRenderPass());
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Tool::Render() {
    ImGui::Render();
    
#if defined(__APPLE__)
    // HACK for retina
    ImGui::GetDrawData()->FramebufferScale = ImVec2(1,1);
#endif
    
    platform_->RenderDrawData(ImGui::GetDrawData(), Graphics::GetInstance()->GetCommandList()->GetLL());
}

inline ImVec2 toImVec2(const Vector2F& v) { return ImVec2(v.X, v.Y); }

inline ImVec4 toImVec4(const Vector4F& v) { return ImVec4(v.X, v.Y, v.Z, v.W); }

bool Tool::Begin(const char16_t* name, ToolWindow flags) { return ImGui::Begin(utf16_to_utf8(name).c_str(), nullptr, static_cast<ImGuiWindowFlags>(flags)); }

void Tool::End() { ImGui::End(); }

void Tool::Dummy(Vector2F size) { ImGui::Dummy(toImVec2(size)); }

void Tool::Text(const char16_t* text) { ImGui::Text("%s", utf16_to_utf8(text).c_str()); }

void Tool::TextUnformatted(const char16_t* text) { ImGui::TextUnformatted(utf16_to_utf8(text).c_str()); }

void Tool::TextWrapped(const char16_t* text) { ImGui::TextWrapped("%s", utf16_to_utf8(text).c_str());  };

void Tool::TextColored(const Vector4F color, const char16_t* text) { ImGui::TextColored(toImVec4(color), "%s", utf16_to_utf8(text).c_str()); }

void Tool::TextDisabled(const char16_t* text) { ImGui::TextDisabled("%s", utf16_to_utf8(text).c_str()); }

void Tool::BulletText(const char16_t* text) { ImGui::BulletText("%s", utf16_to_utf8(text).c_str()); }

void Tool::LabelText(const char16_t* label, const char16_t* text) { ImGui::LabelText(utf16_to_utf8(label).c_str(), "%s", utf16_to_utf8(text).c_str()); }

bool Tool::CollapsingHeader(const char16_t* label, ToolTreeNode flags) { return ImGui::CollapsingHeader(utf16_to_utf8(label).c_str(), static_cast<ImGuiTreeNodeFlags>(flags)); }

bool Tool::TreeNode(const char16_t* label) { return ImGui::TreeNode(utf16_to_utf8(label).c_str()); }

bool Tool::TreeNodeEx(const char16_t* label, ToolTreeNode flags) { return ImGui::TreeNodeEx(utf16_to_utf8(label).c_str(), static_cast<ImGuiTreeNodeFlags>(flags)); }

void Tool::TreePop() { ImGui::TreePop(); }

void Tool::SetNextItemOpen(bool is_open, ToolCond cond) { ImGui::SetNextItemOpen(is_open, static_cast<ImGuiCond>(cond)); }

bool Tool::Button(const char16_t* label, const Vector2F size) { return ImGui::Button(utf16_to_utf8(label).c_str(), toImVec2(size)); }

bool Tool::CheckBox(const char16_t* label, bool* is_open) { return ImGui::Checkbox(utf16_to_utf8(label).c_str(), is_open); }

bool Tool::RadioButton(const char16_t* label, bool active) { return ImGui::RadioButton(utf16_to_utf8(label).c_str(), active); }

bool Tool::ArrowButton(const char16_t* id, ToolDir dir) { return ImGui::ArrowButton(utf16_to_utf8(id).c_str(), static_cast<ImGuiDir>(dir)); }

bool Combo(const char16_t* label, int* current, const char16_t* items_separated_by_zeros) {
    return ImGui::Combo(utf16_to_utf8(label).c_str(), current, utf16_to_utf8(items_separated_by_zeros).c_str());
}

bool ListBox(const char16_t* label, int* current, const char* items[], size_t count) {
    return ImGui::ListBox(utf16_to_utf8(label).c_str(), current, items, count);
}

bool Tool::InvisibleButton(const char16_t* label, Vector2F size) {
    return ImGui::InvisibleButton(utf16_to_utf8(label).c_str(), toImVec2(size));
}

bool Tool::Selectable(const char16_t* label, bool* selected, ToolSelectable flags) {
    return ImGui::Selectable(utf16_to_utf8(label).c_str(), selected, static_cast<ImGuiSelectableFlags>(flags));
}

bool Tool::InputText(const char16_t* label, char* buf, size_t buf_size, ToolInputText flags) {
    return ImGui::InputText(utf16_to_utf8(label).c_str(), buf, buf_size, static_cast<ImGuiInputTextFlags>(flags));
}

bool Tool::InputTextWithHint(const char16_t* label, const char16_t* hint, char* buf, size_t buf_size, ToolInputText flags) {
    return ImGui::InputTextWithHint(utf16_to_utf8(label).c_str(), utf16_to_utf8(hint).c_str(), buf, buf_size, static_cast<ImGuiInputTextFlags>(flags));
}

bool Tool::InputTextMultiline(const char16_t* label, char* buf, size_t buf_size, Vector2F size, ToolInputText flags) {
    return ImGui::InputTextMultiline(utf16_to_utf8(label).c_str(), buf, buf_size, toImVec2(size), static_cast<ImGuiInputTextFlags>(flags));
}

bool Tool::InputInt(const char16_t* label, int* v) { return ImGui::InputInt(utf16_to_utf8(label).c_str(), v); }

bool Tool::InputInt2(const char16_t* label, int* array) { return ImGui::InputInt2(utf16_to_utf8(label).c_str(), array); }

bool Tool::InputInt3(const char16_t* label, int* array) { return ImGui::InputInt3(utf16_to_utf8(label).c_str(), array); }

bool Tool::InputInt4(const char16_t* label, int* array) { return ImGui::InputInt4(utf16_to_utf8(label).c_str(), array); }

bool Tool::InputFloat(const char16_t* label, float* v) { return ImGui::InputFloat(utf16_to_utf8(label).c_str(), v); }

bool Tool::InputFloat2(const char16_t* label, float* array) { return ImGui::InputFloat2(utf16_to_utf8(label).c_str(), array); }

bool Tool::InputFloat3(const char16_t* label, float* array) { return ImGui::InputFloat3(utf16_to_utf8(label).c_str(), array); }

bool Tool::InputFloat4(const char16_t* label, float* array) { return ImGui::InputFloat4(utf16_to_utf8(label).c_str(), array); }

bool Tool::DragInt(const char16_t* label, int* v, float speed, int v_min, int v_max) {
    return ImGui::DragInt(utf16_to_utf8(label).c_str(), v, speed, v_min, v_max);
}

bool Tool::SliderInt(const char16_t* label, int* v, float speed, int v_min, int v_max) {
    return ImGui::SliderInt(utf16_to_utf8(label).c_str(), v, v_min, v_max);
}

bool Tool::SliderInt2(const char16_t* label, int* array, float speed, int v_min, int v_max) {
    return ImGui::SliderInt2(utf16_to_utf8(label).c_str(), array, v_min, v_max);
}

bool Tool::SliderInt3(const char16_t* label, int* array, float speed, int v_min, int v_max) {
    return ImGui::SliderInt3(utf16_to_utf8(label).c_str(), array, v_min, v_max);
}

bool Tool::SliderInt4(const char16_t* label, int* array, float speed, int v_min, int v_max) {
    return ImGui::SliderInt4(utf16_to_utf8(label).c_str(), array, v_min, v_max);
}

bool Tool::SliderFloat(const char16_t* label, float* v, float speed, int v_min, int v_max) {
    return ImGui::SliderFloat(utf16_to_utf8(label).c_str(), v, v_min, v_max);
}

bool Tool::SliderFloat2(const char16_t* label, float* array, float speed, int v_min, int v_max) {
    return ImGui::SliderFloat2(utf16_to_utf8(label).c_str(), array, v_min, v_max);
}

bool Tool::SliderFloat3(const char16_t* label, float* array, float speed, int v_min, int v_max) {
    return ImGui::SliderFloat3(utf16_to_utf8(label).c_str(), array, v_min, v_max);
}

bool Tool::SliderFloat4(const char16_t* label, float* array, float speed, int v_min, int v_max) {
    return ImGui::SliderFloat4(utf16_to_utf8(label).c_str(), array, v_min, v_max);
}

bool Tool::SliderAngle(const char16_t* label, float* angle) { return ImGui::SliderAngle(utf16_to_utf8(label).c_str(), angle); }

bool Tool::VSliderInt(const char16_t* label, Vector2F size, int* v, float v_min, float v_max) {
    return ImGui::VSliderInt(utf16_to_utf8(label).c_str(), toImVec2(size), v, v_min, v_max);
}

bool Tool::VSliderFloat(const char16_t* label, Vector2F size, float* v, float v_min, float v_max) {
    return ImGui::VSliderFloat(utf16_to_utf8(label).c_str(), toImVec2(size), v, v_min, v_max);
}

bool Tool::DragFloat(const char16_t* label, float* v, float speed, int v_min, int v_max) {
    return ImGui::DragFloat(utf16_to_utf8(label).c_str(), v, speed, v_min, v_max);
}
bool Tool::DragIntRange2(const char16_t* label, int* current_min, int* current_max, float speed, int v_min, int v_max) {
    return ImGui::DragIntRange2(utf16_to_utf8(label).c_str(), current_min, current_max, speed, v_min, v_max);
}

bool Tool::DragFloatRange2(const char16_t* label, float* current_min, float* current_max, float speed, int v_min, int v_max) {
    return ImGui::DragFloatRange2(utf16_to_utf8(label).c_str(), current_min, current_max, speed, v_min, v_max);
}

bool Tool::ColorEdit3(const char16_t* label, float* color, ToolColorEdit flags) {
    return ImGui::ColorEdit3(utf16_to_utf8(label).c_str(), color, static_cast<ImGuiColorEditFlags>(flags));
}

bool Tool::ColorEdit4(const char16_t* label, float* color, ToolColorEdit flags) {
    return ImGui::ColorEdit4(utf16_to_utf8(label).c_str(), color, static_cast<ImGuiColorEditFlags>(flags));
}

bool Tool::BeginPopup(const char16_t* label) { return ImGui::BeginPopup(utf16_to_utf8(label).c_str()); }

bool Tool::BeginPopupModal(const char16_t* label) { return ImGui::BeginPopupModal(utf16_to_utf8(label).c_str()); }

void Tool::EndPopup() { ImGui::EndPopup(); }

bool Tool::BeginChild(const char16_t* label, Vector2F size, bool border, ToolWindow flags) {
    return ImGui::BeginChild(utf16_to_utf8(label).c_str(), toImVec2(size), border, static_cast<ImGuiWindowFlags>(flags));
}

void Tool::EndChild() { ImGui::EndChild(); }

bool Tool::BeginMenuBar() { return ImGui::BeginMenuBar(); }

void Tool::EndMenuBar() { ImGui::EndMenuBar(); }

bool Tool::BeginMenu(const char16_t* label, bool enabled) { return ImGui::BeginMenu(utf16_to_utf8(label).c_str(), enabled); }

void Tool::EndMenu() { ImGui::EndMenu(); }

bool Tool::MenuItem(const char16_t* label, const char16_t* shortcut, bool selected, bool enabled) {
    return ImGui::MenuItem(utf16_to_utf8(label).c_str(), utf16_to_utf8(shortcut).c_str(), selected, enabled);
}

bool Tool::BeginTabBar(const char16_t* id, ToolTabBar flags) {
    return ImGui::BeginTabBar(utf16_to_utf8(id).c_str(), static_cast<ImGuiTabBarFlags>(flags));
}

void Tool::EndTabBar() { ImGui::EndTabBar(); }

bool Tool::BeginTabItem(const char16_t* label) {
    return ImGui::BeginTabItem(utf16_to_utf8(label).c_str());
}

bool Tool::EndTabItem() { ImGui::EndTabItem(); }

void Tool::Indent() { ImGui::Indent(); }

void Tool::Unindent() { ImGui::Unindent(); }

void Tool::Separator() { ImGui::Separator(); }

void Tool::SetToolTip(const char16_t* text) { ImGui::SetTooltip("%s", utf16_to_utf8(text).c_str()); }

void Tool::BeginTooltip() { ImGui::BeginTooltip(); }

void Tool::EndTooltip() { ImGui::EndTooltip(); }

void Tool::NewLine() { ImGui::NewLine(); }

void Tool::SameLine() { ImGui::SameLine(); }

void Tool::PushTextWrapPos(float wrap_local_pos_x) { ImGui::PushTextWrapPos(wrap_local_pos_x); }

void Tool::PopTextWrapPos() { ImGui::PopTextWrapPos(); }

void Tool::SetNextItemWidth(int width) { ImGui::SetNextItemWidth(width); }

void Tool::PushButtonRepeat(bool repeat) { ImGui::PushButtonRepeat(repeat); }

void Tool::PopButtonRepeat() { ImGui::PopButtonRepeat(); }

void Tool::Columns(int count, bool border) { ImGui::Columns(count, static_cast<const char*>(__null), border); }

void Tool::PushID(int id) { ImGui::PushID(id); }

void Tool::PopID() { ImGui::PopID(); }

bool Tool::IsItemActive() { return ImGui::IsItemActive(); }

bool Tool::IsItemHovered() { return ImGui::IsItemHovered(); }

void Tool::SetScrollHere() { ImGui::SetScrollHere(); }

void Tool::SetScrollHereX() { ImGui::SetScrollHereX(); }

void Tool::SetScrollHereY() { ImGui::SetScrollHereY(); }

float Tool::GetTextLineHeight() { return ImGui::GetTextLineHeight(); }

float Tool::GetFontSize() { return ImGui::GetFontSize(); }

Vector2F Tool::GetWindowSize() {
    auto size = ImGui::GetWindowSize();
    return Vector2F(size.x, size.y);
}

void Tool::SetWindowSize(Vector2F size) { ImGui::SetWindowSize(toImVec2(size)); }

bool Tool::IsMousePosValid() { return ImGui::IsMousePosValid(); }

bool Tool::IsMouseDragging() { return ImGui::IsMouseDragging(); }

bool Tool::IsMouseDoubleClicked(int button) {
    return ImGui::IsMouseDoubleClicked(button);
}

Vector2F Tool::GetMouseDragDelta(int button) {
    auto d = ImGui::GetMouseDragDelta(button);
    return Vector2F(d.x, d.y);
}

void Tool::ResetMouseDragDelta(int button) { ImGui::ResetMouseDragDelta(button); }

void Tool::SetNextWindowContentSize(Vector2F size) { ImGui::SetNextWindowContentSize(toImVec2(size)); }

}  // namespace Altseed
