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
#include "../Logger/Log.h"

namespace Altseed {

std::shared_ptr<Tool> Tool::instance_;

std::shared_ptr<Tool>& Tool::GetInstance() { return instance_; }

bool Tool::Initialize(std::shared_ptr<Graphics> graphics) {
    instance_ = MakeAsdShared<Tool>(graphics);
    return true;
}

void Tool::Terminate() { instance_ = nullptr; }

Tool::Tool(std::shared_ptr<Graphics> graphics) {
    graphics_ = graphics;

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

Tool::~Tool() { OnTerminating(); }

void Tool::OnTerminating() {
    if (platform_ != nullptr) {
        platform_.reset();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

ToolUsage Tool::GetToolUsage() const { return toolUsageMode_; }

void Tool::SetToolUsage(ToolUsage toolUsageMode) { toolUsageMode_ = toolUsageMode; }

void Tool::NewFrame() {
    if (toolUsageMode_ == ToolUsage::Main) {
        auto renderPass = Graphics::GetInstance()->GetCommandList()->GetActualScreenRenderPass();
        Graphics::GetInstance()->GetCommandList()->SetIsPresentScreenBufferDirectly(false);

        platform_->NewFrame(renderPass);
    } else if (toolUsageMode_ == ToolUsage::Overwrapped) {
        // Very Dirty hack
        // auto renderPass = Graphics::GetInstance()->GetCommandList()->GetScreenRenderPass();
        auto renderPass = Graphics::GetInstance()->GetCommandList()->GetActualScreenRenderPass();
        Graphics::GetInstance()->GetCommandList()->SetIsPresentScreenBufferDirectly(true);
        platform_->NewFrame(renderPass);
    }

    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Tool::Render() {
    if (toolUsageMode_ == ToolUsage::Main) {
        RenderPassParameter parameter;
        parameter.IsColorCleared = true;
        parameter.IsDepthCleared = false;
        Graphics::GetInstance()->GetCommandList()->SetRenderTargetWithScreen(parameter);
    } else if (toolUsageMode_ == ToolUsage::Overwrapped) {
        // Very dirty hack
        RenderPassParameter parameter;
        parameter.IsColorCleared = false;
        parameter.IsDepthCleared = false;
        Graphics::GetInstance()->GetCommandList()->PresentInternal();
        Graphics::GetInstance()->GetCommandList()->SetRenderTargetWithScreen(parameter);
        Graphics::GetInstance()->GetCommandList()->SetIsPresentScreenBufferDirectly(false);
    }

    ImGui::Render();

    platform_->RenderDrawData(ImGui::GetDrawData(), Graphics::GetInstance()->GetCommandList()->GetLL());
}

inline ImVec2 toImVec2(const Vector2F& v) { return ImVec2(v.X, v.Y); }

inline ImVec4 toImVec4(const Vector4F& v) { return ImVec4(v.X, v.Y, v.Z, v.W); }

inline ImVec4 toImVec4(const Color& v) { return ImVec4(v.R / 255.0f, v.G / 255.0f, v.B / 255.0f, v.A / 255.0f); }

inline Vector2F toVector2F(const ImVec2& v) { return Vector2F(v.x, v.y); }

inline Color toColor(const ImVec4& v) { return Color(v.x * 255, v.y * 255, v.z * 255, v.w * 255); }

const ImWchar* toImGlyphRanges(ImGuiIO& io, ToolGlyphRanges ranges) {
    switch (ranges) {
        case ToolGlyphRanges::Cyrillic:
            return io.Fonts->GetGlyphRangesCyrillic();
        case ToolGlyphRanges::Japanese:
            return io.Fonts->GetGlyphRangesJapanese();
        case ToolGlyphRanges::ChineseFull:
            return io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
        case ToolGlyphRanges::Korean:
            return io.Fonts->GetGlyphRangesKorean();

        default:
            Log::GetInstance()->Error(LogCategory::Core, u"Unexpected FontGlyphRange, use 'Default' instead.");
        case ToolGlyphRanges::Default:
            return io.Fonts->GetGlyphRangesDefault();
    }
}

bool Tool::AddFontFromFileTTF(const char16_t* path, float sizePixels, ToolGlyphRanges ranges) {
    auto& io = ImGui::GetIO();
    auto path_ = utf16_to_utf8(path);
    auto font = io.Fonts->AddFontFromFileTTF(path_.c_str(), sizePixels, nullptr, toImGlyphRanges(io, ranges));

    if (font == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"Tool::AddFonrFromFileTTF: Failed to load font from '%s'", path_.c_str());
        return false;
    }

    return true;
}

bool Tool::Begin(const char16_t* name, ToolWindow flags) {
    auto str = utf16_to_utf8(name);
    if (str.length() > 0) {
        return ImGui::Begin(str.c_str(), nullptr, static_cast<ImGuiWindowFlags>(flags));
    } else {
        Log::GetInstance()->Warn(LogCategory::Core, u"Tool::Begin: Window's name must contains at least one character");
        return false;
    }
}

void Tool::End() { ImGui::End(); }

void Tool::Dummy(Vector2F size) { ImGui::Dummy(toImVec2(size)); }

void Tool::Text(const char16_t* text) { ImGui::Text("%s", utf16_to_utf8(text).c_str()); }

void Tool::TextUnformatted(const char16_t* text) { ImGui::TextUnformatted(utf16_to_utf8(text).c_str()); }

void Tool::TextWrapped(const char16_t* text) { ImGui::TextWrapped("%s", utf16_to_utf8(text).c_str()); };

void Tool::TextColored(const Color color, const char16_t* text) { ImGui::TextColored(toImVec4(color), "%s", utf16_to_utf8(text).c_str()); }

void Tool::TextDisabled(const char16_t* text) { ImGui::TextDisabled("%s", utf16_to_utf8(text).c_str()); }

void Tool::BulletText(const char16_t* text) { ImGui::BulletText("%s", utf16_to_utf8(text).c_str()); }

void Tool::LabelText(const char16_t* label, const char16_t* text) {
    ImGui::LabelText(utf16_to_utf8(label).c_str(), "%s", utf16_to_utf8(text).c_str());
}

bool Tool::CollapsingHeader(const char16_t* label, ToolTreeNode flags) {
    return ImGui::CollapsingHeader(utf16_to_utf8(label).c_str(), static_cast<ImGuiTreeNodeFlags>(flags));
}

bool Tool::TreeNode(const char16_t* label) { return ImGui::TreeNode(utf16_to_utf8(label).c_str()); }

bool Tool::TreeNodeEx(const char16_t* label, ToolTreeNode flags) {
    return ImGui::TreeNodeEx(utf16_to_utf8(label).c_str(), static_cast<ImGuiTreeNodeFlags>(flags));
}

void Tool::TreePop() { ImGui::TreePop(); }

void Tool::SetNextItemOpen(bool is_open, ToolCond cond) { ImGui::SetNextItemOpen(is_open, static_cast<ImGuiCond>(cond)); }

bool Tool::Button(const char16_t* label, const Vector2F size) { return ImGui::Button(utf16_to_utf8(label).c_str(), toImVec2(size)); }

bool Tool::CheckBox(const char16_t* label, bool* is_open) { return ImGui::Checkbox(utf16_to_utf8(label).c_str(), is_open); }

bool Tool::RadioButton(const char16_t* label, bool active) { return ImGui::RadioButton(utf16_to_utf8(label).c_str(), active); }

bool Tool::ArrowButton(const char16_t* id, ToolDir dir) {
    return ImGui::ArrowButton(utf16_to_utf8(id).c_str(), static_cast<ImGuiDir>(dir));
}

bool Tool::ListBox(const char16_t* label, int32_t* current, const char16_t* items_separated_by_tabs, int32_t height_in_items) {
    auto tmp = split(items_separated_by_tabs, u'\t');
    std::vector<std::string> itemsVector;
    for (int32_t i = 0; i < tmp.size(); i++) {
        itemsVector.push_back(utf16_to_utf8(tmp[i]));
    }
    std::vector<char*> items;
    for (int32_t i = 0; i < tmp.size(); i++) {
        items.push_back(itemsVector[i].data());
    }
    return ImGui::ListBox(utf16_to_utf8(label).c_str(), current, &items[0], itemsVector.size(), height_in_items);
}

bool Tool::InvisibleButton(const char16_t* label, Vector2F size) {
    return ImGui::InvisibleButton(utf16_to_utf8(label).c_str(), toImVec2(size));
}

bool Tool::Selectable(const char16_t* label, bool* selected, ToolSelectable flags) {
    return ImGui::Selectable(utf16_to_utf8(label).c_str(), selected, static_cast<ImGuiSelectableFlags>(flags));
}

static std::u16string tempInputText;

const char16_t* Tool::InputText(const char16_t* label, const char16_t* input, int32_t max_length, ToolInputText flags) {
    std::u16string u16str(input);
    auto buf = new char[max_length + 1]{};
    utf16_to_utf8(u16str).copy(buf, u16str.size());
    auto res = ImGui::InputText(utf16_to_utf8(label).c_str(), buf, max_length + 1, static_cast<ImGuiInputTextFlags>(flags));
    if (res) {
        tempInputText = utf8_to_utf16(buf);
        delete[] buf;
        return tempInputText.c_str();
    } else {
        tempInputText = u"";
        delete[] buf;
        return nullptr;
    }
}

const char16_t* Tool::InputTextWithHint(
        const char16_t* label, const char16_t* hint, const char16_t* input, int32_t max_length, ToolInputText flags) {
    std::u16string u16str(input);
    auto buf = new char[u16str.size() + 5]{};
    utf16_to_utf8(u16str).copy(buf, u16str.size());
    auto res = ImGui::InputTextWithHint(
            utf16_to_utf8(label).c_str(), utf16_to_utf8(hint).c_str(), buf, max_length + 1, static_cast<ImGuiInputTextFlags>(flags));
    if (res) {
        tempInputText = utf8_to_utf16(buf);
        delete[] buf;
        return tempInputText.c_str();
    } else {
        tempInputText = u"";
        delete[] buf;
        return nullptr;
    }
}

const char16_t* Tool::InputTextMultiline(
        const char16_t* label, const char16_t* input, int32_t max_length, Vector2F size, ToolInputText flags) {
    std::u16string u16str(input);
    auto buf = new char[max_length + 1]{};
    utf16_to_utf8(u16str).copy(buf, u16str.size());
    auto res = ImGui::InputTextMultiline(
            utf16_to_utf8(label).c_str(), buf, max_length + 1, toImVec2(size), static_cast<ImGuiInputTextFlags>(flags));
    if (res) {
        tempInputText = utf8_to_utf16(buf);
        delete[] buf;
        return tempInputText.c_str();
    } else {
        tempInputText = u"";
        delete[] buf;
        return nullptr;
    }
}

bool Tool::InputInt(const char16_t* label, int32_t* v) { return ImGui::InputInt(utf16_to_utf8(label).c_str(), v); }

bool Tool::InputInt2(const char16_t* label, std::shared_ptr<Int32Array> array) {
    return ImGui::InputInt2(utf16_to_utf8(label).c_str(), &array->GetVector()[0]);
}

bool Tool::InputInt3(const char16_t* label, std::shared_ptr<Int32Array> array) {
    return ImGui::InputInt3(utf16_to_utf8(label).c_str(), &array->GetVector()[0]);
}

bool Tool::InputInt4(const char16_t* label, std::shared_ptr<Int32Array> array) {
    return ImGui::InputInt4(utf16_to_utf8(label).c_str(), &array->GetVector()[0]);
}

bool Tool::InputFloat(const char16_t* label, float* v) { return ImGui::InputFloat(utf16_to_utf8(label).c_str(), v); }

bool Tool::InputFloat2(const char16_t* label, std::shared_ptr<FloatArray> array) {
    return ImGui::InputFloat2(utf16_to_utf8(label).c_str(), &array->GetVector()[0]);
}

bool Tool::InputFloat3(const char16_t* label, std::shared_ptr<FloatArray> array) {
    return ImGui::InputFloat3(utf16_to_utf8(label).c_str(), &array->GetVector()[0]);
}

bool Tool::InputFloat4(const char16_t* label, std::shared_ptr<FloatArray> array) {
    return ImGui::InputFloat4(utf16_to_utf8(label).c_str(), &array->GetVector()[0]);
}

bool Tool::DragInt(const char16_t* label, int32_t* v, float speed, int32_t v_min, int32_t v_max) {
    return ImGui::DragInt(utf16_to_utf8(label).c_str(), v, speed, v_min, v_max);
}

bool Tool::SliderInt(const char16_t* label, int32_t* v, float speed, int32_t v_min, int32_t v_max) {
    return ImGui::SliderInt(utf16_to_utf8(label).c_str(), v, v_min, v_max);
}

bool Tool::SliderInt2(const char16_t* label, std::shared_ptr<Int32Array> array, float speed, int32_t v_min, int32_t v_max) {
    return ImGui::SliderInt2(utf16_to_utf8(label).c_str(), &array->GetVector()[0], v_min, v_max);
}

bool Tool::SliderInt3(const char16_t* label, std::shared_ptr<Int32Array> array, float speed, int32_t v_min, int32_t v_max) {
    return ImGui::SliderInt3(utf16_to_utf8(label).c_str(), &array->GetVector()[0], v_min, v_max);
}

bool Tool::SliderInt4(const char16_t* label, std::shared_ptr<Int32Array> array, float speed, int32_t v_min, int32_t v_max) {
    return ImGui::SliderInt4(utf16_to_utf8(label).c_str(), &array->GetVector()[0], v_min, v_max);
}

bool Tool::SliderFloat(const char16_t* label, float* v, float speed, float v_min, float v_max) {
    return ImGui::SliderFloat(utf16_to_utf8(label).c_str(), v, v_min, v_max);
}

bool Tool::SliderFloat2(const char16_t* label, std::shared_ptr<FloatArray> array, float speed, float v_min, float v_max) {
    return ImGui::SliderFloat2(utf16_to_utf8(label).c_str(), &array->GetVector()[0], v_min, v_max);
}

bool Tool::SliderFloat3(const char16_t* label, std::shared_ptr<FloatArray> array, float speed, float v_min, float v_max) {
    return ImGui::SliderFloat3(utf16_to_utf8(label).c_str(), &array->GetVector()[0], v_min, v_max);
}

bool Tool::SliderFloat4(const char16_t* label, std::shared_ptr<FloatArray> array, float speed, float v_min, float v_max) {
    return ImGui::SliderFloat4(utf16_to_utf8(label).c_str(), &array->GetVector()[0], v_min, v_max);
}

bool Tool::SliderAngle(const char16_t* label, float* angle) { return ImGui::SliderAngle(utf16_to_utf8(label).c_str(), angle); }

bool Tool::VSliderInt(const char16_t* label, Vector2F size, int32_t* v, float v_min, float v_max) {
    return ImGui::VSliderInt(utf16_to_utf8(label).c_str(), toImVec2(size), v, v_min, v_max);
}

bool Tool::VSliderFloat(const char16_t* label, Vector2F size, float* v, float v_min, float v_max) {
    return ImGui::VSliderFloat(utf16_to_utf8(label).c_str(), toImVec2(size), v, v_min, v_max);
}

bool Tool::DragFloat(const char16_t* label, float* v, float speed, float v_min, float v_max) {
    return ImGui::DragFloat(utf16_to_utf8(label).c_str(), v, speed, v_min, v_max);
}
bool Tool::DragIntRange2(const char16_t* label, int32_t* current_min, int32_t* current_max, float speed, int32_t v_min, int32_t v_max) {
    return ImGui::DragIntRange2(utf16_to_utf8(label).c_str(), current_min, current_max, speed, v_min, v_max);
}

bool Tool::DragFloatRange2(const char16_t* label, float* current_min, float* current_max, float speed, float v_min, float v_max) {
    return ImGui::DragFloatRange2(utf16_to_utf8(label).c_str(), current_min, current_max, speed, v_min, v_max);
}

bool Tool::ColorEdit3(const char16_t* label, Color* color, ToolColorEdit flags) {
    float v[3];
    v[0] = color->R / 255.0f;
    v[1] = color->G / 255.0f;
    v[2] = color->B / 255.0f;
    auto res = ImGui::ColorEdit3(utf16_to_utf8(label).c_str(), v, static_cast<ImGuiColorEditFlags>(flags));
    color->R = v[0] * 255;
    color->G = v[1] * 255;
    color->B = v[2] * 255;
    return res;
}

bool Tool::ColorEdit4(const char16_t* label, Color* color, ToolColorEdit flags) {
    float v[4];
    v[0] = color->R / 255.0f;
    v[1] = color->G / 255.0f;
    v[2] = color->B / 255.0f;
    v[3] = color->A / 255.0f;
    auto res = ImGui::ColorEdit4(utf16_to_utf8(label).c_str(), v, static_cast<ImGuiColorEditFlags>(flags));
    color->R = v[0] * 255;
    color->G = v[1] * 255;
    color->B = v[2] * 255;
    color->A = v[3] * 255;
    return res;
}

void Tool::OpenPopup(const char16_t* label) { ImGui::OpenPopup(utf16_to_utf8(label).c_str()); }

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

bool Tool::BeginTabItem(const char16_t* label) { return ImGui::BeginTabItem(utf16_to_utf8(label).c_str()); }

void Tool::EndTabItem() { ImGui::EndTabItem(); }

void Tool::Indent() { ImGui::Indent(); }

void Tool::Unindent() { ImGui::Unindent(); }

void Tool::Separator() { ImGui::Separator(); }

void Tool::SetTooltip(const char16_t* text) { ImGui::SetTooltip("%s", utf16_to_utf8(text).c_str()); }

void Tool::BeginTooltip() { ImGui::BeginTooltip(); }

void Tool::EndTooltip() { ImGui::EndTooltip(); }

void Tool::NewLine() { ImGui::NewLine(); }

void Tool::SameLine() { ImGui::SameLine(); }

void Tool::PushTextWrapPos(float wrap_local_pos_x) { ImGui::PushTextWrapPos(wrap_local_pos_x); }

void Tool::PopTextWrapPos() { ImGui::PopTextWrapPos(); }

void Tool::PushItemWidth(float width) { ImGui::PushItemWidth(width); }

void Tool::PopItemWidth() { ImGui::PopItemWidth(); }

void Tool::PushButtonRepeat(bool repeat) { ImGui::PushButtonRepeat(repeat); }

void Tool::PopButtonRepeat() { ImGui::PopButtonRepeat(); }

void Tool::Columns(int32_t count, bool border) { ImGui::Columns(count, static_cast<const char*>(nullptr), border); }

void Tool::NextColumn() { ImGui::NextColumn(); }

void Tool::PushID(int32_t id) { ImGui::PushID(id); }

void Tool::PopID() { ImGui::PopID(); }

bool Tool::SmallButton(const char16_t* label) { return ImGui::SmallButton(utf16_to_utf8(label).c_str()); }

void Tool::Image(std::shared_ptr<Texture2D> texture, Vector2F size, Vector2F uv0, Vector2F uv1, Color tint_col, Color border_col) {
    ImGui::Image(
            platform_->GetTextureIDToRender(texture->GetNativeTexture().get(), Graphics::GetInstance()->GetCommandList()->GetLL()),
            toImVec2(size),
            toImVec2(uv0),
            toImVec2(uv1),
            toImVec4(tint_col),
            toImVec4(border_col));
}

bool Tool::ImageButton(
        std::shared_ptr<Texture2D> texture,
        Vector2F size,
        Vector2F uv0,
        Vector2F uv1,
        int32_t frame_padding,
        Color bg_col,
        Color tint_col) {
    return ImGui::ImageButton(
            platform_->GetTextureIDToRender(texture->GetNativeTexture().get(), Graphics::GetInstance()->GetCommandList()->GetLL()),
            toImVec2(size),
            toImVec2(uv0),
            toImVec2(uv1),
            frame_padding,
            toImVec4(bg_col),
            toImVec4(tint_col));
}

bool Tool::Checkbox(const char16_t* label, bool* v) { return ImGui::Checkbox(utf16_to_utf8(label).c_str(), v); }

bool Tool::CheckboxFlags(const char16_t* label, unsigned int* flags, unsigned int flags_value) {
    return ImGui::CheckboxFlags(utf16_to_utf8(label).c_str(), flags, flags_value);
}

void Tool::ProgressBar(float fraction, Vector2F size_arg, const char16_t* overlay) {
    ImGui::ProgressBar(fraction, toImVec2(size_arg), utf16_to_utf8(overlay).c_str());
}

void Tool::Bullet() { ImGui::Bullet(); }

bool Tool::BeginCombo(const char16_t* label, const char16_t* preview_value, ToolCombo flags) {
    return ImGui::BeginCombo(utf16_to_utf8(label).c_str(), utf16_to_utf8(preview_value).c_str(), (ImGuiComboFlags)flags);
}

void Tool::EndCombo() { ImGui::EndCombo(); }

bool Tool::Combo(const char16_t* label, int32_t* current_item, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items) {
    auto tmp = split(items_separated_by_tabs, u'\t');
    std::vector<std::string> itemsVector;
    for (int32_t i = 0; i < tmp.size(); i++) {
        itemsVector.push_back(utf16_to_utf8(tmp[i]));
    }
    std::vector<char*> items;
    for (int32_t i = 0; i < tmp.size(); i++) {
        items.push_back(itemsVector[i].data());
    }
    return ImGui::Combo(utf16_to_utf8(label).c_str(), current_item, &items[0], itemsVector.size(), popup_max_height_in_items);
}

bool Tool::ColorButton(const char16_t* desc_id, Color* col, ToolColorEdit flags, Vector2F size) {
    auto imVec4 = toImVec4(*col);
    return ImGui::ColorButton(utf16_to_utf8(desc_id).c_str(), imVec4, (ImGuiColorEditFlags)flags, toImVec2(size));
    col->R = imVec4.x;
    col->G = imVec4.y;
    col->B = imVec4.z;
    col->A = imVec4.w;
}

void Tool::SetColorEditOptions(ToolColorEdit flags) { ImGui::SetColorEditOptions((ImGuiColorEditFlags)flags); }

float Tool::GetTreeNodeToLabelSpacing() { return ImGui::GetTreeNodeToLabelSpacing(); }

bool Tool::ListBoxHeader(const char16_t* label, Vector2F size) {
    return ImGui::ListBoxHeader(utf16_to_utf8(label).c_str(), toImVec2(size));
}

void Tool::ListBoxFooter() { ImGui::ListBoxFooter(); }

void Tool::PlotLines(
        const char16_t* label,
        std::shared_ptr<FloatArray> values,
        int32_t values_count,
        int32_t values_offset,
        const char16_t* overlay_text,
        float scale_min,
        float scale_max,
        Vector2F graph_size,
        int32_t stride) {
    ImGui::PlotLines(
            utf16_to_utf8(label).c_str(),
            &values->GetVector()[0],
            values_count,
            values_offset,
            utf16_to_utf8(overlay_text).c_str(),
            scale_min,
            scale_max,
            toImVec2(graph_size),
            stride);
}

void Tool::PlotHistogram(
        const char16_t* label,
        std::shared_ptr<FloatArray> values,
        int32_t values_count,
        int32_t values_offset,
        const char16_t* overlay_text,
        float scale_min,
        float scale_max,
        Vector2F graph_size,
        int32_t stride) {
    ImGui::PlotHistogram(
            utf16_to_utf8(label).c_str(),
            &values->GetVector()[0],
            values_count,
            values_offset,
            utf16_to_utf8(overlay_text).c_str(),
            scale_min,
            scale_max,
            toImVec2(graph_size),
            stride);
}

void Tool::ValueBool(const char16_t* prefix, bool b) { ImGui::Value(utf16_to_utf8(prefix).c_str(), b); }

void Tool::ValueInt(const char16_t* prefix, int32_t v) { ImGui::Value(utf16_to_utf8(prefix).c_str(), v); }

void Tool::ValueFloat(const char16_t* prefix, float v, const char16_t* float_format) {
    ImGui::Value(utf16_to_utf8(prefix).c_str(), v, utf16_to_utf8(float_format).c_str());
}

bool Tool::BeginMainMenuBar() { return ImGui::BeginMainMenuBar(); }

void Tool::EndMainMenuBar() { ImGui::EndMainMenuBar(); }

bool Tool::BeginPopupContextItem(const char16_t* str_id, int32_t mouse_button) {
    return ImGui::BeginPopupContextItem(utf16_to_utf8(str_id).c_str(), mouse_button);
}

bool Tool::BeginPopupContextWindow(const char16_t* str_id, int32_t mouse_button, bool also_over_items) {
    return ImGui::BeginPopupContextWindow(utf16_to_utf8(str_id).c_str(), mouse_button, also_over_items);
}

bool Tool::BeginPopupContextVoid(const char16_t* str_id, int32_t mouse_button) {
    return ImGui::BeginPopupContextVoid(utf16_to_utf8(str_id).c_str(), mouse_button);
}

bool Tool::BeginPopupModalEx(const char16_t* name, bool* p_open, ToolWindow flags) {
    return ImGui::BeginPopupModal(utf16_to_utf8(name).c_str(), p_open, (ImGuiWindowFlags)flags);
}

bool Tool::OpenPopupOnItemClick(const char16_t* str_id, int32_t mouse_button) {
    return ImGui::OpenPopupOnItemClick(utf16_to_utf8(str_id).c_str(), mouse_button);
}

bool Tool::IsPopupOpen(const char16_t* str_id) { return ImGui::IsPopupOpen(utf16_to_utf8(str_id).c_str()); }

void Tool::CloseCurrentPopup() { ImGui::CloseCurrentPopup(); }

int32_t Tool::GetColumnIndex() { return ImGui::GetColumnIndex(); }

float Tool::GetColumnWidth(int32_t column_index) { return ImGui::GetColumnWidth(column_index); }

void Tool::SetColumnWidth(int32_t column_index, float width) { ImGui::SetColumnWidth(column_index, width); }

float Tool::GetColumnOffset(int32_t column_index) { return ImGui::GetColumnOffset(column_index); }

void Tool::SetColumnOffset(int32_t column_index, float offset_x) { return ImGui::SetColumnOffset(column_index, offset_x); }

int32_t Tool::GetColumnsCount() { return ImGui::GetColumnsCount(); }

void Tool::SetTabItemClosed(const char16_t* tab_or_docked_window_label) {
    ImGui::SetTabItemClosed(utf16_to_utf8(tab_or_docked_window_label).c_str());
}

void Tool::PushClipRect(Vector2F clip_rect_min, Vector2F clip_rect_max, bool intersect_with_current_clip_rect) {
    ImGui::PushClipRect(toImVec2(clip_rect_min), toImVec2(clip_rect_max), intersect_with_current_clip_rect);
}

void Tool::PopClipRect() { ImGui::PopClipRect(); }

void Tool::SetItemDefaultFocus() { ImGui::SetItemDefaultFocus(); }

void Tool::SetKeyboardFocusHere(int32_t offset) { ImGui::SetKeyboardFocusHere(offset); }

bool Tool::IsItemHoveredWithFlags(ToolHovered flags) { return ImGui::IsItemHovered((ImGuiHoveredFlags)flags); }

bool Tool::IsItemFocused() { return ImGui::IsItemFocused(); }

bool Tool::IsItemClicked(int32_t mouse_button) { return ImGui::IsItemClicked(mouse_button); }

bool Tool::IsItemVisible() { return ImGui::IsItemVisible(); }

bool Tool::IsItemEdited() { return ImGui::IsItemEdited(); }

bool Tool::IsItemActivated() { return ImGui::IsItemActivated(); }

bool Tool::IsItemDeactivated() { return ImGui::IsItemDeactivated(); }

bool Tool::IsItemDeactivatedAfterEdit() { return ImGui::IsItemDeactivatedAfterEdit(); }

bool Tool::IsAnyItemHovered() { return ImGui::IsAnyItemHovered(); }

bool Tool::IsAnyItemActive() { return ImGui::IsAnyItemActive(); }

bool Tool::IsAnyItemFocused() { return ImGui::IsAnyItemFocused(); }

Vector2F Tool::GetItemRectMin() { return toVector2F(ImGui::GetItemRectMin()); }

Vector2F Tool::GetItemRectMax() { return toVector2F(ImGui::GetItemRectMax()); }

Vector2F Tool::GetItemRectSize() { return toVector2F(ImGui::GetItemRectSize()); }

void Tool::SetItemAllowOverlap() { ImGui::SetItemAllowOverlap(); }

bool Tool::IsRectVisible(Vector2F size) { return ImGui::IsRectVisible(toImVec2(size)); }

bool Tool::IsRectVisibleVector2F2(Vector2F rect_min, Vector2F rect_max) {
    return ImGui::IsRectVisible(toImVec2(rect_min), toImVec2(rect_max));
}

float Tool::GetTime() { return (float)ImGui::GetTime(); }

static std::u16string tempClipboardText;

const char16_t* Tool::GetClipboardText() {
    tempClipboardText = utf8_to_utf16(ImGui::GetClipboardText());
    return tempClipboardText.c_str();
}

void Tool::SetClipboardText(const char16_t* text) { ImGui::SetClipboardText(utf16_to_utf8(text).c_str()); }

void Tool::LoadIniSettingsFromDisk(const char16_t* ini_filename) { ImGui::LoadIniSettingsFromDisk(utf16_to_utf8(ini_filename).c_str()); }

void Tool::SaveIniSettingsToDisk(const char16_t* ini_filename) { ImGui::SaveIniSettingsToDisk(utf16_to_utf8(ini_filename).c_str()); }

bool Tool::IsItemActive() { return ImGui::IsItemActive(); }

bool Tool::IsItemHovered() { return ImGui::IsItemHovered(); }

void Tool::SetScrollHere() { ImGui::SetScrollHere(); }

float Tool::GetTextLineHeight() { return ImGui::GetTextLineHeight(); }

float Tool::GetFontSize() { return ImGui::GetFontSize(); }

Vector2F Tool::GetWindowSize() {
    auto size = ImGui::GetWindowSize();
    return Vector2F(size.x, size.y);
}

void Tool::SetWindowSize(Vector2F size) { ImGui::SetWindowSize(toImVec2(size)); }

bool Tool::IsMousePosValid() { return ImGui::IsMousePosValid(); }

bool Tool::IsMouseDragging() { return ImGui::IsMouseDragging(); }

bool Tool::IsMouseDoubleClicked(int32_t button) { return ImGui::IsMouseDoubleClicked(button); }

Vector2F Tool::GetMouseDragDelta(int32_t button) {
    auto d = ImGui::GetMouseDragDelta(button);
    return Vector2F(d.x, d.y);
}

void Tool::ResetMouseDragDelta(int32_t button) { ImGui::ResetMouseDragDelta(button); }

void Tool::SetNextWindowContentSize(Vector2F size) { ImGui::SetNextWindowContentSize(toImVec2(size)); }

void Tool::SetNextWindowPos(Vector2F pos, ToolCond cond) { ImGui::SetNextWindowPos(toImVec2(pos), (ImGuiCond)cond); }

void Tool::SetNextWindowSize(Vector2F size, ToolCond cond) { ImGui::SetNextWindowSize(toImVec2(size), (ImGuiCond)cond); }

bool Tool::IsWindowAppearing() { return ImGui::IsWindowAppearing(); }

bool Tool::IsWindowCollapsed() { return ImGui::IsWindowCollapsed(); }

bool Tool::IsWindowFocused(ToolFocused flags) { return ImGui::IsWindowFocused(); }

bool Tool::IsWindowHovered(ToolFocused flags) { return ImGui::IsWindowHovered(); }

Vector2F Tool::GetWindowPos() { return toVector2F(ImGui::GetWindowPos()); }

void Tool::SetNextWindowCollapsed(bool collapsed, ToolCond cond) { ImGui::SetNextWindowCollapsed(collapsed, (ImGuiCond)cond); }

void Tool::SetNextWindowFocus() { ImGui::SetNextWindowFocus(); }

void Tool::SetNextWindowBgAlpha(float alpha) { ImGui::SetNextWindowBgAlpha(alpha); }

void Tool::SetWindowPosWithCond(Vector2F pos, ToolCond cond) { ImGui::SetWindowPos(toImVec2(pos), (ImGuiCond)cond); }

void Tool::SetWindowSizeWithCond(Vector2F size, ToolCond cond) { ImGui::SetWindowSize(toImVec2(size), (ImGuiCond)cond); }

void Tool::SetWindowCollapsedWithCond(bool collapsed, ToolCond cond) { ImGui::SetWindowCollapsed(collapsed, (ImGuiCond)cond); }

void Tool::SetWindowFocus() { ImGui::SetWindowFocus(); }

void Tool::SetWindowFontScale(float scale) { ImGui::SetWindowFontScale(scale); }

void Tool::SetWindowPosByName(const char16_t* name, Vector2F pos, ToolCond cond) {
    ImGui::SetWindowPos(utf16_to_utf8(name).c_str(), toImVec2(pos), (ImGuiCond)cond);
}

void Tool::SetWindowSizeByName(const char16_t* name, Vector2F size, ToolCond cond) {
    ImGui::SetWindowSize(utf16_to_utf8(name).c_str(), toImVec2(size), (ImGuiCond)cond);
}

void Tool::SetWindowCollapsedByName(const char16_t* name, bool collapsed, ToolCond cond) {
    ImGui::SetWindowCollapsed(utf16_to_utf8(name).c_str(), collapsed, (ImGuiCond)cond);
}

void Tool::SetWindowFocusByName(const char16_t* name) { ImGui::SetWindowFocus(utf16_to_utf8(name).c_str()); }

Vector2F Tool::GetContentRegionMax() { return toVector2F(ImGui::GetContentRegionMax()); }

Vector2F Tool::GetContentRegionAvail() { return toVector2F(ImGui::GetContentRegionAvail()); }

Vector2F Tool::GetWindowContentRegionMin() { return toVector2F(ImGui::GetWindowContentRegionMin()); }

Vector2F Tool::GetWindowContentRegionMax() { return toVector2F(ImGui::GetWindowContentRegionMax()); }

float Tool::GetWindowContentRegionWidth() { return ImGui::GetWindowContentRegionWidth(); }

float Tool::GetScrollX() { return ImGui::GetScrollX(); }

float Tool::GetScrollY() { return ImGui::GetScrollY(); }

float Tool::GetScrollMaxX() { return ImGui::GetScrollMaxX(); }

float Tool::GetScrollMaxY() { return ImGui::GetScrollMaxY(); }

void Tool::SetScrollX(float scroll_x) { ImGui::SetScrollX(scroll_x); }

void Tool::SetScrollY(float scroll_y) { ImGui::SetScrollY(scroll_y); }

void Tool::SetScrollHereX(float center_x_ratio) { ImGui::SetScrollHereX(center_x_ratio); }

void Tool::SetScrollHereY(float center_y_ratio) { ImGui::SetScrollHereY(center_y_ratio); }

void Tool::SetScrollFromPosX(float local_x, float center_x_ratio) { ImGui::SetScrollFromPosX(local_x, center_x_ratio); }

void Tool::SetScrollFromPosY(float local_y, float center_y_ratio) { ImGui::SetScrollFromPosY(local_y, center_y_ratio); }

void Tool::PushStyleColor(ToolColor idx, Color col) { ImGui::PushStyleColor((ImGuiColorEditFlags)idx, toImVec4(col)); }

void Tool::PopStyleColor(int32_t count) { ImGui::PopStyleColor(count); }

void Tool::PushStyleVarFloat(ToolStyleVar idx, float val) { ImGui::PushStyleVar((ImGuiStyleVar)idx, val); }

void Tool::PushStyleVarVector2F(ToolStyleVar idx, Vector2F val) { ImGui::PushStyleVar((ImGuiStyleVar)idx, toImVec2(val)); }

void Tool::PopStyleVar(int32_t count) { ImGui::PopStyleVar(count); }

Color Tool::GetStyleColor(ToolColor idx) { return toColor(ImGui::GetStyleColorVec4((ImGuiStyleVar)idx)); }

Vector2F Tool::GetFontTexUvWhitePixel() { return toVector2F(ImGui::GetFontTexUvWhitePixel()); }

void Tool::SetNextItemWidth(float item_width) { ImGui::SetNextItemWidth(item_width); }

float Tool::CalcItemWidth() { return ImGui::CalcItemWidth(); }

void Tool::PushAllowKeyboardFocus(bool allow_keyboard_focus) { ImGui::PushAllowKeyboardFocus(allow_keyboard_focus); }

void Tool::PopAllowKeyboardFocus() { ImGui::PopAllowKeyboardFocus(); }

void Tool::Spacing() { ImGui::Spacing(); }

void Tool::BeginGroup() { ImGui::BeginGroup(); }

void Tool::EndGroup() { ImGui::EndGroup(); }

Vector2F Tool::GetCursorPos() { return toVector2F(ImGui::GetCursorPos()); }

void Tool::SetCursorPos(Vector2F local_pos) { ImGui::SetCursorPos(toImVec2(local_pos)); }

Vector2F Tool::GetCursorStartPos() { return toVector2F(ImGui::GetCursorStartPos()); }

Vector2F Tool::GetCursorScreenPos() { return toVector2F(ImGui::GetCursorScreenPos()); }

void Tool::AlignTextToFramePadding() { ImGui::AlignTextToFramePadding(); }

float Tool::GetTextLineHeightWithSpacing() { return ImGui::GetTextLineHeightWithSpacing(); }

float Tool::GetFrameHeight() { return ImGui::GetFrameHeight(); }

float Tool::GetFrameHeightWithSpacing() { return ImGui::GetFrameHeightWithSpacing(); }

//! for Dialog
static std::u16string temp;

const char16_t* Tool::OpenDialog(const char16_t* filter, const char16_t* defaultPath) {
    auto filterList_ = utf16_to_utf8(filter);
    auto defaultPath_ = utf16_to_utf8(defaultPath);

    nfdchar_t* outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(filterList_.c_str(), defaultPath_.c_str(), &outPath);

    if (result == NFD_OKAY) {
        temp = utf8_to_utf16(outPath);
        free(outPath);
        return temp.c_str();
    } else if (result == NFD_CANCEL) {
        temp = u"";
        return temp.c_str();
    }

    temp = u"";
    return temp.c_str();
}

const char16_t* Tool::OpenDialogMultiple(const char16_t* filter, const char16_t* defaultPath) {
    auto filterList_ = utf16_to_utf8(filter);
    auto defaultPath_ = utf16_to_utf8(defaultPath);

    nfdpathset_t pathSet;
    nfdresult_t result = NFD_OpenDialogMultiple(filterList_.c_str(), defaultPath_.c_str(), &pathSet);
    if (result == NFD_OKAY) {
        temp = u"";
        size_t i;
        for (i = 0; i < NFD_PathSet_GetCount(&pathSet); ++i) {
            nfdchar_t* path = NFD_PathSet_GetPath(&pathSet, i);
            if (i != 0) temp += u",";
            temp += utf8_to_utf16(path);
        }
        NFD_PathSet_Free(&pathSet);

        return temp.c_str();
    } else if (result == NFD_CANCEL) {
        temp = u"";
        return temp.c_str();
    } else {
        temp = u"";
        return temp.c_str();
    }

    temp = u"";
    return temp.c_str();
}

const char16_t* Tool::SaveDialog(const char16_t* filter, const char16_t* defaultPath) {
    auto filterList_ = utf16_to_utf8(filter);
    auto defaultPath_ = utf16_to_utf8(defaultPath);

    nfdchar_t* outPath = NULL;
    nfdresult_t result = NFD_SaveDialog(filterList_.c_str(), defaultPath_.c_str(), &outPath);

    if (result == NFD_OKAY) {
        temp = utf8_to_utf16(outPath);
        free(outPath);
        return temp.c_str();
    } else if (result == NFD_CANCEL) {
        temp = u"";
        return temp.c_str();
    }

    temp = u"";
    return temp.c_str();
}

const char16_t* Tool::PickFolder(const char16_t* defaultPath) {
    auto defaultPath_ = utf16_to_utf8(defaultPath);

    nfdchar_t* outPath = NULL;
    nfdresult_t result = NFD_PickFolder(defaultPath_.c_str(), &outPath);

    if (result == NFD_OKAY) {
        temp = utf8_to_utf16(outPath);
        free(outPath);
        return temp.c_str();
    } else if (result == NFD_CANCEL) {
        temp = u"";
        return temp.c_str();
    }

    temp = u"";
    return temp.c_str();
}

}  // namespace Altseed
