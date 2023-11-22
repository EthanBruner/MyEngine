#pragma once

#include "vulkan_core_context.hpp"
#include "swap_chain.hpp"

namespace engine {

	class RenderPass {
	public:

		RenderPass(VulkanCoreContext& vulkanContex, VulkanSwapChain& swapChain);

		VkRenderPass& getRenderPass() { return renderPass; }
		VkSampleCountFlagBits getMsaaSampleCount() { return msaaSampleCount; }

	private:
		VulkanCoreContext& vulkanContext;
		VulkanSwapChain& swapChain;

		VkRenderPass renderPass;
		VkSampleCountFlagBits msaaSampleCount = VK_SAMPLE_COUNT_1_BIT;
		
		void createRenderPass();
	};
}