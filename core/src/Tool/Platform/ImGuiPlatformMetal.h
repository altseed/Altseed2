
#pragma once

#include <unordered_set>
#include "ImGuiPlatform.h"

class ImguiPlatformMetal_Impl;

class ImguiPlatformMetal : public ImguiPlatform {
    ImguiPlatformMetal_Impl* impl = nullptr;
    std::unordered_set<std::shared_ptr<LLGI::Texture>> textures_;

public:
    ImguiPlatformMetal(LLGI::Graphics* g);

    virtual ~ImguiPlatformMetal();

    void NewFrame(LLGI::RenderPass* renderPass) override;

    void RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) override;

    ImTextureID GetTextureIDToRender(LLGI::Texture* texture, LLGI::CommandList* commandList) override;

    void InvalidateDeviceObjects() override;
};
