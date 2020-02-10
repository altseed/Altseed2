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
    platform_->RenderDrawData(ImGui::GetDrawData(), Graphics::GetInstance()->GetCommandList()->GetLL());
}

bool Tool::Begin(const char16_t* name) { return ImGui::Begin(utf16_to_utf8(name).c_str(), nullptr); }

void Tool::Text(const char16_t* text) { ImGui::Text(utf16_to_utf8(text).c_str()); }

void Tool::End() { ImGui::End(); }

}  // namespace Altseed
