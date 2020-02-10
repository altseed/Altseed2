
#pragma once

#include "ImGuiPlatform.h"

class ImguiPlatformMetal_Impl;

class ImguiPlatformMetal : public ImguiPlatform
{
	ImguiPlatformMetal_Impl* impl = nullptr;

public:
	ImguiPlatformMetal(LLGI::Graphics* g);

	virtual ~ImguiPlatformMetal();

	void NewFrame(LLGI::RenderPass* renderPass) override;

	void RenderDrawData(ImDrawData* draw_data, LLGI::CommandList* commandList) override;
};
