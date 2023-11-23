#pragma once

#include "vulkan_core_context.hpp"
#include "swap_chain.hpp"

namespace engine {

	enum RenderPassAttachmentFlag {
		COLOR_ATTACHMENT = 1,
		COLOR_RESOLVE_ATTACHMENT = 2,
		DEPTH_ATTACHMENT = 4,
	};

	class RenderPass {
	public:

		RenderPass(VkDevice device, VulkanSwapChain& swapChain);

		VkRenderPass& getRenderPass() { return renderPass; }
		VkSampleCountFlagBits getMsaaSampleCount() { return msaaSampleCount; }

	private:
		VkDevice device;
		VulkanSwapChain& swapChain;

		VkRenderPass renderPass;
		VkSampleCountFlagBits msaaSampleCount = VK_SAMPLE_COUNT_1_BIT;
		
		void createRenderPass();
	};
}