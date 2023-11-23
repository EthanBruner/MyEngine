#pragma once

#include "vulkan_core_context.hpp"
#include "vulkan_pipeline.hpp"
#include "window.hpp"
#include "camera.hpp"

#include <memory>
#include <vector>

namespace engine {

	class SimpleRenderSystem {
	public:
		SimpleRenderSystem(VulkanCoreConstruct& vulkanContext, VkRenderPass renderPass);
		~SimpleRenderSystem();

		// Delete copy constructor and copy assignment opperators
		SimpleRenderSystem(const SimpleRenderSystem&) = delete;
		SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;


		//void renderObjects(VkCommandBuffer commandBuffer, std::vector<Object> &objects, const Camera& camera);
	private:
		void createPipelineLayout();
		void createPipeline(VkRenderPass renderPass);

		VkDevice device;
		std::unique_ptr<VulkanPipeline> vulkanPipeline;
		VkPipelineLayout pipelineLayout;
	};


}