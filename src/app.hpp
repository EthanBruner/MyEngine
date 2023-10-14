#pragma once

#include "window.hpp"
#include "vulkan_system.hpp"
#include "ecs/scene.hpp"
#include "ecs/component.hpp"
#include "ecs/entity_component_manager.hpp"
#include "ecs/component_container.hpp"
#include "ecs/ecsUtils.hpp"

namespace engine {

	class App {
	public:

		void run();

	private:
		Window window { 800, 600, "A Window" };
		VulkanSystem vulkan{ window, "shaders\\vert.spv", "shaders\\frag.spv" };
		Scene scene{};

	};
}