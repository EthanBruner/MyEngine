#pragma once

#include "systems/graphics/vulkan/vulkan_system.hpp"
#include "systems/graphics/resource_manager/resource_manager.hpp"
#include "ecs/entity_component_system.hpp"

namespace engine {

	class App {
	public:
		void run();
	private:
		EntityComponentSystem scene{};
	};
}