#pragma once

#include "../../../ecs/system.hpp"
#include "window.hpp"
#include "vulkan_core_context.hpp"
#include "renderer.hpp"
#include "simple_render_system.hpp"

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
		VulkanCoreConstruct vulkanContext { window };
		VulkanRenderer vulkanRenderer{ vulkanContext, window };

	};

}