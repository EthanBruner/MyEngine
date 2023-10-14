#pragma once

#include "window.hpp"
#include "vulkan_system.hpp"

namespace engine {

	class App {
	public:

		void run();

	private:
		Window window { 800, 600, "A Window" };
		VulkanSystem vulkan{ window, "shaders\\vert.spv", "shaders\\frag.spv" };

	};


}