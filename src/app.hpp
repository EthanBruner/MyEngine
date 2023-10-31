#pragma once

#include "systems/graphics/vulkan/vulkan_system.hpp"
#include "ecs/entity_component_system.hpp"

namespace engine {

	class App {
	public:
		void run();
	private:
		EntityComponentSystem scene{};
	};
}