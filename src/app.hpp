#pragma once

#include "ecs/entity_component_system.hpp"
#include "systems/test_system.hpp"
#include "systems/vulkan/vulkan_system.hpp"

namespace engine {

	class App {
	public:
		void run();
	private:
		EntityComponentSystem scene{};
	};
}