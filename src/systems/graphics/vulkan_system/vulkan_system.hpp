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
		~VulkanSystem() {};

	private:
		int width;
		int height;
		std::string windowName;
		bool framebufferResized = false;
		GLFWwindow* window;

		void initWindow() {
			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Prevents creation of OpenGl context

			window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
			glfwSetWindowUserPointer(window, this);
			glfwSetFramebufferSizeCallback(window, resizeCallback);
		}

		static void resizeCallback(GLFWwindow* window, int width, int height) {
			auto vulkanWindow = reinterpret_cast<VulkanSystem*>(glfwGetWindowUserPointer(window));
			vulkanWindow->framebufferResized = true;
			vulkanWindow->width = width;
			vulkanWindow->height = height;
		}

		void mainLoop(void (*f)()) {
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();

				f();


			}
		}

	};
}