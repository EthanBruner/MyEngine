#pragma once

#include "vulkan/window.hpp"
#include "vulkan/vulkan_pipeline.hpp"
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
		Scene scene{};
		Window window { 800, 600, "A Window" };
		VulkanPipeline vulkan{ window, "shaders\\vert.spv", "shaders\\frag.spv" };

	};
}