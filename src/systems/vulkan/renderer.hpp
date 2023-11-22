#pragma once

#include "window.hpp"
#include "swap_chain.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace engine {

	class Renderer {
	public:
		Renderer(VulkanCoreContext& vulkanContext, Window& vulkanWindow);
		~Renderer();

		// Delete copy constructor and copy assignment opperators
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		VkRenderPass getSwapChainRenderPass() const { return vulkanSwapChain->getRenderPass(); }
		float getAspectRatio() const { return vulkanSwapChain->extentAspectRatio(); }

		bool frameInProgress() const { return frameStarted; }

		VkCommandBuffer getCurrentCommandBuffer() const { 
			assert(frameStarted && "Cannot get current command buffer when frame is not in progress...");
			return commandBuffers[currentFrameIndex]; 
		}

		int getFrameIndex() const {
			assert(frameStarted && "Cannot get frame index if frame not in progess...");
			return currentFrameIndex;
		}

		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

	private:
		Window& window;
		VulkanCoreContext& vulkanContext;

		std::unique_ptr<VulkanSwapChain> vulkanSwapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex;
		int currentFrameIndex = 0;
		bool frameStarted = false;

		void createCommandBuffers();
		void freeCommandBuffers();
		void createSwapChain();
	};
}