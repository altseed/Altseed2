
#pragma once

#include <DX12/LLGI.CommandListDX12.h>
#include <DX12/LLGI.GraphicsDX12.h>
#include <imgui.h>
#include <imgui_impl_dx12.h>
#include "ImGuiPlatform.h"

class ImguiPlatformDX12 : public ImguiPlatform {
    LLGI::GraphicsDX12* g_ = nullptr;
    ID3D12DescriptorHeap* srvDescHeap_ = nullptr;

public:
    ImguiPlatformDX12(LLGI::Graphics* g) : g_(static_cast<LLGI::GraphicsDX12*>(g)) {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        desc.NumDescriptors = 1;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        if (g_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvDescHeap_)) != S_OK) throw "Failed to initialize.";

        ImGui_ImplDX12_Init(
                g_->GetDevice(),
                g_->GetSwapBufferCount(),
                DXGI_FORMAT_R8G8B8A8_UNORM,
                srvDescHeap_->GetCPUDescriptorHandleForHeapStart(),
                srvDescHeap_->GetGPUDescriptorHandleForHeapStart());
    }

    virtual ~ImguiPlatformDX12() {
        LLGI::SafeRelease(srvDescHeap_);
        ImGui_ImplDX12_Shutdown();
    }

    void NewFrame(LLGI::RenderPass* renderPass) override { ImGui_ImplDX12_NewFrame(); }

    void RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) override {
        auto cl = static_cast<LLGI::CommandListDX12*>(commandList);
        cl->GetCommandList()->SetDescriptorHeaps(1, &srvDescHeap_);
        ImGui_ImplDX12_RenderDrawData(draw_data, cl->GetCommandList());
    }
};
