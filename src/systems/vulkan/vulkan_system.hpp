#pragma once

#include "../../ecs/system.hpp"
#include "window.hpp"
#include "vulkan_core_context.hpp"
#include "renderer.hpp"
//#include "vulkan_pipeline.hpp"

#include <memory>
#include <vector>

namespace engine {
	
	class VulkanSystem: public MainSystem {
	public:
		VulkanSystem(int windowWidth, int windowHeight, std::string windowName);
		~VulkanSystem();

		// Delete copy constructor and copy assignment opperators
		VulkanSystem(const VulkanSystem&) = delete;
		VulkanSystem& operator=(const VulkanSystem&) = delete;

		virtual void update();
		virtual void loop(std::function<void()> func);
		
	private:
		Window window;
		VulkanCoreContext vulkanContext { window };
		Renderer vulkanRenderer{ vulkanContext, window };

		//void loadObjects();
		//void createPipelines(VkRenderPass renderPass);
		//void renderObjects(VkCommandBuffer commandBuffer, std::vector<Object> objects);
	};

}