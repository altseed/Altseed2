
#pragma once

#include <Vulkan/LLGI.CommandListVulkan.h>
#include <Vulkan/LLGI.GraphicsVulkan.h>
#include <Vulkan/LLGI.PlatformVulkan.h>
#include <Vulkan/LLGI.RenderPassVulkan.h>
#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include "ImGuiPlatform.h"

class ImguiPlatformVulkan : public ImguiPlatform {
    LLGI::GraphicsVulkan* g_ = nullptr;
    LLGI::PlatformVulkan* p_ = nullptr;
    LLGI::RenderPassPipelineStateVulkan* ps_ = nullptr;

    VkDescriptorPool descriptorPool_ = VK_NULL_HANDLE;

public:
    ImguiPlatformVulkan(LLGI::Graphics* g, LLGI::Platform* p);

    virtual ~ImguiPlatformVulkan();

    void NewFrame(LLGI::RenderPass* renderPass) override { ImGui_ImplVulkan_NewFrame(); }

    void RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) override {
        auto cl = static_cast<LLGI::CommandListVulkan*>(commandList);
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cl->GetCommandBuffer());
    }
};
