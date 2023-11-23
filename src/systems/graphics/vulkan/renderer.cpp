#include "renderer.hpp"


#include <stdexcept>
#include <array>

using namespace engine;

VulkanRenderer::VulkanRenderer(VulkanCoreConstruct& vulkanContext, Window& vulkanWindow) : window{ vulkanWindow }, vulkanContext{ vulkanContext } {
	createSwapChain();
	createCommandBuffers();
}


VulkanRenderer::~VulkanRenderer() {
	freeCommandBuffers();
}

void VulkanRenderer::createSwapChain() {
	while (window.width() == 0 || window.height() == 0) {
		glfwWaitEvents();
	}
	vkDeviceWaitIdle(vulkanContext.getDevice());

	if (vulkanSwapChain == nullptr) {
		vulkanSwapChain = std::make_unique<VulkanSwapChain>(vulkanContext, window);
	}
	else {
		std::shared_ptr<VulkanSwapChain> oldSwapChain = std::move(vulkanSwapChain);
		vulkanSwapChain = std::make_unique<VulkanSwapChain>(vulkanContext, window, oldSwapChain);

		if (!oldSwapChain->compareSwapFormats(*vulkanSwapChain.get())) {
			throw std::runtime_error("Swap chain image(or depth) format has changed!");
		}
	}
}


void VulkanRenderer::createCommandBuffers() {
	commandBuffers.resize(VulkanSwapChain::MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = vulkanContext.getCommandPool();
	allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

	if (vkAllocateCommandBuffers(vulkanContext.getDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("Failed to allocate command buffers...");
	}
};

void VulkanRenderer::freeCommandBuffers() {
	vkFreeCommandBuffers(vulkanContext.getDevice(), vulkanContext.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
	commandBuffers.clear();
}



VkCommandBuffer VulkanRenderer::beginFrame() {
	assert(!frameStarted && "Cant call beginFrame while already in progress...");

	auto result = vulkanSwapChain->acquireNextImage(&currentImageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		createSwapChain();
		return nullptr;
	}


	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("Failed to acqire swap chain image...");
	}

	frameStarted = true;

	auto commandBuffer = getCurrentCommandBuffer();
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("Failed to begin recording command buffer...");
	}
	return commandBuffer;
};


void VulkanRenderer::endFrame() {
	auto commandBuffer = getCurrentCommandBuffer();
	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("Failed to record command buffer...");
	}

	auto result = vulkanSwapChain->submitCommandBuffers(&commandBuffer, &currentImageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window.wasWindowResized()) {
		window.resetWindowResizedFlag();
		createSwapChain();
	} else if (result != VK_SUCCESS) {
		throw std::runtime_error("Failed to acqire swap chain image...");
	}

	frameStarted = false;
	currentFrameIndex = (currentFrameIndex + 1) % VulkanSwapChain::MAX_FRAMES_IN_FLIGHT;
};


void VulkanRenderer::beginSwapChainRenderPass(VkCommandBuffer commandBuffer) {
	assert(frameStarted && "Cannot call beginSwapChainRenderPass if frame not in progress...");
	assert(commandBuffer = getCurrentCommandBuffer());


	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = vulkanSwapChain->getRenderPass();
	renderPassInfo.framebuffer = vulkanSwapChain->getFrameBuffer(currentImageIndex);

	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = vulkanSwapChain->getSwapChainExtent();

	std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color = { 0.01f, 0.01f, 0.01f, 1.0f };
	clearValues[1].depthStencil = { 1.0f, 0 };
	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);


	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(vulkanSwapChain->getSwapChainExtent().width);
	viewport.height = static_cast<float>(vulkanSwapChain->getSwapChainExtent().height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	VkRect2D scissor{ {0, 0}, vulkanSwapChain->getSwapChainExtent() };
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
};


void VulkanRenderer::endSwapChainRenderPass(VkCommandBuffer commandBuffer) {
	vkCmdEndRenderPass(commandBuffer);
};
