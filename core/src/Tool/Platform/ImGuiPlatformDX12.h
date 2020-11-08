
#pragma once

#include <DX12/LLGI.CommandListDX12.h>
#include <DX12/LLGI.GraphicsDX12.h>
#include <DX12/LLGI.TextureDX12.h>
#include <imgui.h>
#include <imgui_impl_dx12.h>

#include "ImGuiPlatform.h"

#if !USE_CBG

class ImguiPlatformDX12 : public ImguiPlatform {
    const int32_t DescriptorMax = 512;
    LLGI::GraphicsDX12* g_ = nullptr;
    ID3D12DescriptorHeap* srvDescHeap_ = nullptr;
    int32_t handleOffset_ = 0;
    int32_t handleSize_ = 0;

    std::unordered_map<std::shared_ptr<LLGI::Texture>, ImTextureID> textures_;

public:
    ImguiPlatformDX12(LLGI::Graphics* g) : g_(static_cast<LLGI::GraphicsDX12*>(g)) {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        desc.NumDescriptors = DescriptorMax;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        if (g_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvDescHeap_)) != S_OK)
            throw "Failed to initialize.";

        ImGui_ImplDX12_Init(g_->GetDevice(), g_->GetSwapBufferCount(), DXGI_FORMAT_R8G8B8A8_UNORM, srvDescHeap_, srvDescHeap_->GetCPUDescriptorHandleForHeapStart(), srvDescHeap_->GetGPUDescriptorHandleForHeapStart());

        handleSize_ = static_cast<int>(g_->GetDevice()->GetDescriptorHandleIncrementSize(desc.Type));
        handleOffset_ = 1;
    }

    virtual ~ImguiPlatformDX12() {
        LLGI::SafeRelease(srvDescHeap_);
        ImGui_ImplDX12_Shutdown();
    }

    void NewFrame(LLGI::RenderPass* renderPass) override {
        ImGui_ImplDX12_NewFrame();
        textures_.clear();
        handleOffset_ = 1;
    }

    ImTextureID GetTextureIDToRender(LLGI::Texture* texture, LLGI::CommandList* commandList) override {
        auto t = LLGI::CreateSharedPtr(static_cast<LLGI::TextureDX12*>(texture), true);

        if (textures_.count(t)) {
            return textures_[t];
        }

        auto cpuDescriptorHandle = srvDescHeap_->GetCPUDescriptorHandleForHeapStart();
        auto gpuDescriptorHandle = srvDescHeap_->GetGPUDescriptorHandleForHeapStart();

        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Format = t->GetDXGIFormat();
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Texture2D.MipLevels = 1;
        srvDesc.Texture2D.MostDetailedMip = 0;

        cpuDescriptorHandle.ptr += handleSize_ * handleOffset_;
        gpuDescriptorHandle.ptr += handleSize_ * handleOffset_;

        g_->GetDevice()->CreateShaderResourceView(t->Get(), &srvDesc, cpuDescriptorHandle);

        auto textureID = reinterpret_cast<ImTextureID>(gpuDescriptorHandle.ptr);
        textures_[t] = textureID;

        handleOffset_ += 1;

        return textureID;
    }

    void RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) override {
        auto cl = static_cast<LLGI::CommandListDX12*>(commandList);

        for (auto tex : textures_) {
            auto t = LLGI::CreateSharedPtr(static_cast<LLGI::TextureDX12*>(tex.first.get()), true);

            if (t->GetType() == LLGI::TextureType::Render) {
                t->ResourceBarrior(cl->GetCommandList(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
            }
        }

        cl->GetCommandList()->SetDescriptorHeaps(1, &srvDescHeap_);
        ImGui_ImplDX12_RenderDrawData(draw_data, cl->GetCommandList());
    }

    void CreateFont() override { ImGui_ImplDX12_CreateDeviceObjects(); }

    void DisposeFont() override { ImGui_ImplDX12_InvalidateDeviceObjects(); }
};

#endif