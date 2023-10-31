#pragma once

#include "../../../ecs/system.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace engine {

	class VulkanSystem: public System {
	public:

		VulkanSystem(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
			initWindow();
		};
		~VulkanSystem() {
			glfwDestroyWindow(window);
			glfwTerminate();
		};
		virtual void update(std::shared_ptr<ContainerPool> containerpool) {};
		virtual std::size_t size() { return sizeof(VulkanSystem); };


		template<typename F>
		void loop(const F& func) {
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();
				func();
			}
		}


	private:
		int width;
		int height;
		std::string windowName;
		GLFWwindow* window;
		bool windowResized = false;



		void initWindow();
		static void resizeCallback(GLFWwindow* window, int width, int height);
	};
}