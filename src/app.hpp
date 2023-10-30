#pragma once

//#include "systems/graphics/vulkan/window.hpp"
//#include "systems/graphics/vulkan/vulkan_system.hpp"

#include "systems/graphics/vulkan_system/vulkan_system.hpp"


#include "ecs/entity_component_system.hpp"
#include "ecs/component.hpp"
#include "ecs/component_container.hpp"
#include "ecs/utils.hpp"

namespace engine {

	class App {
	public:
		void run();

	private:
		EntityComponentSystem scene{};
		//Window window { 800, 600, "A Window" };
		//VulkanSystem vulkan{ window, "shaders\\vert.spv", "shaders\\frag.spv" };

	};
}