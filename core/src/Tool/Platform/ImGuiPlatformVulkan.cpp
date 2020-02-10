#include "ImGuiPlatformVulkan.h"

ImguiPlatformVulkan::ImguiPlatformVulkan(LLGI::Graphics* g, LLGI::Platform* p)
	: g_(static_cast<LLGI::GraphicsVulkan*>(g)), p_(static_cast<LLGI::PlatformVulkan*>(p))
{
	{
		VkDescriptorPoolSize pool_sizes[] = {{VK_DESCRIPTOR_TYPE_SAMPLER, 1000},
											 {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000},
											 {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000},
											 {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000},
											 {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000},
											 {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000},
											 {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000},
											 {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000},
											 {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000},
											 {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000},
											 {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000}};
		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
		pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
		pool_info.pPoolSizes = pool_sizes;
		vkCreateDescriptorPool(g_->GetDevice(), &pool_info, nullptr, &descriptorPool_);
		assert(descriptorPool_ != nullptr);
	}

	LLGI::RenderPassPipelineStateKey psk;
	psk.IsPresent = true;
	psk.HasDepth = false;
	psk.RenderTargetFormats.resize(1);
	psk.RenderTargetFormats.at(0) = LLGI::TextureFormatType::R8G8B8A8_UNORM;

	ps_ = static_cast<LLGI::RenderPassPipelineStateVulkan*>(g_->CreateRenderPassPipelineState(psk));

	ImGui_ImplVulkan_InitInfo info{};
	info.Instance = p_->GetInstance();
	info.PhysicalDevice = p_->GetPhysicalDevice();
	info.Device = g_->GetDevice();
	info.QueueFamily = p_->GetQueueFamilyIndex();
	info.Queue = p_->GetQueue();
	info.PipelineCache = p_->GetPipelineCache();
	info.DescriptorPool = descriptorPool_;
	info.MinImageCount = p_->GetSwapBufferCountMin();
	info.ImageCount = p_->GetSwapBufferCount();
	info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
	info.Allocator = nullptr;

	ImGui_ImplVulkan_Init(&info, ps_->GetRenderPass());

	// update fonts
	auto sfm = g_->CreateSingleFrameMemoryPool(1024 * 128, 128);
	auto cl = static_cast<LLGI::CommandListVulkan*>(g_->CreateCommandList(sfm));

	sfm->NewFrame();
	cl->Begin();
	
	ImGui_ImplVulkan_CreateFontsTexture(cl->GetCommandBuffer());

	cl->End();
	g_->Execute(cl);
	g_->WaitFinish();

	LLGI::SafeRelease(sfm);
	LLGI::SafeRelease(cl);

	ImGui_ImplVulkan_DestroyFontUploadObjects();
	/*
		// Upload Fonts
{
	// Use any command queue
	VkCommandPool command_pool = wd->Frames[wd->FrameIndex].CommandPool;
	VkCommandBuffer command_buffer = wd->Frames[wd->FrameIndex].CommandBuffer;

	err = vkResetCommandPool(g_Device, command_pool, 0);
	check_vk_result(err);
	VkCommandBufferBeginInfo begin_info = {};
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	err = vkBeginCommandBuffer(command_buffer, &begin_info);
	check_vk_result(err);

	ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

	VkSubmitInfo end_info = {};
	end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	end_info.commandBufferCount = 1;
	end_info.pCommandBuffers = &command_buffer;
	err = vkEndCommandBuffer(command_buffer);
	check_vk_result(err);
	err = vkQueueSubmit(g_Queue, 1, &end_info, VK_NULL_HANDLE);
	check_vk_result(err);

	err = vkDeviceWaitIdle(g_Device);
	check_vk_result(err);
	ImGui_ImplVulkan_DestroyFontUploadObjects();
}
	*/
}

ImguiPlatformVulkan::~ImguiPlatformVulkan()
{
	vkDestroyDescriptorPool(g_->GetDevice(), descriptorPool_, nullptr);
	ImGui_ImplVulkan_Shutdown();
	LLGI::SafeRelease(ps_);
}