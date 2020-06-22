
#pragma once

#ifdef _WIN32
#define VK_PROTOTYPES
#define VK_USE_PLATFORM_WIN32_KHR
#else
#define VK_PROTOTYPES
#define VK_USE_PLATFORM_XCB_KHR
#endif

#include <Vulkan/LLGI.CommandListVulkan.h>
#include <Vulkan/LLGI.GraphicsVulkan.h>
#include <Vulkan/LLGI.PlatformVulkan.h>
#include <Vulkan/LLGI.RenderPassVulkan.h>
#include <imgui.h>
#include <imgui_impl_vulkan.h>

#include <unordered_map>

#include "ImGuiPlatform.h"

class ImguiPlatformVulkan : public ImguiPlatform {
private:
    struct TextureHolder {
        std::shared_ptr<LLGI::Texture> texture;
        int32_t life;
        ImTextureID id;
    };

    LLGI::GraphicsVulkan* g_ = nullptr;
    LLGI::PlatformVulkan* p_ = nullptr;
    LLGI::RenderPassPipelineStateVulkan* ps_ = nullptr;

    VkDescriptorPool descriptorPool_ = VK_NULL_HANDLE;

    std::unordered_map<LLGI::Texture*, TextureHolder> textures_;

public:
    ImguiPlatformVulkan(LLGI::Graphics* g, LLGI::Platform* p);

    virtual ~ImguiPlatformVulkan();

    void NewFrame(LLGI::RenderPass* renderPass) override;

    void RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) override {
        auto cl = static_cast<LLGI::CommandListVulkan*>(commandList);
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cl->GetCommandBuffer());
    }

    ImTextureID GetTextureIDToRender(LLGI::Texture* texture, LLGI::CommandList* commandList) override;

    void InvalidateDeviceObjects() override { ImGui_ImplVulkan_DestroyFontUploadObjects(); }
};
