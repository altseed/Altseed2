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
#include "../System/SynchronizationContext.h"
#include "../Window/Window.h"

namespace Altseed2 {
std::shared_ptr<Tool> Tool::instance_;

std::shared_ptr<Tool>& Tool::GetInstance() { return instance_; }

void Tool::Dispose() {
    std::lock_guard<std::mutex> lock(terminatingMtx_);

    if (platform_ != nullptr) {
        platform_.reset();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

bool Tool::Initialize(std::shared_ptr<Graphics> graphics, const char16_t* iniFilename) {
    instance_ = MakeAsdShared<Tool>(graphics, iniFilename);
    return true;
}

void Tool::Terminate() { instance_ = nullptr; }

Tool::Tool(std::shared_ptr<Graphics> graphics, const char16_t* iniFilename) {
    SetIsTerminateingEnabled(true);

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
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    if (iniFilename == nullptr) {
        iniFilename_ = "";
        io.IniFilename = nullptr;
    } else {
        iniFilename_ = utf16_to_utf8(iniFilename);
        io.IniFilename = iniFilename_.c_str();
    }

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

Tool::~Tool() { Dispose(); }

void Tool::OnTerminating() {
    Dispose();
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

    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();

    platform_->RenderDrawData(ImGui::GetDrawData(), Graphics::GetInstance()->GetCommandList()->GetLL());
}

inline ImVec2 toImVec2(const Vector2F& v) { return ImVec2(v.X, v.Y); }

inline ImVec4 toImVec4(const Vector4F& v) { return ImVec4(v.X, v.Y, v.Z, v.W); }

inline ImVec4 toImVec4(const Color& v) { return ImVec4(v.R / 255.0f, v.G / 255.0f, v.B / 255.0f, v.A / 255.0f); }

inline Vector2F toVector2F(const ImVec2& v) { return Vector2F(v.x, v.y); }

inline Color toColor(const ImVec4& v) { return Color(v.x * 255, v.y * 255, v.z * 255, v.w * 255); }

const ImWchar* toImGlyphRanges(ImGuiIO& io, ToolGlyphRange ranges) {
    switch (ranges) {
        case ToolGlyphRange::Cyrillic:
            return io.Fonts->GetGlyphRangesCyrillic();
        case ToolGlyphRange::Japanese:
            return io.Fonts->GetGlyphRangesJapanese();
        case ToolGlyphRange::ChineseFull:
            return io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
        case ToolGlyphRange::Korean:
            return io.Fonts->GetGlyphRangesKorean();
        case ToolGlyphRange::Default:
            return io.Fonts->GetGlyphRangesDefault();
        default:
            Log::GetInstance()->Error(LogCategory::Core, u"Unexpected FontGlyphRange, use 'Default' instead.");
    }

    return nullptr;
}

bool Tool::AddFontFromFileTTF(const char16_t* path, float sizePixels, ToolGlyphRange ranges) {
    RETURN_IF_NULL(path, false);

    auto file = StaticFile::Create(path);

    if (file == nullptr) {
        return false;
    }

    auto this_ = instance_;

    auto path_ = utf16_to_utf8(path);

    SynchronizationContext::GetInstance()->AddEvent([file, this_, sizePixels, ranges, path_]() -> void {
        auto& io = ImGui::GetIO();

        this_->platform_->DisposeFont();

        io.Fonts->Clear();

        auto buffer = IM_ALLOC(file->GetSize());
        memcpy(buffer, file->GetData(), file->GetSize());

        auto font = io.Fonts->AddFontFromMemoryTTF(buffer, file->GetSize(), sizePixels, nullptr, toImGlyphRanges(io, ranges));
        io.Fonts->Build();

        if (font == nullptr) {
            Log::GetInstance()->Error(LogCategory::Core, u"Tool::AddFonrFromFileTTF: Failed to load font from '{0}'", path_.c_str());
        }

        this_->platform_->CreateFont();
    });

    Log::GetInstance()->Error(LogCategory::Core, u"Tool::AddFonrFromFileTTF: Failed to load font from '{0}'", path_.c_str());

    return true;
}

bool Tool::ListBox(const char16_t* label, int32_t* current, const char16_t* items_separated_by_tabs, int32_t height_in_items) {
    RETURN_IF_NULL(label, false);
    RETURN_IF_NULL(current, false);
    RETURN_IF_NULL(items_separated_by_tabs, false);

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

static std::u16string tempInputText;

const char16_t* Tool::InputText(const char16_t* label, const char16_t* input, int32_t max_length, ToolInputTextFlags flags) {
    RETURN_IF_NULL(label, nullptr);
    RETURN_IF_NULL(input, nullptr);

    std::u16string u16str(input);
    auto buf = new char[max_length + 1]{};
    utf16_to_utf8(u16str).copy(buf, utf16_to_utf8(u16str).size());
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
        const char16_t* label, const char16_t* hint, const char16_t* input, int32_t max_length, ToolInputTextFlags flags) {
    RETURN_IF_NULL(label, nullptr);
    RETURN_IF_NULL(hint, nullptr);
    RETURN_IF_NULL(input, nullptr);

    std::u16string u16str(input);
    auto buf = new char[max_length + 1]{};
    utf16_to_utf8(u16str).copy(buf, utf16_to_utf8(u16str).size());
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
        const char16_t* label, const char16_t* input, int32_t max_length, Vector2F size, ToolInputTextFlags flags) {
    RETURN_IF_NULL(label, nullptr);
    RETURN_IF_NULL(input, nullptr);

    std::u16string u16str(input);
    auto buf = new char[max_length + 1]{};
    utf16_to_utf8(u16str).copy(buf, utf16_to_utf8(u16str).size());
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

bool Tool::ColorEdit3(const char16_t* label, Color* color, ToolColorEditFlags flags) {
    RETURN_IF_NULL(label, false);
    RETURN_IF_NULL(color, false);

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

bool Tool::ColorEdit4(const char16_t* label, Color* color, ToolColorEditFlags flags) {
    RETURN_IF_NULL(label, false);
    RETURN_IF_NULL(color, false);

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

void Tool::Image(std::shared_ptr<TextureBase> texture, Vector2F size, Vector2F uv0, Vector2F uv1, Color tint_col, Color border_col) {
    RETURN_IF_NULL(texture, );
    ImGui::Image(
            platform_->GetTextureIDToRender(texture->GetNativeTexture().get(), Graphics::GetInstance()->GetCommandList()->GetLL()),
            toImVec2(size),
            toImVec2(uv0),
            toImVec2(uv1),
            toImVec4(tint_col),
            toImVec4(border_col));
}

bool Tool::ImageButton(
        std::shared_ptr<TextureBase> texture,
        Vector2F size,
        Vector2F uv0,
        Vector2F uv1,
        int32_t frame_padding,
        Color bg_col,
        Color tint_col) {
    RETURN_IF_NULL(texture, false);
    return ImGui::ImageButton(
            platform_->GetTextureIDToRender(texture->GetNativeTexture().get(), Graphics::GetInstance()->GetCommandList()->GetLL()),
            toImVec2(size),
            toImVec2(uv0),
            toImVec2(uv1),
            frame_padding,
            toImVec4(bg_col),
            toImVec4(tint_col));
}

bool Tool::Combo(const char16_t* label, int32_t* current_item, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items) {
    RETURN_IF_NULL(label, false);
    RETURN_IF_NULL(current_item, false);
    RETURN_IF_NULL(items_separated_by_tabs, false);

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

bool Tool::ColorButton(const char16_t* desc_id, Color* col, ToolColorEditFlags flags, Vector2F size) {
    RETURN_IF_NULL(desc_id, false);
    RETURN_IF_NULL(col, false);

    auto imVec4 = toImVec4(*col);
    return ImGui::ColorButton(utf16_to_utf8(desc_id).c_str(), imVec4, (ImGuiColorEditFlags)flags, toImVec2(size));
    col->R = imVec4.x;
    col->G = imVec4.y;
    col->B = imVec4.z;
    col->A = imVec4.w;
}

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
    RETURN_IF_NULL(label, );
    RETURN_IF_NULL(overlay_text, );

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
    RETURN_IF_NULL(label, );
    RETURN_IF_NULL(values, );
    RETURN_IF_NULL(overlay_text, );
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

float Tool::GetTime() { return (float)ImGui::GetTime(); }

void Tool::DockSpace(int32_t id, Vector2F size, ToolDockNodeFlags flags) { ImGui::DockSpace(id, toImVec2(size), (ImGuiDockNodeFlags)flags); }

bool Tool::BeginDockHost(const char16_t* label, Vector2F offset) {
    Vector2F windowSize = Vector2F(graphics_->GetLLGIWindow()->GetWindowSize().X, graphics_->GetLLGIWindow()->GetWindowSize().Y);
    SetNextWindowSize(windowSize);

    auto pos = toVector2F(ImGui::GetMainViewport()->Pos);
    pos.X += offset.X;
    pos.Y += offset.Y;
    SetNextWindowPos(pos);

    ToolWindowFlags flags = (ToolWindowFlags)((int32_t)ToolWindowFlags::NoMove | (int32_t)ToolWindowFlags::NoBringToFrontOnFocus | (int32_t)ToolWindowFlags::NoResize | (int32_t)ToolWindowFlags::NoScrollbar | (int32_t)ToolWindowFlags::NoSavedSettings | (int32_t)ToolWindowFlags::NoTitleBar | (int32_t)ToolWindowFlags::DockNodeHost);
    PushStyleVar(ToolStyleVar::WindowRounding, 0);
    PushStyleVar(ToolStyleVar::WindowPadding, Vector2F());
    const bool visible = Begin(label, nullptr, flags);
    ImGui::PopStyleVar(2);

    DockSpace(GetID(u"dock host"), Vector2F(), ToolDockNodeFlags::None);

    return visible;
}

void Tool::ShowDemoWindowNoCloseButton() { ShowDemoWindow(NULL); }

void Tool::ShowAboutWindowNoCloseButton() { ShowAboutWindow(NULL); }

void Tool::ShowMetricsWindowNoCloseButton() { ShowMetricsWindow(NULL); }

bool Tool::Begin(const char16_t* name, ToolWindowFlags flags) {
    return Begin(name, NULL, flags);
}

bool Tool::BeginPopupModal(const char16_t* name, ToolWindowFlags flags) {
    return BeginPopupModal(name, NULL, flags);
}

bool Tool::BeginTabItem(const char16_t* label, ToolTabItemFlags flags) {
    return BeginTabItem(label, NULL, flags);
}

//! for Dialog
static std::u16string temp;

const char16_t* Tool::OpenDialog(const char16_t* filter, const char16_t* defaultPath) {
    RETURN_IF_NULL(filter, nullptr);
    RETURN_IF_NULL(defaultPath, nullptr);

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
        return nullptr;
    }

    temp = u"";
    return nullptr;
}

const char16_t* Tool::OpenDialogMultiple(const char16_t* filter, const char16_t* defaultPath) {
    RETURN_IF_NULL(filter, nullptr);
    RETURN_IF_NULL(defaultPath, nullptr);

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
        return nullptr;
    } else {
        temp = u"";
        return nullptr;
    }

    temp = u"";
    return nullptr;
}

const char16_t* Tool::SaveDialog(const char16_t* filter, const char16_t* defaultPath) {
    RETURN_IF_NULL(filter, nullptr);
    RETURN_IF_NULL(defaultPath, nullptr);

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
        return nullptr;
    }

    temp = u"";
    return nullptr;
}

const char16_t* Tool::PickFolder(const char16_t* defaultPath) {
    RETURN_IF_NULL(defaultPath, nullptr);

    auto defaultPath_ = utf16_to_utf8(defaultPath);

    nfdchar_t* outPath = NULL;
    nfdresult_t result = NFD_PickFolder(defaultPath_.c_str(), &outPath);

    if (result == NFD_OKAY) {
        temp = utf8_to_utf16(outPath);
        free(outPath);
        return temp.c_str();
    } else if (result == NFD_CANCEL) {
        temp = u"";
        return nullptr;
    }

    temp = u"";
    return nullptr;
}

}  // namespace Altseed2
