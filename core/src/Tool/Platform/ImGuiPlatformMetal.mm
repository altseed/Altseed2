#include "ImGuiPlatformMetal.h"

#include <Metal/LLGI.CommandListMetal.h>
#include <Metal/LLGI.GraphicsMetal.h>
#include <Metal/LLGI.Metal_Impl.h>
#include <Metal/LLGI.RenderPassMetal.h>
#include <Metal/LLGI.TextureMetal.h>
#include <imgui.h>
#include <imgui_impl_metal.h>

class ImguiPlatformMetal_Impl {
    LLGI::GraphicsMetal* g_ = nullptr;

public:
    ImguiPlatformMetal_Impl(LLGI::Graphics* g) : g_(static_cast<LLGI::GraphicsMetal*>(g)) { ImGui_ImplMetal_Init(g_->GetImpl()->device); }

    virtual ~ImguiPlatformMetal_Impl() { ImGui_ImplMetal_Shutdown(); }

    void NewFrame(LLGI::RenderPass* renderPass) {
        auto rp = (LLGI::RenderPassMetal*)renderPass;
        ImGui_ImplMetal_NewFrame(rp->GetImpl()->renderPassDescriptor);
    }

    void RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) {
        auto cl = static_cast<LLGI::CommandListMetal*>(commandList);
        ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), cl->GetImpl()->commandBuffer, cl->GetImpl()->renderEncoder);
    }
};

ImguiPlatformMetal::ImguiPlatformMetal(LLGI::Graphics* g) { impl = new ImguiPlatformMetal_Impl(g); }

ImguiPlatformMetal::~ImguiPlatformMetal() { delete impl; }

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
    auto impl = t->GetImpl();
    return (__bridge void*)(impl->texture);
}
