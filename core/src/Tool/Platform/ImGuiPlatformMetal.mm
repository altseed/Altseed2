#include "ImGuiPlatformMetal.h"

#include <Metal/LLGI.CommandListMetal.h>
#include <Metal/LLGI.GraphicsMetal.h>
#include <Metal/LLGI.Metal_Impl.h>
#include <Metal/LLGI.RenderPassMetal.h>
#include <Metal/LLGI.TextureMetal.h>
#include <imgui.h>
#include <imgui_impl_metal.h>

class ImguiPlatformMetal_Impl {
public:
    LLGI::GraphicsMetal* g_ = nullptr;

    ImguiPlatformMetal_Impl(LLGI::Graphics* g) : g_(static_cast<LLGI::GraphicsMetal*>(g)) { ImGui_ImplMetal_Init(g_->GetDevice()); }

    virtual ~ImguiPlatformMetal_Impl() { ImGui_ImplMetal_Shutdown(); }

    void NewFrame(LLGI::RenderPass* renderPass) {
        auto rp = (LLGI::RenderPassMetal*)renderPass;
        ImGui_ImplMetal_NewFrame(rp->GetRenderPassDescriptor());
    }

    void RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) {
        auto cl = static_cast<LLGI::CommandListMetal*>(commandList);
        ImGui_ImplMetal_RenderDrawData(
                ImGui::GetDrawData(), cl->GetCommandBuffer(), cl->GetRenderCommandEncorder());
    }
};

ImguiPlatformMetal::ImguiPlatformMetal(LLGI::Graphics* g) {
    impl = new ImguiPlatformMetal_Impl(g);
}

ImguiPlatformMetal::~ImguiPlatformMetal() {
    delete impl;
}

void ImguiPlatformMetal::NewFrame(LLGI::RenderPass* renderPass) {
    textures_.clear();
    impl->NewFrame(renderPass);
}

void ImguiPlatformMetal::RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) {
    impl->RenderDrawData(draw_data, commandList);
}

ImTextureID ImguiPlatformMetal::GetTextureIDToRender(LLGI::Texture* texture, LLGI::CommandList* commandList) {
    LLGI::SafeAddRef(texture);
    auto texturePtr = LLGI::CreateSharedPtr(texture);
    textures_.insert(texturePtr);

    auto t = static_cast<LLGI::TextureMetal*>(texture);
    return (__bridge void*)(t->GetTexture());
}

void ImguiPlatformMetal::CreateFont() {
    ImGui_ImplMetal_CreateFontsTexture(impl->g_->GetDevice());
}

void ImguiPlatformMetal::DisposeFont() {
    ImGui_ImplMetal_DestroyFontsTexture();
}
